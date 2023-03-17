#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::setEtudiant(Etudiant e)
{

    ui->lineEdi_nom->setText(e.nom);
        ui->lineEdit_prenom->setText(e.prenom);
            ui->lineEditcin->setText(e.id);
}
