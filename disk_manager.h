#ifndef DISKMANAGER_H
#define DISKMANAGER_H
#define BLOCK_SIZE   4
#define MAX_NUMBER_IN_BLOCK 2
#define MAX_BLOCK_NUMBER 900
#include <queue>
#include "data_define.h"

class DiskManager
{
public:
    //位示图
    BitMapItem Map[1024];
    // 构造函数
    DiskManager();
    //磁盘分配
    int getBlock(int blocksize);
    //释放盘块
    int ReleaseBlock(int blocknum,int blocksize);
    // 从内存接收对换数据
    int receiveM(FCB * e);

    // 从目录管理接受删除
    int receiveF_delete(FCB * e);

    // 从目录接受添加
    int receiveF_add(string data,string fileName);

    // 从目录中读取
    string receiveF_read(FCB* e);

    // 输出接口，输出位示图，注意：输出当前位示图中的每一个元素，用queue传值
    queue<BitMapItem> getCurrentBitMap();

    DIndex_File* DiskManager::indexFile(int filesize);

    int DiskManager::findBlock(int addrss, Index_File *indexfile);




private:
};



//定义一次间址的索引块、二次和三次间址的最后一层索引快；
struct Index_block_three
{
    int blocks[MAX_NUMBER_IN_BLOCK];
};

//定义二次间址的第一个索引块，和三次间址的第二个索引块
struct Index_block_two
{
    Index_block_three *blocks[MAX_NUMBER_IN_BLOCK];
};

//定义三次间址的第一个索引块
struct Index_block_one
{
    Index_block_two *blocks[MAX_NUMBER_IN_BLOCK];
};

//定义混合索引的数据结构
struct Index_File
{
    //文件大小
    int fileSize;
    //定义10个直接地址项
    int addr[10];
    //定义一次间址的地指项
    Index_block_three *addr10;
    //定义二次间址的地址项
    Index_block_two *addr11;
    //定义三次间址的地址项
    Index_block_one *addr12;
};

#endif // DISKMANAGER_H
