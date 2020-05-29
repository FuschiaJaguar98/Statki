#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Plansza.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);                  //ui - dostęp do rzeczy z formularza
    liczbaStatkowGracza = 0;
    liczbaStatkowKomputera = 0;
    planszaGraczaJeden = new Plansza(ui->plansza1, ui->plansza1grid);
    planszaGraczaDwa = new Plansza(ui->plansza2, ui->plansza1grid_2);
    srand( time( NULL ) );
}

void MainWindow:: ustawStatekGracza(int liczbaMasztow)
{

    int wspolrzedna_x = ui->podanywiersz-> toPlainText().toInt();       //zwracamy zamisat string wartość int
    int wspolrzedna_y = ui->podanaKolumna-> toPlainText().toInt();
    QString kierunekString = ui-> podanyKierunek->toPlainText();
    Kierunek kierunek;
    if(kierunekString == "prawo"){
        kierunek = Kierunek::prawo;
    } else if (kierunekString == "gora"){
        kierunek = Kierunek::gora;
    } else if (kierunekString == "lewo"){
        kierunek = Kierunek::lewo;
    } else if (kierunekString == "dol"){
        kierunek = Kierunek::dol;
    } else {
        return;                                             //jeśli mamy słówko void to możemy dać return aby wcześniej wyjść z funkcji
    }


        Statek * nowyStatek = new Statek(wspolrzedna_x,wspolrzedna_y, kierunek,liczbaMasztow);
        if (planszaGraczaJeden->sprobujWstawicStatek(wspolrzedna_x, wspolrzedna_y, kierunek, liczbaMasztow)){
            planszaGraczaJeden->dodajStatek(nowyStatek);
            liczbaStatkowGracza++;

    }


}
void MainWindow::ustawStatkiKomputera(int liczbaMasztow){                   //losowanie wartości dla statku
    int wspolrzedna_x = rand() %10;
    int wspolrzedna_y = rand() %10;
    Kierunek kierunek = Kierunek(rand()%4);

    if(planszaGraczaDwa->sprobujWstawicStatek(wspolrzedna_x, wspolrzedna_y, kierunek, liczbaMasztow)){
            planszaGraczaDwa->dodajStatek(new Statek(wspolrzedna_x,wspolrzedna_y,kierunek,liczbaMasztow));
            liczbaStatkowKomputera++;
}

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ustawStatkiKopmutera()
{
    while(liczbaStatkowKomputera < Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW + Plansza::LICZBA_DWUMASZTOWCOW + Plansza::LICZBA_JEDNOMASZTOWCOW)
        if(liczbaStatkowKomputera < Plansza::LICZBA_CZTEROMASZTOWCOW) {
        ustawStatkiKomputera(4);
        } else if (liczbaStatkowKomputera < Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW) {
        ustawStatkiKomputera(3);
        }else if (liczbaStatkowKomputera < Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW
                  + Plansza::LICZBA_DWUMASZTOWCOW) {
        ustawStatkiKomputera(2);
        }else if (liczbaStatkowKomputera < Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW
                  + Plansza::LICZBA_DWUMASZTOWCOW + Plansza::LICZBA_JEDNOMASZTOWCOW) {
        ustawStatkiKomputera(1);
        }
}

void MainWindow::on_pushButton_clicked()
{
    ustawStatkiKopmutera();
    if (liczbaStatkowGracza < Plansza::LICZBA_CZTEROMASZTOWCOW){
        ustawStatekGracza (4);
    } else if (liczbaStatkowGracza <Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW){
        ustawStatekGracza (3);
        //wstaw 3

    } else if (liczbaStatkowGracza <Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW + Plansza::LICZBA_DWUMASZTOWCOW) {

         ustawStatekGracza (2);//wstaw 2

    } else if (liczbaStatkowGracza <Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW + Plansza::LICZBA_DWUMASZTOWCOW + Plansza::LICZBA_JEDNOMASZTOWCOW){
         ustawStatekGracza (1);
    }
     if (liczbaStatkowGracza== Plansza::LICZBA_DWUMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW + Plansza::LICZBA_JEDNOMASZTOWCOW + Plansza::LICZBA_CZTEROMASZTOWCOW){      //jedno równa się, czy dana operacja się uda
        ustawStatkiKopmutera();
         /*while(1){
             //strzalgracza
         while(planszaGraczaJeden->strzalKomputera(rand() % 2, rand() % 2));
         }*/
     }

         //strzal gracza

}
