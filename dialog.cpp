#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent, QString *string, QStringList *strlst) :
    QDialog(parent),
    ui(new Ui::Dialog)
{


    this->_string = string;
    ui->setupUi(this);
    QStringListIterator it(*strlst);
    it.toFront();
    while ( it.hasNext() ) {
        ui->comboBox->addItem(QString(it.next()));
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    *_string = ui->comboBox->currentText();
    QDialog::reject();

}

void Dialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}
