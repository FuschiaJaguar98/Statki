#ifndef PLANSZA_H
#define PLANSZA_H
#include "QPushButton"
#include "QWidget"
#include "QGridLayout"
class Plansza{
private:
    const int ROZMIAR_PLANSZY = 500;
    const int SZEROKOSC_PLANSZY = 10;
    const int ROZMIAR_PRZYCISKU = ROZMIAR_PLANSZY/SZEROKOSC_PLANSZY;
    QPushButton* przyciski [10][10]; //tworzenie planszy dla jednego gracza
    QWidget* widget;
    QGridLayout* layout;
    void stworzPrzyciski();
public:
    Plansza(QWidget* widget, QGridLayout* layout);  //konstruktor


};

#endif // PLANSZA_H
//w pliku h są includy są metody i klasy, implementacja w pliku cpp
