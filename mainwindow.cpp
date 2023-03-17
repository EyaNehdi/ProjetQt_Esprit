#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"gestion_voyageur.h"
#include"gestion_vol.h"
#include"gestion_billet.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_b_clicked()
{
     gestion_billet *w =new gestion_billet ;
    w->show();
   this->hide();
}




void MainWindow::on_pushButton_v_clicked()
{

    gestion_vol *w =new gestion_vol ;
    w->show();
   this->hide();

}

void MainWindow::on_pushButton_voy_clicked()
{
    gestion_voyageur *w =new gestion_voyageur ;
   w->show();
  this->hide();
}
