#ifndef DISK_MONITOR_H
#define DISK_MONITOR_H

#include "data_define.h"
#include "cglobal.h"

#include <QDebug>

#include <QMainWindow>

namespace Ui {
class DiskMonitor;
}

class DiskMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit DiskMonitor(QWidget *parent = nullptr);
    ~DiskMonitor();

private:
    Ui::DiskMonitor *ui;

signals:
    // 通知主线程更新线程
    void needUpdate();

public slots:
    // 刷新内存
    void updateDiskUI();
};

#endif // DISK_MONITOR_H
