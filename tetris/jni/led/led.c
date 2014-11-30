/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/mman.h>
#include <errno.h>




jint
Java_com_example_ledseg_MainActivity_LEDControl( JNIEnv* env,
                                                  jobject thiz, jint data )
{
	int fd,ret;

	fd = open("/dev/ledioport",O_WRONLY);
	if(fd < 0) return -errno;
	if(fd > 0) {
		data &= 0xff;
		ret = write(fd,&data,1);
		close(fd);
	} else return fd;

	if(ret == 1) return 0;
	
	return -1;
}


