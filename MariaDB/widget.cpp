#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDate>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Connect();
    PrincipalLayout();
    GetNotes(0, 10, 2);
    /*model = new QSqlTableModel(this);
    model->setTable("users");
    model->select();*/

}

Widget::~Widget()
{
    delete ui;
}

bool Widget::Connect() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("enaarmen");
    if (!db.open()) {
        QMessageBox::critical(this, "Erreur db open", db.lastError().text());
        return (false);
    }
    return (true);
}

bool Widget::PrincipalLayout() {
    QString q("connected on " + db.hostName() + " with userame: " + db.userName() + ".");
    //ui->tableView->setHtml(q);
    ui->suivi->setReadOnly(true);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    palette->setColor(QPalette::Text, Qt::darkGray);
    ui->suivi->setPalette(*palette);
    ui->suivi->setHtml(q);
    return (true);
}

bool Widget::GetNotes(unsigned int loadDown, unsigned int loadUp, unsigned int patient) {
    QSqlQuery query;
    QSqlRecord rec;

    query.prepare("select (idnote, FK_IDOrtho, FK_IDPatient, note, date) from notess where idnote >= ? and idnote <= ? and FK_IDPatient == ?;");
    query.addBindValue(loadDown);
    query.addBindValue(loadUp);
    query.addBindValue(patient);
    if (query.exec()) {
        rec = query.record();
        if (rec.count() > 0) {
            for (int i = 0; i < rec.count(); i++) {
                qDebug() << rec.fieldName(i);
                qDebug() << rec.value(i).toString();
            }
            return (true);
        } else {
            qDebug() << "Pas de notes enregistrée.";
        }
    } else
        ui->suivi->setText("Notes could not been loaded: " + db.lastError().text());
    return (false);
}

void Widget::on_Nouveau_clicked()
{

}

void Widget::on_sauvegarder_clicked()
{
    QSqlQuery query;
    QDate     date(QDate::currentDate());

    query.prepare("insert into notes values (0, 1, 2, ?, ?);");
    query.addBindValue(ui->note->toPlainText());
    query.addBindValue(date);
    if (query.exec()) {
        qDebug() << "Insertion reussie.";
        qDebug() << "A la date de: " << date;
    } else
        ui->suivi->setText("Erreur D'insertion de la note: " + db.lastError().text());
}
