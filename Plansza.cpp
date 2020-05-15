#include "Plansza.h"
#include <iostream>
Plansza::Plansza(QWidget* widget, QGridLayout* layout): widget (widget), layout(layout){
    stworzPrzyciski();
};

void Plansza::stworzPrzyciski(){        //tworzę przyciski, trzeba robić zmienne const aby przypisywać im określoną wartość
    widget->resize(ROZMIAR_PLANSZY, ROZMIAR_PLANSZY);
    for (int wiersz=0; wiersz < SZEROKOSC_PLANSZY; wiersz++){
     layout->setRowMinimumHeight(wiersz, ROZMIAR_PRZYCISKU);   //ustawienie miejsca dla każdego elementu w grid layout
     layout->setRowStretch(wiersz,0);            //rozszerzenie elementu
     for(int kolumna = 0; kolumna< SZEROKOSC_PLANSZY; kolumna++) {
         layout->setColumnMinimumWidth(kolumna, ROZMIAR_PRZYCISKU);   //ustawienie miejsca dla każdego elementu w grid layout
         layout->setColumnStretch(kolumna,0);
         przyciski[wiersz][kolumna] = new PrzyciskPlanszy(wiersz,kolumna, widget);
         przyciski[wiersz][kolumna] ->show();
         przyciski [wiersz][kolumna]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
         przyciski[wiersz][kolumna] ->resize(ROZMIAR_PRZYCISKU,ROZMIAR_PRZYCISKU);
         layout->addWidget(przyciski[wiersz][kolumna],wiersz,kolumna);
     }
    }
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    widget->setLayout(layout);
}
void Plansza:: dodajStatek(Statek *nowyStatek){
   int wspolrzedna_x  = nowyStatek->getWspolrzedna_x();
   int wspolrzedna_y = nowyStatek->getWspolrzedna_y();

   for(int numerPrzycisku = 0; numerPrzycisku <nowyStatek ->getMaszty(); numerPrzycisku++)  //dodanie statku na plansze
       switch (nowyStatek->getKierunek()) {
       case Kierunek::gora: {
           przyciski[wspolrzedna_x-numerPrzycisku][wspolrzedna_y]->setStyleSheet("background-color: blue");
             przyciski[wspolrzedna_x-numerPrzycisku][wspolrzedna_y]->setStatek(nowyStatek);
             ustawZajeteWokol(wspolrzedna_x-numerPrzycisku,wspolrzedna_y);
       }
       case Kierunek::lewo: {
           przyciski[wspolrzedna_x][wspolrzedna_y - numerPrzycisku]->setStyleSheet("background-color: blue");
       przyciski[wspolrzedna_x][wspolrzedna_y-numerPrzycisku]->setStatek(nowyStatek);
       ustawZajeteWokol(wspolrzedna_x,wspolrzedna_y-numerPrzycisku);
       }

       case Kierunek::dol: {
           przyciski[wspolrzedna_x + numerPrzycisku][wspolrzedna_y]->setStyleSheet("background-color: blue");
           przyciski[wspolrzedna_x+numerPrzycisku][wspolrzedna_y]->setStatek(nowyStatek);
            ustawZajeteWokol(wspolrzedna_x+numerPrzycisku,wspolrzedna_y);
       }

       case Kierunek::prawo: {
           przyciski[wspolrzedna_x][wspolrzedna_y + numerPrzycisku]->setStyleSheet("background-color: blue");
           przyciski[wspolrzedna_x][wspolrzedna_y + numerPrzycisku]->setStatek(nowyStatek);
            ustawZajeteWokol(wspolrzedna_x,wspolrzedna_y+numerPrzycisku);
       }


       }

}
void PrzyciskPlanszy:: setStatek(Statek *nowyStatek){
    statek = nowyStatek;
}
void PrzyciskPlanszy:: setZajety(bool zajety){
    this->zajety = zajety;}
bool PrzyciskPlanszy::getZajety(){
    return zajety;
}
void Plansza:: ustawZajeteWokol(int pozycja_x, int pozycja_y) {
    for(int wiersz = pozycja_x - 1; wiersz<= pozycja_x+1; wiersz++){
        for(int kolumna = pozycja_y - 1; kolumna <= pozycja_y + 1; kolumna++){
            przyciski[wiersz][kolumna]->setZajety(true);
            przyciski[wiersz][kolumna]->setStyleSheet("background-color:red");
    }
    }
}
