#ifndef DIALOG_MAILING_H
#define DIALOG_MAILING_H

#include <QDialog>

namespace Ui {
class Dialog_mailing;
}

class Dialog_mailing : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_mailing(QWidget *parent = nullptr);
    explicit Dialog_mailing(QString,QString,QString,QWidget *parent = nullptr);
    ~Dialog_mailing();
private slots:
void set_tmpemail(QString e){tmpemail=e;}

void on_envoyer_dialog_2_clicked();

private:
    Ui::Dialog_mailing *ui;
    QString tmpemail;
};

#endif // DIALOG_MAILING_H
