　#include "folder_manager.h"

FolderManager::FolderManager(DiskManager * dManager)
{
        this->dManager = dManager;
}

// 按照指针指向的FolderElement删除目录项
int FolderManager::deleteData(FCB* element){
        // 删除磁盘中FCB
        this->dManager->receiveF_delete(element);
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
}

// 输出信息：获取所有文件
queue<FCB*> FolderManager::getFiles(){
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
}

// 读取数据
string FolderManager::getData(FCB * element){
    return element->data;
}
