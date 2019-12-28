#ifndef FOLDERMANAGER_H
#define FOLDERMANAGER_H

#include "data_define.h"

class FolderManager
{
public:
    FolderManager();

    // 获取所有文件
    queue<FolderElement*> getFiles();

    // 添加目录项，注意：添加时记得往element里面填写tm时间数据
    bool createFolderElement(FolderElement * element);

    // 按照指针指向的FolderElement删除目录项
    bool deleteFolderElement(FolderElement * element);

};

#endif // FOLDERMANAGER_H
