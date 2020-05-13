#include "Plansza.h"
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
         przyciski[wiersz][kolumna] = new QPushButton();
         przyciski[wiersz][kolumna] ->show();
         przyciski[wiersz][kolumna] ->resize(ROZMIAR_PRZYCISKU,ROZMIAR_PRZYCISKU);
         layout->addWidget(przyciski[wiersz][kolumna],wiersz,kolumna);
     }
    }
    widget->setLayout(layout);
}
