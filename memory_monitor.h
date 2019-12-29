#ifndef MEMORY_MONITOR_H
#define MEMORY_MONITOR_H

#include <QMainWindow>
#include "cglobal.h"
#include <QDebug>

namespace Ui {
class MemoryMonitor;
}

class MemoryMonitor : public QMainWindow
{
    Q_OBJECT

public:
    explicit MemoryMonitor(QWidget *parent = nullptr);
    ~MemoryMonitor();

signals:
    // 通知主线程更新线程
    void needUpdate();

public slots:
    // 刷新内存
    void updateMemoryUI();


private:
    Ui::MemoryMonitor *ui;
};

#endif // MEMORY_MONITOR_H
