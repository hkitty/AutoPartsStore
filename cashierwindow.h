#ifndef CASHIERWINDOW_H
#define CASHIERWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QInputDialog>
#include <QFile>
#include <QDateTime>

namespace Ui {
class CashierWindow;
}

class CashierWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CashierWindow(QString login, QWidget *parent = 0);
    ~CashierWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionID_triggered();

    void on_actionOrder_triggered();

    void on_pushButton_clicked();

    void on_actionName_triggered();

private:
    Ui::CashierWindow *ui;

    QString lgn;
    QSqlDatabase autoPartsDB;
    QSqlRelationalTableModel *model;
};

#endif // CASHIERWINDOW_H
