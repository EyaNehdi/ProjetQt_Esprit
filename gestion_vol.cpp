#include "gestion_vol.h"
#include "ui_gestion_vol.h"
#include "vol.h"
#include<QMessageBox>
#include<QIntValidator>
#include<QPainter>
#include<QPdfWriter>
#include<QtSql/QSqlQuery>
#include<QWidget>
#include <QDate>
#include<QComboBox>
#include<QTextEdit>
#include<QtCharts>
#include "arduino.h"
#include "mainwindow.h"
//#include"statistique.h"

gestion_vol::gestion_vol(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_vol)
{
    ui->setupUi(this);
      popUp = new PopUp();
    ui->le_ID->setValidator(new QIntValidator(0, 9999999, this));
    ui->lineEdit_vol_mod->setInputMask("NNNNNNNNNNN");
    ui->lineEdit_duree_mod->setInputMask("AAAAAAAAAAAAAA");
    ui->lineEdit_destination_mod->setInputMask("AAAAAAAAAAAAAA");
    ui->le_destination->setInputMask("AAAAAAAAAAAAAA");
    ui->le_duree->setInputMask("AAAAAAAAAAAAAA");
    ui->tableView->setModel(Vt.afficher());
    ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).

}

gestion_vol::~gestion_vol()
{
    delete ui;
}
                                                                             /*ajouter*/
void gestion_vol::on_pb_ajouter_clicked()
{
    QString id_vol=ui->le_ID->text();
    QString destination=ui->le_destination->text();
     QString duree=ui->le_duree->text();
     Vol V(id_vol,duree,destination);
     bool test=V.ajouter();
     if(test)
          {
              QMessageBox::information(nullptr, QObject::tr("Ok"),
                   QObject::tr("Ajout effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(Vt.afficher());



          }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                   QObject::tr("Ajout non effectué.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);


          }
}
                                                                                /*supprimer*/

void gestion_vol::on_pushButton_clicked()
{
    QString id_vol=ui->lineEdit_supp->text();
        bool test=Vt.supprimer(id_vol);

        if(test)
        {ui->tableView->setModel(Vt.afficher());
            QMessageBox::information(nullptr, QObject::tr("ok"),
                                 QObject::tr("Suppression effectué"),QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                                 QObject::tr("Suppression non effectué"),QMessageBox::Cancel);
}
                                                                         /*modifier*/
void gestion_vol::on_pushButton_2_clicked()
{
    QString id_vol=ui->lineEdit_vol_mod->text();
      QString duree=ui->lineEdit_duree_mod->text();
      QString destination=ui->lineEdit_destination_mod->text();
      Vol V(id_vol,duree,destination);

      bool test=V.modifier();
      if(test)
      {ui->tableView->setModel(Vt.afficher());
          QMessageBox::information(nullptr, QObject::tr("ok"),
                               QObject::tr("Modification effectué"),QMessageBox::Cancel);

      }
      else
          QMessageBox::critical(nullptr, QObject::tr("not ok"),
                               QObject::tr("Modiffication non effectué"),QMessageBox::Cancel);
}

                                                                             /*PDF*/
void gestion_vol::on_pushButton_4_clicked()
{
    QPdfWriter pdf("C:/Users/Eya Nehdi/Desktop/2A30-integration/pdfvol.pdf");

                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 25));
                          painter.drawText(950,1100,"GESTION DES VOLS");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 15));
                         //
                          painter.drawRect(100,100,7300,2600);
                          painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Eya Nehdi/Desktop/2A30-integration"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(200,3300,"ID_Vol");
                          painter.drawText(1600,3300,"Duree");
                          painter.drawText(3000,3300,"Destination");
                       /*    painter.drawText(4200,3300,"BUDGET");
                         painter.drawText(5300,3300,"DATE DEBUT");
                          painter.drawText(7400,3300,"DATE FIN");*/


                          QSqlQuery query;
                          query.prepare("select * from VOL");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1600,i,query.value(1).toString());
                              painter.drawText(3000,i,query.value(2).toString());
                              painter.drawText(4200,i,query.value(3).toString());
                              painter.drawText(5300,i,query.value(4).toString());
                              painter.drawText(7400,i,query.value(5).toString());


                             i = i + 500;
                          }
                          QMessageBox::information(nullptr, QObject::tr("PDF Enregistré!"),
                                      QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }


/*rechercher*/

void gestion_vol::on_pushButton_3_clicked()
{
    QString rech=ui->line_recherche->text();
        if(rech!="")
        {
            QSqlQueryModel *tab_recherche=Vt.recherche(rech);
            if (tab_recherche!=nullptr)
            {
                ui->tab_recherche->setModel(tab_recherche);
            }
        }
}
/* trier*/

void gestion_vol::on_pushButton_5_clicked()
{
      ui->tableView->setModel(Vt.trier());
}
/*notification*/
void gestion_vol::on_pushButton_6_clicked()
{
    popUp->setPopupText(ui->textEdit_2->toPlainText());


       popUp->show();
}

/*void gestion_vol::on_pb_stat_clicked()
{
    s = new statistiques();
       s->setWindowTitle("PRODUCTIVITE en fonction des taches effectuées");
       s->choix_pie();
       s->show();
}
*/
                                   //arduino
void gestion_vol::on_pushButton_7_clicked()
{
    data=A.read_from_arduino();
qDebug()<<data;
int i=0;


if (ret == -1)
{ //msgBox.setText("arduino not found ");


     QMessageBox::information(this, QObject::tr("database is open"),
                 QObject::tr("arduino not found.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
   //   msgBox.exec();
} else{
     //   QMessageBox msgBox;
        if (data=="Leave\r\nCar")
        { i-- ; } else{i++;}
        if (i<3)
        {

            QMessageBox::information(this, QObject::tr("database is open"),
                        QObject::tr("parcing comp.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
             else if((i>0)&&(i<3))
            {
                QMessageBox::information(this, QObject::tr("database is open"),
                            QObject::tr("parc not com.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             }

        }}



void gestion_vol::on_pushButton_66_clicked()
{
    MainWindow *w =new MainWindow ;
        w->show();
       this->hide();

}
