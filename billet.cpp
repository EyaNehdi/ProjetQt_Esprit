#include "billet.h"
#include <QtSql/QSqlQuery>
#include <QtDebug>
#include <QtSql/QSqlQueryModel>
#include <QObject>
Billet::Billet()
{
ID_B=0;
DESTINATION="";
CLASSE="";
}
Billet::Billet(int ID_B,QDate DATE_DEP_B,QDate DATE_AR_B,QString DESTINATION,QString CLASSE)
{
    this->ID_B=ID_B;
    this->DATE_DEP_B=DATE_DEP_B;
    this->DATE_AR_B=DATE_AR_B;
    this->DESTINATION=DESTINATION;
    this->CLASSE=CLASSE;
}
int Billet::getID_B()
{
    return ID_B;
}
QString Billet::getDESTINATION()
{
    return DESTINATION;
}
QString Billet::getCLASSE()
{
    return CLASSE;
}
QDate Billet::getDATE_DEP_B()
{
    return DATE_DEP_B;
}
QDate Billet::getDATE_AR_B()
{
    return DATE_AR_B;
}
void Billet::setID_B(int ID_B)
{
    this->ID_B=ID_B;
}
void Billet::setDESTINATION(QString DESTINATION)
{
    this->DESTINATION=DESTINATION;
}
void Billet::setCLASSE(QString CLASSE)
{
    this->CLASSE=CLASSE;
}
void Billet::setDATE_DEP_B(QDate DATE_DEP_B)
{
    this->DATE_DEP_B=DATE_DEP_B;
}
void Billet::setDATE_AR_B(QDate DATE_AR_B)
{
    this->DATE_AR_B=DATE_AR_B;
}
//ajouter un billet
bool Billet::ajouter()
{
    QSqlQuery query;
          query.prepare("INSERT INTO BILLETS (ID_B, DATE_DEP_B, DATE_AR_B, DESTINATION, CLASSE) "
                        "VALUES (:ID_B, :DATE_DEP_B, :DATE_AR_B, :DESTINATION, :CLASSE)");
          query.bindValue(":ID_B", ID_B);
          query.bindValue(":DATE_DEP_B", DATE_DEP_B);
          query.bindValue(":DATE_AR_B", DATE_AR_B);
          query.bindValue(":DESTINATION", DESTINATION);
          query.bindValue(":CLASSE", CLASSE);
          return query.exec();
}
//afficher billet
QSqlQueryModel* Billet::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM BILLETS");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant Billet"));
          model->setHeaderData(1, Qt::Horizontal,QObject::tr("Date de depart"));
          model->setHeaderData(2, Qt::Horizontal,QObject::tr("Date d arrivee"));
          model->setHeaderData(3, Qt::Horizontal,QObject::tr("Destination"));
          model->setHeaderData(4, Qt::Horizontal,QObject::tr("Classe"));

    return model;
}
//supprimer billet
bool Billet::supprimer(int ID_B)
{
    QSqlQuery query;
    query.prepare("DELETE FROM BILLETS where ID_B= :ID_B");
    query.bindValue(0, ID_B);

    return query.exec();
}
//modifier un billet
bool Billet::modifier()
{
    QSqlQuery query;
        query.prepare("UPDATE BILLETS set ID_B=:ID_B,DATE_DEP_B=:DATE_DEP_B,DATE_AR_B=:DATE_AR_B,DESTINATION=:DESTINATION,CLASSE=:CLASSE WHERE ID_B=:ID_B");
        query.bindValue(":ID_B", ID_B);
        query.bindValue(":DATE_DEP_B",DATE_DEP_B);
        query.bindValue(":DATE_AR_B", DATE_AR_B);
        query.bindValue(":DESTINATION", DESTINATION);
        query.bindValue(":CLASSE", CLASSE);
          return query.exec();


    }
QSqlQueryModel* Billet ::afficher_id()
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT ID_B from BILLETS");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_B"));
    return model;
}
QSqlQueryModel* Billet ::afficher_id2()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT ID_B from BILLETS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_B"));
    return model;
}
QSqlQueryModel * Billet::tri_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from BILLETS order by ID_B");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_B"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_DEP_B"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_AR_B"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESTINATION"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("CLASSE"));
    return model;
}
QSqlQueryModel * Billet::tri_classe()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from BILLETS order by CLASSE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_B"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_DEP_B"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATE_AR_B"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESTINATION"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("CLASSE"));
    return model;
}

QSqlQueryModel* Billet ::chercher (QString rech)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM BILLETS WHERE ID_B LIKE'%"+rech+"%' or DATE_DEP_B LIKE'%"+rech+"%' or DATE_AR_B  LIKE'%"+rech+"%' or DESTINATION LIKE'%"+rech+"%' or CLASSE  LIKE'%"+rech+"%'  ");
    return model;
}
