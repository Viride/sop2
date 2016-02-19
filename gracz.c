#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

#define REJ 1
#define REJE 2
#define POKOJ 3
#define KARTA 4
#define KARTA_ODP 5
/// na 31000 komunikacja poczatkowa

struct  buf_elem{
	long mtype;
	int mvalue;
}*buf;

struct  buf2_elem{
	long mtype;
	char mvalue[10];
}*buf2;

typedef struct buf_el buf_el;
struct  buf_el{
	long mtype;
	int mvalue;
}*buf_e;
typedef struct buf2_el buf2_el;
struct  buf2_el{
	long mtype;
	char mvalue[4];
}*buf2_e;
//buf_el buf_e;
//buf2_el buf2_e;


/// MAIN--------------------------------------------------------------------------------
int main(){

///DEKLARACJE
char login[10];
int msgid;
int msgid2;
buf=malloc(sizeof(struct buf_elem));
buf2=malloc(sizeof(struct buf2_elem));
buf_e=malloc(sizeof(struct buf_el));
buf2_e=malloc(sizeof(struct buf2_el));
int a;
int y=0;

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

///buf->mtype=REJ2;
///buf->mvalue=5;
///msgsnd(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)), 0);
///msgrcv(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)),1, 0);
///printf("%d\n", buf->mvalue);
msgrcv(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)),REJE, 0);
a=buf->mvalue;

msgid2 = msgget (31000+a+1 , IPC_CREAT|0660);

msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),POKOJ, 0);
printf("%d\n", buf_e->mvalue);

///-------------------------------------------------------------------------------
///PRZYJECIE KART
///-------------------------------------------------------------------------------
char **karty;
    karty=malloc((8+1)*sizeof(*karty));
    for(p=0;p<8+1;++p){ *(karty+p)=malloc(4*sizeof(**karty));}

for(y=0;y<8;y++){
msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),KARTA, 0);
strcpy(karty[y], buf2_e->mvalue);
}
buf_e->mtype=KARTA_ODP;
buf_e->mvalue=1;
msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);


}
