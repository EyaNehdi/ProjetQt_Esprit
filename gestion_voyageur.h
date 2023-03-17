#ifndef gestion_voyageur_H
#define gestion_voyageur_H
#include"etudiant.h"
#include <QMainWindow>
#include "QSerialPort"
#include "QSerialPortInfo"
#include "arduino.h"

namespace Ui {
class gestion_voyageur;
}

class gestion_voyageur : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_voyageur(QWidget *parent = nullptr);
    ~gestion_voyageur();

private slots:
    //void on_pushButton_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_sup_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pb_ajouter_8_clicked();

    void on_pb_ajouter_4_clicked();

    void on_pb_ajouter_7_clicked();

    void on_pb_ajouter_6_clicked();

    void on_pb_ajouter_5_clicked();

    void on_pushMailing_clicked();

    void on_pushMailing_2_clicked();

    void on_secu_clicked();
    void on_insertimg_clicked();

    void on_retour_clicked();

private:
    Ui::gestion_voyageur *ui;
    Arduino a;

    Etudiant etmp;


};

#endif // gestion_voyageur_H
