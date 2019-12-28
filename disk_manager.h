#ifndef DISKMANAGER_H
#define DISKMANAGER_H

#include <queue>
#include "data_define.h"

class DiskManager
{
public:
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

private:
};

#endif // DISKMANAGER_H
