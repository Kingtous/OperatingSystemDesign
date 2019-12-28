#include "memory_manager.h"
// 构造函数
MemoryManager::MemoryManager(DiskManager * dManager)
{

}

// 分配内存，分配成功isAlloc <- true.
int MemoryManager::allocMemory(TCB *t){

}

// 释放TCB里面的数据
bool MemoryManager::freeBlock(TCB *t){

}

// 从内存读取数据，index
int MemoryManager::read(TCB *t,int index){

}

// 回写数据
int MemoryManager::writeBack(TCB* t,int index){

}

// 读取换出页的数据
int MemoryManager::loadWriteBackData(TCB*t,int index){

}
