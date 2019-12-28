#include "disk_manager.h"
#define BlockNum     1024      //磁盘块的数目(编号从0开始)
#define BlockSize    4         //磁盘块大小
#define SystemSize   1024*4     //磁盘总容量
#define exchange_x   (900-1)/32       //对换区首址x
#define exchange_y   (900-1)%32       //对换区首址y
// 初始化函数
DiskManager::DiskManager()
{
    /*//分配1024*4B空间
    SystemAddr = (char*)malloc(SystemSize*sizeof(char));
    //初始化盘块的位示图
    for(int i=0;i<BlockNum;i++)
        SystemAddr[i]=0;//未使用
    int BitMapSize = 256;//存放位示图要用到的空间
    for(int i=0;i<BitMapSize;i++)
        SystemAddr[i]=1;//已经使用*/
    SystemAddr = (char *)malloc(SystemSize*sizeof(char));
    //BitMapItem Map[32][32];
    for(int i=0;i<32;i++){
        for(int j=0;j<32;j++){
            Map[i][j].isFree = true;
        }
    }
}

//对换区磁盘分配
int DiskManager::getBlock(int blocksize){
    int startBlock = 0;
    int sum = 0;
    int b = 0;
    int c = 0;
    for(int i=900;i<1024;i++){
        k = (i-1)/32;
        l = (i-1)%32;
        if(Map[k][l].isFree == true){
            if(sum==0)
                startBlock=i;
                //
            sum++;
            if(sum==blocksize)
            {
                for(int j=startBlock;j<startBlock+BlockSize;j++){
                    g = (j-1)/32;
                    h = (j-1)%32;
                    Map[g][h].isFree = false;
                }
                return startBlock;
            }
        }
        else sum=0;
    }
    printf("not found such series memory or memory is full\n");
    return -1;
}
//获得盘块的物理地址
char* DiskManager::GetBlockAddr(int blocknum){
    return SystemAddr + blocknum * 4;//偏移量位字节

}
//获得物理地址的盘块号
int DiskManager::GetAddrBlock(string* addr){
    return (addr-SystemAddr)/4;
}
//释放盘块
int DiskManager::ReleaseBlock(int blocknum,int blocksize){
    int endblock = blocknum + blocksize;
    for(int i=blocknum;i<endblock;i++)
    x = (i-1)/32;
    y = (i-1)%32;
    Map[x][y].isFree = true;
    return 0;
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
    for(int i=0;i<32;i++){
        for(int j=0;j<=32;j++){
            q.push(Map[i][j]);
        }
    }
    return q;
}
