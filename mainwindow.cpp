#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Plansza.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Plansza planszaGraczaJeden(ui->plansza1, ui->plansza1grid);
    Statek statek(1,1,Kierunek::prawo,3);
    planszaGraczaJeden.dodajStatek(&statek);
}

MainWindow::~MainWindow()
{
    delete ui;
}

