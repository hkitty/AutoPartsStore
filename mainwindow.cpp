#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    accountsDB.setDatabaseName("Accounts.sqlite");
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    exit(1);
}

void MainWindow::on_pushButton_clicked()
{
    if ( !ui->loginEdit->text().isEmpty() && !ui->passwordEdit->text().isEmpty() ) {
        login = ui->loginEdit->text();
        password = ui->passwordEdit->text();

        switch (isLogin(login, password)) {
        case 0: {
            AdmWindow *aw = new AdmWindow();
            aw->show();
            break;
        }
        case 1: {
            ManagerWindow *mw = new ManagerWindow();
            mw->show();
            break;
        }
        case 2: {
            QFile file(login);
            if (file.open(QIODevice::Append)) {
                QTextStream out(&file);
                out << "\n" << "Login on " << QDateTime::currentDateTime().toString();
            }
            file.close();

            CashierWindow *cw = new CashierWindow(login);
            cw->show();
            break;
        }
        case 254: {
            QMessageBox::critical(0, "Login error", "User not found!");
            break;
        }
        case 255: {
            QMessageBox::critical(0, "Database error", "Check database connection!");
            break;
        }
        default: {
            QMessageBox::critical(0, "Login error", "Unknown error!");
            break;
        }
        }
    } else {
        QMessageBox::critical(0, "Login error", "Fill in all the fields!");
    }
}

int MainWindow::isLogin(QString userLogin, QString userPassword)
{
    if ( !accountsDB.open() ) {
        return 255;
    } else {
        QSqlQuery loginQuery(accountsDB);

        loginQuery.prepare("SELECT accessRights FROM Users WHERE login=:login AND password=:password");
        loginQuery.bindValue(":login", userLogin);
        loginQuery.bindValue(":password", userPassword);

        if ( !loginQuery.exec() ) {
            qDebug() << "Login error: " << loginQuery.lastError().text();
            return 254;
        } else {
            while ( loginQuery.next() ) {
                qDebug()  << "Access rights: " << loginQuery.value(0).toInt();;
                return loginQuery.value(0).toInt();
            }
        }
    }
    return 254;
}
