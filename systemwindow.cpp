#include "disk_monitor.h"
#include "systemwindow.h"
#include "ui_systemwindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <qpushbutton.h>

SystemWindow::SystemWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindow)
{
    //初始化全局变量
    cglobal = new CGlobal();

    ui->setupUi(this);
    this->setWindowTitle("系统模拟器：计科1702班17-20号作品");
    //全局垂直局部
    QWidget * widget = new QWidget(this);
    this->setCentralWidget(widget);
    QVBoxLayout *layout = new QVBoxLayout();

    // 功能面板
    functionLabel = new QLabel("线程功能列表");
    functionLabel->setAlignment(Qt::AlignCenter);
    btn_gen_data = new QPushButton("创建一个数据生成线程");
    btn_del_data = new QPushButton("创建一个删除数据线程");
    btn_exe_data = new QPushButton("创建一个执行线程");
    // 状态栏显示
    connect(btn_gen_data,SIGNAL(clicked()),SLOT(showBtnTextOnStatusBar()));
    connect(btn_del_data,SIGNAL(clicked()),SLOT(showBtnTextOnStatusBar()));
    connect(btn_exe_data,SIGNAL(clicked()),SLOT(showBtnTextOnStatusBar()));
    // 启动线程
    connect(btn_gen_data,SIGNAL(clicked()),SLOT(createDataGenThread()));
    connect(btn_del_data,SIGNAL(clicked()),SLOT(createDataDelThread()));
    connect(btn_exe_data,SIGNAL(clicked()),SLOT(createDataExeThread()));

    layout->addWidget(functionLabel);
    h1Layout = new QHBoxLayout();
    h1Layout->addWidget(btn_gen_data);
    h1Layout->addWidget(btn_del_data);
    h1Layout->addWidget(btn_exe_data);
    layout->addLayout(h1Layout);

    // 检测面板
    monitorLabel = new QLabel("监视功能列表");
    monitorLabel->setAlignment(Qt::AlignCenter);
    btn_memory_monitor = new QPushButton("内存监控");
    btn_disk_monitor = new QPushButton("磁盘监控（位示图法）");
    h2Layout = new QHBoxLayout();
    layout->addWidget(monitorLabel);
    h2Layout->addWidget(btn_memory_monitor);
    h2Layout->addWidget(btn_disk_monitor);
    layout->addLayout(h2Layout);
    // 状态输出
    connect(btn_memory_monitor,SIGNAL(clicked()),SLOT(showBtnTextOnStatusBar()));
    connect(btn_disk_monitor,SIGNAL(clicked()),SLOT(showBtnTextOnStatusBar()));
    // 信号唤醒UI
    connect(btn_memory_monitor,SIGNAL(clicked()),SLOT(openMemoryMonitor()));
    connect(btn_disk_monitor,SIGNAL(clicked()),SLOT(openDiskMonitor()));
    //最后设置布局
    widget->setLayout(layout);

}

SystemWindow::~SystemWindow()
{
    delete ui;
}

void SystemWindow::showMessageOnStatusBar(QString str)
{
  // 可以用来显示文字
    this->ui->statusbar->showMessage(str);
}

void SystemWindow::showBtnTextOnStatusBar()
{
    this->ui->statusbar->showMessage("进入："+((QPushButton*)sender())->text());
}

// 创建一个数据生成线程
void SystemWindow::createDataGenThread()
{
    GenDataThread *thread = new GenDataThread();
    QObject::connect(thread,SIGNAL(showWaitDialog(QDialog *)),this,SLOT(showDialog(QDialog *)));
    QObject::connect(thread,SIGNAL(closeWaitDialog(QDialog *)),this,SLOT(closeDialog(QDialog *)));
    QObject::connect(thread,SIGNAL(openUI()),this,SLOT(openDataGenUI()));
    thread->start();
    qDebug() <<"数据生成线程启动";
}

void SystemWindow::createDataDelThread()
{
    DelDataThread *thread = new DelDataThread();
    QObject::connect(thread,SIGNAL(showWaitDialog(QDialog *)),this,SLOT(showDialog(QDialog *)));
    QObject::connect(thread,SIGNAL(closeWaitDialog(QDialog *)),this,SLOT(closeDialog(QDialog *)));
    QObject::connect(thread,SIGNAL(openUI()),this,SLOT(openDataDelUI()));
    thread->start();
    qDebug() <<"数据生成线程启动";
}

void SystemWindow::createDataExeThread()
{
    ExeDataThread *thread = new ExeDataThread();
    QObject::connect(thread,SIGNAL(showWaitDialog(QDialog *)),this,SLOT(showDialog(QDialog *)));
    QObject::connect(thread,SIGNAL(closeWaitDialog(QDialog *)),this,SLOT(closeDialog(QDialog *)));
    QObject::connect(thread,SIGNAL(openUI()),this,SLOT(openDataExeUI()));
    //连接信号
    thread->start();
    qDebug() <<"执行线程启动";
}

void SystemWindow::openDataGenUI()
{
    dialog_gen_data * gdata = new dialog_gen_data(this);
    connect(gdata,SIGNAL(dataUpdated()),this,SLOT(updateData()));
    gdata->show();
}

void SystemWindow::openDataDelUI()
{
    dialog_delete_data * ddata = new dialog_delete_data(this);
    connect(ddata,SIGNAL(dataUpdated()),this,SLOT(updateData()));
    ddata->show();
}

void SystemWindow::openDataExeUI()
{
    // 初始化其他
    window_exe_data * exeform = new window_exe_data();
    exeform->show();
}

void SystemWindow::openMemoryMonitor()
{
    qDebug() << "开启内存可视化";
    MemoryMonitor * monitor = new MemoryMonitor(this);
    // 连接信号
    connect(this,SIGNAL(notifyUpdate()),monitor,SLOT(updateMemoryUI()));
    monitor->show();
}

void SystemWindow::openDiskMonitor()
{
    qDebug() << "开启磁盘可视化";
    DiskMonitor * monitor = new DiskMonitor(this);
    connect(this,SIGNAL(notifyUpdate()),monitor,SLOT(updateDiskUI()));
    monitor ->show();
}

void SystemWindow::showDialog(QDialog *dialog)
{
    dialog->show();
}

void SystemWindow::closeDialog(QDialog *dialog)
{
    dialog->close();
}

void SystemWindow::updateMemoryUI()
{
    // 备用
}

void SystemWindow::updateDiskUI()
{
    // 备用
}

void SystemWindow::updateData()
{
    // 通知两个监视器进行更新
    emit notifyUpdate();
}



