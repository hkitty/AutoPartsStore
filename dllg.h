#ifndef DLLG_H
#define DLLG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class Dllg;
}

class Dllg : public QDialog
{
    Q_OBJECT

public:
    explicit Dllg(QWidget *parent = 0, QString *string = 0, QStringList *strlst = 0);
    ~Dllg();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dllg *ui;
    QString *_string;
};

#endif // DLLG_H
