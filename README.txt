Gr� kompiluje skrypt start.sh .
Server uruchamia si� poprzez " ./server ", a gracza przez "./gracz ".
Plik server.c zawiera obs�ug� servera, a gracz.c obs�ug� gracza.



Gdyby nast�pi�a nieoczekiwana sytuacja i program si� zawiesi�, nale�y zako�czy� 
procesy wszystkich graczy i najlepiej serwera(ale nie trzeba) i sprawdzi� przy 
u�yciu polecenia "ipcs" czy w kolejkach nie pozosta�y niechciane komunikaty, 
je�li tak, to przy pomocy polecenia "ipcrm -q id_kolejki" nale�y je usun�� i 
sprawdzi� czy kolejki s� czyste.