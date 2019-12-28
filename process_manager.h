#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

// 多线程
#include <QThread>
#include "data_define.h"
// 文件夹
#include "folder_manager.h"
#include "memory_manager.h"
#include "disk_manager.h"
// 信号量
#include <semaphore.h>

class ThreadManager
{
public:
    ThreadManager();
    // 两个Manager
    DiskManager dManager;
    FolderManager fManager(DiskManager * dManager);
    MemoryManager mManager(DiskManager * dManager);


    void showFiles();

    void exe_read();

    void deleteFile(FCB *t);




};







#endif // PROCESS_MANAGER_H
