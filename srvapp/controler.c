#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 128

int main(int argc, char *argv[])
{
	char msg[MSG_SIZE];
    int fd_c2n, fd_n2c;
    int nread;
	int id;

	if(argc < 2){
		printf("arg error");
		exit(1);
	}

    if(mkfifo("./nr2ctrl",0666) == -1){
        //printf("fail to call mkfifo() c2n\n");
    }

    if((fd_n2c = open("./nr2ctrl", O_RDWR)) < 0){
        printf("fail to call open() n2c\n");
        exit(1);
	}

    while((fd_c2n = open("./ctrl2nr", O_WRONLY)) < 0){
        // printf("fail to call open() c2n\n");
		sleep(1);
        // exit(1);
	}

	if(strcmp(argv[1], "push") == 0){
		strcpy(msg, argv[1]);
		if(write(fd_c2n, msg, MSG_SIZE)==-1){
			printf("fail to call write()\n");
			exit(1);
		}
		strcpy(msg, argv[2]);
		if(write(fd_c2n, msg, MSG_SIZE)==-1){
			printf("fail to call write()\n");
			exit(1);
		}
		if((nread = read(fd_n2c, msg, MSG_SIZE)) < 0 ){
			printf("fail to call read()\n");
			exit(1);
		}
		id = atoi(msg);
		if(id)
			printf("success");
		else
			printf("fail");
	}
	else if(strcmp(argv[1], "pop") == 0){
		strcpy(msg, argv[1]);
		if(write(fd_c2n, msg, MSG_SIZE)==-1){
			printf("fail to call write()\n");
			exit(1);
		}
		if((nread = read(fd_n2c, msg, MSG_SIZE)) < 0 ){
			printf("fail to call read()\n");
			exit(1);
		}
		id = atoi(msg);
		printf("%d", id);
	}
	if(strcmp(argv[1], "at") == 0){
		strcpy(msg, argv[1]);
		if(write(fd_c2n, msg, MSG_SIZE)==-1){
			printf("fail to call write()\n");
			exit(1);
		}
		strcpy(msg, argv[2]);
		if(write(fd_c2n, msg, MSG_SIZE)==-1){
			printf("fail to call write()\n");
			exit(1);
		}
		if((nread = read(fd_n2c, msg, MSG_SIZE)) < 0 ){
			printf("fail to call read()\n");
			exit(1);
		}
		id = atoi(msg);
		printf("%d", id);
	}
	// unlink("./ctrl2nr");

	return 0;
}
