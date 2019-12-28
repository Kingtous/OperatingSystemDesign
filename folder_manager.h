#ifndef FOLDERMANAGER_H
#define FOLDERMANAGER_H

#include "data_define.h"
#include "disk_manager.h"

class FolderManager
{
public:
    // 暂存磁盘管理的指针变量
    DiskManager * dManager;


    FolderManager(DiskManager * dManager);

    // 输出信息：获取所有文件
    queue<FCB*> getFiles();

    // 添加目录项，注意：添加时记得往element里面填写tm时间数据
    FCB* generateData(string data,string fileName);

    // 按照指针指向的FolderElement删除目录项
    int deleteData(FCB* element);

    // 读取数据
    string getData(FCB * element);
};

#endif // FOLDERMANAGER_H
