#include "Plansza.h"
#include <iostream>
Plansza::Plansza(QWidget* widget, QGridLayout* layout,Plansza *drugaPlansza): widget (widget), layout(layout),drugaPlansza (drugaPlansza){
    stworzPrzyciski();
};
void Plansza::setDrugaPlansza(Plansza *drugaPlansza){
    this->drugaPlansza = drugaPlansza;                      //strzałka jeśli mamy zmienne w danej klasie które są wskaźnikami to używamy strzałki, strzałka to rozpakowywanie wskaźnika, każdy obiekt ma swoją
}                                                           //własną zmienną typu this, też adres, używamy naszej zmiennej po równa się jest inna zmienna, this jest to adres i wskazuje na własny obiekt, adres jest kopiowany
Plansza *Plansza:: getDrugaPlansza(){                       //adres obiektu na którym jest obecnie wywoływana metoda, po równa się przesłanianie zmiennej, this użycie zmiennej w srodku klasy, zmienna bez this chodzi nam o zmienną użytą w klasie ale o jej adres
    return drugaPlansza;
}
void Plansza::stworzPrzyciski(){        //tworzę przyciski, trzeba robić zmienne const aby przypisywać im określoną wartość
    widget->resize(Plansza::ROZMIAR_PLANSZY, Plansza::ROZMIAR_PLANSZY);
    for (int wiersz=0; wiersz < Plansza::SZEROKOSC_PLANSZY; wiersz++){
     layout->setRowMinimumHeight(wiersz, ROZMIAR_PRZYCISKU);   //ustawienie miejsca dla każdego elementu w grid layout
     layout->setRowStretch(wiersz,0);            //rozszerzenie elementu
     for(int kolumna = 0; kolumna< Plansza::SZEROKOSC_PLANSZY; kolumna++) {
         layout->setColumnMinimumWidth(kolumna, Plansza::ROZMIAR_PRZYCISKU);   //ustawienie miejsca dla każdego elementu w grid layout
         layout->setColumnStretch(kolumna,0);
         przyciski[wiersz][kolumna] = new PrzyciskPlanszy(wiersz,kolumna,this, widget);
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
const bool Plansza::sprobujWstawicStatek(int wspolrzedna_x, int wspolrzedna_y, Kierunek kierunek, int maszty){


    bool moznaWstawicStatek = true;

    for(int pozycja = 0; pozycja< maszty; pozycja++){
        switch(kierunek){
        case Kierunek::gora: {
            if (!(wspolrzedna_x -  pozycja>= 0 && wspolrzedna_x < Plansza::SZEROKOSC_PLANSZY && wspolrzedna_y >= 0 && wspolrzedna_y < Plansza::SZEROKOSC_PLANSZY)){
                moznaWstawicStatek = false;
            } else {
            moznaWstawicStatek = moznaWstawicStatek & !przyciski[wspolrzedna_x - pozycja][wspolrzedna_y]->getZajety();
            }
        break;
        }
        case Kierunek::lewo:{
             if (!(wspolrzedna_x >= 0 && wspolrzedna_x < Plansza::SZEROKOSC_PLANSZY && wspolrzedna_y - pozycja >= 0 && wspolrzedna_y < Plansza::SZEROKOSC_PLANSZY)){
                 moznaWstawicStatek = false;

             } else {
           moznaWstawicStatek = moznaWstawicStatek &  !przyciski[wspolrzedna_x][wspolrzedna_y - pozycja]->getZajety();
             }
        break;

        }
        case Kierunek::dol:{
            if(!(wspolrzedna_x  + pozycja>= 0 && wspolrzedna_x + pozycja < Plansza::SZEROKOSC_PLANSZY && wspolrzedna_y >= 0 && wspolrzedna_y < Plansza::SZEROKOSC_PLANSZY)){
                moznaWstawicStatek = false;
            } else {
            moznaWstawicStatek = moznaWstawicStatek & !przyciski[wspolrzedna_x + pozycja][wspolrzedna_y]->getZajety();}
        break;
        }
        case Kierunek::prawo:{
            if (!(wspolrzedna_x >= 0 && wspolrzedna_x < Plansza::SZEROKOSC_PLANSZY && wspolrzedna_y + pozycja >= 0 && wspolrzedna_y +  pozycja < Plansza::SZEROKOSC_PLANSZY)){
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


void PrzyciskPlanszy::setTrafiony(bool trafiony){
    this->trafiony = trafiony;
}
bool PrzyciskPlanszy::getTrafiony(){
    return trafiony;
}

void Plansza:: ustawZajeteWokol(int pozycja_x, int pozycja_y) {
    for(int wiersz = pozycja_x - 1; wiersz<= pozycja_x+1; wiersz++){
        for(int kolumna = pozycja_y - 1; kolumna <= pozycja_y + 1; kolumna++){
            if(wiersz >= 0 && wiersz <Plansza::SZEROKOSC_PLANSZY && kolumna>=0 &&kolumna<Plansza::SZEROKOSC_PLANSZY){
                przyciski[wiersz][kolumna]->setZajety(true);
            }
        }
    }
}
Q_SLOT bool PrzyciskPlanszy::przyciskKlikniety()
{
    bool trafiony = strzal();
    if (!trafiony){
        plansza->turaKomputera();
    }
    plansza->usunZatopioneStatki();
    plansza->brakStatkow();{
        //kod konczacy gre zwyciestwem gracza
        QApplication::quit();
    }
    return true;
}


bool PrzyciskPlanszy::strzal(){
if(trafiony == false) {
    trafiony = true;
    //zaznaczyc jako trafiony na planszy
    if(statek != nullptr) {
        this->setStyleSheet("background-color: red");
        statek->statekTrafiony();
        return true;
    } else {
        this->setStyleSheet("background-color: green");
        return false;
    }
}
return false;
}

bool Plansza::strzalKomputera(int wspolrzedna_x, int wspolrzedna_y){
    if (przyciski[wspolrzedna_x][wspolrzedna_y]->getTrafiony()) {                   //sprawdzamy czy dane pole jest już trafione, jeśli tak to strzela jeszcez raz
        return true;
    }
    bool trafiony = przyciski[wspolrzedna_x][wspolrzedna_y]->strzal();

    return przyciski[wspolrzedna_x][wspolrzedna_y]->strzal();
    usunZatopioneStatki();
    if(brakStatkow()){
            //kod konczacy gre zwyciestwem komputera
            QApplication::quit();
    }
            return trafiony;
}

void Plansza:: turaKomputera(){
    while(drugaPlansza->strzalKomputera(rand() % 10, rand() % 10));
}

void Plansza::dodajStatekDoListy(Statek &statek){
    statki.push_back(statek);                                           //każdy nowy statek będziemy dodawać na koniec listy, każdy element listy wskazuje na kolejny, na pierwszy nic nie wskazuje, ostatni nie wskazuje na nic tylko na nullptr
}                                                                       //dodajemy listę dla każdej planszy aby były na niej jakieś obiekty, będziemy przechodzić przez wszystkie elementy listy żeby sprawdzać czy wszystkie maszty są wyzerowane

void Plansza:: usunZatopioneStatki(){
    std::list<Statek>::iterator it;                 //iterator do poruszania się po liście, wskaźnik specjalny który może przechodzić po kilku elementach
    for (it = statki.begin(); it !=statki.end(); ++it)                       //wskazujemy na pierwszy element tablicy, poruszamy się po wszystich elementach
    {
        if(it->getMaszty()==0){
            it = statki.erase(it);                      //zwracana jest wartość nowego it, nadpisujemy it nową wartością, jeżeli trafione wszystkie maszty to statek usunięty z listy, zostaną tylko niezatopione statki
        }

    }
}

bool Plansza::brakStatkow(){
    std::cout<<statki.size();
    return statki.empty();                      //metoda zwraca wartość true jeśli jest pusta
}
