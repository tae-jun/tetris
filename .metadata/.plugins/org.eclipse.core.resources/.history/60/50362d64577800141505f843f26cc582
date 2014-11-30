NDK = /root/tools/android-ndk-r4/
TETRIS = /root/share/tetris/
TFTP = /tftpboot/

default:
	$(NDK)ndk-build -C $(TETRIS)
	cp $(TETRIS)libs/armeabi/libnative.so $(TFTP)
	cp $(TETRIS)bin/tetris.apk $(TFTP)
