#ifndef DISKMANAGER_H
#define DISKMANAGER_H
#define BLOCK_SIZE   4
#include <queue>
#include "data_define.h"


class DiskManager
{
public:
    //磁盘空间
    string disk[1024];
    //位示图
    BitMapItem Map[1024];
    // 构造函数
    DiskManager();
    //删除对换区数据
    int deleteBlock(FCB *e);
    //磁盘分配
    int changeBlock(FCB *e,string dt,int number);
    //释放盘块
    int ReleaseBlock(FCB *e);
    // 从内存接收对换数据
    int receiveM(FCB * e,int pageNumber,string data);

    // 从目录管理接受删除
    int receiveF_delete(FCB * e);

    // 从目录接受添加
    int receiveF_add(FCB *e,string data);

    // 从目录中读取
    string receiveF_read(FCB* e);

    // 输出接口，输出位示图，注意：输出当前位示图中的每一个元素，用queue传值
    queue<BitMapItem> getCurrentBitMap();

    Index_File* indexFile(FCB *e);

};



#endif // DISKMANAGER_H
