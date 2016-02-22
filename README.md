# sop2
Gra jest stworzona na podstawie Tysiąca. W grze jest 3 graczy, grają 24 kartami liczy się tylko kolor wystawiany, nie ma meldunków. 
Karty są reprezentowane poprzez Ka/Ki/Pi/Tr i figurę, czyli 9/J/D/K/1/A, czyli Ki1 to dziesiątka kier.

Przy licytacji podajemy 0 gdy pasujemy, liczbę większą od podanej, gdy podbijamy stawkę lub tą samą co podana, aby ją potwierdzić (pod warunkiem, że to ten gracz wcześniej ją zadeklarował). Gdy raz się da pass, nie bierze się udziału w licytacji w danym rozdaniu.
Licytujemy ilością lew, które deklarujemy, że zabierzemy.

Podczas wybierania kart należy podać jedną z dostępnych, wybranie wcześniej użytej może spowodować nieoczekiwane konsekwencje.

Gdyby nastąpiła nieoczekiwana sytuacja i program się zawiesił, należy zakończyć procesy wszystkich graczy i najlepiej serwera(ale nie trzeba) i sprawdzić przy użyciu polecenia "ipcs" czy w kolejkach nie pozostały niechciane komunikaty, jeśli tak, to przy pomocy polecenia "ipcrm -q id_kolejki" należy je usunąć i sprawdzić czy kolejki są czyste.

W grze nie ma wyboru pokoju, jesteśmy automatycznie dopisywani do aktualnie otwartego.
Przyłączenie nastąpi dopiero po wybraniu loginu.
