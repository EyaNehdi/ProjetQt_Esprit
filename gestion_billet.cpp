#include "gestion_billet.h"
#include "ui_gestion_billet.h"
#include "billet.h"
#include <QIntValidator>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QIntValidator>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPushButton>
#include <QPdfWriter>
#include <QPainter>
#include "dialog_stats.h"
#include "exportexcelobject.h"
#include "arduino.h"
#include "mainwindow.h"
gestion_billet::gestion_billet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_billet)
{
    ui->setupUi(this);
    ui->lineEdit_ID_ajout->setValidator(new QIntValidator(0,9999999,this));
    ui->lineEdit_DES->setInputMask("AAAAAAAAAAAAAAAAAA");
    ui->lineEdit_CLASS->setInputMask("AAAAAAAAAAAAAAAA");
    ui->comboBox->setModel(etmp.afficher_id());
    ui->comboBox_2->setModel(etmp.afficher_id2());
    ui->tableView->setModel(etmp.afficher());
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

gestion_billet::~gestion_billet()
{
    delete ui;
}

// acceder au different widgets
void gestion_billet::on_pushButton_b_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void gestion_billet::on_pushButton_valider_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void gestion_billet::on_pushButton_ab_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void gestion_billet::on_pushButton_affb_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void gestion_billet::on_pushButton_eb_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void gestion_billet::on_pushButton_mb_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void gestion_billet::on_pushButton_annuler_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


//bouton ajouter
void gestion_billet::on_AJOUTER_clicked()
{
    int ID_B=ui->lineEdit_ID_ajout->text().toInt();
    QString DESTINATION=ui->lineEdit_DES->text();
    QString CLASSE=ui->lineEdit_CLASS->text();
    QDate DATE_DEP_B=ui->dateEdit_datedep->date();
    QDate DATE_AR_B=ui->dateEdit_datear->date();
    Billet B(ID_B,DATE_DEP_B,DATE_AR_B,DESTINATION,CLASSE);
    bool test=B.ajouter();
    QMessageBox msgBox;
    if (test)
    {  ui->tableView->setModel(B.afficher());
        msgBox.setText("Ajout avec succes");

    } else
        msgBox.setText("Echec d ajout");
    msgBox.exec();
}
//bouton modifier
void gestion_billet::on_modifier_clicked()
{
    int ID_B=ui->lineEdit_ID_ajout->text().toInt();
    QString DESTINATION=ui->lineEdit_DES->text();
    QString CLASSE=ui->lineEdit_CLASS->text();
    QDate DATE_AR_B=ui->dateEdit_datear->date();
    QDate DATE_DEP_B=ui->dateEdit_datedep->date();
    Billet B(ID_B,DATE_DEP_B,DATE_AR_B,DESTINATION,CLASSE);
    bool test=etmp.modifier();
    if(test)
    {
        ui->labelinfo->setText("Modification effectué");
        ui->tableView->setModel(etmp.afficher());
        ui->comboBox->setModel(etmp.afficher_id());
        ui->comboBox_2->setModel(etmp.afficher_id2());
    }
    else
    {
        ui->labelinfo->setText("Modification non effectué");
    }
}
//Selection avec combo box
void gestion_billet::on_comboBox_currentIndexChanged(QString)
{
    int id=ui->comboBox->currentText().toInt();
    QString id_1=QString::number(id);
    QSqlQuery query ;
    query.prepare("SELECT * FROM  BILLETS where ID_B='"+id_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_ID_ajout->setText(query.value(0).toString()) ;
            ui->dateEdit_datedep->setDate(query.value(1).toDate());
            ui->dateEdit_datear->setDate(query.value(2).toDate());
            ui->lineEdit_DES->setText(query.value(3).toString()) ;
            ui->lineEdit_CLASS->setText(query.value(4).toString());

        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }


}
//bouton supprimer
void gestion_billet::on_SUPRIMER_clicked()
{
    Billet b ;
    b.setID_B(ui->comboBox->currentText().toInt());
    bool test=b.supprimer(b.getID_B());
    if(test)
    {
        ui->labelinfo->setText("Suppression effectué");
        ui->tableView->setModel(b.afficher());
        ui->comboBox->setModel(b.afficher_id());
        ui->comboBox_2->setModel(etmp.afficher_id2());
    }
    else
    {
        ui->labelinfo->setText("Suppression non effectué");
    }
}

void gestion_billet::on_CHERCHER_textChanged(const QString &arg1)
{
    ui->tableView->setModel(etmp.chercher(arg1));
}
//bouton tri par id
void gestion_billet::on_TRIE_ID_clicked()
{
    ui->labelinfo->setText("Tri par ID effectué");
    ui->tableView->setModel(etmp.tri_id());
}

//bouton tri par classe
void gestion_billet::on_TRIE_CLASS_clicked()
{
    ui->labelinfo->setText("Tri par Classe effectué");
    ui->tableView->setModel(etmp.tri_classe());
}

//bouton statistique
void gestion_billet::on_STAT_clicked()
{
    Dialog_stats stats;
    stats.setModal(true);
    stats.exec();
}
//export excel
void gestion_billet::on_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "BILLETS", ui->tableView);

    //colums to export
    obj.addField(0, "ID_B", "char(20)");
    obj.addField(1, "DATE_DEP_B", "char(20)");
    obj.addField(2, "DATE_AR_B", "char(20)");
    obj.addField(3, "DESTINATION", "char(20)");
    obj.addField(4, "CLASSE", "char(20)");



    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
//bouton qr code
void gestion_billet::on_qr_code_clicked()
{
    QDesktopServices::openUrl(QUrl("https://app.qr-code-generator.com/manage/?aftercreate=1&count=1"));
        QString filename = QFileDialog::getSaveFileName(this,tr("choose"),"",tr("Image(*.png )"));
        if (QString::compare(filename,QString()) !=0)
        {
            QImage image;
            bool valid = image.load(filename);
            if(valid)
            {
                image=image.scaledToWidth(ui->lbl_image_2->width(), Qt::SmoothTransformation);
                        ui->lbl_image_2->setPixmap(QPixmap::fromImage(image));
            }
            else
            {
                //ERROR HANDLING
            }
        }







}




void gestion_billet::on_comboBox_2_currentIndexChanged(QString)
{

    int id2=ui->comboBox_2->currentText().toInt();
    QString id2_1=QString::number(id2);
    QSqlQuery query ;
    query.prepare("SELECT * FROM  BILLETS where ID_B='"+id2_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            QPdfWriter pdf("D:/projetcplusplus/gestionbillet.pdf");
            QPainter painter(&pdf);



            //painter.drawText(3000,1500,"LISTE DES BILLETS");
            painter.setPen(Qt::blue);
            painter.drawPixmap(QRect(0,0,9500,12000),QPixmap("C:/Users/Eya Nehdi/Desktop/BILLET.png"));
            painter.setFont(QFont("Arial", 50));
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 9));
            painter.drawText(300,1500,query.value(0).toString());
            painter.drawText(6700,3100,query.value(1).toString());
            painter.drawText(2700,2600,query.value(1).toString());
            painter.drawText(400,2600,query.value(2).toString());
            painter.drawText(6700,2500,query.value(2).toString());
            painter.drawText(400,3500,query.value(3).toString());
            painter.drawText(6700,1500,query.value(3).toString());
            painter.drawText(6900,700,query.value(4).toString());
            painter.drawText(500,1200,query.value(4).toString());
            if(ui->comboBox_2->currentIndex())
            {
            int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile("D:/projetcplusplus/gestionbillet.pdf"));
                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                painter.end();
            }
}
    }

}
}



void gestion_billet::on_arduino_clicked()
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
                        QObject::tr("parking comp.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);}
             else if((i>0)&&(i<3))
            {
                QMessageBox::information(this, QObject::tr("database is open"),
                            QObject::tr("parking not com.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             }

        }}


void gestion_billet::on_qr_code_2_clicked()
{
    MainWindow *w =new MainWindow ;
   w->show();
  this->hide();
}
