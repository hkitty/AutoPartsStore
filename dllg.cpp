#include "dllg.h"
#include "ui_dllg.h"

Dllg::Dllg(QWidget *parent, QString *string, QStringList *strlst) :
    QDialog(parent),
    ui(new Ui::Dllg)
{


    this->_string = string;
    ui->setupUi(this);
    QStringListIterator it(*strlst);
    it.toFront();
    while ( it.hasNext() ) {
        ui->comboBox->addItem(QString(it.next()));
    }
}

Dllg::~Dllg()
{
    delete ui;
}

void Dllg::on_pushButton_clicked()
{
    *_string = ui->comboBox->currentText();
    QDialog::reject();

}

void Dllg::on_pushButton_2_clicked()
{
    QDialog::reject();
}
