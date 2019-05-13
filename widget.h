#ifndef WIDGET_H
#define WIDGET_H


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

private:
    Ui::Widget *ui;
    QSqlTableModel *model;
    QSqlDatabase db;
};

#endif // WIDGET_H
