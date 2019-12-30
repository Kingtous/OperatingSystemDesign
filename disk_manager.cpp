#include "disk_manager.h"
#include <string.h>
#include <stdlib.h>
#define BlockNum     1024      //磁盘块的数目(编号从0开始)
#define BlockSize    4         //磁盘块大小
#define SystemSize   1024*4     //磁盘总容量
#define exchange_x   (900-1)/32       //对换区首址x
#define exchange_y   (900-1)%32       //对换区首址y
#define BLOCK_SIZE   4
// 初始化函数
DiskManager::DiskManager()
{
    //分配1024*4B空间

    for(int i=0;i<1024;i++){
        Map[i].isFree = true;
        Map[i].x = (i-1)/32;
        Map[i].y = (i-1)%32;
        disk[i] = nullData;
    }
}
int DiskManager::deleteBlock(FCB *e){
    for(int i=900;i<1024;i++){
        if(e->fileName == this->Map[i].fileName){
            this->Map[i].isFree = true;
            this->Map[i].fileName = nullName;
            this->Map[i].data = nullData;
            this->disk[i] = nullData;
        }
    }
    return STATUS_OK;
}
//对换区磁盘分配
int DiskManager::changeBlock(FCB *e,string dt,int number){
    int sum = 0;
    for(int i=900;i<1024;i++){
        if(this->Map[i].isFree == true){
            if(sum==0)
            sum++;
            this->Map[i].fileName = e->fileName;
            this->Map[i].data = dt;
            this->Map[i].pageNumber = number;
            this->disk[i] = dt;
        }
        else sum=0;
    }
    return STATUS_BUSY;
}
//释放盘块
int DiskManager::ReleaseBlock(FCB *e){
    for(int i=0;i<1024;i++){
        if(e->fileName == this->Map[i].fileName){
            this->Map[i].isFree = true;
            this->Map[i].fileName = nullName;
            this->Map[i].data = nullData;
            this->disk[i] = nullData;
        }
    }
    return STATUS_OK;
}
// 从内存接收对换数据
int DiskManager::receiveM(FCB * e,int pageNumber,string data){
    for(int i=900;i<1024;i++){
        if(pageNumber == this->Map[i].pageNumber){
            return STATUS_OK;
            break;
        }
    }
    changeBlock(e,data,pageNumber);
    return STATUS_OK;
}

// 从目录管理接受删除
int DiskManager::receiveF_delete(FCB * e){
    for(int i=0;i<900;i++){
        if(Map[i].fileName == e->fileName){
            Map[i].isFree = true;
            Map[i].fileName = nullName;
            Map[i].data = nullData;
            disk[i] = nullData;
        }
    }
    return STATUS_OK;
}

// 从目录接受添加
int DiskManager::receiveF_add(FCB *e,string data){
    Index_File* iFile = indexFile(e);
    int b[10];
    int a;
    for(int i=0;i<10;i++){
        b[i] = iFile->addr[i];
    }
    e->iFile = iFile;
    a = data.size();

}

// 从目录中读取
string DiskManager::receiveF_read(FCB* e){
    int b[10];
    for(int i=0;i<10;i++){
        b[i] = e->iFile->addr[i];
    }
    int sum = 0;
    for(int i=0;i<10;i++){
        if(b[i] != -1)sum++;
    }
    string a = "";
    for(int j=0;j<sum;j++){
        a = a + Map[a[j]].data;
    }
    return a;
}


// 输出接口，输出位示图，注意：输出当前位示图中的每一个元素，用queue传值
queue<BitMapItem> DiskManager::getCurrentBitMap(){
    queue<BitMapItem> q;
    for(int i=0;i<1024;i++)q.push(this->Map[i]);
    return q;
}

//生成第三层索引，并并根据blocks赋值，
Index_block_three* indexBlockThree(int blocks[],int start,int end)
{
    Index_block_three * ans = (Index_block_three*) malloc(sizeof(Index_block_three));
    int j = 0;
    for(int i = start; i < end; i++)
    {
        ans->blocks[j++] = blocks[i];
    }
    return ans;
}
//生成第二层索引
Index_block_two* indexBlockTwo(int blocks[],int start,int end)
{
    //计算生成几个第三层索引
    int num = (end - start) % MAX_NUMBER_IN_BLOCK == 0? (end - start) / MAX_NUMBER_IN_BLOCK : (end - start) / MAX_NUMBER_IN_BLOCK + 1;
    //生成第二层索引
    Index_block_two *ans = (Index_block_two *) malloc (sizeof(Index_block_two));
    //生成num第三层索引
    for(int i = 0; i < num; i++)
    {
        if(i != num -1)
            ans->blocks[i] = indexBlockThree(blocks,start + i * MAX_NUMBER_IN_BLOCK,start + (i + 1) * MAX_NUMBER_IN_BLOCK);
        else
            ans->blocks[i] = indexBlockThree(blocks,start + i * MAX_NUMBER_IN_BLOCK,end);
    }
    return ans;
}

Index_block_one* indexBlockOne(int blocks[],int start,int end)
{
    //计算二层索引块的个数
    int num = (end - start) % (MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK) == 0 ?
    (end - start) / (MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK) :
    (end - start) / (MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK) + 1 ;
    Index_block_one *ans = (Index_block_one*) malloc(sizeof(Index_block_one));
    //生成num个二层索引的块
    for(int i = 0; i < num; i++)
    {
        if(i != num - 1)
            ans->blocks[i] = indexBlockTwo(blocks,start + i * MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK,start + (i + 1) * MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK);
        else
            ans->blocks[i] = indexBlockTwo(blocks,start + i * MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK,end);
    }
    return ans;
}

//给定一个文件的长度，给出模拟分配占用的磁盘块的情况
 Index_File* DiskManager::indexFile(FCB *e)
 {
     int filesize = (e->fileSize)*4;
     //计算该文件需要多少盘块
     int block_num = filesize % BLOCK_SIZE == 0 ? filesize / BLOCK_SIZE : filesize / BLOCK_SIZE + 1;
     //定义保存所有盘块号的数组
     int *blocks = (int *) malloc(sizeof(int) * block_num);
     //初始化数组
     memset(blocks,0,sizeof(int) * block_num);


     //模拟系统分配空闲盘块号
     srand(time(NULL));
     for(int i = 0; i < block_num; i++)
     {
         int temp = rand() % MAX_BLOCK_NUMBER;
         while(this->Map[temp].isFree = false)
         {
            temp = rand() % MAX_BLOCK_NUMBER;
         }
         this->Map[temp].isFree = false;
         blocks[i] = temp;
     }


     Index_File *indexfile = new Index_File();
     indexfile->fileSize = filesize;
     indexfile->fileName = e->fileName;
     //直接地址
     if(block_num <= 10)
     {
        for(int i = 0; i < block_num; i++)
        {
            indexfile->addr[i] = blocks[i];
        }
     }
     //一次间址
     else if(block_num <= MAX_NUMBER_IN_BLOCK + 10)
     {
        for(int i = 0; i < 10; i++)
        {
            indexfile->addr[i] = blocks[i];
        }
        indexfile->addr10 = indexBlockThree(blocks,10,block_num);
     }
     //二次间址
     else if(block_num <= MAX_NUMBER_IN_BLOCK * (MAX_NUMBER_IN_BLOCK + 1) + 10)
     {
        for(int i = 0; i < 10; i++)
        {
            indexfile->addr[i] = blocks[i];
        }
        indexfile->addr10 = indexBlockThree(blocks,10,MAX_NUMBER_IN_BLOCK + 10);
        indexfile->addr11 = indexBlockTwo(blocks,MAX_NUMBER_IN_BLOCK+10,block_num);
     }
     //三次间址
     else if(block_num <= MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK + MAX_NUMBER_IN_BLOCK * (MAX_NUMBER_IN_BLOCK + 1) + 10)
     {
        for(int i = 0; i < 10; i++)
        {
            indexfile->addr[i] = blocks[i];
        }
        indexfile->addr10 = indexBlockThree(blocks,10,MAX_NUMBER_IN_BLOCK + 10);
        indexfile->addr11 = indexBlockTwo(blocks,MAX_NUMBER_IN_BLOCK+10,MAX_NUMBER_IN_BLOCK * (MAX_NUMBER_IN_BLOCK + 1) + 10);
        indexfile->addr12 = indexBlockOne(blocks,MAX_NUMBER_IN_BLOCK * (MAX_NUMBER_IN_BLOCK + 1) + 10,block_num);
     }
     return indexfile;
 }
