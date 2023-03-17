#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"vol.h"
//#include"statistiques.h"
#include"arduino.h"
#include"popup.h"
#include"gestion_vol.h"
#include"gestion_billet.h"
#include"gestion_voyageur.h"
#include"dialog_mailing.h"


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
    void on_pushButton_b_clicked();

    /*void on_pushButton_a_clicked();

    void on_pushButton_voy_clicked();*/

   // void on_pushButton_a_clicked();

    void on_pushButton_v_clicked();

    void on_pushButton_voy_clicked();

private:
    Ui::MainWindow *ui;
    Vol Vt;
        PopUp *popUp;
    // statistiques *s;
        int ret;
        Arduino a;
        QByteArray data;
};
#endif // MAINWINDOW_H
