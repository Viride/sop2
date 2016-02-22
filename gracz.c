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
/// na 31000 komunikacja
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
///-------------------------------------------------------------------------------
///DEKLARACJE
///-------------------------------------------------------------------------------
char login[10];
int msgid;
int msgid2;
buf=malloc(sizeof(struct buf_elem));
buf2=malloc(sizeof(struct buf2_elem));
buf_e=malloc(sizeof(struct buf_el));
buf2_e=malloc(sizeof(struct buf2_el));
int a;
int y=0;
int rozdanie=1;


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
while(rozdanie<3){

char **karty;
    karty=malloc((8+1)*sizeof(*karty));
    for(y=0;y<8+1;++y){ *(karty+y)=malloc(4*sizeof(**karty));}

    for(y=0;y<8;y++){
        msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),KARTA, 0);
        strcpy(karty[y], buf2_e->mvalue);
        usleep(10);
    }
    buf_e->mtype=KARTA_ODP;
    buf_e->mvalue=1;
    msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);

    for(y=0;y<8;y++){
        printf("%d\t", y);
    }
    printf("\n");
    for(y=0;y<8;y++){
        printf("%s\t", karty[y]);
    }
    printf("\n\n");

///-------------------------------------------------------------------------------
///LICYTACJA
///-------------------------------------------------------------------------------
    int numer=5;
    int licyt_done=0;
    int licyt=-1;

    //printf("Czekam na rozpoczecie licytacji\n");
    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA, 0);
    numer=buf_e->mvalue;
    printf("Moj numer to: %d\n", numer);
    //printf("Wysyłam potwiedzenie\n");
    if(numer==0) {
            strcpy(buf2_e->mvalue,login);
            buf2_e->mtype=LICYTACJA0_ODP;
            msgsnd(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)), 0);
            sleep(1);}
    else {
            if(numer==1){
                strcpy(buf2_e->mvalue,login);
                buf2_e->mtype=LICYTACJA1_ODP;
                msgsnd(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)), 0);
                sleep(1);}

            else {
                if(numer==2){
                    strcpy(buf2_e->mvalue,login);
                    buf2_e->mtype=LICYTACJA2_ODP;
                    msgsnd(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)), 0);
                    sleep(1);}
            }}

    printf("Rozpoczynamy licytacje\n");
    while(licyt_done==0){

    if(numer==0 && licyt!=0) {
            msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA0, 0);
            printf("Podaj ile licytujesz: "); scanf("%d", &licyt);
            buf_e->mtype=LICYTACJA0_ODP;
            buf_e->mvalue=licyt;
            msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);
            ///printf("Wyslalem: %d\n", licyt);
            }
    else {
            if(numer==1 && licyt!=0){
                msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA1, 0);
                printf("Podaj ile licytujesz: "); scanf("%d", &licyt);
                buf_e->mtype=LICYTACJA1_ODP;
                buf_e->mvalue=licyt;
                msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);
                ///printf("Wyslalem: %d\n", licyt);
                }

            else {
                if(numer==2 && licyt!=0){
                    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA2, 0);
                    printf("Podaj ile licytujesz: "); scanf("%d", &licyt);
                    buf_e->mtype=LICYTACJA2_ODP;
                    buf_e->mvalue=licyt;
                    msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);
                    ///printf("Wyslalem: %d\n", licyt);
                    }
            }}
    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA, 0);
    licyt_done=buf_e->mvalue;
    } ///koniec while
    printf("Koniec licytacji\n");
    ///printf("%d\n", msgid2);
    int wygral_licyt=5;
    int wynik_licyt=0;
    ///printf("Czekam na wiadomosc\n");
    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA_WYNIK, 0);
    ///printf("Odebralem wygranego\n");
    wygral_licyt=buf_e->mvalue;
    buf_e->mtype=LICYTACJA_WYNIK_ODP;
    buf_e->mvalue=0;
    msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);
    ///printf("Wysłałem wygranego\n");
    sleep(1);
    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA_WYNIK1, 0);
    wynik_licyt=buf_e->mvalue;
    buf_e->mtype=LICYTACJA_WYNIK1_ODP;
    buf_e->mvalue=0;
    ///printf("Odebralem wygraną stawkę\n");
    msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);

    printf("Licytację wygrał gracz %d licytując: %d\n", wygral_licyt, wynik_licyt);

    ///msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),LICYTACJA, 0);

///-------------------------------------------------------------------------------
///GRA
///-------------------------------------------------------------------------------
    printf("Rozpoczynamy grę\n");
    int kolejka=1;
    int nr_karty;
    int ile_kart;
    char karta0[4];
    char karta1[4];
    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA, 0);

    while(kolejka<9){
        buf_e->mtype=GRA_POCZ;
        buf_e->mvalue=0;
        msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);
        //printf("Wysłałem komunikat, pocz. while\n");
        if(numer==0) {
                msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA0, 0);
                ile_kart=buf_e->mvalue;
                if(ile_kart==2){
                    msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA0, 0);
                    strcpy(karta0, buf2_e->mvalue);
                    printf("Karty na stole:\n %s\n", karta0);
                }
                 if(ile_kart==3){
                    msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA0, 0);
                    strcpy(karta0, buf2_e->mvalue);
                    msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA0, 0);
                    strcpy(karta1, buf2_e->mvalue);
                    printf("Karty na stole:\n %s\t %s\n", karta0, karta1);
                }
                msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA0, 0);
                for(y=0;y<8;y++) printf("%d\t", y);
                printf("\n");
                for(y=0;y<8;y++) printf("%s\t", karty[y]);
                printf("\nWybierz karte: ");
                scanf("%d", &nr_karty);
                printf("\n");
                buf2_e->mtype=GRA0_ODP;
                strcpy(buf2_e->mvalue,karty[nr_karty]);
                msgsnd(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)), 0);
                karty[nr_karty]="   ";
                ///printf("Wyslalem: %d\n", licyt);
                }
        else {
                if(numer==1){
                    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA1, 0);
                        ile_kart=buf_e->mvalue;
                    if(ile_kart==2){
                        msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA1, 0);
                        strcpy(karta0, buf2_e->mvalue);
                        printf("Karty na stole:\n %s\n", karta0);
                    }
                     if(ile_kart==3){
                        msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA1, 0);
                        strcpy(karta0, buf2_e->mvalue);
                        msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA1, 0);
                        strcpy(karta1, buf2_e->mvalue);
                        printf("Karty na stole:\n %s\t %s\n", karta0, karta1);
                        }
                    msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA1, 0);
                    for(y=0;y<8;y++) printf("%d\t", y);
                    printf("\n");
                    for(y=0;y<8;y++) printf("%s\t", karty[y]);
                    printf("\nWybierz karte: ");
                    scanf("%d", &nr_karty);
                    printf("\n");
                    buf2_e->mtype=GRA1_ODP;
                    strcpy(buf2_e->mvalue,karty[nr_karty]);
                    msgsnd(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)), 0);
                    karty[nr_karty]="   ";
                    ///printf("Wyslalem: %d\n", licyt);
                    }

                else {
                    if(numer==2){
                        msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA2, 0);
                        ile_kart=buf_e->mvalue;
                        if(ile_kart==2){
                            msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA2, 0);
                            strcpy(karta0, buf2_e->mvalue);
                            printf("Karty na stole:\n %s\n", karta0);
                        }
                         if(ile_kart==3){
                            msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA2, 0);
                            strcpy(karta0, buf2_e->mvalue);
                            msgrcv(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)),GRA2, 0);
                            strcpy(karta1, buf2_e->mvalue);
                            printf("Karty na stole:\n %s\t %s\n", karta0, karta1);
                        }
                        msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA2, 0);
                        for(y=0;y<8;y++) printf("%d\t", y);
                        printf("\n");
                        for(y=0;y<8;y++) printf("%s\t", karty[y]);
                        printf("\nWybierz karte: ");
                        scanf("%d", &nr_karty);
                        printf("\n");
                        buf2_e->mtype=GRA2_ODP;
                        strcpy(buf2_e->mvalue,karty[nr_karty]);
                        msgsnd(msgid2, buf2_e, (sizeof(struct buf2_el)-sizeof(long)), 0);
                        karty[nr_karty]="   ";
                        ///printf("Wyslalem: %d\n", licyt);
                        }
                }}
        kolejka++;
        buf_e->mtype=GRA_KON;
        buf_e->mvalue=0;
        msgsnd(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)), 0);
        //msgrcv(msgid2, buf_e, (sizeof(struct buf_el)-sizeof(long)),GRA_KON, 0);
        //printf("Odebrałem komunikat, koniec while\n");
    }
    rozdanie++;
    free(karty);
}

printf("\nKoniec!\n");
exit(0);
}
