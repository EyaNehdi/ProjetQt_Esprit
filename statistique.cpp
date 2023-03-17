#include "statistique.h"
#include "ui_statistique.h"
#include <qvariant.h>
#include <QGridLayout>
#include <QWidget>
#include <QtCore>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <qwindow.h>
#include <QDialog>

statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
}

statistique::~statistique()
{
    delete ui;
}

void stat::choix_pie()
{
    QSqlQuery q1,q2,q3,q4,q5;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0;

    q1.prepare("SELECT * FROM VOL");
    q1.exec();

    q2.prepare("SELECT * FROM VOL WHERE destination='FR'");
    q2.exec();

    q3.prepare("SELECT * FROM VOL WHERE destination='CA'");
    q3.exec();

    q4.prepare("SELECT * FROM VOL WHERE destination='TN'");
    q4.exec();

    q5.prepare("SELECT * FROM VOL WHERE destination='NY'");
    q5.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    while (q5.next()){c4++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
    c4=c4/tot;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("France",c1);
    series->append("Canada",c2);
    series->append("Tunisie",c3);
    series->append("New York",c4);

    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();

    // Used to display the chart
    chartView = new QChartView(chart,ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);
    chartView->show();


}

