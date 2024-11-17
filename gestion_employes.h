/*#ifndef GESTION_EMPLOYES_H
#define GESTION_EMPLOYES_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Gestion_employes; }
QT_END_NAMESPACE

class Gestion_employes : public QMainWindow
{
    Q_OBJECT

public:
    Gestion_employes(QWidget *parent = nullptr);
    ~Gestion_employes();

private:
    Ui::Gestion_employes *ui;
};
#endif // GESTION_EMPLOYES_H
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<employes.h>

#include<QPropertyAnimation>
#include<QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supp_clicked();
    void on_pb_modifier_clicked();
    void updateCountdown();

    void on_actionNew_triggered();

    void on_actionExit_triggered();



    void on_lineEdit_recherche_textChanged();

    void on_pb_recherche_clicked();

    void on_actionGen_rer_PDF_triggered();

    void on_radioButton_id_clicked();

    void on_radioButton_nom_clicked();



    void on_actionStatistiques_triggered();

    void on_pushButton_2_clicked();

    void on_lineEdit_ID_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
    employes SP;
    QPropertyAnimation *animation;
    QTimer *timer;
};

#endif // MAINWINDOW_H
