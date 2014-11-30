/*
 * 8bit-LED Device Driver test Program
 *  Hanback Electronics Co.,ltd
 * File : led_test.c
 * Date : April,2009
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// argc : �ܺ��Է� �ܾ� ����, argv: �ܺ��Է� ������
int main(int argc, char **argv)
{
	int dev;
	char buff;
	
	//�ܺ��Է� �ܾ���� 2���� �ƴ϶�� �޼��� ����� ����
	if(argc <= 1) {
		printf("please input the parameter! ex)./test 0xff\n");
		return -1;
	}

	// /dev/ledioport ������ ���� ���� �׼��� ���� ����
	// dev ������ ���� ����ڸ� �����Ѵ�.
	dev = open("/dev/ledioport", O_WRONLY);

	if (dev != -1) {	// ������ ���������� ������ ��
		// �ܺ��Է� �ܾ� ���ڿ��� 16�������� Ȯ���� ���������� ��ȯ
		// strtol() : Ư�� ���� ������ ���ڿ��� ���������� ��ȯ
		// atoi() : 10�� ���� ������ ���ڿ��� ����(int��)���� ��ȯ
		
		// �Էµ� ���ڰ� 16���� �ϰ��
		if(argv[1][0] == '0' && (argv[1][1] == 'x' || argv[1][1] == 'X'))
			buff  = (unsigned short)strtol(&argv[1][2],NULL,16);
		// 10���� �� ���
		else 		
			buff = atoi(argv[1]);

		// ����̹� ���� ledioport_write_byte �� ����
		write(dev,&buff,2);

		// ������ �ݴ´�
		close(dev);
	} 
	else {	// ���� ���⸦ ���� ���� ��
		printf( "Device Open ERROR!\n");
		return -1;
	}

	return 0;
}
