#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

#define REJ 1
#define LOGIN 2
/// na 31000 komunikacja poczatkowa

struct  buf_elem{
	long mtype;
	int mvalue;
}*buf;

struct  buf2_elem{
	long mtype;
	char mvalue[10];
}*buf2;

/// MAIN--------------------------------------------------------------------------------
int main(){

///DEKLARACJE
char login[10];
int msgid;
buf=malloc(sizeof(struct buf_elem));
buf2=malloc(sizeof(struct buf2_elem));
int i=1;

///TWORZENIE KOLEJEK
msgid = msgget (31000 , IPC_CREAT|0660);
if (msgid ==  -1){
	perror (" Utworzenie  kolejki komunikatów ");
	exit (1);
}

///DZIALANIE
printf("Podaj nazwe gracza (maks 9 znakow)\n");
scanf("%s", login);

strcpy(buf2->mvalue,login);
buf2->mtype=REJ;
msgsnd(msgid, buf2, (sizeof(struct buf2_elem)-sizeof(long)), 0);

buf->mtype=REJ;
buf->mvalue=5;
msgsnd(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)), 0);
///msgrcv(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)),1, 0);
///printf("%d\n", buf->mvalue);

}
