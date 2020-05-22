#include "Plansza.h"
#include <iostream>
Plansza::Plansza(QWidget* widget, QGridLayout* layout): widget (widget), layout(layout){
    stworzPrzyciski();
};

void Plansza::stworzPrzyciski(){        //tworzę przyciski, trzeba robić zmienne const aby przypisywać im określoną wartość
    widget->resize(Plansza::ROZMIAR_PLANSZY, Plansza::ROZMIAR_PLANSZY);
    for (int wiersz=0; wiersz < Plansza::SZEROKOSC_PLANSZY; wiersz++){
     layout->setRowMinimumHeight(wiersz, ROZMIAR_PRZYCISKU);   //ustawienie miejsca dla każdego elementu w grid layout
     layout->setRowStretch(wiersz,0);            //rozszerzenie elementu
     for(int kolumna = 0; kolumna< Plansza::SZEROKOSC_PLANSZY; kolumna++) {
         layout->setColumnMinimumWidth(kolumna, Plansza::ROZMIAR_PRZYCISKU);   //ustawienie miejsca dla każdego elementu w grid layout
         layout->setColumnStretch(kolumna,0);
         przyciski[wiersz][kolumna] = new PrzyciskPlanszy(wiersz,kolumna, widget);
         przyciski[wiersz][kolumna] ->show();
         przyciski [wiersz][kolumna]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
         przyciski[wiersz][kolumna] ->resize(Plansza::ROZMIAR_PRZYCISKU,Plansza::ROZMIAR_PRZYCISKU);
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
             break;
       }
       case Kierunek::lewo: {
           przyciski[wspolrzedna_x][wspolrzedna_y - numerPrzycisku]->setStyleSheet("background-color: blue");
       przyciski[wspolrzedna_x][wspolrzedna_y-numerPrzycisku]->setStatek(nowyStatek);
       ustawZajeteWokol(wspolrzedna_x,wspolrzedna_y-numerPrzycisku);
       break;
       }

       case Kierunek::dol: {
           przyciski[wspolrzedna_x + numerPrzycisku][wspolrzedna_y]->setStyleSheet("background-color: blue");
           przyciski[wspolrzedna_x+numerPrzycisku][wspolrzedna_y]->setStatek(nowyStatek);
            ustawZajeteWokol(wspolrzedna_x+numerPrzycisku,wspolrzedna_y);
            break;
       }

       case Kierunek::prawo: {
           przyciski[wspolrzedna_x][wspolrzedna_y + numerPrzycisku]->setStyleSheet("background-color: blue");
           przyciski[wspolrzedna_x][wspolrzedna_y + numerPrzycisku]->setStatek(nowyStatek);
            ustawZajeteWokol(wspolrzedna_x,wspolrzedna_y+numerPrzycisku);
            break;
       }


       }

}
bool Plansza::sprobujWstawicStatek(int wspolrzedna_x, int wspolrzedna_y, Kierunek kierunek, int maszty){


    bool moznaWstawicStatek = true;

    for(int pozycja = 0; pozycja< maszty; pozycja++){
        switch(kierunek){
        case Kierunek::gora: {
            if (wspolrzedna_x - pozycja<0){
                moznaWstawicStatek = false;
            } else {
            moznaWstawicStatek = moznaWstawicStatek & !przyciski[wspolrzedna_x - pozycja][wspolrzedna_y]->getZajety();
            }
        break;
        }
        case Kierunek::lewo:{
             if (wspolrzedna_y - pozycja<0){
                 moznaWstawicStatek = false;

             } else {
           moznaWstawicStatek = moznaWstawicStatek &  !przyciski[wspolrzedna_x][wspolrzedna_y - pozycja]->getZajety();
             }
        break;

        }
        case Kierunek::dol:{
            if(wspolrzedna_x + pozycja> Plansza::SZEROKOSC_PLANSZY){
                moznaWstawicStatek = false;
            } else {
            moznaWstawicStatek = moznaWstawicStatek & !przyciski[wspolrzedna_x + pozycja][wspolrzedna_y]->getZajety();}
        break;
        }
        case Kierunek::prawo:{
            if (wspolrzedna_y + pozycja > Plansza::SZEROKOSC_PLANSZY){
                moznaWstawicStatek = false;
            } else {
           moznaWstawicStatek = moznaWstawicStatek & !przyciski[wspolrzedna_x][wspolrzedna_y + pozycja]->getZajety();
            }
        break;
        }
        }
    }
    return moznaWstawicStatek;
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
            if(wiersz >= 0 && wiersz <+Plansza::SZEROKOSC_PLANSZY && kolumna>=0 &&kolumna<=Plansza::SZEROKOSC_PLANSZY){
                przyciski[wiersz][kolumna]->setZajety(true);
            }
        }
    }
}




