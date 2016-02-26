Grê kompiluje skrypt start.sh .
Server uruchamia siê poprzez " ./server ", a gracza przez "./gracz ".
Plik server.c zawiera obs³ugê servera, a gracz.c obs³ugê gracza.



Gdyby nast¹pi³a nieoczekiwana sytuacja i program siê zawiesi³, nale¿y zakoñczyæ 
procesy wszystkich graczy i najlepiej serwera(ale nie trzeba) i sprawdziæ przy 
u¿yciu polecenia "ipcs" czy w kolejkach nie pozosta³y niechciane komunikaty, 
jeœli tak, to przy pomocy polecenia "ipcrm -q id_kolejki" nale¿y je usun¹æ i 
sprawdziæ czy kolejki s¹ czyste.