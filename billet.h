#ifndef BILLET_H
#define BILLET_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QTableView>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QDate>
class Billet
{
public:
    Billet();
    Billet(int,QDate,QDate,QString,QString);

    int getID_B();
    QString getDESTINATION();
    QString getCLASSE();
    QDate getDATE_DEP_B();
    QDate getDATE_AR_B();

    void setID_B(int);
    void setDESTINATION(QString);
    void setCLASSE(QString);
    void setDATE_DEP_B(QDate);
    void setDATE_AR_B(QDate);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* afficher_id();
    QSqlQueryModel* afficher_id2();
    QSqlQueryModel* tri_id();
    QSqlQueryModel* tri_classe();
    QSqlQueryModel* chercher (QString rech);
private:
    int ID_B;
    QString DESTINATION,CLASSE;
    QDate DATE_DEP_B,DATE_AR_B;

};

#endif // BILLET_H
