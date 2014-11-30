#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

static int dev;

jint Java_jni_Gpio_waitClick(JNIEnv* env, jobject thiz) {
	char buff[40];

	dev = open("/dev/gpiobutton", O_RDWR);

	if (dev < 0) {
		//printf("Device Open ERROR\n");
		return -1;
	}

	//printf("Please push the GPIO_0 port\n");

	read(dev, buff, 40);

	//printf("%s\n", buff);
	close(dev);

	return 0;
}

jint Java_jni_Led_control(JNIEnv* env, jobject thiz,
		jint data) {
	int fd, ret;

	fd = open("/dev/ledioport", O_WRONLY);
	if (fd < 0)
		return -errno;
	if (fd > 0) {
		data &= 0xff;
		ret = write(fd, &data, 1);
		close(fd);
	} else
		return fd;

	if (ret == 1)
		return 0;

	return -1;
}

