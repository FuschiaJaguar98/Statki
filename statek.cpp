#include <Statek.h>
Statek::Statek( int wspolrzedna_x, int wspolrzedna_y,
               Kierunek kierunek,int maszty): wspolrzedna_x( wspolrzedna_x),wspolrzedna_y(wspolrzedna_y), kierunek(kierunek), zatopiony (false),
    maszty(maszty ){
    //lista inicjalizacyjna, zamiast pisać każda zmienną po koleji przed nawiasem nazwa zmiennej w naszej klasie (składnik naszej klasy)
    //, a w nawiasie sama zmienna podawana jako parametr, zmienne który mają być przypisane wartości mają być na końcu

}

int Statek::getMaszty(){
    return maszty;
}
int Statek::getWspolrzedna_x(){
   return wspolrzedna_x;
}
int Statek::getWspolrzedna_y(){
    return wspolrzedna_y;
}
Kierunek Statek::getKierunek(){
    return kierunek;
}

void Statek::statekTrafiony() {
    maszty--;
    if(maszty ==0) {
        zatopiony = true;
    }
}
