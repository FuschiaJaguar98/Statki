#include "Plansza.h"
#include <iostream>
bool Plansza::graWToku = false;             //deklaracja tu bo jak by była w pliku h to byłaby podwójna deklaracjia
Plansza::Plansza(QWidget* widget, QGridLayout* layout,Plansza *drugaPlansza, QLabel* komunikatWygranej, bool nalezyDoGracza): widget (widget), layout(layout),drugaPlansza (drugaPlansza), komunikatWygranej(komunikatWygranej), nalezyDoGracza(nalezyDoGracza){
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
            przyciski[wiersz][kolumna] = new PrzyciskPlanszy(wiersz,kolumna,this, widget, nalezyDoGracza);
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
            if(nalezyDoGracza){
                przyciski[wspolrzedna_x-numerPrzycisku][wspolrzedna_y]->setStyleSheet("background-color: blue");    //statki komputera nie widoczne dla gracza, jak nie należy do gracza to nie kolorujemy na niebiesko
            }przyciski[wspolrzedna_x-numerPrzycisku][wspolrzedna_y]->setStatek(nowyStatek);                         //wstawianie statku
            ustawZajeteWokol(wspolrzedna_x-numerPrzycisku,wspolrzedna_y);
            break;
        }
        case Kierunek::lewo: {
            if(nalezyDoGracza) {

                przyciski[wspolrzedna_x][wspolrzedna_y - numerPrzycisku]->setStyleSheet("background-color: blue");

            }przyciski[wspolrzedna_x][wspolrzedna_y-numerPrzycisku]->setStatek(nowyStatek);
            ustawZajeteWokol(wspolrzedna_x,wspolrzedna_y-numerPrzycisku);
            break;
        }

        case Kierunek::dol: {
            if(nalezyDoGracza) {

                przyciski[wspolrzedna_x + numerPrzycisku][wspolrzedna_y]->setStyleSheet("background-color: blue");
            } przyciski[wspolrzedna_x+numerPrzycisku][wspolrzedna_y]->setStatek(nowyStatek);
            ustawZajeteWokol(wspolrzedna_x+numerPrzycisku,wspolrzedna_y);
            break;
        }

        case Kierunek::prawo: {
            if(nalezyDoGracza) {

                przyciski[wspolrzedna_x][wspolrzedna_y + numerPrzycisku]->setStyleSheet("background-color: blue");
            } przyciski[wspolrzedna_x][wspolrzedna_y + numerPrzycisku]->setStatek(nowyStatek);
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
    if(Plansza::graWToku){              //jeśli gra się nie rozpoczęła a gracz gdzieś kliknął to zwracamy true aby nie stracił kolejki
        bool trafiony = strzal();
        if (!trafiony){
            plansza->turaKomputera();
        }
        plansza->usunZatopioneStatki();
        if(plansza->brakStatkow()){
            plansza->setKomunikat("Gracz wygral!!!");         //tą metodę można wywoałać tylko na przycisku, trzeba się odwołać do planszy
            Plansza::graWToku = false;
            //QApplication::quit();
        }
        return true;
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
    return true;                        //jeżeli przycisk na który trafiliśmy jest już trafiony to gracz może jeszcze raz
}

bool Plansza::strzalKomputera(int wspolrzedna_x, int wspolrzedna_y){
    if (Plansza::graWToku){
        if (przyciski[wspolrzedna_x][wspolrzedna_y]->getTrafiony()) {                   //sprawdzamy czy dane pole jest już trafione, jeśli tak to strzela jeszcez raz
            return true;                        //while dla tury komputera się dalej wykonuje jeżeli dwa razy trafi w to samo miejsce
        }
        bool trafiony = przyciski[wspolrzedna_x][wspolrzedna_y]->strzal();

        //return przyciski[wspolrzedna_x][wspolrzedna_y]->strzal();
        usunZatopioneStatki();
        if(brakStatkow()){
            komunikatWygranej->setText("Komputer wygral!!!");

            Plansza::graWToku = false;
            //kod konczacy gre zwyciestwem komputera

        }
        return trafiony;
    }
    return false;               //jeżeli gra się skończyła to przechodzi tu i nie jest wykonywany ostatni strzał
}

void Plansza:: turaKomputera(){
    while(drugaPlansza->strzalKomputera(rand() % 10, rand() % 10));
}

void Plansza::dodajStatekDoListy(Statek &statek){
    statki.push_back(&statek);                                           //każdy nowy statek będziemy dodawać na koniec listy, każdy element listy wskazuje na kolejny, na pierwszy nic nie wskazuje, ostatni nie wskazuje na nic tylko na nullptr
}                                                                       //nowy wskaźnik wskazuje na nowy obiekt statek,dodajemy listę dla każdej planszy aby były na niej jakieś obiekty, będziemy przechodzić przez wszystkie elementy listy żeby sprawdzać czy wszystkie maszty są wyzerowane
//& zwracamy wartość adresu, *zamiast adresu zwraca wartość, w funkcji ma inne znaczenie &statek zwykły obiekt czyli referencja, nie skopiowany obiekt, bez & - kopia obiektu, jakbyśmy modyfikowali oryginalny obiekt to byśmy go ni ewidizeli, nie widzieli zmian
void Plansza:: usunZatopioneStatki(){
    std::list<Statek*>::iterator it;                                     //iterator do poruszania się po liście, wskaźnik specjalny który może przechodzić po kilku elementach
    for (it = statki.begin(); it !=statki.end(); ++it)                       //wskazujemy na pierwszy element tablicy, poruszamy się po wszystich elementach
    {
        if((*it)->getMaszty()==0){                      //jak it bez gwiazdki to it wskaźnik na element listy, które mają w środku statek, ze wskaźnikiem to mamy nowy wskaźnik na te elementy dlatego musimy użyć podwójnego wskaźnika i rozpakowania tego iteratora, po dodaniu wskaźnika mamy listę wskaźników a nie listę obiektów
            it = statki.erase(it);                      //zwracana jest wartość nowego it, nadpisujemy it nową wartością, jeżeli trafione wszystkie maszty to statek usunięty z listy, zostaną tylko niezatopione statki
        }

    }
}

bool Plansza::brakStatkow(){

    return statki.empty();                      //metoda zwraca wartość true jeśli jest pusta
}

void Plansza::setKomunikat(const QString &komunikat)
{
    komunikatWygranej->setText(komunikat);

}
