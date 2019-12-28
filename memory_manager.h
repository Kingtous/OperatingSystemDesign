#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "data_define.h"
#include "disk_manager.h"

class MemoryManager
{
public:
    // 构造函数
    MemoryManager(DiskManager * dManager);

    // 分配内存，分配成功isAlloc <- true.
    int allocMemory(TCB *t);

    // 释放TCB里面的数据
    bool freeBlock(TCB *t);

    // 从内存读取数据，index
    int read(TCB *t,int index);

    // 回写数据
    int writeBack(TCB* t,int index);

    // 读取换出页的数据
    int loadWriteBackData(TCB*t,int index);

};

#endif // MEMORYMANAGER_H
