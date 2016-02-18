#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

struct stolik{

    char nazwa[10];
    int ile_osob;
    int status;
};


int main(){

struct  buf_elem{
	long mtype;
	int mvalue;
}*buf;

int msgid;
buf=malloc(sizeof(struct buf_elem));
int i=1;


msgid = msgget (31000 , IPC_CREAT|0660);

if (msgid ==  -1){
	perror (" Utworzenie  kolejki komunikatów ");
	exit (1);
}

buf->mvalue=5;
buf->mtype=1;
printf("Test1\n");
msgsnd(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)), 0);
printf("Test2\n");

while(i==1);


/*
char buf[10];
int i=0;
int j=0;
int k=0;
int pdesk;

switch (fork()){

    case 0:
        pdesk = open ("serwer", O_WRONLY);
        printf("%d\n", pdesk);
        while(i!=1){
        write(pdesk, "witaj", 6);
        j=j+1;
        }
        printf("%d\n", j);
        exit(1);
    default:
        pdesk = open ("serwer", O_RDONLY);
        printf("%d\n", pdesk);
        while(i!=1){
        sleep(2);
        read(pdesk, buf, 10);
        printf("%s\n", buf);
        if(buf[0]=='w') i=1;
        k=k+1;
        }
        printf("%d\n", k);
        exit(1);
    }
*/

}


