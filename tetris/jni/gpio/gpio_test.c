#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

static int dev;

int main(void){
	char buff[40];

	dev = open("/dev/gpiobutton", O_RDWR);

	if (dev < 0){
		printf("Device Open ERROR\n");
		return -1;
	}

	printf("Please push the GPIO_0 port\n");

	read(dev, buff, 40);

	printf("%s\n", buff);
	close(dev);
	
	return 0;
}