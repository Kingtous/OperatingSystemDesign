#include "memory_manager.h"

#include <QString>
// 构造函数
MemoryManager::MemoryManager(DiskManager * dManager)
{

}

// 分配内存，分配成功isAlloc <- true.并且修改TCB中的block内存号
int MemoryManager::allocMemory(TCB *t){

}

// 释放TCB里面的数据
bool MemoryManager::freeBlock(TCB *t){

}

// 从内存读取数据，需要将strIndex/4转成页号
string MemoryManager::read(TCB *t,int pageIndex){

}

// 回写数据，需要将strIndex/4转成页号
int MemoryManager::writeBack(TCB* t,int pageIndex){

}

// 读取换出页的数据，需要将strIndex/4转成页号
int MemoryManager::loadWriteBackData(TCB*t,int pageIndex){

}

// 输出当前MemoryBlock的状态
queue<MemoryBlockItem> MemoryManager::getCurrentMemoryBlock(){
    // 以下为测试数据
    queue<MemoryBlockItem> q;
    MemoryBlockItem items[16];
    for (int i =0;i<16;i++){
        items[i].id=i;
        items[i].data=QString::number(QRandomGenerator::global()->bounded(256)).toStdString();
        if(i%2==0){
            items[i].isFree = true;
        } else {
            items[i].isFree = false;
        }
        q.push(items[i]);
    }
    return q;
}
