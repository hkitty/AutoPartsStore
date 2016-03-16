#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <managerwindow.h>
#include <admwindow.h>
#include <cashierwindow.h>
#include <QFile>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_pushButton_clicked();

    int isLogin(QString userLogin, QString userPassword);

private:
    Ui::MainWindow *ui;

    QString login;
    QString password;

    QSqlDatabase accountsDB = QSqlDatabase::addDatabase("QSQLITE");
};

#endif // MAINWINDOW_H
