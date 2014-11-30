#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/irq.h>

//#include <plat/irqs.h>
#include <linux/gpio.h>
#include <plat/gpio-bank-h1.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-gpio.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define DRIVER_AUTHOR		"hanback"
#define DRIVER_DESC		"GPIO-BUTTON Program"

#define GPIO_MAJOR		249
#define GPIO_NAME		"GPIO-BUTTON"
#define GPIO_MODULE_VERSION	"GPIO-BUTTON-V0.1"
#define IRQ_BUTTON 		IRQ_EINT11


unsigned 	long gpl1;
static irqreturn_t button_interrupt(int irq, void *dev_id);
static DECLARE_WAIT_QUEUE_HEAD(wait_queue);



static irqreturn_t button_interrupt(int irq, void *dev_id)
{
	wake_up_interruptible( &wait_queue );
	return IRQ_HANDLED;
}



int gpio_open( struct inode *minode, struct file *mfile)
{
	int res;

	set_irq_type( IRQ_BUTTON, IRQ_TYPE_EDGE_RISING );

	res = request_irq( IRQ_BUTTON, button_interrupt, IRQF_DISABLED, "GPIO", NULL );

	if( res < 0 )
		printk(KERN_ERR"%s: Request for IRQ %d failed\n", __FUNCTION__, IRQ_BUTTON );

	return 0;
}



int gpio_release( struct inode *minode, struct file *mfile )
{
	free_irq(IRQ_BUTTON, NULL );
	return 0;
}



ssize_t gpio_read( struct file *inode, char *gdata, size_t length, loff_t *off_what )
{
	char hello[] = "GPIO_0 port was pushed by 2012440037 Tae-Jun Kim";

	int ret = 0;
	interruptible_sleep_on( &wait_queue );

	ret = copy_to_user(gdata, &hello, sizeof(hello) );
	if( ret < 0 ) return -1;
}



struct file_operations gpio_fops = {
	.owner 		= THIS_MODULE,
	.open		= gpio_open,
	.read		= gpio_read,
	.release	= gpio_release,
};



int gpio_init( void )
{
	int result;
	result = register_chrdev( GPIO_MAJOR, GPIO_NAME, &gpio_fops );

	if( result < 0 )
	{
		printk(KERN_WARNING"Can't get any major \n");
		return result;
	}

	int err;
	err = gpio_request( S5PC1XX_GPH1(3), "GPH1" );
	printk("S5PC1XX_GPH1(3) : %d \n", S5PC1XX_GPH1(3) );
	printk("S5PC1XX_GPH1(3) : %d \n", S5PC1XX_GPH1(4) );
	printk("err		: %d \n", err );

	if( err )
	{
		printk(KERN_ERR "%s:gpio request error(%d) !!\n", __FUNCTION__, err );
	}
	else
	{
		s3c_gpio_cfgpin(S5PC1XX_GPH1(3), S5PC1XX_GPH1_3_WAKEUP_INT_11);
		s3c_gpio_setpull(S5PC1XX_GPH1(3), S3C_GPIO_PULL_NONE);
	}

	printk("Init Module, GPIO-BUTTON Major Number : %d \n", GPIO_MAJOR);
	return 0;
}



void gpio_exit(void)
{
	unregister_chrdev( GPIO_MAJOR, GPIO_NAME );
	printk("driver: %s DRIVER EXIT\n", GPIO_NAME );
}


module_init( gpio_init );
module_exit( gpio_exit );


MODULE_AUTHOR (DRIVER_AUTHOR);
MODULE_DESCRIPTION( DRIVER_DESC);
MODULE_LICENSE("Dual BSD/GPL" );
