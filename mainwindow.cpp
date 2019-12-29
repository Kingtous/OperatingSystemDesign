#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QTabWidget>

#include "systemwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1.设置UI界面
    // 设置菜单
    QMenuBar * bar = new QMenuBar();
    bar->setParent(this);
    setMenuBar(bar);
    // 第一个菜单，
    QMenu * menu1 = new QMenu();
    menu1->addAction("关于",[=](){
       QMessageBox  * message = new QMessageBox();
       message->setText("Thread Simulator V1.0\n东北大学秦皇岛分校计科1702班小组作品：\n成员：金韬、杭功茂、王鹏、张伯羽");
       message->addButton("确定",QMessageBox::AcceptRole);
       message->addButton("取消",QMessageBox::DestructiveRole);
       message->show();
    });
    menu1->addAction("退出",[=](){
        // 退出功能
        this->close();
    });
    menu1->setTitle("关于");
    bar->addMenu(menu1);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    this->hide();
    sysWin.show();
}

void MainWindow::showDialog(QDialog *dialog)
{

}
