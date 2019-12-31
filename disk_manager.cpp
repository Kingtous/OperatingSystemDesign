#include "disk_manager.h"

// 初始化函数
DiskManager::DiskManager()
{

}

// 从内存接收对换数据
int DiskManager::receiveM(FCB * e){

}

// 从目录管理接受删除
int DiskManager::receiveF_delete(FCB * e){

}

// 从目录接受添加
int DiskManager::receiveF_add(string data,string fileName){

}

// 从目录中读取
string DiskManager::receiveF_read(FCB* e){

}


// 输出接口，输出位示图，注意：输出当前位示图中的每一个元素，用queue传值
queue<BitMapItem> DiskManager::getCurrentBitMap(){
    queue<BitMapItem> q;
    for (int j =0 ;j<32;j++){
        for(int k =0;k<32;k++){
            BitMapItem item;
            item.x=j;
            item.y=k;
            item.data=User::userName;
            item.isFree = true;
            q.push(item);
        }
    }
    return q;
}
