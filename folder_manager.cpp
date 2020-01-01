#include "folder_manager.h"
#include "data_define.h"
#include <queue>

FolderManager::FolderManager(DiskManager * dManager)
{
        this->dManager = dManager;
        for(int i=0;i<128;i++){
            fileTable[i] = new FCB();
            fileTable[i]->fileName = "";
            fileTable[i]->fileSize = 0;
            fileTable[i]->owner = "";
            fileTable[i]->type = 0;
            fileLocks[i] = false;
        }

}


// 按照指针指向的FolderElement删除目录项
int FolderManager::deleteData(FCB* element){
        // 删除磁盘中FCB
        this->dManager->receiveF_delete(element);
        return STATUS_OK;
}

// 输出信息：获取所有文件
queue<FCB*> FolderManager::getFiles(){
        queue<FCB*> q;
        for(int i=0;i<128;i++){
            if(fileTable[i]->fileName != ""){
                q.push(fileTable[i]);
            }
            else continue;
        }
        return q;
}

// 创建新文件，注意：添加时记得往element里面填写tm时间数据
int FolderManager::generateData(string data,string fileName){
        for(int k=0;k<128;k++){
            if(fileTable[k]->fileName == fileName){
                return STATUS_SAME_FILE;
            }
        }
        // 获取时间
        for(int i=0;i<128;i++){
            if(this->fileTable[i]->fileName == ""){
                this->fileTable[i]->fileName = fileName;
                int a;
                a = data.size();
                int b;
                if(a%4 == 0){
                    b = a/4;
                }
                else b = (a/4)+1;
                this->fileTable[i]->fileSize = b;
                time_t t = time(0);
                this->fileTable[i]->createTime = localtime(&t);
                //fileTable[i]->owner = User::userName;
                this->dManager->receiveF_add(this->fileTable[i],data);
                return STATUS_OK;

            }
        }
        return STATUS_OK;
}

// 读取数据
string FolderManager::getData(FCB * element){
    string data_read = this->dManager->receiveF_read(element);
    return data_read;
}
int FolderManager::lockFile(FCB * fcb){
    for(int i=0;i<128;i++){
        if(fcb->fileName == fileTable[i]->fileName){
            this->fileLocks[i] = true;
        }
    }
    return STATUS_OK;
}
int FolderManager::unlockFile(FCB * fcb){
    for(int i=0;i<128;i++){
        if(fcb->fileName == fileTable[i]->fileName){
            this->fileLocks[i] = false;
        }
    }
    return STATUS_OK;
}
