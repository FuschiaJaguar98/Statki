#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Plansza.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    liczbaStatkow = 0;
    planszaGraczaJeden = new Plansza(ui->plansza1, ui->plansza1grid);

}

void MainWindow:: ustawStatekGracza(int liczbaMasztow)
{

    int wspolrzedna_x = ui->podanywiersz-> toPlainText().toInt();       //zwracamy zamisat string wartość int
    int wspolrzedna_y = ui->podanaKolumna-> toPlainText().toInt();

        Statek * nowyStatek = new Statek(wspolrzedna_x,wspolrzedna_y, Kierunek::prawo,liczbaMasztow);
        if (planszaGraczaJeden->sprobujWstawicStatek(wspolrzedna_x, wspolrzedna_y, Kierunek::prawo, liczbaMasztow)){
            planszaGraczaJeden->dodajStatek(nowyStatek);
          liczbaStatkow++;

    }


}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (liczbaStatkow < Plansza::LICZBA_CZTEROMASZTOWCOW){
        ustawStatekGracza (4);
    } else if (liczbaStatkow <Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW){
        ustawStatekGracza (3);
        //wstaw 3

    } else if (liczbaStatkow <Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW + Plansza::LICZBA_DWUMASZTOWCOW) {

         ustawStatekGracza (2);//wstaw 2

    } else if (liczbaStatkow <Plansza::LICZBA_CZTEROMASZTOWCOW + Plansza::LICZBA_TRZYMASZTOWCOW + Plansza::LICZBA_DWUMASZTOWCOW + Plansza::LICZBA_JEDNOMASZTOWCOW){
         ustawStatekGracza (1);
    }

}
