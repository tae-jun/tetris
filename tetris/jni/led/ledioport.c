/*
 * 8bit-LED Device Driver
 *  Hanback Electronics Co.,ltd
 * File : ledioport.c
 * Date : April,2009
 */ 

// ����� ������� ����
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/ioport.h>

#define DRIVER_AUTHOR			"hanback"		// ����� ������
#define DRIVER_DESC			"led test program"	// ��⿡ ���� ����

#define LEDIOPORT_MAJOR   		241		// ����̽� �ֹ�ȣ
#define LEDIOPORT_NAME    		"LED IO PORT"	// ����̽� �̸�
#define LEDIOPORT_MODULE_VERSION	"LED IO PORT V0.1"	// ����̽� ����
#define LEDIOPORT_ADDRESS 		0x88000020	// led�� ���� �ּ�
#define LEDIOPORT_ADDRESS_RANGE 	0x1000		// I/O ������ ũ��

//Global variable
static int ledioport_usage = 0;		// ����̹��� ��뿩�θ� Ȯ���ϴ� ��
static unsigned long *ledioport_ioremap; //IO �ּ� ���� ����

// define functions...
// ���� ���α׷����� ����̽��� ó�� ����ϴ� ��츦 ó���ϴ� �Լ�
int ledioport_open(struct inode *minode, struct file *mfile) 
{
	// ����̽��� ���� �ִ��� Ȯ��.
	if(ledioport_usage != 0) return -EBUSY;
	
	// LED�� ���� �ּ� ����
	ledioport_ioremap= ioremap(LEDIOPORT_ADDRESS,LEDIOPORT_ADDRESS_RANGE);

	// ����� �� �ִ� I/O �������� Ȯ��
	if(!check_mem_region((unsigned long)ledioport_ioremap,LEDIOPORT_ADDRESS_RANGE)){
		// I/O �޸� ������ ���
		request_mem_region((unsigned long)ledioport_ioremap,LEDIOPORT_ADDRESS_RANGE,LEDIOPORT_NAME);
	} else printk(KERN_WARNING"Can't get IO Region 0x%x\n", (unsigned int)ledioport_ioremap);
	
	ledioport_usage = 1;
	return 0;
}

// ���� ���α׷����� ����̽��� ���̻� ������� �ʾƼ� �ݱ⸦ �����ϴ� �Լ�
int ledioport_release(struct inode *minode, struct file *mfile) 
{	
	// ���ε� �����ּҸ� ����
	iounmap(ledioport_ioremap);

	// ��ϵ� I/O �޸� ������ ����
	release_mem_region((unsigned long)ledioport_ioremap,LEDIOPORT_ADDRESS_RANGE);
	ledioport_usage = 0;
	return 0;
}

// ����̽� ����̹��� ���⸦ �����ϴ� �Լ�
ssize_t ledioport_write_byte(struct file *inode, const char *gdata, size_t length, loff_t *off_what) 
{
	unsigned short *addr;
	unsigned char  c;

	// gdata�� ����� ������ �޸𸮿��� c�� �о�´�.
	get_user(c,gdata); 
	
	addr = (unsigned short*)ledioport_ioremap;
	*addr = c|0x100;
	
	return length;
}

// ���� ���۷��̼� ����ü
// ������ ���� open()�� ����Ѵ�. open()�� �ý��� ���� ȣ���Ͽ� Ŀ�� ���η� ����.
// �ش� �ý��� �ݰ� ���õ� ���� ������ ����ü ������ open�� �ش��ϴ� �ʵ尡 ����̹� ������
// ledioport_open()���� ���ǵǾ� �����Ƿ� ledioport_open()�� ȣ��ȴ�.
// write�� release�� ���������� �����Ѵ�. ���� ��ϵ��� ���� ���ۿ� ���ؼ��� Ŀ�ο��� ������
// ���� default ������ �ϵ��� �Ǿ� �ִ�.
static struct file_operations led_fops = {
	.owner		= THIS_MODULE, 
	.open		= ledioport_open,
	.write		= ledioport_write_byte,
	.release	= ledioport_release,
};

// ����� Ŀ�� ���η� ����
// ��� ���α׷��� �ٽ����� ������ Ŀ�� ���η� ���� ���񽺸� �����޴� ���̹Ƿ� 
// Ŀ�� ���η� ���� init()�� ���� �����Ѵ�.
// ���� ���α׷��� �ҽ� ���ο��� ���ǵ��� ���� ���� �Լ��� ����Ѵ�. �װ��� �ܺ�
// ���̺귯���� ������ �������� ��ũ�Ǿ� ���Ǳ� �����̴�. ��� ���α׷��� Ŀ��
// �����ϰ� ��ũ�Ǳ� ������ Ŀ�ο��� �����ϰ� ����ϴ� �Լ����� ����� �� �ִ�.
int led_init(void) {
	
	int result;

	// ���� ����̽� ����̹��� ����Ѵ�.
	result = register_chrdev(LEDIOPORT_MAJOR,LEDIOPORT_NAME,&led_fops);
	
	if(result < 0) { // ��Ͻ���
		printk(KERN_WARNING"Can't get any major\n");
		return result;
	}
	
	// major ��ȣ�� ����Ѵ�.
	printk(KERN_INFO"Init Module, ledioport Major Number : %d\n",LEDIOPORT_MAJOR);
	return 0;
}

// ����� Ŀ�ο��� ����
void led_exit(void) 
{
	// ���� ����̽� ����̹��� �����Ѵ�.
	unregister_chrdev(LEDIOPORT_MAJOR,LEDIOPORT_NAME);

	printk(KERN_INFO"driver: %s DRIVER EXIT\n", LEDIOPORT_NAME);
}


module_init(led_init);	// ��� ���� �� ȣ��Ǵ� �Լ�
module_exit(led_exit);	// ��� ���� �� ȣ��Ǵ� �Լ�

MODULE_AUTHOR(DRIVER_AUTHOR);	// ����� ������
MODULE_DESCRIPTION(DRIVER_DESC); // ��⿡ ���� ����
MODULE_LICENSE("Dual BSD/GPL");	 // ����� ���̼��� ���
