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


struct stolik{

    char nazwa;
    int ile_osob;
    int status;
    char gracz1[10];
    char gracz2[10];
    char gracz3[10];
    char gracz4[10];
}*stolik;

struct  buf_elem{
	long mtype;
	int mvalue;
}*buf;

struct  buf2_elem{
	long mtype;
	char mvalue[10];
}*buf2;

char nazwa_pokoju='A';

/// MAIN--------------------------------------------------------------------------------
int main(){

///DEKLARACJE
int msgid;
buf=malloc(sizeof(struct buf_elem));
buf2=malloc(sizeof(struct buf2_elem));
stolik=malloc(sizeof(struct stolik));
int i=1;
int gracze_oczek=0;


///TWORZENIE KOLEJEK
msgid = msgget (31000 , IPC_CREAT|0660);
if (msgid ==  -1){
	perror (" Utworzenie  kolejki komunikatów ");
	exit (1);
}

///DZIALANIE

///printf("Test1\n");
///msgsnd(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)), 0);

gracze_oczek=0;
stolik->nazwa=nazwa_pokoju;
stolik->ile_osob=0;
stolik->status=0;

while(gracze_oczek<4){

printf("Dolaczyl: \n");
msgrcv(msgid, buf2, (sizeof(struct buf2_elem)-sizeof(long)),REJ, 0);
printf("Login: %s\n", buf2->mvalue);
msgrcv(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)),REJ, 0);
printf("Liczba: %d\n", buf->mvalue);
gracze_oczek=gracze_oczek+1;

if(gracze_oczek==1) strcpy(stolik->gracz1, buf2->mvalue);
if(gracze_oczek==2) strcpy(stolik->gracz2, buf2->mvalue);
if(gracze_oczek==3) strcpy(stolik->gracz3, buf2->mvalue);
if(gracze_oczek==4) strcpy(stolik->gracz4, buf2->mvalue);
}
printf("Stolik: %s\n", stolik->nazwa);
printf("Gracz1: %s\n", stolik->gracz1);
printf("Gracz2: %s\n", stolik->gracz2);
printf("Gracz3: %s\n", stolik->gracz3);
printf("Gracz4: %s\n", stolik->gracz4);



}


