#ifndef PLANSZA_H
#define PLANSZA_H
#include "QPushButton"
#include "QWidget"
#include "QGridLayout"
#include "Statek.h"
#include <iostream>


class PrzyciskPlanszy:public QPushButton{     //musi być wyżej żeby cpp się nie gubił jak jest niżej i bez nagłówka to się gubi
    Q_OBJECT        //do definicji QSLot
 private:
    int pozycja_x;      //inicjalizacja pola, przypisanie współrzędnych
    int pozycja_y;
    Statek* statek;
    bool zajety;

public:
    PrzyciskPlanszy(int pozycja_x, int pozycja_y, QWidget* parent) : QPushButton (parent), pozycja_x (pozycja_x),pozycja_y (pozycja_y), zajety(false)    {
        connect(this, SIGNAL(clicked()), this, SLOT(przyciskKlikniety()));            //nasz obiekt, akcja, obiekt na którym wywołujemy metodę w tym przypadku ten sam
    }
    //wywoływanie metody do kliknięcia, Qslot, żeby coś się działo
    Q_SLOT void przyciskKlikniety()
    {
        std::cout << pozycja_x<<","<<pozycja_y<< std::endl;
    }
    void setStatek(Statek* nowyStatek);
    void setZajety(bool zajety);
    bool getZajety();
};

class Plansza{

private:
    static const int ROZMIAR_PLANSZY = 500;        //każda plansza ma takie pole
    static const int SZEROKOSC_PLANSZY = 10;       //static jako część planszy, nie przypisana do obiektu, jedna zmeinna wspólna dla wszystkich obiektów
    static const int ROZMIAR_PRZYCISKU = ROZMIAR_PLANSZY/SZEROKOSC_PLANSZY;

    PrzyciskPlanszy* przyciski [10][10]; //tworzenie planszy dla jednego gracza
    QWidget* widget;
    QGridLayout* layout;

    void stworzPrzyciski();
    void ustawZajeteWokol(int pozycja_x,int pozycja_y);

public:
    static const int LICZBA_CZTEROMASZTOWCOW = 1;
    static const int LICZBA_TRZYMASZTOWCOW = 2;
    static const int LICZBA_DWUMASZTOWCOW = 3;
    static const int LICZBA_JEDNOMASZTOWCOW = 4;

    Plansza(QWidget* widget, QGridLayout* layout);  //konstruktor
                                        //zapobiega wyciekowi pamięci
    void dodajStatek(Statek* nowyStatek);
    bool sprobujWstawicStatek(int wspolrzedna_x, int wspolrzedna_y, Kierunek kierunek, int maszty);

};

#endif // PLANSZA_H
//w pliku h są includy są metody i klasy, implementacja w pliku cpp
