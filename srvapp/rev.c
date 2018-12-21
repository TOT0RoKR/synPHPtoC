#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 128

int **queue = NULL;
int size = 128;
int front = 0;
int rare = 0;

int main(int argc, char *argv[])
{
	char msg[MSG_SIZE];
    int fd_c2n, fd_n2c;
    int nread;
	int id;

	queue = (int**)malloc(sizeof(int*) * size);

    if(mkfifo("./nr2ctrl",0666) == -1){
        //printf("fail to call mkfifo() c2n\n");
    }

    if((fd_n2c = open("./nr2ctrl", O_RDWR)) < 0){
        printf("fail to call open() c2n\n");
        exit(1);
	}
/*
    while((fd_n2c = open("./ctrl2nr", O_WRONLY)) < 0){
        // printf("fail to call open() n2c\n");
		sleep(1);
        // exit(1);
	}
*/
	printf("start\n");
	for(;;){
		if((nread = read(fd_n2c, msg, MSG_SIZE)) < 0 ){
			printf("fail to call read()\n");
			exit(1);
		}
		printf("recv: %s\n", msg);
	}
	unlink("./nr2ctrl");

	return 0;
}
