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
#define LICYTACJA 6
#define LICYTACJA_ODP 7
#define LICYTACJA0 8
#define LICYTACJA0_ODP 9
#define LICYTACJA1 10
#define LICYTACJA1_ODP 11
#define LICYTACJA2 12
#define LICYTACJA2_ODP 13
/// na 31000 komunikacja poczatkowa
/// na 31000 + a + 1 komunikacja pokoi

typedef struct stoliki stoliki;
struct stoliki{
    char nazwa;
    int ile_osob;
    int status;
    char gracz0[10];
    char gracz1[10];
    char gracz2[10];
    int gracz0_win;
    int gracz1_win;
    int gracz2_win;
    ///char gracz4[10];
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

typedef struct buf_el buf_el;
struct  buf_el{
	long mtype;
	int mvalue;
};
typedef struct buf2_el buf2_el;
struct  buf2_el{
	long mtype;
	char mvalue[4];
};
buf_el buf_e[10];
buf2_el buf2_e[10];

typedef struct licytacja licytacja;
struct licytacja{
    int gracz0;
    int gracz1;
    int gracz2;
};
licytacja licyt[10];

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
int i=1;
int gracze_oczek=0;

int p=0;
char **talia;
    talia=malloc((24+1)*sizeof(*talia));
    for(p=0;p<24+1;++p){ *(talia+p)=malloc(4*sizeof(**talia));}
talia[0]="Ka9";  talia[1]="Ka1";  talia[2]="KaJ";  talia[3]="KaD";  talia[4]="KaK";  talia[5]="KaA";
talia[6]="Ki9";  talia[7]="Ki1";  talia[8]="KiJ";  talia[9]="KiD";  talia[10]="KiK"; talia[11]="KiA";
talia[12]="Pi9"; talia[13]="Pi1"; talia[14]="PiJ"; talia[15]="PiD"; talia[16]="PiK"; talia[17]="PiA";
talia[18]="Tr9"; talia[19]="Tr1"; talia[20]="TrJ"; talia[21]="TrD"; talia[22]="TrK"; talia[23]="TrA";

///-------------------------------------------------------------------------------
///TWORZENIE KOLEJEK
///-------------------------------------------------------------------------------
msgctl(31000, IPC_RMID, NULL);
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

///while(gracze_oczek<4){
while(gracze_oczek<3){
msgrcv(msgid, buf2, (sizeof(struct buf2_elem)-sizeof(long)),REJ, 0);
    printf("\nDolaczyl do stolika %c: \n",stolik[j].nazwa);
    printf("Nick: %s\n", buf2->mvalue);
///msgrcv(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)),REJ, 0);
///    printf("Liczba: %d\n", buf->mvalue);

gracze_oczek=gracze_oczek+1;
stolik[j].ile_osob=stolik[j].ile_osob+1;

if(gracze_oczek==1) strcpy(stolik[j].gracz0, buf2->mvalue);
if(gracze_oczek==2) strcpy(stolik[j].gracz1, buf2->mvalue);
if(gracze_oczek==3) {strcpy(stolik[j].gracz2, buf2->mvalue); stolik[j].status=1;}
///if(gracze_oczek==4) {strcpy(stolik[j].gracz4, buf2->mvalue); stolik[j].status=1;}

if(stolik[j].status==1){
    printf("\n\nStolik: %c\n", stolik[j].nazwa);
    printf("Gracz0: %s\n", stolik[j].gracz0);
    printf("Gracz1: %s\n", stolik[j].gracz1);
    printf("Gracz2: %s\n", stolik[j].gracz2);
    ///printf("Gracz4: %s\n", stolik[j].gracz4);
    buf->mvalue=j;
    buf->mtype=REJE;
    int x=0;
    for(x=0;x<3;x++){ /*4*/
        msgsnd(msgid, buf, (sizeof(struct buf_elem)-sizeof(long)), 0);
        printf("Wyslalem: %d\n", x);
    }

    if(fork()==0){
        break;
    }
    else {
    printf("Test nazwy: %c\n", stolik[j].nazwa);
    nazwa_pokoju=(char)(nazwa_pokoju+1);
    sleep(3);
    j=j+1;
    stolik[j].nazwa=nazwa_pokoju;
    stolik[j].status=0;
    stolik[j].ile_osob=0;
    gracze_oczek=0;
    }

}
}


int a=j;
int y=0;
///-------------------------------------------------------------------------------
///DEKLARACJE
///-------------------------------------------------------------------------------
int msgid2[10];
printf("Zaczynam gre: %d\n\n", a);
///-------------------------------------------------------------------------------
///TWORZENIE KOLEJEK
///-------------------------------------------------------------------------------
msgctl(31000+a+1, IPC_RMID, NULL);
msgid2[a] = msgget (31000+a+1 , IPC_CREAT|0660);
if (msgid2[a] ==  -1){
	perror (" Utworzenie  kolejki komunikatów ");
	exit (1);
}
///-------------------------------------------------------------------------------
///DZIALANIE
///-------------------------------------------------------------------------------
buf_e[a].mtype=POKOJ;
buf_e[a].mvalue=1;
printf("Test1\n");
for(y=0;y<3;y++){/*4*/
    buf_e[a].mvalue=y;
    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
    printf("Wyruszyl: %d\n", y);
}
///-------------------------------------------------------------------------------
///PĘTLA DO GRY
///-------------------------------------------------------------------------------
int tura;
///while(tura!=3);

///-------------------------------------------------------------------------------
///ROZDANIE KART
///-------------------------------------------------------------------------------

buf2_e[a].mtype=KARTA;
for(y=0;y<24;y++){
    strcpy(buf2_e[a].mvalue, talia[y]);
    msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
}
for(y=0;y<3;y++){ /*4*/
    msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),KARTA_ODP, 0);
}
printf("Koniec wysylania kart: %d\n", a);

///-------------------------------------------------------------------------------
///LICYTACJA
///-------------------------------------------------------------------------------

printf("Rozpoczynam licytacje\n");
int licznik=tura;
for(y=0;y<3;y++){
    buf_e[a].mtype=LICYTACJA;
    buf_e[a].mvalue=y;
    printf("%d\t", y);
    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
    }
printf("\nCzekam na potwierdzenia\n");
msgrcv(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)),LICYTACJA0_ODP, 0);
strcpy(stolik[a].gracz0, buf2_e[a].mvalue);
msgrcv(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)),LICYTACJA1_ODP, 0);
strcpy(stolik[a].gracz1, buf2_e[a].mvalue);
msgrcv(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)),LICYTACJA2_ODP, 0);
strcpy(stolik[a].gracz2, buf2_e[a].mvalue);


licyt[a].gracz0=-1; if(tura%3==0) licyt[a].gracz0=1;
licyt[a].gracz1=-1; if(tura%3==1) licyt[a].gracz1=1;
licyt[a].gracz2=-1; if(tura%3==2) licyt[a].gracz2=1;
int lic_done=0;
int max_licyt=1;
printf("Start\n");
while(lic_done!=1){

    if(licznik%3==0){
        buf_e[a].mtype=LICYTACJA0;
        buf_e[a].mvalue=max_licyt;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
        msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA0_ODP, 0);
        printf("Odebrałem gracz0\n");
        licyt[a].gracz0=buf_e[a].mvalue;
        if(licyt[a].gracz0>max_licyt) max_licyt=licyt[a].gracz0;
        licznik++;
    }

    if(licznik%3==1){
        buf_e[a].mtype=LICYTACJA1;
        buf_e[a].mvalue=max_licyt;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
        msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA1_ODP, 0);
        printf("Odebrałem gracz1\n");
        licyt[a].gracz1=buf_e[a].mvalue;
        if(licyt[a].gracz1>max_licyt) max_licyt=licyt[a].gracz1;
        licznik++;
    }

    if(licznik%3==2){
        buf_e[a].mtype=LICYTACJA2;
        buf_e[a].mvalue=max_licyt;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
        msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA2_ODP, 0);
        printf("Odebrałem gracz2\n");
        licyt[a].gracz1=buf_e[a].mvalue;
        if(licyt[a].gracz2>max_licyt) max_licyt=licyt[a].gracz2;
        licznik++;
    }

    if( (licyt[a].gracz0==0 && licyt[a].gracz1==0)||
        (licyt[a].gracz0==0 && licyt[a].gracz2==0)||
        (licyt[a].gracz1==0 && licyt[a].gracz2==0)) {lic_done=1; break;}

for(y=0;y<3;y++){
    buf_e[a].mtype=LICYTACJA;
    buf_e[a].mvalue=0;
    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
    }

}


for(y=0;y<3;y++){
    buf_e[a].mtype=LICYTACJA;
    buf_e[a].mvalue=1;
    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
    }
printf("0\t1\t2\t\n%d\t%d\t%d\t\n", licyt[a].gracz0, licyt[a].gracz1, licyt[a].gracz2);





free(talia);
exit(0);

}


