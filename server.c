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
#define GRA 14
#define GRA_ODP 15
#define GRA0 16
#define GRA0_ODP 17
#define GRA1 18
#define GRA1_ODP 19
#define GRA2 20
#define GRA2_ODP 21
#define LICYTACJA_WYNIK 22
#define LICYTACJA_WYNIK_ODP 22
#define LICYTACJA_WYNIK1 23
#define LICYTACJA_WYNIK1_ODP 24
#define GRA_POCZ 25
#define GRA_KON 26
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

int zabral(char karta0[4],char karta1[4],char karta2[4], int tura){
int wygral=tura%3;
char kolor0[3];  kolor0[2]='\0';
///char znak0[2];   znak0[1]='\0';
char kolor1[3];  kolor1[2]='\0';
///char znak1[2];   znak1[1]='\0';
char kolor2[3];  kolor2[2]='\0';
///char znak2[2];   znak2[1]='\0';
int karta_0;
int karta_1;
int karta_2;
kolor0[0]=karta0[0]; kolor0[1]=karta0[1]; ///znak0[0]=karta0[2];
kolor1[0]=karta1[0]; kolor1[1]=karta1[1]; ///znak1[0]=karta1[2];
kolor2[0]=karta2[0]; kolor2[1]=karta2[1]; ///znak2[0]=karta2[2];
if(karta0[2]=='9') {karta_0=1;} else if(karta0[2]=='J') {karta_0=2;} else if(karta0[2]=='D') {karta_0=3;}
                            else if(karta0[2]=='K') {karta_0=4;} else if(karta0[2]=='1') {karta_0=5;}
                            else if(karta0[2]=='A') {karta_0=6;}
if(karta1[2]=='9') {karta_1=1;} else if(karta1[2]=='J') {karta_1=2;} else if(karta1[2]=='D') {karta_1=3;}
                            else if(karta1[2]=='K') {karta_1=4;} else if(karta1[2]=='1') {karta_1=5;}
                            else if(karta1[2]=='A') {karta_1=6;}
if(karta2[2]=='9') {karta_2=1;} else if(karta2[2]=='J') {karta_2=2;} else if(karta2[2]=='D') {karta_2=3;}
                            else if(karta2[2]=='K') {karta_2=4;} else if(karta2[2]=='1') {karta_2=5;}
                            else if(karta2[2]=='A') {karta_2=6;}

if(tura%3==0) {
    wygral=0;
    if(strcmp(kolor0,kolor1)==0 && karta_0<karta_1) {
        wygral=1;
        if(strcmp(kolor1,kolor2)==0 && karta_1<karta_2)   {wygral=2;}
    }
    else if(strcmp(kolor0,kolor2)==0 && karta_0<karta_2)   {wygral=2;}
}

if(tura%3==1) {
    wygral=1;
    if(strcmp(kolor1,kolor2)==0 && karta_1<karta_2) {
        wygral=2;
        if(strcmp(kolor2,kolor0)==0 && karta_2<karta_0)   {wygral=0;}
    }
    else if(strcmp(kolor1,kolor0)==0 && karta_1<karta_0)   {wygral=0;}
}
if(tura%3==2) {
    wygral=2;
    if(strcmp(kolor2,kolor0)==0 && karta_2<karta_0) {
        wygral=0;
        if(strcmp(kolor0,kolor1)==0 && karta_0<karta_1)   {wygral=1;}
    }
    else if(strcmp(kolor2,kolor1)==0 && karta_2<karta_1)   {wygral=1;}
}

return wygral;
}
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
talia[0]="Ka9";  talia[4]="Ka1";  talia[1]="KaJ";  talia[2]="KaD";  talia[3]="KaK";  talia[5]="KaA";
talia[6]="Ki9";  talia[10]="Ki1";  talia[7]="KiJ";  talia[8]="KiD";  talia[9]="KiK"; talia[11]="KiA";
talia[12]="Pi9"; talia[16]="Pi1"; talia[13]="PiJ"; talia[14]="PiD"; talia[15]="PiK"; talia[17]="PiA";
talia[18]="Tr9"; talia[22]="Tr1"; talia[19]="TrJ"; talia[20]="TrD"; talia[21]="TrK"; talia[23]="TrA";

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
    //printf("Test nazwy: %c\n", stolik[j].nazwa);
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
int rozdanie=1;
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
for(y=0;y<3;y++){/*4*/
    buf_e[a].mvalue=y;
    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
    printf("Wyruszyl: %d\n", y);
}
///-------------------------------------------------------------------------------
///PĘTLA DO GRY
///-------------------------------------------------------------------------------
int tura=0;
while(rozdanie<3){

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
    int lic_done=0;
    int max_licyt=1;
    int wygral_licyt=5;

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

    printf("Start\n");
    while(lic_done!=1){

        if(licznik%3==0 && licyt[a].gracz0!=0){
            buf_e[a].mtype=LICYTACJA0;
            buf_e[a].mvalue=max_licyt;
            ///printf("Wysłałem gracz0\n");
            msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
            msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA0_ODP, 0);
            ///printf("Odebrałem gracz0\n");
            licyt[a].gracz0=buf_e[a].mvalue;
            if(licyt[a].gracz0>max_licyt) max_licyt=licyt[a].gracz0;

        }
        licznik++;
        if(licznik%3==1 && licyt[a].gracz1!=0){
            buf_e[a].mtype=LICYTACJA1;
            buf_e[a].mvalue=max_licyt;
            ///printf("Wysłałem gracz1\n");
            msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
            msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA1_ODP, 0);
            ///printf("Odebrałem gracz1\n");
            licyt[a].gracz1=buf_e[a].mvalue;
            if(licyt[a].gracz1>max_licyt) max_licyt=licyt[a].gracz1;

        }
        licznik++;
        if(licznik%3==2 && licyt[a].gracz2!=0){
            buf_e[a].mtype=LICYTACJA2;
            buf_e[a].mvalue=max_licyt;
            ///printf("Wysłałem gracz2\n");
            msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
            msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA2_ODP, 0);
            ///printf("Odebrałem gracz2\n");
            licyt[a].gracz2=buf_e[a].mvalue;
            if(licyt[a].gracz2>max_licyt) max_licyt=licyt[a].gracz2;

        }
        licznik++;
    printf("0\t1\t2\t\n%d\t%d\t%d\t\n", licyt[a].gracz0, licyt[a].gracz1, licyt[a].gracz2);

        if( (licyt[a].gracz0==0 && licyt[a].gracz1==0)||
            (licyt[a].gracz0==0 && licyt[a].gracz2==0)||
            (licyt[a].gracz1==0 && licyt[a].gracz2==0)) {lic_done=1; break;}


    for(y=0;y<3;y++){
        buf_e[a].mtype=LICYTACJA;
        buf_e[a].mvalue=0;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
        }

    } ///koniec while
    for(y=0;y<3;y++){
        buf_e[a].mtype=LICYTACJA;
        buf_e[a].mvalue=1;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
        }



    printf("Koniec licytacji!!\n");


    if(licyt[a].gracz0==max_licyt) wygral_licyt=0;
    if(licyt[a].gracz1==max_licyt) wygral_licyt=1;
    if(licyt[a].gracz2==max_licyt) wygral_licyt=2;
    sleep(1);
    ///printf("%d\n", msgid2[a]);
    for(y=0;y<3;y++){
        buf_e[a].mtype=LICYTACJA_WYNIK;
        buf_e[a].mvalue=wygral_licyt;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
        ///printf("YUP\t");
    }
    ///printf("\nWyslalem, kto wygral licytacje\n");
    for(y=0;y<3;y++){
        msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA_WYNIK_ODP, 0);
        ///printf("YUP_ODP\t");
    }
    ///printf("\nOdebrałem, kto wygral licytacje\n");
    sleep(1);
    for(y=0;y<3;y++){
        buf_e[a].mtype=LICYTACJA_WYNIK1;
        buf_e[a].mvalue=max_licyt;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
        ///printf("YUP\t");
        }
    ///printf("\nWyslalem, jak wygral licytacje\n");
    for(y=0;y<3;y++){
        msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),LICYTACJA_WYNIK1_ODP, 0);
        ///printf("YUP_ODP\t");
    }
    ///printf("\nOdebrałem, jak wygral licytacje\n");
    ///printf("0\t1\t2\t\n%d\t%d\t%d\t\n", licyt[a].gracz0, licyt[a].gracz1, licyt[a].gracz2);

///-------------------------------------------------------------------------------
///GRA
///-------------------------------------------------------------------------------
    printf("Rozpoczynamy grę\n");

    int kolejka=1;
    int karty=1;
    int tura_karty=wygral_licyt;
    int wygrane0=0;
    int wygrane1=0;
    int wygrane2=0;
    char karta0[4];
    char karta1[4];
    char karta2[4];
    int zm_pom=wygral_licyt;

    for(y=0;y<3;y++){
        buf_e[a].mtype=GRA;
        buf_e[a].mvalue=0;
        msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
    }

    while(kolejka<9){
        for(y=0;y<3;y++){
            msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),GRA_POCZ, 0);
        }
        //printf("Odebrałem komunikaty, pocz. while\n");
        printf("Rozdanie zacznie: %d\n", zm_pom);
        karty=1;
        while(karty<4){
            if(tura_karty%3==0){
                    buf_e[a].mtype=GRA0;
                    buf_e[a].mvalue=karty;
                    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
                    printf("Karty: %d\n", karty);
                    if(karty==2){
                        buf2_e[a].mtype=GRA0;
                        strcpy(buf2_e[a].mvalue, karta2);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                    }
                    if(karty==3){
                        buf2_e[a].mtype=GRA0;
                        strcpy(buf2_e[a].mvalue, karta1);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                        buf2_e[a].mtype=GRA0;
                        strcpy(buf2_e[a].mvalue, karta2);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                    }
                    buf_e[a].mtype=GRA0;
                    buf_e[a].mvalue=0;
                    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
                    msgrcv(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)),GRA0_ODP, 0);
                    strcpy(karta0, buf2_e[a].mvalue);
                    //printf("Dostalem karte od %d\n", tura_karty);
            }
            if(tura_karty%3==1){
                    buf_e[a].mtype=GRA1;
                    buf_e[a].mvalue=karty;
                    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
                    printf("Karty: %d\n", karty);
                    if(karty==2){
                        buf2_e[a].mtype=GRA1;
                        strcpy(buf2_e[a].mvalue, karta0);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                    }
                    if(karty==3){
                        buf2_e[a].mtype=GRA1;
                        strcpy(buf2_e[a].mvalue, karta2);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                        buf2_e[a].mtype=GRA1;
                        strcpy(buf2_e[a].mvalue, karta0);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                    }
                    buf_e[a].mtype=GRA1;
                    buf_e[a].mvalue=0;
                    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
                    msgrcv(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)),GRA1_ODP, 0);
                    strcpy(karta1, buf2_e[a].mvalue);
                    //printf("Dostalem karte od %d\n", tura_karty);
            }
            if(tura_karty%3==2){
                    buf_e[a].mtype=GRA2;
                    buf_e[a].mvalue=karty;
                    printf("Karty: %d\n", karty);
                    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
                    if(karty==2){
                        buf2_e[a].mtype=GRA2;
                        strcpy(buf2_e[a].mvalue, karta1);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                    }
                    if(karty==3){
                        buf2_e[a].mtype=GRA2;
                        strcpy(buf2_e[a].mvalue, karta0);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                        buf2_e[a].mtype=GRA2;
                        strcpy(buf2_e[a].mvalue, karta1);
                        msgsnd(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)), 0);
                    }
                    buf_e[a].mtype=GRA2;
                    buf_e[a].mvalue=0;
                    msgsnd(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)), 0);
                    msgrcv(msgid2[a], &buf2_e[a], (sizeof(struct buf2_el)-sizeof(long)),GRA2_ODP, 0);
                    strcpy(karta2, buf2_e[a].mvalue);
                    //printf("Dostalem karte od %d\n", tura_karty);
            }
            tura_karty++;
            karty++;
        }
        //printf("Odebrałem karty\n");
        for(y=0;y<3;y++){
            msgrcv(msgid2[a], &buf_e[a], (sizeof(struct buf_el)-sizeof(long)),GRA_KON, 0);
        }
        //printf("Wysłałem komunikaty, koniec while\n");
        zm_pom=zabral(karta0, karta1, karta2, tura_karty);
        tura_karty=zm_pom;
        printf("Rozdanie wygrał: %d\n", zm_pom);
        if(zm_pom==0) wygrane0++;
        if(zm_pom==1) wygrane1++;
        if(zm_pom==2) wygrane2++;
        kolejka++;
    }
    printf("Wyniki po %d rozdaniu:\n", rozdanie);
    if(wygral_licyt==0 && max_licyt<=wygrane0) {
        stolik[a].gracz0_win=stolik[a].gracz0_win+wygrane0; printf("Rozdanie wygrał: %d\n", wygral_licyt);}
    else if(wygral_licyt==1 && max_licyt<=wygrane1) {
        stolik[a].gracz1_win=stolik[a].gracz1_win+wygrane1; printf("Rozdanie wygrał: %d\n", wygral_licyt);}
    else if(wygral_licyt==2 && max_licyt<=wygrane2) {
        stolik[a].gracz2_win=stolik[a].gracz2_win+wygrane2; printf("Rozdanie wygrał: %d\n", wygral_licyt);}
    else printf("Gracz %d nie ugrał deklarowanej ilości bitek\n", wygral_licyt);
    rozdanie++;
}

/// Miejsce na wysłanie wyników
free(talia);
exit(0);

}


