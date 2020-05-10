#include <Statek.h>
Statek::Statek( int wspolrzedna_x, int wspolrzedna_y,
               Kierunek kierunek,int maszty): wspolrzedna_x( wspolrzedna_x),wspolrzedna_y(wspolrzedna_y), kierunek(kierunek),
    maszty(maszty = 1){
    //lista inicjalizacyjna, zamiast pisać każda zmienną po koleji przed nawiasem nazwa zmiennej w naszej klasie (składnik naszej klasy)
    //, a w nawiasie sama zmienna podawana jako parametr, zmienne który mają być przypisane wartości mają być na końcu

}
Maszt::Maszt(int wspolrzedna_x, int wspolrzedna_y):wspolrzedna_x(wspolrzedna_x),
wspolrzedna_y(wspolrzedna_y), trafiony(false){}
