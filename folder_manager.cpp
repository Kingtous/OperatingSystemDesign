#include "folder_manager.h"

FolderManager::FolderManager(DiskManager * dManager)
{
    this->dManager = dManager;
}

// 按照指针指向的FolderElement删除目录项
int FolderManager::deleteData(FCB* element){

    // 删除磁盘中FCB
    this->dManager->receiveF_delete(element);
    return STATUS_ERR;
}

// 输出信息：获取所有文件
queue<FCB*> FolderManager::getFiles(){
    // FCB模拟
    queue<FCB*> q;
    int i=10;
    while(i--){
        FCB* fcb = new FCB();
        fcb->type = 0;
        fcb->owner = "jintao";
        fcb->fileName = "文件";
        time_t timep;
        fcb->createTime = localtime(&timep);
        q.push(fcb);
    }
    return q;
}

// 添加目录项，注意：添加时记得往element里面填写tm时间数据
FCB* FolderManager::generateData(string data,string fileName){
    return nullptr;
}

// 读取数据
string FolderManager::getData(FCB * element){


}
