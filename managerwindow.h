#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QValidator>

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = 0);
    ~ManagerWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionLogout_triggered();

    void on_actionProducts_triggered();

    void on_addButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::ManagerWindow *ui;

    QSqlDatabase autoPartsDB;
    QSqlRelationalTableModel *model;
};

#endif // MANAGERWINDOW_H
