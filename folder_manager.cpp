#include "folder_manager.h"

FolderManager::FolderManager(DiskManager * dManager)
{
    this->dManager = dManager;
}


int FolderManager::deleteData(FCB* element){

    // 删除磁盘中FCB
    this->dManager->receiveF_delete(element);
}
