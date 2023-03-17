#ifndef DIALOG_H
#define DIALOG_H
#include"etudiant.h"
#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setEtudiant(Etudiant e);
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
