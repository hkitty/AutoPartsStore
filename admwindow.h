#ifndef ADMWINDOW_H
#define ADMWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QInputDialog>
#include "dllg.h"

namespace Ui {
class AdmWindow;
}

class AdmWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdmWindow(QWidget *parent = 0);
    ~AdmWindow();

private slots:
    void on_actionExit_triggered();

    void on_productShow_triggered();

    void on_categoryShow_triggered();

    void on_countryShow_triggered();

    void on_manufacturerShow_triggered();

    void on_receiptShow_triggered();

    void on_customerShow_triggered();

    void addRow();

    void on_pushButton_clicked();

    void saveChanges();

    void on_actionId_triggered();

    void on_actionName_triggered();

    void on_actionPrice_triggered();

    void on_actionCount_triggered();

    void on_actionManufacturer_triggered();

    void on_actionCountry_2_triggered();

    void on_actionCategory_2_triggered();

    void on_actionName_Surname_triggered();

    void on_actionCity_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::AdmWindow *ui;

    QSqlDatabase autoPartsDB;
    QSqlRelationalTableModel *model;
};

#endif // ADMWINDOW_H
