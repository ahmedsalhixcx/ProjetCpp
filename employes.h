#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQueryModel>
#include <QImage>
#include <QSqlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>


class employes
{
public:
    employes();
    employes(QString,QString,int,QString,int,QString,int);
    QString get_Nom();
    QString get_prenom();
    int get_ID();
    QString get_mail();
    int get_salaire();
    QString get_poste();
    int get_hdt();



    void set_Nom(QString);
    void set_prenom(QString);
    void set_ID(int);
    void set_mail(QString);
    void set_salaire(int);
    void set_poste(QString);
    void set_hdt(int);

    bool Ajouter();
    bool modifier(QString nom, QString prenom, int ID, QString mail, int salaire, QString poste, int hdt);
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool RechercheemployesParID(int IDrecherche);
    QSqlQueryModel* sortBySalaire();
    QSqlQueryModel* search(int searchId);
    bool exportToPDF(const QString &filePath);
    void statistique(QWidget *parent);
    bool sendEmail(QString NOM, QString PRENOM, QString MAIL, QString MESSAGE);
    void onEmailFinished();




   // QSqlQueryModel *tri_ID();
   // QSqlQueryModel *tri_nom();


private:
    int ID,salaire,hdt;
    QString nom_employes,prenom_employes,mail,poste;

};

#endif // EMPLOYES_H
