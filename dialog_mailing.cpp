#include "dialog_mailing.h"
#include "ui_dialog_mailing.h"
#include "smtp.h"
#include <QMessageBox>
Dialog_mailing::Dialog_mailing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_mailing)
{
    ui->setupUi(this);
    connect(ui->envoyer_dialog_2, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->annuler_mail_2, SIGNAL(clicked()),this, SLOT(close()));
}
Dialog_mailing::Dialog_mailing(QString e,QString n,QString s,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_mailing)
{
    QString contenu="Contenu";
    ui->setupUi(this);

    ui->recipient_2->setText(e);
    ui->uname->setText("apptayarni@gmail.com");
    ui->passwd_2->setText("bguhpdfmhbrmddne");
    ui->passwd_2->setEchoMode(QLineEdit::Password);

    if (s=="Homme")
    {
        ui->message_2->setText("Cher Monsieur "+n+",\n\n"+contenu+"\n\n"+"Cordialement,\n");
    }
    else if (s=="Femme")
    {
        ui->message_2->setText("Chère Madame "+n+",\n\n"+contenu+"\n\n"+"Cordialement,\n");
    }

}
void Dialog_mailing::on_envoyer_dialog_2_clicked()
{QString status;
    Smtp* smtp = new Smtp(ui->uname->text(), ui->passwd_2->text(), "smtp.gmail.com", 465); //smtp.gmail.com

    smtp->sendMail(ui->uname->text(), ui->recipient_2->text() , ui->subjectLineEdit_2->text() ,ui->message_2->toPlainText());

    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
Dialog_mailing::~Dialog_mailing()
{
    delete ui;
}
