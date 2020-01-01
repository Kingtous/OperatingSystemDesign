#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include "systemwindow.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    //
    void showDialog(QDialog * dialog);

private:
    Ui::MainWindow *ui;
    SystemWindow sysWin;
    CGlobal* cglobal;

    //表格属性
    QStandardItemModel * model;

};

#endif // MAINWINDOW_H
