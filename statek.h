#ifndef STATEK_H
#define STATEK_H

enum class Kierunek{
    gora,
    lewo,
    dol,
    prawo
};

class Maszt{
public:
    Maszt(int wspolrzedna_x, int wspolrzedna_y);
private:
    bool trafiony;

    int wspolrzedna_x;
    int wspolrzedna_y;

};

class Statek {
public:
    Statek(int wspolrzedna_x, int wspolrzedna_y, Kierunek kierunek, int maszty);
private:
    int maszty;             //zmienne nie powinny być publiczne, dostęp do nich przez metody
    int wspolrzedna_x;
    int wspolrzedna_y;
    Kierunek kierunek;

};

#endif // STATEK_H
