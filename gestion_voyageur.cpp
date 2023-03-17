#include "gestion_voyageur.h"
#include "ui_gestion_voyageur.h"
#include"etudiant.h"
#include "connection.h"
#include"dialog.h"
#include<QIntValidator>
#include<QMessageBox>
#include <QPushButton>
#include<QPdfWriter>
#include<QPainter>
#include<QSqlQuery>
#include<QFileDialog>
#include<QDesktopServices>
#include<QtPrintSupport/QPrinter>
#include<QTextDocument>
#include "dialog_mailing.h"
#include<dialog_stats.h>
#include"arduino.h"
#include "QIntValidator"
#include "QSerialPort"
#include "QSerialPortInfo"
#include"mainwindow.h"
gestion_voyageur::gestion_voyageur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_voyageur)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0,99999999,this));
    ui->le_id_3->setValidator(new QIntValidator(0,99999999,this));
    ui->le_id_sup->setValidator(new QIntValidator(0,99999999,this));
    ui->le_nom->setInputMask("AAAAAAAAA");
    ui->le_prenom->setInputMask("AAAAAAAAA");
    ui->le_nom_2->setInputMask("AAAAAAAAA");
    ui->le_prenom_2->setInputMask("AAAAAAAAA");
    ui->tab_Etudiant->setModel(etmp.afficher());
    int ret=a.connect_arduino();
    switch(ret){
    case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
    break;
    case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
    break;
    case(-1):qDebug()<<"arduino is not available";
    }
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

gestion_voyageur::~gestion_voyageur()
{
    delete ui;
}


void gestion_voyageur::on_pb_ajouter_clicked()
{
    QString NOM=ui->le_nom->text();
    QString PRENOM=ui->le_prenom->text();
    int ID=ui->le_id->text().toInt();
    int NUM_VOY=ui->le_prenom_3->text().toInt();

   Etudiant i(ID,NOM,PRENOM,NUM_VOY);

    bool test=i.ajouter();

     if(test)
     {ui->tab_Etudiant->setModel(etmp.afficher());
         QMessageBox::information(nullptr, QObject::tr("Ok"),
              QObject::tr("Ajout effectué.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);



     }
     else

         QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
              QObject::tr("Ajout non effectué.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);



}

void gestion_voyageur::on_pb_sup_clicked()
{
    int ID=(ui->le_id_sup->text().toInt());
     bool test=etmp.supprimer(ID);
     if(test)
     {ui->tab_Etudiant->setModel(etmp.afficher());
         QMessageBox::information(nullptr, QObject::tr("Ok"),
              QObject::tr("Suppression effectué.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);



     }
     else

         QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
              QObject::tr("Suppression non effectué.\n"
                          "Click Cancel to exit."), QMessageBox::Cancel);



}

void gestion_voyageur::on_pb_ajouter_2_clicked()
{
    QString NOM=ui->le_nom_2->text();
    QString PRENOM=ui->le_prenom_2->text();
    int ID=ui->le_id_3->text().toInt();
    int NUM_VOY=ui->le_prenom_4->text().toInt();


   Etudiant i(ID,NOM,PRENOM,NUM_VOY);



    bool test=i.modifier(ID);
    if (test)
    { ui->tab_Etudiant->setModel(etmp.afficher());
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectue\n ""click cancel"),QMessageBox::Cancel);

    }
    else
    {QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non fonctional\n""click to cancel"),QMessageBox::Cancel);}


}

void gestion_voyageur::on_pb_ajouter_8_clicked()
{
    QPdfWriter pdf("C:/Users/Eya Nehdi/Desktop/2A30-integration/pdfvoyageur.pdf");

                     QPainter painter(&pdf);

                     int i = 4000;


                     painter.drawText(3000,1500,"LISTE DES VOYAGEUR");
                     painter.setPen(Qt::blue);
                     painter.setFont(QFont("Arial", 50));
                     painter.drawRect(2700,200,6300,2600);
                     painter.drawRect(0,3000,9600,500);
                     painter.setPen(Qt::black);
                     painter.setFont(QFont("Arial", 9));
                     painter.drawText(300,3300,"ID");
                     painter.drawText(2300,3300,"PRENOM");
                     painter.drawText(4300,3300,"NOM");
                     painter.drawText(6300,3300,"NUM_VOY");

                     QSqlQuery query;
                     query.prepare("select * from GS_VOYAGEURS");
                     query.exec();
                     while (query.next())
                     {
                         painter.drawText(300,i,query.value(0).toString());
                         painter.drawText(2300,i,query.value(1).toString());
                         painter.drawText(4300,i,query.value(2).toString());
                         painter.drawText(6300,i,query.value(2).toString());

                         i = i +500;
                     }

                  /*   int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                     if (reponse == QMessageBox::Yes)
                     {
                         QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Eya Nehdi/Desktop/2A30-integration/pdfvoyageur.pdf"));

                         painter.end();
                     }
                     if (reponse == QMessageBox::No)
                     {
                         painter.end();
                     }*/
                     QMessageBox::information(nullptr, QObject::tr("PDF Enregistré!"),
                                                         QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void gestion_voyageur::on_pb_ajouter_4_clicked()
{
    Etudiant e;
        QString text;



            e.clearTable(ui->tab_Etudiant);
                int ID=ui->le_id_2->text().toInt();
                e.chercheID(ui->tab_Etudiant,ID);
}

void gestion_voyageur::on_pb_ajouter_7_clicked()
{

    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_Etudiant->setModel(etmp.tri_prenom());
}

void gestion_voyageur::on_pb_ajouter_6_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_Etudiant->setModel(etmp.tri_nom());
}

void gestion_voyageur::on_pb_ajouter_5_clicked()
{
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
             ui->tab_Etudiant->setModel(etmp.tri_id());
}


void gestion_voyageur::on_pushMailing_clicked()
{
    Dialog_mailing mail;
    mail.setModal(true);
    mail.exec();
}

void gestion_voyageur::on_pushMailing_2_clicked()
{
    Dialog_stats stat;
    stat.setModal(true);
    stat.exec();
}

void gestion_voyageur::on_secu_clicked()
{
    a.write_to_arduino("1");
}
void gestion_voyageur::on_insertimg_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png *.jpeg *.jpg *.bmp *.gif)"));
    QSqlQuery query;
          query.prepare("INSERT INTO IMAGE (IMG) "
                        "VALUES (:LOAD_FILE(filename))");
          query.bindValue(":LOAD_FILE(filename)",  filename);
          //QLabel* x = ui->imagee;
          //x->text();
          //x->(filename);


      if (QString::compare(filename,QString()) !=0)
      {
          QImage image;
          bool valid = image.load(filename);
          if(valid)
          {
              image=image.scaledToWidth(ui->imagee->width(), Qt::SmoothTransformation);
                      ui->imagee->setPixmap(QPixmap::fromImage(image));
                      query.exec();
          }
          else
          {
              //ERROR HANDLING
          }
      }
}

void gestion_voyageur::on_retour_clicked()
{
     MainWindow *w =new MainWindow ;
    w->show();
   this->hide();
}
