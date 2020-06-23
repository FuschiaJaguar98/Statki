#ifndef STATEK_H
#define STATEK_H

enum class Kierunek{                //enum class każdy element ma przypisany do siebie cyfrę, góra-0, lewo - 1, dol - 2, prawo -3
    gora,
    lewo,
    dol,
    prawo
};



class Statek {
public:
    Statek(int wspolrzedna_x, int wspolrzedna_y, Kierunek kierunek, int maszty =1);
    int getMaszty();        //metoda zwykła zwraca dla każdego obiektu ilość tych masztów jakie przyjmujemy, zwraca coś innego (metoda statyczna)
    int getWspolrzedna_x();
    int getWspolrzedna_y(); //nie mamy metod na modyfikacje statkóW, tworzymy publiczne metody aby dostać się do zmiennych
    Kierunek getKierunek();
    void statekTrafiony();
private:
    int maszty;             //zmienne nie powinny być publiczne, dostęp do nich przez metody
    int wspolrzedna_x;
    int wspolrzedna_y;
    Kierunek kierunek;
    bool zatopiony;

};

#endif // STATEK_H
