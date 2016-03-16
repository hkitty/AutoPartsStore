#include "admwindow.h"
#include "ui_admwindow.h"

AdmWindow::AdmWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdmWindow)
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

AdmWindow::~AdmWindow()
{
    if ( autoPartsDB.isOpen() )
    {
        autoPartsDB.close();
        autoPartsDB.~QSqlDatabase();
    } else {
        qDebug() << autoPartsDB.lastError().text();
    }
    delete ui;
}

void AdmWindow::on_actionExit_triggered()
{
    exit(0);
}
void AdmWindow::on_productShow_triggered()
{
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

void AdmWindow::on_categoryShow_triggered()
{
    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowCategory(autoPartsDB);
        QShowCategory.prepare("SELECT * FROM Category");

        if ( !QShowCategory.exec() ) {
            qDebug() << QShowCategory.lastError().text();
        } else {

            model->setTable("Category");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("category_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
            model->select();

            ui->databaseTable->setModel(model);
            ui->databaseTable->update();
        }
    }
    ui->databaseTable->show();
}

void AdmWindow::on_countryShow_triggered()
{
    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowCountry(autoPartsDB);
        QShowCountry.prepare("SELECT * FROM Country");

        if ( !QShowCountry.exec() ) {
            qDebug() << QShowCountry.lastError().text();
        } else {

            model->setTable("Country");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("country_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("country_name"));
            model->select();

            ui->databaseTable->setModel(model);
            ui->databaseTable->update();
        }
    }
    ui->databaseTable->show();
}

void AdmWindow::on_manufacturerShow_triggered()
{
    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowManufacturer(autoPartsDB);
        QShowManufacturer.prepare("SELECT * FROM Manufacturer");

        if ( !QShowManufacturer.exec() ) {
            qDebug() << QShowManufacturer.lastError().text();
        } else {

            model->setTable("Manufacturer");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("manufacturer_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("manufacturer_name"));
            model->select();

            ui->databaseTable->setModel(model);
            ui->databaseTable->update();
        }
    }
    ui->databaseTable->show();
}

void AdmWindow::on_receiptShow_triggered()
{
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
}

void AdmWindow::on_customerShow_triggered()
{
    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowCustomer(autoPartsDB);
        QShowCustomer.prepare("SELECT * FROM Customer");

        if ( !QShowCustomer.exec() ) {
            qDebug() << QShowCustomer.lastError().text();
        } else {

            model->setTable("Customer");

            model->setHeaderData(0, Qt::Horizontal, QObject::tr("customer_id"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("first_name"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("second_name"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("city"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("address"));
            model->select();

            ui->databaseTable->setModel(model);
            ui->databaseTable->update();
        }
    }
    ui->databaseTable->show();
}

void AdmWindow::addRow()
{
    model->insertRow(model->rowCount());
}

void AdmWindow::on_pushButton_clicked()
{
    saveChanges();
    addRow();
}

void AdmWindow::saveChanges()
{
    if ( !model->submitAll() ) {
        qDebug() << "Error: " << model->lastError().text();
    }
}

void AdmWindow::on_actionId_triggered()
{
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

void AdmWindow::on_actionName_triggered()
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

void AdmWindow::on_actionPrice_triggered()
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
    QString prodPrice = QInputDialog::getText( 0,
                                         "Price filter",
                                         "Enter price (mask [minPrice maxPrice]):",
                                         QLineEdit::Normal,
                                         "",
                                         &bOk
                                        );
    if (!bOk) {

    } else {

        QStringList price = prodPrice.split(" ");

        if ( !autoPartsDB.open() ) {
            qDebug() << "Open error: " << autoPartsDB.lastError().text();
            return;
        } else {

            QSqlQuery QShowProduct(autoPartsDB);
            QShowProduct.prepare("SELECT * FROM Product WHERE product_price>:prodPrice1 AND product_price<:prodPrice2");
            QShowProduct.bindValue(":prodPrice1", price.at(0));
            QShowProduct.bindValue(":prodPrice2", price.at(1));

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

void AdmWindow::on_actionCount_triggered()
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
    QString prodCount = QInputDialog::getText( 0,
                                         "Count filter",
                                         "Enter count (mask [>\<\= count]):",
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
            QStringList count = prodCount.split(" ");

            if ( count.at(0) == QString::fromStdString("<") ) {
                qDebug() << count.at(0);
                qDebug() << count.at(1);
                QShowProduct.prepare("SELECT * FROM Product WHERE product_count<:prodCount");
                QShowProduct.bindValue(":prodCount", count.at(1));
            } if ( count.at(0) == QString::fromStdString(">") ) {
                qDebug() << count.at(0);
                qDebug() << count.at(1);
                QShowProduct.prepare("SELECT * FROM Product WHERE product_count>:prodCount");
                QShowProduct.bindValue(":prodCount", count.at(1));
            }  if ( count.at(0) == QString::fromStdString("=") ) {
                qDebug() << count.at(0);
                qDebug() << count.at(1);
                QShowProduct.prepare("SELECT * FROM Product WHERE product_count=:prodCount");
                QShowProduct.bindValue(":prodCount", count.at(1));
            } else {  }


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
            ui->databaseTable->show();
        }
    }
}

void AdmWindow::on_actionManufacturer_triggered()
{



    QStringList strnglst;

    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowManufacturer(autoPartsDB);
        QShowManufacturer.prepare("SELECT manufacturer_name FROM Manufacturer");

        if ( !QShowManufacturer.exec() ) {
            qDebug() << QShowManufacturer.lastError().text();
        } else {
            while ( QShowManufacturer.next() ) {
                strnglst.append(QShowManufacturer.value(0).toString());
            }
        }
    }

    QString string;

    Dllg *dlg = new Dllg(0, &string, &strnglst);
    dlg->setModal(true);
    dlg->setWindowTitle("Manufacturer");
    dlg->exec();

    qDebug() << string;

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



    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowProduct(autoPartsDB);
        QShowProduct.prepare("SELECT * FROM Product INNER JOIN Manufacturer ON Product.manufacturer = Manufacturer.manufacturer_id WHERE manufacturer_name=:manName");
        QShowProduct.bindValue(":manName", string);

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

void AdmWindow::on_actionCountry_2_triggered()
{
    QStringList strnglst;

    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowManufacturer(autoPartsDB);
        QShowManufacturer.prepare("SELECT country_name FROM Country");

        if ( !QShowManufacturer.exec() ) {
            qDebug() << QShowManufacturer.lastError().text();
        } else {
            while ( QShowManufacturer.next() ) {
                strnglst.append(QShowManufacturer.value(0).toString());
            }
        }
    }

    QString string;

    Dllg *dlg = new Dllg(0, &string, &strnglst);
    dlg->setModal(true);
    dlg->setWindowTitle("Country");
    dlg->exec();

    qDebug() << string;

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



    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowProduct(autoPartsDB);
        QShowProduct.prepare("SELECT * FROM Product INNER JOIN Country ON Product.country = Country.country_id WHERE country_name=:conName");
        QShowProduct.bindValue(":conName", string);

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

void AdmWindow::on_actionCategory_2_triggered()
{
    QStringList strnglst;

    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowManufacturer(autoPartsDB);
        QShowManufacturer.prepare("SELECT category_name FROM Category");

        if ( !QShowManufacturer.exec() ) {
            qDebug() << QShowManufacturer.lastError().text();
        } else {
            while ( QShowManufacturer.next() ) {
                strnglst.append(QShowManufacturer.value(0).toString());
            }
        }
    }

    QString string;

    Dllg *dlg = new Dllg(0, &string, &strnglst);
    dlg->setModal(true);
    dlg->setWindowTitle("Category");
    dlg->exec();

    qDebug() << string;

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



    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {
        QSqlQuery QShowProduct(autoPartsDB);
        QShowProduct.prepare("SELECT * FROM Product INNER JOIN Category ON Product.category = Category.category_id WHERE category_name=:catName");
        QShowProduct.bindValue(":catName", string);

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

void AdmWindow::on_actionName_Surname_triggered()
{
    model->clear();

    model->setTable("Customer");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("customer_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("customer_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("customer_surname"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("city"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("address"));

    ui->databaseTable->reset();
    ui->databaseTable->setModel(model);
    ui->databaseTable->update();


    bool bOk;
    QString custNameSurname = QInputDialog::getText( 0,
                                         "Search customer",
                                         "Enter customer info(mask [name surname]):",
                                         QLineEdit::Normal,
                                         "",
                                         &bOk
                                        );
    if (!bOk) {

    } else {

        QStringList fullname = custNameSurname.split(" ");

        if ( !autoPartsDB.open() ) {
            qDebug() << "Open error: " << autoPartsDB.lastError().text();
            return;
        } else {

            QSqlQuery QShowProduct(autoPartsDB);
            QShowProduct.prepare("SELECT * FROM Customer WHERE customer_name=:custName AND customer_surname=:custSurname");
            QShowProduct.bindValue(":custName", fullname.at(0));
            QShowProduct.bindValue(":custSurname", fullname.at(1));

            if ( !QShowProduct.exec() ) {
                qDebug() << QShowProduct.lastError().text();
            } else {
                int row = 0;
                while ( QShowProduct.next() ) {

                    qDebug() << QShowProduct.value(0).toString() << " " << QShowProduct.value(1).toString() << " " << QShowProduct.value(2).toString() << " "
                             << QShowProduct.value(3).toString() << " " << QShowProduct.value(4).toString();

                    model->insertRows(row, 1);
                    model->setData(model->index(row, 0), QShowProduct.value(0));
                    model->setData(model->index(row, 1), QShowProduct.value(1));
                    model->setData(model->index(row, 2), QShowProduct.value(2));
                    model->setData(model->index(row, 3), QShowProduct.value(3));
                    model->setData(model->index(row, 4), QShowProduct.value(4));

                    model->submitAll();

                    row++;
                }

                ui->databaseTable->update();
            }
        }
    }
}

void AdmWindow::on_actionCity_triggered()
{
    model->clear();

    model->setTable("Customer");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("customer_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("customer_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("customer_surname"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("city"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("address"));

    ui->databaseTable->reset();
    ui->databaseTable->setModel(model);
    ui->databaseTable->update();


    bool bOk;
    QString custCity = QInputDialog::getText( 0,
                                         "Search customer",
                                         "Enter city:",
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
            QShowProduct.prepare("SELECT * FROM Customer WHERE city=:custCity");
            QShowProduct.bindValue(":custCity", custCity);

            if ( !QShowProduct.exec() ) {
                qDebug() << QShowProduct.lastError().text();
            } else {
                int row = 0;
                while ( QShowProduct.next() ) {

                    qDebug() << QShowProduct.value(0).toString() << " " << QShowProduct.value(1).toString() << " " << QShowProduct.value(2).toString() << " "
                             << QShowProduct.value(3).toString() << " " << QShowProduct.value(4).toString();

                    model->insertRows(row, 1);
                    model->setData(model->index(row, 0), QShowProduct.value(0));
                    model->setData(model->index(row, 1), QShowProduct.value(1));
                    model->setData(model->index(row, 2), QShowProduct.value(2));
                    model->setData(model->index(row, 3), QShowProduct.value(3));
                    model->setData(model->index(row, 4), QShowProduct.value(4));

                    model->submitAll();

                    row++;
                }

                ui->databaseTable->update();
            }
        }
    }
}

void AdmWindow::on_pushButton_2_clicked()
{
    saveChanges();
}

void AdmWindow::on_pushButton_3_clicked()
{
    if ( !autoPartsDB.open() ) {
        qDebug() << "Open error: " << autoPartsDB.lastError().text();
        return;
    } else {

        QSqlQuery QDeleteRecord(autoPartsDB);
        QModelIndex index = ui->databaseTable->currentIndex();

//        int rw = index.row();
        int id = ui->databaseTable->model()->data(index).toInt();
        QDeleteRecord.prepare("DELETE FROM " + model->tableName() + " WHERE " + QString(model->tableName().toLower() + "_id") + "=:id");
        QDeleteRecord.bindValue(":id", id);

        if ( !QDeleteRecord.exec() ) {
            qDebug() << QDeleteRecord.lastError().text();
        } else {
            ui->databaseTable->update();
        }
    }
    saveChanges();
}
