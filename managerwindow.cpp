#include "managerwindow.h"
#include "ui_managerwindow.h"

ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    autoPartsDB = QSqlDatabase::addDatabase("QMYSQL");


    model = new QSqlRelationalTableModel(this, autoPartsDB);
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    autoPartsDB.setHostName("localhost");
    autoPartsDB.setDatabaseName("AutoPartsStore");
    autoPartsDB.setUserName("root");
    autoPartsDB.setPassword("root");

    ui->setupUi(this);

}

ManagerWindow::~ManagerWindow()
{
    autoPartsDB.close();
    delete ui;
}

void ManagerWindow::on_actionExit_triggered()
{
    exit(2);
}

void ManagerWindow::on_actionLogout_triggered()
{

}

void ManagerWindow::on_actionProducts_triggered()
{
    ui->databaseTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowProduct(autoPartsDB);
        QShowProduct.prepare("SELECT * FROM Product");

        if ( !QShowProduct.exec() ) {
            qDebug() << QShowProduct.lastError().text();
        } else {

            model->setTable("Product");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("product_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("product_name"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("product_description"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("product_price"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("product_count"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("manufacturer"));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("country"));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("category"));

            model->setRelation(5, QSqlRelation("Manufacturer", "manufacturer_id", "manufacturer_name"));
            model->setRelation(6, QSqlRelation("Country", "country_id", "country_name"));
            model->setRelation(7, QSqlRelation("Category", "category_id", "category_name"));

            model->select();


            ui->databaseTable->setItemDelegate(new QSqlRelationalDelegate(ui->databaseTable));
            ui->databaseTable->setModel(model);
            ui->databaseTable->update();
        }
    }
    ui->databaseTable->show();
}

void ManagerWindow::on_addButton_clicked()
{
    ui->databaseTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowReceipt(autoPartsDB);
        QShowReceipt.prepare("SELECT * FROM Receipt");

        if ( !QShowReceipt.exec() ) {
            qDebug() << QShowReceipt.lastError().text();
        } else {
            model->setTable("Receipt");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("receipt_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("order_id"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("customer_id"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("product_id"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("out_data"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("count_of_product"));

            model->setRelation(2, QSqlRelation("Customer", "customer_id", "customer_surname"));
            model->setRelation(3, QSqlRelation("Product", "product_id", "product_name"));

            model->select();

            ui->databaseTable->setModel(model);
            ui->databaseTable->update();
        }
    }
    ui->databaseTable->show();
    model->insertRow(model->rowCount());
}

void ManagerWindow::on_pushButton_clicked()
{
    if ( !model->submitAll() ) {
        qDebug() << "Error: " << model->lastError().text();
    }
}
