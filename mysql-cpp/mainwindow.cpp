#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>

#include <iostream>

/*#include <winsock.h>
#include <MYSQL/mysql.h>*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("enaarmen");
    db.setDatabaseName("users_datas");
    db.setPort(3306);// peut etre a enlever
    if (db.open()) {
        std::cout << "You are now connected at " << q2c(db.databaseName()) << std::endl;
        std::cout << "insertion of name: guigui" << std::endl;
        QSqlQuery query;
        query.prepare("insert (name, email, password, group) values (:name, :email, :password, :group) INTO users");
        query.bindValue(":name", QString("guigui"));
        query.bindValue(":email", QString("guigui@guigui.com"));
        query.bindValue(":password", QString("gougou"));
        query.bindValue(":group", QString("ortho"));
        if (query.exec()) {
            std::cout << "you been inserted " << std::endl;
            QSqlQuery get("select * from users", db);
            QSqlRecord rec = get.record();
            std::cout << "Nombre de colones: " << rec.count();
            int nameCol = rec.indexOf("name");
            while (get.next())
                std::cout << "NAME: " << q2c(get.value(nameCol).toString()) << std::endl;
        } else
            std::cout << "no insertion. error: " << q2c(query.lastError().text()) << std::endl;
        db.close();
    } else {
        std::cout << "Connection failed" << std::endl << q2c(db.lastError().text()) << std::endl;
    }

}
/*
bool MainWindow::DoQuery(QString & query_str, QSqlDatabase & db) {
    QSqlQuery query(query_str, db);
    return (true);
}
*/
