CC	= arm-linux-gcc

obj-m	:= gpio.o

KDIR	:=/Android/linux-2.6.29.0-hanback

PWD	:=$(shell pwd)

TEST_TARGET = gpio_test
TEST_SRCS = $(TEST_TARGET).c

default:$(TEST_TARGET)
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	$(CC) $(TEST_SRCS) -static -o $(TEST_TARGET)
	rm -f default

clean:
	rm -f *.ko
	rm -f *.o
	rm -f *.mod.*
	rm -f .*.cmd
	rm -f $(TEST_TARGET) 
