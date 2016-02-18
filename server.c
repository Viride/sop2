#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

#define REJ 1       ///gracze zglaszaja sie serwerowi
#define POKOJ 2
/// na 31000 komunikacja poczatkowa


typedef struct stoliki stoliki;
struct stoliki{
    char nazwa;
    int ile_osob;
    int status;
    char gracz1[10];
    char gracz2[10];
    char gracz3[10];
    char gracz4[10];
};

stoliki stolik[10];

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

///-------------------------------------------------------------------------------
///DEKLARACJE
///-------------------------------------------------------------------------------
int msgid;
buf=malloc(sizeof(struct buf_elem));
buf2=malloc(sizeof(struct buf2_elem));
int j=0;
//for(j=0;j<10;j++){
//  *stolik[j]=malloc(sizeof(struct stolik));
//}
//stolik=malloc(sizeof(struct stolik));
int i=1;
int gracze_oczek=0;

///-------------------------------------------------------------------------------
///TWORZENIE KOLEJEK
///-------------------------------------------------------------------------------
msgid = msgget (31000 , IPC_CREAT|0660);
if (msgid ==  -1){
	perror (" Utworzenie  kolejki komunikatów ");
	exit (1);
}
///-------------------------------------------------------------------------------
///DZIALANIE
///-------------------------------------------------------------------------------
///printf("Test1\n");
///msgsnd(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)), 0);

gracze_oczek=0;
stolik[j].nazwa=nazwa_pokoju;
stolik[j].ile_osob=0;
stolik[j].status=0;
//printf("%c\n", stolik[j].nazwa);

while(gracze_oczek<4){

msgrcv(msgid, buf2, (sizeof(struct buf2_elem)-sizeof(long)),REJ, 0);
    printf("\nDolaczyl do stolika %c: \n",stolik[j].nazwa);
    printf("Login: %s\n", buf2->mvalue);
msgrcv(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)),REJ, 0);
    printf("Liczba: %d\n", buf->mvalue);

gracze_oczek=gracze_oczek+1;
stolik[j].ile_osob=stolik[j].ile_osob+1;

if(gracze_oczek==1) strcpy(stolik[j].gracz1, buf2->mvalue);
if(gracze_oczek==2) strcpy(stolik[j].gracz2, buf2->mvalue);
if(gracze_oczek==3) strcpy(stolik[j].gracz3, buf2->mvalue);
if(gracze_oczek==4) {strcpy(stolik[j].gracz4, buf2->mvalue); stolik[j].status=1;}

if(stolik[j].status==1){
    printf("\n\nStolik: %c\n", stolik[j].nazwa);
    printf("Gracz1: %s\n", stolik[j].gracz1);
    printf("Gracz2: %s\n", stolik[j].gracz2);
    printf("Gracz3: %s\n", stolik[j].gracz3);
    printf("Gracz4: %s\n", stolik[j].gracz4);

    if(fork()==0){
        break;
    }
    else {
    printf("Test nazwy: %c\n", stolik[j].nazwa);
    nazwa_pokoju=(char)(nazwa_pokoju+1);
    j=j+1;
    stolik[j].nazwa=nazwa_pokoju;
    stolik[j].status=0;
    stolik[j].ile_osob=0;
    gracze_oczek=0;
    }

}
}
int a=j;

printf("To powinno sie pokazac tylko raz: %d\n", a);
sleep(30);
exit(0);

}


