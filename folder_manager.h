#ifndef FOLDERMANAGER_H
#define FOLDERMANAGER_H
#include "disk_manager.h"
#include "data_define.h"
#include <time.h>

struct FCB{
    string name;
    string data;
    string Creat_tm;
    FCB *next;
}*root,*now;

class FolderManager
{
public:
    // 暂存磁盘管理的指针变量
    DiskManager * dManager;
    //FCN保存的
    FCB fileTable[128];
    bool fileLocks[128];
    //初始化
    FolderManager* fManager;(DiskManager * dManager);
    // 添加目录项，注意：添加时记得往element里面填写tm时间数据
    int generateData(string data,string fileName);
    // 按照指针指向的FolderElement删除目录项
    int deleteData(FCB* element);
    // 读取数据
    string getData(FCB* element);
<<<<<<< Updated upstream

    // 输出信息：获取所有文件
    queue<FCB*> getFiles();
=======
    // 输出信息：获取所有文件
    queue<FCB*> getFiles();
    //上锁
    int lockFile(FCB * fcb);
    //不上锁
    int unlockFile(FCB * fcb);
>>>>>>> Stashed changes

};

#endif // FOLDERMANAGER_H
