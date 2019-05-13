#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("enaarmen");
        if (!db.open()) {
            QMessageBox::critical(this, "Erreur db open", db.lastError().text());
            return ;
        }
        model = new QSqlTableModel(this);
        model->setTable("users");
        model->select();
        QString *q = new QString("connected on " + db.hostName() + " with userame: " + db.userName() + ".");
        ui->tableView->setHtml((QString) (*q));
}

Widget::~Widget()
{
    delete ui;
}
