#include "disk_monitor.h"
#include "ui_disk_monitor.h"

DiskMonitor::DiskMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiskMonitor)
{
    ui->setupUi(this);
    this->setWindowTitle("磁盘监视器");
}

DiskMonitor::~DiskMonitor()
{
    delete ui;
}

void DiskMonitor::updateDiskUI()
{
    qDebug() << "磁盘监视器：更新数据";

}
