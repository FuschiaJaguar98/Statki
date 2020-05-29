#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Plansza.h>
#include <cstdlib>
#include<cstdio>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Plansza* planszaGraczaJeden;
    Plansza* planszaGraczaDwa;
    int liczbaStatkowGracza;
    int liczbaStatkowKomputera;
    Ui::MainWindow *ui;
    void ustawStatekGracza(const int liczbaMasztow);
    void ustawStatkiKomputera(int liczbaMasztow);
    void ustawStatkiKopmutera();
};
#endif // MAINWINDOW_H
