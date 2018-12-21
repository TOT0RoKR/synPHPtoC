#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 128

int **queue = NULL;
int size = 4;
int front = 0;
int rare = 0;

int push(int);
int pop();
int at(int);

int main(int argc, char *argv[])
{
	char msg[MSG_SIZE];
    int fd_c2n, fd_n2c;
    int nread;
	int id;
	int i;

	queue = (int**)malloc(sizeof(int*) * size);
	for(i=0;  i<size; i++){
		queue[i] = NULL;
	}

    if(mkfifo("./ctrl2nr",0666) == -1){
        //printf("fail to call mkfifo() c2n\n");
    }

    if((fd_c2n = open("./ctrl2nr", O_RDWR)) < 0){
        printf("fail to call open() c2n\n");
        exit(1);
	}

    while((fd_n2c = open("./nr2ctrl", O_WRONLY)) < 0){
        // printf("fail to call open() n2c\n");
		sleep(1);
        // exit(1);
	}
	printf("start\n");

	while(1){
		if((nread = read(fd_c2n, msg, MSG_SIZE)) < 0 ){
            printf("fail to call read()\n");
            exit(1);
        }
        //printf("recv: %s\n", msg);
		else if(strcmp(msg, "quit")==0) {
			printf("quit\n");
			break;
		}
		else if(strcmp(msg, "push")==0) {
			if((nread = read(fd_c2n, msg, MSG_SIZE)) < 0 ){
				printf("fail to call read()\n");
				exit(1);
			}
			id = atoi(msg);
			printf("push %d\n", id);
			sprintf(msg, "%d", push(id));
			printf("res = %s\n", msg);
			if(write(fd_n2c, msg, MSG_SIZE)==-1){
				printf("fail to call write()\n");
				exit(1);
			}
		}
		else if(strcmp(msg, "pop")==0) {
			id = pop();	
			printf("pop %d\n", id);
			sprintf(msg, "%d", id);
			if(write(fd_n2c, msg, MSG_SIZE)==-1){
				printf("fail to call write()\n");
				exit(1);
			}
		}
		else if(strcmp(msg, "at")==0) {
			if((nread = read(fd_c2n, msg, MSG_SIZE)) < 0 ){
				printf("fail to call read()\n");
				exit(1);
			}
			id = atoi(msg);
			printf("at %d\n", id);
			sprintf(msg, "%d", at(id));
			printf("res = %s\n", msg);
			if(write(fd_n2c, msg, MSG_SIZE)==-1){
				printf("fail to call write()\n");
				exit(1);
			}
		}
		else if(strcmp(msg, "info")==0) {
			printf("size %d/ front %d/ rare  %d\n",  size, front, rare);
		}
		else
			printf("rev = %s\n", msg);
	}
	while(front != rare)
		pop();
	free(queue);
//	unlink("./ctrl2nr");
//	unlink("./nr2ctrl");

	return 0;
}

int push(int id)
{
	int *p;
	int tempsize;
	int ** tempqueue;
	int i;
	/*
	 * 대기 인원이 queue size보다 많아지는 경우.
	 */
	if(rare - front >= size - 1) {
		tempsize = size;
		size <<= 1;
		// queue = (int**)realloc(queue, sizeof(int*) * size);
		tempqueue = (int**)malloc(sizeof(int*) * size);
		for(i=0; i<size; i++)
			tempqueue[i] = queue[i];
		free(queue);
		queue = tempqueue;
		for(i=0; i<rare % tempsize;  i++){
			queue[tempsize+i] = queue[i];
		}
		printf("size %d/ front %d/ rare  %d\n",  size, front, rare);
	}

	p = (int*)malloc(sizeof(int));
	*p = id;

	queue[rare % size] = p;
	rare++;

	return 1;
}

int pop()
{
	int id;
	int i;
	int ** tempqueue;

	if(front == rare) return 0;

	/*
	 * 대기 인원이 queue size의 1/4 보다  적어지는 경우.
	 */
	if(rare - front <= size / 4 && size >4) {
		size >>= 1;
		for(i=0; i<size;  i++){
			if(queue[size+i])
				queue[i] = queue[size+i];
		}
		// queue = (int**)realloc(queue, sizeof(int*) * size);
		tempqueue = (int**)malloc(sizeof(int*) * size);
		for(i=0; i<size; i++)
			tempqueue[i] = queue[i];
		free(queue);
		queue = tempqueue;
		printf("size %d/ front %d/ rare  %d\n",  size, front, rare);
	}

	id = *queue[front % size];
	
	free(queue[front % size]);
	queue[front % size] =  NULL;
	front++;

	return id;
}

int at(int id)
{
	int i=-1;
	for(i=front; i<rare; i++) {
		if(*queue[i % size] == id)
			break;
	}
	return i;
}
