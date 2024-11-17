#include "employes.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QByteArray>
#include<map>
#include<QSqlRecord>
#include <QFile>
#include <QSqlError>
#include <QTextDocument>
#include <QPrinter>
#include <QtWidgets/QWidget>
#include <QtCharts>
#include <QtNetwork>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

employes::employes()
{
     nom_employes="";
     prenom_employes="";
     ID=0;
     mail="";
     salaire=0;
     poste="";
     hdt=0;

}
employes::employes(QString nom_employes,QString prenom_employes,int ID,QString mail,int salaire,QString poste,int hdt)
{
    this->nom_employes=nom_employes;
    this->prenom_employes=prenom_employes;
    this->ID=ID;
    this->mail=mail;
    this->salaire=salaire;
    this->poste=poste;
    this->hdt=hdt;

}

QString employes::get_Nom()
{
    return nom_employes;
}
QString employes::get_prenom()
{
    return prenom_employes;
}
int employes::get_ID()
{
    return ID;
}
QString employes::get_mail()
{
    return mail;
}
int employes::get_salaire()
{
    return salaire;
}
QString employes::get_poste()
{
    return poste;
}
int employes::get_hdt()
{
    return hdt;
}

// setters
void employes::set_Nom(QString nom_employes)
{
    this->nom_employes=nom_employes;
}
void employes::set_prenom(QString prenom_employes)
{
    this->prenom_employes=prenom_employes;
}
void employes::set_ID(int ID)
{
    this->ID=ID;
}
void employes::set_mail(QString mail)
{
    this->mail=mail;
}
void employes::set_salaire(int salaire)
{
    this->salaire=salaire;
}
void employes::set_poste(QString poste)
{
    this->poste=poste;
}
void employes::set_hdt(int hdt)
{
    this->hdt=hdt;
}


bool employes::Ajouter()
{

    QSqlQuery query;
    QString id_string= QString::number(ID);

    query.prepare("INSERT INTO Employe(NOM, PRENOM, ID, MAIL, SALAIRE, POSTE, HDT)"
                  "VALUES (:NOM, :PRENOM, :ID, :MAIL, :SALAIRE, :POSTE, :HDT)");

          query.bindValue(":NOM", get_Nom());
          query.bindValue(":PRENOM", get_prenom());
          query.bindValue(":ID", get_ID());
          query.bindValue(":MAIL", get_mail());
          query.bindValue(":SALAIRE", get_salaire());
          query.bindValue(":POSTE", get_poste());
          query.bindValue(":HDT", get_hdt());



         return query.exec();
}


bool employes::modifier(QString NOM, QString PRENOM, int ID, QString MAIL, int SALAIRE, QString POSTE, int HDT)
{
    QSqlQuery query;
    query.prepare("UPDATE AHMED.EMPLOYE SET NOM = :NOM, PRENOM = :PRENOM, POSTE = :POSTE, "
                  "SALAIRE = :SALAIRE, HDT = :HDT, MAIL = :MAIL WHERE ID = :ID");


    if (ID <= 0 || NOM.isEmpty() || PRENOM.isEmpty() || POSTE.isEmpty() || SALAIRE < 0 || HDT < 0 || MAIL.isEmpty()) {
           qDebug() << "Update Error: Invalid input data.";
           return false;
       }
    // Bind values to the query
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ID", ID); // Use ID to find the record
    query.bindValue(":MAIL", MAIL);
    query.bindValue(":SALAIRE", SALAIRE);
    query.bindValue(":POSTE", POSTE);
    query.bindValue(":HDT", HDT);


    // Execute the query and return the result
    if (!query.exec()) {
           qDebug() << "Update Employe Error:" << query.lastError().text();
           return false;
       }
       return true;
    return true;
}

QSqlQueryModel* employes::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM AHMED.EMPLOYE");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("POSTE"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("HDT"));


    return model;
}

bool employes::supprimer(int ID)
{
    QSqlQuery query;

    if (ID <= 0 ) {
           qDebug() << "Update Error: Invalid input data.";
           return false;
       }
    query.prepare("DELETE FROM AHMED.EMPLOYE WHERE ID = :ID");
          query.bindValue(":ID",ID);

         return query.exec();
}



QSqlQueryModel* employes::search(int searchId) {
    QSqlQueryModel *model = new QSqlQueryModel();

    // SQL query to search across NOM, PRENOM, and POSTE fields
    QString queryStr = "SELECT * FROM EMPLOYE WHERE ID = :id";

        QSqlQuery query;
        query.prepare(queryStr);
        query.bindValue(":id", searchId); // Bind the ID valueartial matching

    if (query.exec()) {
        model->setQuery(query);

        // Optionally set column headers for your table
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("POSTE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("HDT"));

    } else {
        qDebug() << "Error in query execution: " << query.lastError();
    }

    return model;
}
/*bool employes::RechercheemployesParID(int IDrecherche)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM Fournisseur WHERE id=:IDrecherche");
    query.bindValue(":IDrecherche",IDrecherche);
    query.exec();
    if (!query.first()){
        return false;
    }
    else
    {
        int nID = query.record().indexOf("ID");
        int nNom=query.record().indexOf("nom_employes");
        int nPrenom=query.record().indexOf("prenom_employes");
        int nMail=query.record().indexOf("mail");
        int nSalaire=query.record().indexOf("Salaire");
        int nPoste=query.record().indexOf("Poste");
        int nHDT=query.record().indexOf("HDT");

        nom_employes=query.value(nNom).toString();
        prenom_employes=query.value(nPrenom).toString();

        ID=query.value(nID).toInt();
        mail=query.value(nMail).toString();
        salaire=query.value(nSalaire).toInt();
        poste=query.value(nPoste).toString();
        hdt=query.value(nHDT).toInt();


        return true;
    }

}
*/

QSqlQueryModel* employes::sortBySalaire() {
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT  NOM, PRENOM, ID, MAIL, SALAIRE, POSTE, HDT FROM EMPLOYE ORDER BY SALAIRE ASC");

    // Set column headers
    if (model->lastError().isValid()) {
            qDebug() << "Query Error: " << model->lastError().text();
        } else {
            qDebug() << "Query executed successfully.";
        }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POSTE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("HDT"));

    return model;
}
bool employes::exportToPDF(const QString &filePath) {
    QTextDocument document;
    QString htmlContent;

    // Prepare an HTML table to structure the data
    htmlContent.append("<h1>Rapport des Employés</h1>");
    htmlContent.append("<table border='1' cellspacing='0' cellpadding='2'>");
    htmlContent.append("<tr><th>NOM</th><th>PRENOM</th><th>ID</th><th>MAIL</th><th>SALAIRE</th><th>POSTE</th><th>HDT</th></tr>");

    QSqlQuery query("SELECT NOM, PRENOM, ID, MAIL, SALAIRE, POSTE, HDT FROM EMPLOYE");
    while (query.next()) {
        htmlContent.append("<tr>");
        htmlContent.append("<td>" + query.value("NOM").toString() + "</td>");
        htmlContent.append("<td>" + query.value("PRENOM").toString() + "</td>");
        htmlContent.append("<td>" + query.value("ID").toString() + "</td>");
        htmlContent.append("<td>" + query.value("MAIL").toString() + "</td>");
        htmlContent.append("<td>" + query.value("SALAIRE").toString() + "</td>");
        htmlContent.append("<td>" + query.value("POSTE").toString() + "</td>");
        htmlContent.append("<td>" + query.value("HDT").toString() + "</td>");
        htmlContent.append("</tr>");
    }
    htmlContent.append("</table>");

    document.setHtml(htmlContent);

    // Set up the printer for PDF output
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    // Print the document to the specified PDF file
    document.print(&printer);

    return true;  // Return true to indicate success
}
void employes::statistique(QWidget *parent)
{
    // Create a new QWidget for the pie chart window
    QWidget *pieChartWindow = new QWidget(parent);
    pieChartWindow->setWindowTitle("Poste Statistics Pie Chart");
    pieChartWindow->resize(800, 600);

    // Create the chart view to display the pie chart
    QChartView *chartView = new QChartView(pieChartWindow);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Create the chart
    QChart *chart = new QChart();
    QPieSeries *pieSeries = new QPieSeries();

    // SQL query to get Poste and its recurrence count
    QSqlQuery query;
    QString queryString = "SELECT POSTE, COUNT(*) AS Recurrence FROM EMPLOYE GROUP BY POSTE ORDER BY Recurrence DESC";

    // Execute the query and populate the pie series
    if (query.exec(queryString)) {
        while (query.next()) {
            QString poste = query.value(0).toString();
            int recurrence = query.value(1).toInt();

            pieSeries->append(poste, recurrence);
        }

        // Add the series to the chart
        chart->addSeries(pieSeries);
        chart->setTitle("Poste Recurrence Distribution");

        // Add labels to the slices
        for (QPieSlice *slice : pieSeries->slices()) {
            slice->setLabelVisible();
        }

        // Set the chart to the chart view
        chartView->setChart(chart);

        // Add chart view to the pie chart window layout
        QVBoxLayout *layout = new QVBoxLayout(pieChartWindow);
        layout->addWidget(chartView);
        pieChartWindow->setLayout(layout);

        // Show the pie chart window
        pieChartWindow->show();
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
}

/*bool employes::sendEmail(QString NOM, QString PRENOM, QString MAIL, QString MESSAGE)
{
    // Basic validation of email and message
    if (MAIL.isEmpty() || MESSAGE.isEmpty()) {
        qDebug() << "Error: Invalid email or message.";
        return false;
    }

    // SMTP server details (for Gmail)
    QString smtpServer = "smtp.gmail.com"; // SMTP server for Gmail
    int smtpPort = 587;  // Use 587 for TLS (Transport Layer Security)
    QString smtpUsername = "ahmedsalhixcx@gmail.com";  // Your email address (from where the email will be sent)
    QString smtpPassword = "nour59262";  // Your email password (or app-specific password if using 2FA)

    // Construct the email message
    QByteArray emailMessage = "From: " + smtpUsername.toUtf8() + "\r\n"
                              "To: " + MAIL.toUtf8() + "\r\n"
                              "Subject: Email from " + NOM.toUtf8() + " " + PRENOM.toUtf8() + "\r\n"
                              "\r\n" + MESSAGE.toUtf8();

    // Create a QNetworkAccessManager
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // Set up the request to the SMTP server (using a standard POST request to send an email)
    QUrl url("smtp://" + smtpServer);
    QNetworkRequest request(url);

    // Add authentication header (SMTP requires basic authentication)
    request.setRawHeader("Authorization", "Basic " + QByteArray::fromBase64(QString(smtpUsername + ":" + smtpPassword).toUtf8()));

    // Send the email request (simplified, as sending email over SMTP is more complex)
    QNetworkReply *reply = manager->post(request, emailMessage);

    // Connect signal to lambda function (explicit connection syntax)
    connect(reply, SIGNAL(finished()), this, SLOT(onEmailFinished(reply)));

    return true;  // Simulate successful email sending
}

// Slot for handling email sending result
// Slot for handling email sending result (no parameters)
void employes::onEmailFinished()
{
    // Get the sender (the QNetworkReply* object)
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (!reply) {
        qDebug() << "Error: No valid reply object.";
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Email sending failed:" << reply->errorString();
    } else {
        qDebug() << "Email sent successfully!";
    }

    reply->deleteLater();  // Clean up the reply object
}*/
