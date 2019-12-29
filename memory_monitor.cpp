#include "memory_monitor.h"
#include "ui_memory_monitor.h"

MemoryMonitor::MemoryMonitor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MemoryMonitor)
{
    ui->setupUi(this);
    this->setWindowTitle("内存监视器");
}

MemoryMonitor::~MemoryMonitor()
{
    delete ui;
}

// 刷新UI
void MemoryMonitor::updateMemoryUI()
{
    qDebug() << "内存监视器：更新数据";
    queue<MemoryBlockItem> items = CGlobal::mManager->getCurrentMemoryBlock();
     qDebug() << "内存监视器：更新数据";

}

