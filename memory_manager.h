#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "data_define.h"

class MemoryManager
{
public:
    // 构造函数
    MemoryManager();

    // 分配内存块
    bool allocBlock();
    // 释放内存块
    bool freeBlock();



};

#endif // MEMORYMANAGER_H
