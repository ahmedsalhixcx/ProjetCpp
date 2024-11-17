#include "main_fournisseur.h"
#include "ui_main_fournisseur.h"
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
#include "fournisseur.h"
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
//Ajouter
void MainWindow::on_pb_ajouter_clicked()
{


    int ID=ui->lineEdit_ID->text().toInt();
    QString nom_fournisseur=ui->lineEdit_Nom->text();
    QString adresse=ui->lineEdit_Adr->text();
    int tlf=ui->lineEdit_tlf->text().toInt();

       int x=0;

       std::string str_phone = std::to_string(tlf);
       std::string m = adresse.toStdString();


       if (nom_fournisseur=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Nom n'est pas vide"), QMessageBox::Ok);
                 x++;
       }



       else if (m.find("@gmail.com")== std:: string::npos)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("L'e-mail doit se terminer par @gmail.com"), QMessageBox::Ok);
                 x++;
       }

       else if (str_phone.length()!=8)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le numéro de téléphone doit être composé de 8 chiffres"), QMessageBox::Ok);
                 x++;
       }


       else if(x==0)
       {
       Fournisseur Sp(ID,nom_fournisseur,adresse,tlf);
       bool toTest =Sp.Ajouter();
       if(toTest)
       {
           QMessageBox::information(nullptr, QObject::tr("Ajout Fournisseur"),
                             QObject::tr(" ajout Fournisseur avec succès"), QMessageBox::Ok);
                             ui->tab_fournisseur->setModel(Sp.afficher());
       }
       ui->lineEdit_ID->clear();
       ui->lineEdit_Nom->clear();
       ui->lineEdit_Adr->clear();
       ui->lineEdit_tlf->clear();



       }

}
//recherche
void MainWindow::on_pb_recherche_clicked()
{
    Fournisseur Sp;
    Sp.set_ID(ui->lineEdit_recherche->text().toInt());
    bool test=Sp.RechercheFournisseurParID(Sp.get_ID());
    QMessageBox msgbox;

    if (test)
       {
        msgbox.setText("ID existe");
        ui->tab_fournisseur->setModel(Sp.afficher());
        }
    else
        msgbox.setText("ID n'existe pas");
        msgbox.exec();
        ui->lineEdit_recherche->clear();
}
//suprrimer
void MainWindow::on_pb_supp_clicked()
{
    Fournisseur Sp;
    Sp.set_ID(ui->lineEdit_id_sup->text().toInt());
    bool test=Sp.supprimer(Sp.get_ID());
    QMessageBox msgbox;

    if (test)
       {
        msgbox.setText("Suppression avec succes");
        ui->tab_fournisseur->setModel(Sp.afficher());
        }
    else
        msgbox.setText("failed");
        msgbox.exec();
        ui->lineEdit_id_sup->clear();
}
//modifier
void MainWindow::on_pb_modifier_clicked()
{
    int ID=ui->lineEdit_ID->text().toInt();
    QString nom_fournisseur=ui->lineEdit_Nom->text();
    QString adresse=ui->lineEdit_Adr->text();
    int tlf=ui->lineEdit_tlf->text().toInt();


       int x=0;

       std::string str_phone = std::to_string(tlf);
       std::string m = adresse.toStdString();



       if (nom_fournisseur=="")
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Nom n'est pas vide"), QMessageBox::Ok);
                 x++;
       }



       else if (m.find("@gmail.com")== std:: string::npos)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("L'e-mail doit se terminer par @gmail.com"), QMessageBox::Ok);
                 x++;
       }

       else if (str_phone.length()!=8)
       {
           QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                       QObject::tr("Le numéro de téléphone doit être composé de 8 chiffres"), QMessageBox::Ok);
                 x++;
       }


       else if(x==0)
       {
       Fournisseur Sp(ID,nom_fournisseur,adresse,tlf);
       bool toTest =Sp.modifier();
       if(toTest)
       {
           QMessageBox::information(nullptr, QObject::tr("Editing Fournisseur"),
                             QObject::tr("Fournisseur modifier avec succes"), QMessageBox::Ok);
       }
       ui->lineEdit_Nom->clear();
       ui->lineEdit_Adr->clear();
       ui->lineEdit_tlf->clear();



       }
}
//new
void MainWindow::on_actionNew_triggered()
{
    ui->lineEdit_ID->clear();
    ui->lineEdit_Nom->clear();
    ui->lineEdit_Adr->clear();
    ui->lineEdit_tlf->clear();


}
//exit
void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}






//pdf dans le dossier build
void MainWindow::on_actionGen_rer_PDF_triggered()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_fournisseur->model()->rowCount();
                const int columnCount =ui->tab_fournisseur->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor= #fffde0  link=#fffde0>\n"

                            "<h1 >Liste des Fournisseurs</h1> <br></br> <br> </br>  "

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#fffde0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_fournisseur->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_fournisseur->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_fournisseur->isColumnHidden(column)) {
                                   QString data = ui->tab_fournisseur->model()->data(ui->tab_fournisseur->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("mypdffile.pdf");
        document->print(&printer);
}

//Trier
void MainWindow::on_radioButton_id_clicked()
{
    Fournisseur *Sp = new Fournisseur();
     ui->tab_fournisseur->setModel(Sp->tri_ID());
}

void MainWindow::on_radioButton_nom_clicked()
{
    Fournisseur *Sp = new Fournisseur();
     ui->tab_fournisseur->setModel(Sp->tri_nom());
}



//stats
void MainWindow::on_actionStatistiques_triggered()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                            model->setQuery("select * from Fournisseur where id < 10 ");
                            float tarif1=model->rowCount();
                            model->setQuery("select * from Fournisseur where id  between 1 and 15 ");
                            float tarif2=model->rowCount();
                            model->setQuery("select * from Fournisseur where TARIF >10 ");
                            float tarif3=model->rowCount();
                            float total=tarif1+tarif2+tarif3;
                            QString a=QString("moins de 10 Fournisseur "+QString::number((tarif1*100)/total,'f',2)+"%" );
                            QString b=QString("entre 10 et 15 Fournisseur "+QString::number((tarif2*100)/total,'f',2)+"%" );
                            QString c=QString("+10 Fournisseur "+QString::number((tarif3*100)/total,'f',2)+"%" );
                            QPieSeries *series = new QPieSeries();
                            series->append(a,tarif1);
                            series->append(b,tarif2);
                            series->append(c,tarif3);
                    if (tarif1!=0)
                    {QPieSlice *slice = series->slices().at(0);
                     slice->setLabelVisible();
                     slice->setPen(QPen());}
                    if ( tarif2!=0)
                    {
                             // Add label, explode and define brush for 2nd slice
                             QPieSlice *slice1 = series->slices().at(1);
                             //slice1->setExploded();
                             slice1->setLabelVisible();
                    }
                    if(tarif3!=0)
                    {
                             // Add labels to rest of slices
                             QPieSlice *slice2 = series->slices().at(2);
                             //slice1->setExploded();
                             slice2->setLabelVisible();
                    }
                            // Create the chart widget
                            QChart *chart = new QChart();
                            // Add data to chart with title and hide legend
                            chart->addSeries(series);
                            chart->setTitle("Pourcentage Par Fournisseur :Nombre Des Fournisseurs "+ QString::number(total));
                            chart->legend()->hide();
                            // Used to display the chart
                            QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);
                            chartView->resize(1000,500);
                            chartView->show();


         //end statistique
}








