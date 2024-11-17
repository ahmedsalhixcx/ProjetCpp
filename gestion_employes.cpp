#include "main_employes.h"
#include "ui_main_employes.h"
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts>
#include <QIntValidator>
#include<QMessageBox>
#include "employes.h"
#include <iostream>
#include <string>
#include<QPropertyAnimation>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include<QTextDocument>
#include<QtPrintSupport/QPrinter>
#include<QByteArray>
#include <QSqlQuery>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QValidator *validator = new QIntValidator(1, 99999999, this);
    ui->lineEdit_ID->setValidator(validator);
    ui->lineEdit_tlf->setValidator(validator);
    ui->lineEdit_id_sup->setValidator(validator);
    ui->lineEdit_recherche->setValidator(validator);
    ui->lineEdit_Adr->setMaxLength(30);
    ui->lineEdit_Nom->setMaxLength(20);
    ui->tab_fournisseur->setModel(SP.afficher());
    //ui->lineEdit_Nom->setValidator(new QRegExpValidator(QRegExp("[A-Z][a-z]*")));

    QRegularExpression rx3("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                         QRegularExpression::CaseInsensitiveOption);
               ui->lineEdit_Adr->setValidator(new QRegularExpressionValidator(rx3, this));


               //Initialize "countdown" label text
                   ui->countdown->setText("1:00");

                   //Connect timer to slot so it gets updated
                   timer = new QTimer();
                   QTime time(0, 1, 0);
                   connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));

                   //It is started with a value of 1000 milliseconds, indicating that it will time out every second.
                   timer->start(0000);



    //animation
    animation= new QPropertyAnimation(ui->pb_supp, "geometry");
    animation->setDuration(2500);
    animation->setStartValue(QRect(800, 500, 150, 50));
    animation->setEndValue(QRect(ui->pb_supp->geometry()));

    animation->start();

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::updateCountdown()
{
    QTime time = QTime::currentTime();
       QString text = time.toString("hh:mm");
       if ((time.second() % 2) == 0)
           text[2] = ' ';
       ui->countdown->setText(time.toString("m:ss"));
}
