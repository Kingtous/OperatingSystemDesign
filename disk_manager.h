#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <queue>
#include "data_define.h"

class DiskManager
{
public:
    //位示图
    BitMapItem Map[1024];
    // 构造函数
    DiskManager();

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
