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
    ui->tab_employes->setModel(SP.afficher());

    ui->lineEdit_salaire->setMaxLength(20);
    QValidator *validator = new QIntValidator(1, 99999999, this);
    ui->lineEdit_nomE->setMaxLength(30);
    ui->lineEdit_PrenomE->setMaxLength(30);
    ui->lineEdit_mail->setMaxLength(30);
    ui->lineEdit_ID->setValidator(validator);
    ui->lineEdit_id_sup->setValidator(validator);
    ui->lineEdit_recherche->setValidator(validator);
    ui->lineEdit_salaire->setMaxLength(20);
    //ui->tab_fournisseur->setModel(SP.afficher());
    //ui->lineEdit_Nom->setValidator(new QRegExpValidator(QRegExp("[A-Z][a-z]*")));*/

   /* QRegularExpression rx3("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",
                                         QRegularExpression::CaseInsensitiveOption);
               ui->lineEdit_Adr->setValidator(new QRegularExpressionValidator(rx3, this));


               //Initialize "countdown" label text
                   ui->countdown->setText("1:00");

                   //Connect timer to slot so it gets updated
                   timer = new QTimer();
                   QTime time(0, 1, 0);
                   connect(timer, SIGNAL(timeout()), this, SLOT(updateCountdown()));

                   //It is started with a value of 1000 milliseconds, indicating that it will time out every second.
                   timer->start(0000);*/



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
/*void MainWindow::updateCountdown()
{
    QTime time = QTime::currentTime();
       QString text = time.toString("hh:mm");
       if ((time.second() % 2) == 0)
           text[2] = ' ';
       ui->countdown->setText(time.toString("m:ss"));
}*/



void MainWindow::on_pb_ajouter_clicked()
{

       QString nom_employes=ui->lineEdit_nomE->text();
       QString prenom_employes=ui->lineEdit_PrenomE->text();
       int ID=ui->lineEdit_ID->text().toInt();
       QString mail=ui->lineEdit_mail->text(); //mail
       int salaire=ui->lineEdit_salaire->text().toInt(); //salaire
       QString poste=ui->lineEdit_poste->text();//poste
       int hdt=ui->lineEdit_HDT->text().toInt(); //HDT

        QString idString = QString::number(ID);
        QString salaireString = QString::number(salaire);
        QString hdtString = QString::number(hdt);
    QString name = nom_employes;
    QRegExp regex("\\d");
       // Check if ID is valid (positive integer)
          if (ID <= 0) {
              QMessageBox::critical(nullptr, QObject::tr("Invalid ID"),
                                    QObject::tr("L'ID doit être un nombre entier positif."), QMessageBox::Ok);
              return; // Stop if invalid ID
          }else if (idString.isEmpty() || !idString.toInt()) {
              QMessageBox::critical(nullptr, QObject::tr("Invalid ID"),
                                    QObject::tr("L'ID doit être un nombre entier positif et non un caractère."), QMessageBox::Ok);
              return; // Stop if the ID is invalid
          }
          if (salaireString.isEmpty() || !salaireString.toInt()) {
                        QMessageBox::critical(nullptr, QObject::tr("Invalid salaire"),
                                              QObject::tr("Le salaire doit être un nombre entier positif et non un caractère."), QMessageBox::Ok);
                        return; // Stop if the ID is invalid
                    }
          if (hdtString.isEmpty() || !hdtString.toInt()) {
                        QMessageBox::critical(nullptr, QObject::tr("Invalid HDT"),
                                              QObject::tr("Le heure de travail doit être un nombre entier positif et non un caractère."), QMessageBox::Ok);
                        return; // Stop if the ID is invalid
                    }

          if (name.isEmpty() || regex.indexIn(name) != -1) {
              QMessageBox::critical(nullptr, QObject::tr("Invalid Name"),
                                    QObject::tr("Le nom ne doit pas contenir de chiffres ou vide."), QMessageBox::Ok);
              return; // Stop if the name is invalid
          }

          QRegExp emailRegex("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
              if (mail.isEmpty()) {
                  QMessageBox::critical(nullptr, QObject::tr("Email vide"),
                                        QObject::tr("L'email ne peut pas être vide."), QMessageBox::Ok);
                  return; // Stop if email is empty
              } else if (!emailRegex.exactMatch(mail)) {
                  QMessageBox::critical(nullptr, QObject::tr("Email invalide"),
                                        QObject::tr("Veuillez entrer un email valide (exemple@example.com)."), QMessageBox::Ok);
                  return; // Stop if email format is invalid
              }
              if (nom_employes.isEmpty()) {
                  QMessageBox::critical(nullptr, QObject::tr("nom vide"),
                                        QObject::tr("Le nom ne peut pas être vide."), QMessageBox::Ok);
                  return; // Stop if nom is empty
              }
              if (prenom_employes.isEmpty()) {
                  QMessageBox::critical(nullptr, QObject::tr("Prenom vide"),
                                        QObject::tr("Le prenom ne peut pas être vide."), QMessageBox::Ok);
                  return; // Stop if prenom is empty
              }

              if (poste.isEmpty()) {
                  QMessageBox::critical(nullptr, QObject::tr("poste vide"),
                                        QObject::tr("Le poste ne peut pas être vide."), QMessageBox::Ok);
                  return; // Stop if poste is empty
              }

          //int x=0;

         //std::string id_a = std::to_string(id_);
         // std::string m = mail.toStdString();


         /* if (nom_employe=="")
          {
              QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                          QObject::tr("Nom n'est pas vide"), QMessageBox::Ok);
                    x++;
          }*/



          /*else if (m.find("@gmail.com")== std:: string::npos)
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
          }*/


           //if(x==0)
          {
          employes Sp(nom_employes,prenom_employes,ID,mail,salaire,poste,hdt);
          bool toTest =Sp.Ajouter();
          if(toTest)
          {
              ui->tab_employes->setModel(SP.afficher());//refresh
              QMessageBox::information(nullptr, QObject::tr("Ajout employe"),
                                QObject::tr(" ajout employe avec succès"), QMessageBox::Ok);
                                //ui->tab_fournisseur->setModel(Sp.afficher());
          }else{
              QMessageBox::critical(nullptr, QObject::tr("ajout non effectué"),
                                    QObject::tr("ajout failed.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);




      }
          ui->lineEdit_ID->clear();
          ui->lineEdit_nomE->clear();
          ui->lineEdit_PrenomE->clear();
          ui->lineEdit_mail->clear();
          ui->lineEdit_salaire->clear();
          ui->lineEdit_HDT->clear();
          ui->lineEdit_poste->clear();




          }


}
/*void MainWindow::on_pb_recherche_clicked()
{
    employes Sp;
    Sp.set_ID(ui->lineEdit_recherche->text().toInt());
    bool test=Sp.RechercheemployesParID(Sp.get_ID());
    QMessageBox msgbox;

    if (test)
       {
        msgbox.setText("ID existe");
        ui->tab_employes->setModel(Sp.afficher());
        }
    else
        msgbox.setText("ID n'existe pas");
        msgbox.exec();
        ui->lineEdit_recherche->clear();
}*/

void MainWindow::on_pb_supp_clicked()
{
    employes Sp;
    int ID = ui->lineEdit_id_sup->text().toInt();
    bool test=Sp.supprimer(ID);
    QMessageBox msgbox;

    if (test)
       {
        ui->tab_employes->setModel(SP.afficher());//refrech

        msgbox.setText("Suppression avec succes");
        ui->tab_employes->setModel(Sp.afficher());////////////////////////////
        }
    else
        msgbox.setText("failed");
        msgbox.exec();
        ui->lineEdit_id_sup->clear();
}
void MainWindow::on_pb_modifier_clicked()
{
    QString NOM=ui->lineEdit_nomE->text();
    QString PRENOM=ui->lineEdit_PrenomE->text();
    int ID=ui->lineEdit_ID->text().toInt();
    QString MAIL=ui->lineEdit_mail->text(); //mail
    int SALAIRE=ui->lineEdit_salaire->text().toInt(); //salaire
    QString POSTE=ui->lineEdit_poste->text();//poste
    int HDT=ui->lineEdit_HDT->text().toInt(); //HDT
    QString idString = QString::number(ID);
    QString salaireString = QString::number(SALAIRE);
    QString hdtString = QString::number(HDT);

    employes Sp;
    bool test = Sp.modifier(NOM, PRENOM,ID, MAIL, SALAIRE, POSTE, HDT);


    QMessageBox msgbox;
    if (test) {
        msgbox.setText("Modification réussie.");
        ui->tab_employes->setModel(SP.afficher());//refrech
    } else {
        msgbox.setText("Échec de la modification.");
    }
    msgbox.exec();

    // Clear the input fields
    ui->lineEdit_nomE->clear();
    ui->lineEdit_PrenomE->clear();
    ui->lineEdit_ID->clear();
    ui->lineEdit_mail->clear();
    ui->lineEdit_salaire->clear();
    ui->lineEdit_poste->clear();
    ui->lineEdit_HDT->clear();
}



void MainWindow::on_pb_recherche_clicked() {
    // Retrieve the ID from the search input field `lineEdit_recherche`
    int searchId = ui->lineEdit_recherche->text().toInt();

    // Call the `searchById` function of the `employes` class
    QSqlQueryModel *model = SP.search(searchId);

    // Set the model to the table view to display the results
    ui->tab_employes->setModel(model);

    // Optionally handle cases where no results are found
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Search", "No employee found with the given ID.");
    }
}
void MainWindow::on_pb_trier_clicked() {
    QSqlQueryModel *model = SP.sortBySalaire();

    ui->tab_employes->setModel(model); // Set the model
    ui->tab_employes->reset();// Forces the view to refresh


    // Set the model to the table view with sorted data



    // Show a message box to inform the user
    QMessageBox::information(this, QObject::tr("Tri"),
                             QObject::tr("Les employés ont été triés par salaire."));
}
void MainWindow::on_pb_pdf_clicked() {
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer en tant que PDF", QDir::homePath(), "PDF Files (*.pdf)");
    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".pdf", Qt::CaseInsensitive)) {
            filePath.append(".pdf");  // Add .pdf extension if missing
        }
        if (SP.exportToPDF(filePath)) {
            QMessageBox::information(this, QObject::tr("Export PDF"),
                                     QObject::tr("Données exportées avec succès en PDF."));
        } else {
            QMessageBox::critical(this, QObject::tr("Erreur d'export PDF"),
                                   QObject::tr("Échec de l'exportation des données en PDF."));
        }
    }
}

void MainWindow::on_pb_showStatsButton_clicked()
{       // Add a stacked widget in your UI file and access it via ui->stackedWidget

    // Create an instance of Employe class
    employes employe;

    // Call the function to generate the pie chart
    employe.statistique(this);
}
void MainWindow::on_pb_qr_clicked()
{
    QRCodeDialog dialog(this);  // Create an instance of the dialog
    dialog.setWindowTitle("Generate Employee QR Code");
    dialog.exec();  // Show the dialog
}

