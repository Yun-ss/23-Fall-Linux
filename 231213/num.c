#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define MAX_SIZE 10

int main(void){
	int fd;
	char buf[MAX_SIZE];
	char num;
	fd = open("/dev/my_virt_dev",O_RDWR);
	if(fd<0){
		printf("Fail: %s\n",strerror(errno));
		return 0;
	}
	printf("정수를 입력하세요(0~9):");
	scanf("%c",&num);
	if(num>9||num<0){
		return 0;
	}
	write(fd, &num,5);
	read(fd, buf,5);
	printf("%s\n",buf);

	close(fd);
	return 0;
}
