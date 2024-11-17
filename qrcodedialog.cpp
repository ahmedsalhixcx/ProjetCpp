#include "qrcodedialog.h"
#include "ui_qrcodedialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>

QRCodeDialog::QRCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRCodeDialog)
{
    ui->setupUi(this);
}

QRCodeDialog::~QRCodeDialog()
{
    delete ui;
}
void QRCodeDialog::on_pushButton_generate_clicked()
{
    QString id = ui->lineEdit_ID->text();  // Get employee ID from input

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter an employee ID.");
        return;
    }

    // Fetch employee data from the database
    QString employeeData = getEmployeeDataByID(id);
    if (employeeData.isEmpty()) {
        QMessageBox::warning(this, "Error", "No employee found with the given ID.");
        return;
    }

    // Generate QR code for the employee data
    QPixmap qrPixmap = generateQRCode(employeeData);

    // Display the QR code in the label
    ui->label_QRCode->setPixmap(qrPixmap);
}
// Slot for QR code generation
// Fetch employee data by ID from the database
QString QRCodeDialog::getEmployeeDataByID(const QString &id)
{
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, ID, MAIL, SALAIRE, POSTE, HDT FROM EMPLOYE WHERE ID = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to query the database: " + query.lastError().text());
        return QString();
    }

    if (query.next()) {
        // Format the employee data into a string
        QString employeeData = QString("ID: %1\nName: %2 %3\nEmail: %4\nSalary: %5\nPosition: %6\nHDT: %7")
                               .arg(query.value("ID").toString())   // Employee ID
                               .arg(query.value("NOM").toString())  // Employee Last Name
                               .arg(query.value("PRENOM").toString())  // Employee First Name
                               .arg(query.value("MAIL").toString())  // Employee Email
                               .arg(query.value("SALAIRE").toString())  // Employee Salary
                               .arg(query.value("POSTE").toString())  // Employee Position
                               .arg(query.value("HDT").toString());  // Employee Hire Date

        return employeeData;
    }

    return QString();  // Return an empty string if no data is found
}
QPixmap QRCodeDialog::generateQRCode(const QString &data)
{
    using namespace qrcodegen;

    QrCode qr = QrCode::encodeText(data.toUtf8().constData(), QrCode::Ecc::LOW);
    const int size = qr.getSize();

    QImage image(size, size, QImage::Format_RGB32);
    image.fill(Qt::white);  // Fill background with white

    // Draw the QR code
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            QColor color = qr.getModule(x, y) ? Qt::black : Qt::white;
            image.setPixelColor(x, y, color);
        }
    }

    // Scale up the QR code for better visibility
    return QPixmap::fromImage(image.scaled(200, 200, Qt::KeepAspectRatio));
}
