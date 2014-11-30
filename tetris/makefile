NDK = /root/tools/android-ndk-r4/ndk-build
TFTP = /tftpboot/
PWD:=$(shell pwd)

default:
	$(MAKE) -C $(PWD)/jni/gpio
	$(MAKE) -C $(PWD)/jni/led
	$(MAKE) -C $(PWD)/jni/7seg
	$(NDK) -C $(PWD)
	cp $(PWD)/jni/gpio/gpio.ko $(TFTP)
	cp $(PWD)/jni/led/ledioport.ko $(TFTP)
	cp $(PWD)/jni/7seg/segment.ko $(TFTP)
	cp $(PWD)/libs/armeabi/libnative.so $(TFTP)
	cp $(PWD)/bin/tetris.apk $(TFTP)
	ls $(TFTP)
