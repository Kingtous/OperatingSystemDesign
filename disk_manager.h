#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <queue>
#include "data_define.h"

class DiskManager
{
public:
    BitMapItem Map[32][32];
    // 构造函数   初始化系统
    DiskManager();
    //磁盘分配
    int getBlock(int blocksize);
    //获得盘块的物理地址
    char* GetBlockAddr(int blocknum);
    //获得物理地址的盘块号
    int GetAddrBlock(char* addr);
    //释放盘块
    int ReleaseBlock(int blocknum,int blocksize);
    // 从内存接收对换数据
    int receiveM(FCB * e);

    // 从目录管理接受删除
    int receiveF_delete(FCB * e);

    // 从目录接受添加
    int receiveF_add(string data,string fileName);

    // 从目录中读取
    string receiveF_read(FCB* e);

    // 输出接口，输出位示图，注意：输出当前位示图中的每一个元素，用queue传值
    queue<BitMapItem> getCurrentBitMap();




private:
};

#endif // DISKMANAGER_H
