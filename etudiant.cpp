#include "etudiant.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QTableView>
Etudiant::Etudiant()
{
    ID=0;
      NOM=" ";
      PRENOM=" ";

}
Etudiant::Etudiant (int ID,QString NOM,QString PRENOM,int NUM_VOY)
{
    this->ID=ID;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->NUM_VOY=NUM_VOY;

}
int Etudiant::getid()
{
    return ID;
}
QString Etudiant::getnom()
{
    return NOM;
}
QString Etudiant::getprenom()
{
    return PRENOM;
}


int Etudiant::getnum_voy()
{
    return  NUM_VOY;
}

void Etudiant::setnum_voy(int NUM_VOY)
{
    this->NUM_VOY=NUM_VOY;

}
void Etudiant::setid(int ID)
{
    this->ID=ID;

}
void Etudiant::setnom(QString NOM)
{
    this->NOM=NOM;

}
void Etudiant::setprenom(QString PRENOM)
{
    this->PRENOM=PRENOM;

}



bool Etudiant::ajouter()
{


    QSqlQuery query;
    QString id_string=QString::number(ID);
    QString num=QString::number(NUM_VOY);


         query.prepare("INSERT INTO VOYAGEUR(ID,NOM,PRENOM,NUM_VOY)" "VALUES (:ID,:NOM,:PRENOM,:NUM_VOY)");
         query.bindValue(":ID", id_string);
         query.bindValue(":NOM", NOM);
         query.bindValue(":PRENOM", PRENOM);

         query.bindValue(":NUM_VOY", num);


               return query.exec();


}


bool Etudiant::supprimer(int ID)
{
    QSqlQuery query;

         query.prepare("DELETE FROM VOYAGEUR where ID= :ID");
         query.bindValue(0, ID);

return query.exec();

}


QSqlQueryModel *Etudiant::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM VOYAGEUR");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));

          model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_VOY"));

          return  model;
}
bool Etudiant::modifier(int ID)
{
    QSqlQuery query;
    QString A=QString::number(ID);



    query.prepare("UPDATE VOYAGEUR set NOM=:NOM,PRENOM=:PRENOM,ID=:ID WHERE ID=:ID ");



    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":ID",ID);

    query.bindValue(":NUM_VOY",NUM_VOY);


    return query.exec();


}
QSqlQueryModel * Etudiant::tri_id()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from VOYAGEUR order by ID");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_VOY"));

    return model;
}

QSqlQueryModel * Etudiant::tri_prenom()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from VOYAGEUR order by PRENOM");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_VOY"));

    return model;
}
QSqlQueryModel * Etudiant::tri_nom()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from VOYAGEUR order by NOM");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_VOY"));

    return model;
}

void Etudiant::chercheID(QTableView *table, int ID)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from VOYAGEUR where regexp_like(ID,:ID);");
   query->bindValue(":ID",ID);
   if(ID==0)
   {
       query->prepare("select * from VOYAGEUR;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void Etudiant::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}
