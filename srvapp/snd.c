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

/*
    if(mkfifo("./ctrl2nr",0666) == -1){
        //printf("fail to call mkfifo() c2n\n");
    }

    if((fd_c2n = open("./ctrl2nr", O_RDWR)) < 0){
        printf("fail to call open() c2n\n");
        exit(1);
	}
*/
    while((fd_c2n = open("./ctrl2nr", O_WRONLY)) < 0){
        // printf("fail to call open() n2c\n");
		sleep(1);
        // exit(1);
	}

	printf("start\n");

	while(1){
		printf("input: ");
		gets(msg);
		msg[MSG_SIZE-1] = '\0';

		if(write(fd_c2n, msg, MSG_SIZE)==-1){
			printf("fail to call write()\n");
			exit(1);
		}
	}
	unlink("./ctrl2nr");
	unlink("./nr2ctrl");

	return 0;
}
