#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlDatabase>
#include <QMainWindow>

#define q2c(string) string.toStdString()

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void connectDatabase();
    bool DoQuery(QString & query, QSqlDatabase & db);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
