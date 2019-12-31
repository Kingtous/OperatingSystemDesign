<<<<<<< Updated upstream
　#include "folder_manager.h"
=======
#include "folder_manager.h"
#include "data_define.h"
#include <queue>
>>>>>>> Stashed changes

FolderManager::FolderManager(DiskManager * dManager)
{
        this->dManager = dManager;
<<<<<<< Updated upstream
=======
        for(int i=0;i<128;i++){
            fileTable[i].fileName = "";
            fileTable[i].fileSize = 0;
            fileTable[i].owner = "";
            fileTable[i].type = 0;
            fileLocks[i] = false;
        }

>>>>>>> Stashed changes
}


// 按照指针指向的FolderElement删除目录项
int FolderManager::deleteData(FCB* element){
        // 删除磁盘中FCB
        this->dManager->receiveF_delete(element);
<<<<<<< Updated upstream
        FCB* p;
        p=root->next;
        while(p!=nullptr){
            if(p->next==element){
                p->next=element->next;
                if(free(element)){
                    return 0;
                }
                else{
                    return -1;
                }
            }
            else{
                p=p->next;
            }
        }
=======
        return STATUS_OK;
>>>>>>> Stashed changes
}

// 输出信息：获取所有文件
queue<FCB*> FolderManager::getFiles(){
<<<<<<< Updated upstream
        queue<FCB*> FCB_queue;
        FCB* p;
        p=root->next;
        while(p!=nullptr){
            FCB_queue.push(p);
            p=p->next;
        }
}

// 添加目录项，注意：添加时记得往element里面填写tm时间数据
FCB* FolderManager::generateData(string data,string fileName){
        FCB* p,q;
        p=root->next;
        while(p->next!=nullptr){
            p=p->next;
        }
        q=new(FCB);
        q->createTime=tm;
        q=p->next;
        return q;
=======
        queue<FCB*> q;
        for(int i=0;i<128;i++){
            if(fileTable[i].fileName != ""){
                q.push(&fileTable[i]);
            }
            else continue;
        }
        return q;
}

// 创建新文件，注意：添加时记得往element里面填写tm时间数据
int FolderManager::generateData(string data,string fileName){
        // 获取时间
        for(int i=0;i<128;i++){
            if(fileTable[i].fileName == ""){
                fileTable[i].fileName = fileName;
                time_t t = time(0);
                fileTable[i].createTime = localtime(&t);
                this->dManager->receiveF_add(fileTable[i],fileName);
                break;
            }
        }
        return STATUS_OK;
>>>>>>> Stashed changes
}

// 读取数据
string FolderManager::getData(FCB * element){
<<<<<<< Updated upstream
    return element->data;
=======
    string data_read = this->dManager->receiveF_read(element);
    return data_read;
}
int FolderManager::lockFile(FCB * fcb){
    for(int i=0;i<128;i++){
        if(fcb->fileName == fileTable[i].fileName){
            fileLocks[i] = true;
        }
    }
    return STATUS_OK;
}
int FolderManager::unlockFile(FCB * fcb){
    for(int i=0;i<128;i++){
        if(fcb->fileName == fileTable[i].fileName){
            fileLocks[i] = false;
        }
    }
    return STATUS_OK;
>>>>>>> Stashed changes
}
