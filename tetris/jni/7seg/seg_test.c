#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd, value = 1;

	if ((fd = open("/dev/segment", O_RDWR | O_SYNC)) < 0){
		printf("FND open fail\n");
		exit(1);
	}

	while (value != 0){
		printf("Input counter value (0: exit program, 10 = 1sec)\n");

		scanf("%d", &value);
		write(fd, &value, 4);
	}

	close(fd);

	return 0;
}
