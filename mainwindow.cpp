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
    this->setWindowTitle("操作系统课程设计");
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
    // 设置要求表格
    model = new QStandardItemModel();
    // 4个要求
    model->setColumnCount(4);
    model->setRowCount(1);
    model->setHeaderData(0,Qt::Horizontal,"置换策略");
    model->setHeaderData(1,Qt::Horizontal,"目录结构");
    model->setHeaderData(2,Qt::Horizontal,"外存组织");
    model->setHeaderData(3,Qt::Horizontal,"空闲磁盘管理");
    // 要求细则
    QStandardItem * item0 = new QStandardItem("全局置换LRU");
    QStandardItem * item1 = new QStandardItem("单级目录");
    QStandardItem * item2 = new QStandardItem("混合索引");
    QStandardItem * item3 = new QStandardItem("位示图");
    item0->setTextAlignment(Qt::AlignCenter);
    item1->setTextAlignment(Qt::AlignCenter);
    item2->setTextAlignment(Qt::AlignCenter);
    item3->setTextAlignment(Qt::AlignCenter);
    model->setItem(0,0,item0);
    model->setItem(0,1,item1);
    model->setItem(0,2,item2);
    model->setItem(0,3,item3);

    // 设置属性
    ui->tv_class->setModel(model);
    ui->tv_class->setRowHeight(0,50);
    ui->tv_class->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tv_class->setEditTriggers(QTableView::NoEditTriggers);
    ui->tv_class->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tv_class->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tv_class->verticalHeader()->hide();

    //初始化全局变量
    cglobal = new CGlobal();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // 将用户名填入全局变量
    if (ui->edit_username->text().trimmed().size() == 0){
        // 不做任何操作
    } else {
      CGlobal::userName = ui->edit_username->text();
    }
    this->hide();
    sysWin.show();
}

void MainWindow::showDialog(QDialog *dialog)
{
    if (dialog != nullptr){
        dialog->exec();
    }
}
