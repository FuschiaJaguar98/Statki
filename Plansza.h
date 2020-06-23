#ifndef PLANSZA_H
#define PLANSZA_H
#include "QPushButton"
#include "QWidget"
#include "QObject"
#include "QGridLayout"
#include "Statek.h"
#include <iostream>
#include <list>
#include<QApplication>
#include <QLabel>
class Plansza;

class PrzyciskPlanszy:public QPushButton{     //musi być wyżej żeby cpp się nie gubił jak jest niżej i bez nagłówka to się gubi
    Q_OBJECT        //do definicji QSLot
 private:
    int pozycja_x;      //inicjalizacja pola, przypisanie współrzędnych
    int pozycja_y;
    Statek* statek;
    bool zajety;
    bool trafiony;
    Plansza *plansza;

public:
    PrzyciskPlanszy(int pozycja_x, int pozycja_y, Plansza *plansza, QWidget* parent, bool nalezyDoGracza) : QPushButton (parent),
        pozycja_x (pozycja_x),pozycja_y (pozycja_y),plansza(plansza), zajety(false), trafiony(false), statek (nullptr)

    {
        if(!nalezyDoGracza)     {        //jeżeli plansza komputera to wywołujemy metodę connect
        connect(this, SIGNAL(clicked()), this, SLOT(przyciskKlikniety()));            //nasz obiekt, akcja, obiekt na którym wywołujemy metodę w tym przypadku ten sam
        }}
    //wywoływanie metody do kliknięcia, Qslot, żeby coś się działo
    Q_SLOT bool przyciskKlikniety();

    void setStatek(Statek* nowyStatek);
    void setZajety(bool zajety);
    bool getZajety();
    void setTrafiony(bool trafiony);
    bool getTrafiony();
    bool strzal();

};

class Plansza{

private:
    static const int ROZMIAR_PLANSZY = 500;        //każda plansza ma takie pole
    static const int SZEROKOSC_PLANSZY = 10;       //static jako część planszy, nie przypisana do obiektu, jedna zmeinna wspólna dla wszystkich obiektów
    static const int ROZMIAR_PRZYCISKU = ROZMIAR_PLANSZY/SZEROKOSC_PLANSZY;

    PrzyciskPlanszy* przyciski [SZEROKOSC_PLANSZY][SZEROKOSC_PLANSZY]; //tworzenie planszy dla jednego gracza,
    QWidget* widget;
    QGridLayout* layout;                                        //samej w sobie nie da się zmienić planszy czyli layout i rozmair Qwidgetu, musimy ustawić, ze layout jest potomkiem QGridlayout, potomkowie przesuwają się razem z nim, możemy wsadzić do QgridLayout duzo przycisków i wyciagać jeden, wskaźniki do zmiennych na te obiekty w oknie, bezpośredni dostęp do elementów z okna
    Plansza *drugaPlansza;
    std::list<Statek*> statki;                                  //referencja do orginalnych obiektów, dzięki wskaźnikowi wskazujemy na obiekt i nie są tworzone kopie a potem usuwane
    QLabel* komunikatWygranej;
    bool nalezyDoGracza;

    void stworzPrzyciski();
    void ustawZajeteWokol(int pozycja_x,int pozycja_y);

public:
    static bool graWToku;
    static const int LICZBA_CZTEROMASZTOWCOW = 1;                   //ominąć słówko const jak będziemy chcieli nadpisać wartości
    static const int LICZBA_TRZYMASZTOWCOW = 2;
    static const int LICZBA_DWUMASZTOWCOW = 3;
    static const int LICZBA_JEDNOMASZTOWCOW = 4;


    Plansza(QWidget* widget, QGridLayout* layout, Plansza*drugaPlansza, QLabel* komunikatWygranej, bool nalezyDoGracza);  //konstruktor
                                        //zapobiega wyciekowi pamięci
    void dodajStatek(Statek* nowyStatek);
    const bool sprobujWstawicStatek(int wspolrzedna_x, int wspolrzedna_y, Kierunek kierunek, int maszty);
    bool strzalKomputera(int wspolrzedna_x, int wspolrzedna_y);
    void setDrugaPlansza (Plansza *drugaPlansza);
    Plansza * getDrugaPlansza();
    void turaKomputera();
    void dodajStatekDoListy(Statek &statek);                   //przekazujemy parametr jako referencję, możemy coś na nim robić na tej zmiennej, będzie to widoczne na drugiej klasie, bez & będzie widać tylko to co wcześniej zrobilismy
    void usunZatopioneStatki();
    bool brakStatkow();
    void setKomunikat(const QString &komunikat);
};


#endif // PLANSZA_H
//w pliku h są includy są metody i klasy, implementacja w pliku cpp
