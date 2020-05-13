#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Plansza.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Plansza planszaGraczaJeden(ui->plansza1, ui->plansza1grid);
}

MainWindow::~MainWindow()
{
    delete ui;
}

