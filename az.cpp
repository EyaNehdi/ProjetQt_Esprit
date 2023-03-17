#include "az.h"
#include "ui_az.h"
#include"etudiant.h"
#include"az.h"
az::az(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::az)
{
    ui->setupUi(this);
}

az::~az()
{
    delete ui;
}

void az::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
      QString prenom=ui->le_prenom->text();
    Etudiant e(id,nom,prenom);
}
