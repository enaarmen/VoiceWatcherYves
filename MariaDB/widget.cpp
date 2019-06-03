#include <QSqlTableModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QDate>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    actualOrtho(0),
    actualPatient(0),
    actualLoad(0)
{
    ui->setupUi(this);
    Connect();
    PrincipalLayout();
    //GetNotes(1, 10, 2);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::Connect() {
    db = QSqlDatabase::addDatabase("QMYSQL3");
    db.setHostName("localhost");
    db.setDatabaseName("users_datas");
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
    ui->suivi->setReadOnly(true);
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base, Qt::white);
    palette->setColor(QPalette::Text, Qt::darkGray);
    ui->suivi->setPalette(*palette);
    return (true);
}

bool Widget::checkCredential(unsigned int idOrtho, unsigned int idPatient)
{
    QSqlQuery   query;

    if (!this->actualOrtho)

    query.prepare("select FKID_ortho, FKID_patient from credentials where FKID_ortho = ? and FKID_patient = ?;");
    query.addBindValue(idOrtho);
    query.addBindValue(idPatient);
    if (query.size() == 1)
        return (true);
    else
        return(false);
}

bool Widget::GetNotes(unsigned int patient) {
    QSqlQuery   query;
    int         q;

    if (checkCredential(this->actualOrtho, this->actualPatient)) {
        query.prepare("select note, date from notes where FKID_patient = ? order by date desc limit ?;");
        query.addBindValue(patient);
        query.addBindValue(this->actualLoad);
        if (query.exec()) {
            if ((q = query.size())) {
                while (query.next()) {
                    ui->suivi->append("date: " + query.value(1).toString());
                    ui->suivi->append("note: " + query.value(0).toString());
                    ui->suivi->append("-------------");
                }
                if (q <= 20) {
                    ui->suivi->moveCursor(QTextCursor::MoveOperation::End);
                    this->actualLoad = 20;
                } else {
                    this->actualLoad += 20;
                    ui->suivi->moveCursor(QTextCursor::NoMove);
                }
                return (true);
            } else {
               ui->suivi->append("Pas de notes enregistrée.");
            }
        } else
            ui->suivi->append("Aucune notes a charger.");
    }
    return (false);
}

void Widget::on_sauvegarder_clicked()
{
    QSqlQuery query;
    QDate     date(QDate::currentDate());

    if (checkCredential(this->actualOrtho, this->actualPatient)) {
        query.prepare("insert into notes values (0, ?, ?, ?, ?);");
        query.addBindValue(this->actualPatient);
        query.addBindValue(this->actualOrtho);
        query.addBindValue(ui->note->toPlainText());
        query.addBindValue(date);
        if (query.exec()) {
            ui->suivi->clear();
            ui->note->clear();
            this->actualLoad = 20;
            GetNotes(this->actualPatient);
        } else {
            ui->suivi->clear();
            ui->suivi->append("Erreur D'insertion de la note: " + query.lastError().text());
            ui->suivi->append("Que Voici: " + ui->note->toPlainText() + ".");
        }
    }
}
