#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0, QString *string = 0, QStringList *strlst = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    QString *_string;
};

#endif // DIALOG_H
