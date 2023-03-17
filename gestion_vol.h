#ifndef gestion_vol_H
#define gestion_vol_H
#include"popup.h"
#include <QMainWindow>
#include"vol.h"
//#include"statistiques.h"
#include"arduino.h"

namespace Ui {
class gestion_vol;
}

class gestion_vol : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_vol(QWidget *parent = nullptr);
    ~gestion_vol();

private slots:
    void on_pb_ajouter_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

   void on_pushButton_4_clicked();

   void on_pushButton_5_clicked();

   void on_pushButton_6_clicked();

  // void on_pb_stat_clicked();

   void on_pushButton_7_clicked();

   void on_pushButton_65_clicked();

   void on_pushButton_66_clicked();

private:
    Ui::gestion_vol *ui;
    Vol Vt;
     PopUp *popUp;
 // statistiques *s;
     int ret;
     Arduino A;
     QByteArray data;
};

#endif // gestion_vol_H
