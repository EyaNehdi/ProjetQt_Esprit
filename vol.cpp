#include "vol.h"
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QtSql/QSqlQueryModel>
#include <QObject>
Vol::Vol()
{
    id_vol="";  duree=""; Destination=" ";
}

Vol::Vol(QString id_vol,QString duree,QString Destination)
{this->id_vol=id_vol; this->duree=duree; this ->Destination=Destination; }
QString Vol::getid_vol(){return id_vol;}
QString Vol::getDestination() {return Destination;}
QString Vol::getduree() {return duree;}
void Vol::setid_vol(QString id_vol) {this->id_vol=id_vol;}
void Vol::setDestination(QString Destination) {this->Destination=Destination;}
void Vol::setduree(QString duree) {this->duree=duree;}


bool Vol::ajouter()
{

 QSqlQuery query;
 query.prepare("INSERT INTO vol (ID_vol, duree, destination)"
                    "VALUES (:id_vol, :duree, :destination)");
      query.bindValue(":id_vol",id_vol);
      query.bindValue(":duree", duree);
      query.bindValue(":destination", Destination);


    return  query.exec();
}
QSqlQueryModel* Vol::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel ();

         model->setQuery("SELECT * FROM VOL");
         model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant vol"));
         model->setHeaderData(1, Qt::Horizontal,QObject::tr("Duree"));
         model->setHeaderData(2, Qt::Horizontal,QObject::tr("Destination"));


    return model;
}

bool Vol::supprimer(QString id_vol)
{
    QSqlQuery query;
        query.prepare("DELETE FROM VOL WHERE id_vol=:id_vol");
        query.bindValue(0,id_vol);

    return query.exec();
}

bool Vol::modifier()
{
    QSqlQuery query;

            query.prepare("UPDATE VOL SET ID_vol=:id_vol, duree=:duree, destination=:destination WHERE id_vol=id_vol");
            query.bindValue(":id_vol", id_vol);
            query.bindValue(":duree", duree);
            query.bindValue(":destination", Destination);
        return query.exec();


    }
QSqlQueryModel * Vol::recherche(QString rech)
{
   QSqlQuery *qry= new QSqlQuery();
   qry->prepare("select * from vol where id_vol=:id_vol");
   qry->bindValue(":id_vol",rech);
   qry->exec();
   QSqlQueryModel *model = new QSqlQueryModel();
       model->setQuery(*qry);

   return model;
}
QSqlQueryModel * Vol::trier()  //ASC
    {
        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM vol ORDER BY id_vol");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Duree"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Destination"));

        return model;
    }


