#ifndef VOL_H
#define VOL_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>

class Vol
{
public:
    Vol();
    Vol(QString,QString,QString);
   QString getid_vol();
   /* int getID_HA();
   int getID_PILOTE()*/
    QString getDestination ();
    QString getduree ();
  /*  QDate getdate_dep ();
    QDate getdate_arr ();*/
    void setid_vol(QString);
  /*  void setID_HA(int);
    void setID_PILOTE(int); */
    void setDestination(QString);
    void setduree(QString);
  /*  void setdate_dep (QDate);
    void setdate_arr (QDate);*/
    bool ajouter();
    QSqlQueryModel* afficher ();
    bool supprimer(QString);
    bool modifier();
   /* bool rechercher();*/
    QSqlQueryModel* afficher_id();
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * trier();




private:
    QString id_vol, duree /*, ID_HA,ID_PILOTE*/;
    QString Destination;

  /*  QDate date_dep, date_arr;*/










};


#endif // VOL_H
