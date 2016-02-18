#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>


int main(){

char login[10];


printf("Podaj nazwe gracza (maks 9 znakow)\n");
scanf("%s", login);

struct  buf_elem{
	long mtype;
	int mvalue;
}*buf;

int msgid;
buf=malloc(sizeof(struct buf_elem));



msgid = msgget (31000 , IPC_CREAT|0660);

if (msgid ==  -1){
	perror (" Utworzenie  kolejki komunikatów ");
	exit (1);
}

msgrcv(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)),1, 0);

printf("%d\n", buf->mvalue);

}
