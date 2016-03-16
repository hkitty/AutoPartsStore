#include "cashierwindow.h"
#include "ui_cashierwindow.h"

CashierWindow::CashierWindow(QString login, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CashierWindow)
{
    lgn = login;
    autoPartsDB = QSqlDatabase::addDatabase("QMYSQL");


    model = new QSqlRelationalTableModel(this, autoPartsDB);
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    autoPartsDB.setHostName("localhost");
    autoPartsDB.setDatabaseName("AutoPartsStore");
    autoPartsDB.setUserName("root");
    autoPartsDB.setPassword("root");

    ui->setupUi(this);
}

CashierWindow::~CashierWindow()
{

    delete ui;
}

void CashierWindow::on_actionExit_triggered()
{
    QFile file(lgn);
    if ( file.open(QIODevice::Append) ) {
        QTextStream out(&file);
        out << "\n" << "Login off " << QDateTime::currentDateTime().toString();
    }
    file.close();
    exit(3);
}

void CashierWindow::on_actionID_triggered()
{
    model->clear();

    bool bOk;
    QString prodID = QInputDialog::getText( 0,
                                         "Search ID",
                                         "Enter ID:",
                                         QLineEdit::Normal,
                                         "",
                                         &bOk
                                        );
    if (!bOk) {

    } else {
        if ( !autoPartsDB.open() ) {
            qDebug() << "Open error: " << autoPartsDB.lastError().text();
            return;
        } else {
            QSqlQuery QShowProduct(autoPartsDB);
            QShowProduct.prepare("SELECT * FROM Product WHERE product_id=:prodID");
            QShowProduct.bindValue(":prodID", prodID.toInt());

            if ( !QShowProduct.exec() ) {
                qDebug() << QShowProduct.lastError().text();
            } else {
                int row = 0;
                while ( QShowProduct.next() ) {

                    qDebug() << QShowProduct.value(0).toString() << " " << QShowProduct.value(1).toString() << " " << QShowProduct.value(2).toString() << " "
                             << QShowProduct.value(3).toString() << " " << QShowProduct.value(4).toString() << " " << QShowProduct.value(5).toString() << " "
                             << QShowProduct.value(6).toString() << " " << QShowProduct.value(7).toString();



                    model->setTable("Product");
                    model->setHeaderData(0, Qt::Horizontal, QObject::tr("product_id"));
                    model->setHeaderData(1, Qt::Horizontal, QObject::tr("product_name"));
                    model->setHeaderData(2, Qt::Horizontal, QObject::tr("product_description"));
                    model->setHeaderData(3, Qt::Horizontal, QObject::tr("product_price"));
                    model->setHeaderData(4, Qt::Horizontal, QObject::tr("product_count"));
                    model->setHeaderData(5, Qt::Horizontal, QObject::tr("manufacturer"));
                    model->setHeaderData(6, Qt::Horizontal, QObject::tr("country"));
                    model->setHeaderData(7, Qt::Horizontal, QObject::tr("category"));



                    model->insertRows(row, 1);
                    model->setData(model->index(row, 0), QShowProduct.value(0));
                    model->setData(model->index(row, 1), QShowProduct.value(1));
                    model->setData(model->index(row, 2), QShowProduct.value(2));
                    model->setData(model->index(row, 3), QShowProduct.value(3));
                    model->setData(model->index(row, 4), QShowProduct.value(4));
                    model->setData(model->index(row, 5), QShowProduct.value(5));
                    model->setData(model->index(row, 6), QShowProduct.value(6));
                    model->setData(model->index(row, 7), QShowProduct.value(7));

                    model->setRelation(5, QSqlRelation("Manufacturer", "manufacturer_id", "manufacturer_name"));
                    model->setRelation(6, QSqlRelation("Country", "country_id", "country_name"));
                    model->setRelation(7, QSqlRelation("Category", "category_id", "category_name"));
                    model->submitAll();

                    row++;


                }

                ui->databaseTable->setItemDelegate(new QSqlRelationalDelegate(ui->databaseTable));
                ui->databaseTable->setModel(model);
                ui->databaseTable->update();
            }
        }
        ui->databaseTable->show();
    }
}

void CashierWindow::on_actionOrder_triggered()
{
    model->clear();

    bool bOk;
    QString ordID = QInputDialog::getText( 0,
                                         "Search order",
                                         "Enter orderID:",
                                         QLineEdit::Normal,
                                         "",
                                         &bOk
                                        );
    if (!bOk) {

    } else {
        if ( !autoPartsDB.open() ) {
            qDebug() << "Open error: " << autoPartsDB.lastError().text();
            return;
        } else {
            QSqlQuery QShowProduct(autoPartsDB);
            QShowProduct.prepare("SELECT * FROM Receipt WHERE order_id=:ordID");
            QShowProduct.bindValue(":ordID", ordID.toInt());

            if ( !QShowProduct.exec() ) {
                qDebug() << QShowProduct.lastError().text();
            } else {
                int row = 0;
                while ( QShowProduct.next() ) {

                    qDebug() << QShowProduct.value(0).toString() << " " << QShowProduct.value(1).toString() << " " << QShowProduct.value(2).toString() << " "
                             << QShowProduct.value(3).toString() << " " << QShowProduct.value(4).toString() << " " << QShowProduct.value(5).toString();

                    model->setQuery(QShowProduct);

                    model->setTable("Receipt");
                    model->setHeaderData(0, Qt::Horizontal, QObject::tr("receipt_id"));
                    model->setHeaderData(1, Qt::Horizontal, QObject::tr("order_id"));
                    model->setHeaderData(2, Qt::Horizontal, QObject::tr("customer_id"));
                    model->setHeaderData(3, Qt::Horizontal, QObject::tr("product_id"));
                    model->setHeaderData(4, Qt::Horizontal, QObject::tr("out_data"));
                    model->setHeaderData(5, Qt::Horizontal, QObject::tr("count_of_product"));

//                    model->setTable("Receipt");

//                    model->insertRows(row, 1);
                    model->setData(model->index(row, 0), QShowProduct.value(0));
                    model->setData(model->index(row, 1), QShowProduct.value(1));
                    model->setData(model->index(row, 2), QShowProduct.value(2));
                    model->setData(model->index(row, 3), QShowProduct.value(3));
                    model->setData(model->index(row, 4), QShowProduct.value(4));
                    model->setData(model->index(row, 5), QShowProduct.value(5));
                    model->setFilter("order_id =" + ordID);
                    model->select();

                    model->setRelation(2, QSqlRelation("Customer", "customer_id", "customer_surname"));
                    model->setRelation(3, QSqlRelation("Product", "product_id", "product_name"));
                    model->submitAll();

                    row++;


                }

                    ui->databaseTable->setItemDelegate(new QSqlRelationalDelegate(ui->databaseTable));
                ui->databaseTable->setModel(model);
                ui->databaseTable->update();
            }
        }
        ui->databaseTable->show();
    }
}

void CashierWindow::on_pushButton_clicked()
{
    QFile file(model->data(model->index(0, 1)).toString());
    if ( file.open(QIODevice::Append | QIODevice::Truncate) ) {
        QTextStream out(&file);

        for (int i = 0; i < model->rowCount(); i++) {
            out << model->data(model->index(i, 3)).toString() << "x" << model->data(model->index(i, 5)).toString()
                << "\n";
        }
        out << model->data(model->index(0, 2)).toString() << "\n" << model->data(model->index(0, 1)).toString()
            << " " << model->data(model->index(0, 4)).toString();
    }


    file.close();
}

void CashierWindow::on_actionName_triggered()
{
    model->clear();

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

    ui->databaseTable->reset();
    ui->databaseTable->setModel(model);
    ui->databaseTable->update();

    bool bOk;
    QString prodName = QInputDialog::getText( 0,
                                         "Search name",
                                         "Enter name:",
                                         QLineEdit::Normal,
                                         "",
                                         &bOk
                                        );
    if (!bOk) {

    } else {
        if ( !autoPartsDB.open() ) {
            qDebug() << "Open error: " << autoPartsDB.lastError().text();
            return;
        } else {
            QSqlQuery QShowProduct(autoPartsDB);
            QShowProduct.prepare("SELECT * FROM Product WHERE product_name LIKE :prodName");
            QShowProduct.bindValue(":prodName", QString(prodName + "%"));

            if ( !QShowProduct.exec() ) {
                qDebug() << QShowProduct.lastError().text();
            } else {
                int row = 0;
                while ( QShowProduct.next() ) {

                    qDebug() << QShowProduct.value(0).toString() << " " << QShowProduct.value(1).toString() << " " << QShowProduct.value(2).toString() << " "
                             << QShowProduct.value(3).toString() << " " << QShowProduct.value(4).toString() << " " << QShowProduct.value(5).toString() << " "
                             << QShowProduct.value(6).toString() << " " << QShowProduct.value(7).toString();


                    model->insertRows(row, 1);
                    model->setData(model->index(row, 0), QShowProduct.value(0));
                    model->setData(model->index(row, 1), QShowProduct.value(1));
                    model->setData(model->index(row, 2), QShowProduct.value(2));
                    model->setData(model->index(row, 3), QShowProduct.value(3));
                    model->setData(model->index(row, 4), QShowProduct.value(4));
                    model->setData(model->index(row, 5), QShowProduct.value(5));
                    model->setData(model->index(row, 6), QShowProduct.value(6));
                    model->setData(model->index(row, 7), QShowProduct.value(7));

                    model->submitAll();

                    row++;
                }

                ui->databaseTable->update();
            }
        }
    }
}
