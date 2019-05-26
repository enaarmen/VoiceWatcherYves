#ifndef WIDGET_H
#define WIDGET_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class Widget;
}

class QSqlTableModel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    bool Connect();
    bool PrincipalLayout();
    bool GetNotes(unsigned int, unsigned int, unsigned int);

private slots:
    void on_sauvegarder_clicked();

private:
    Ui::Widget      *ui;
    QSqlTableModel  *model;
    QSqlDatabase    db;
};

#endif // WIDGET_H
