#include "disk_manager.h"
#define BlockNum     1024      //磁盘块的数目(编号从0开始)
#define BlockSize    4         //磁盘块大小
#define SystemSize   1024*4     //磁盘总容量
#define exchange_x   (900-1)/32       //对换区首址x
#define exchange_y   (900-1)%32       //对换区首址y
#define BLOCK_SIZE   4
#define MAX_NUMBER_IN_BLOCK 2
#define MAX_BLOCK_NUMBER 900
// 初始化函数
DiskManager::DiskManager()
{
<<<<<<< Updated upstream
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
=======
    //分配1024*4B空间

>>>>>>> Stashed changes
    for(int i=0;i<1024;i++){
        Map[i] = true;
        Map[i].x = (i-1)/32;
        Map[i].y = (i-1)%32;
    }
}

//对换区磁盘分配
int DiskManager::getBlock(int blocksize){
    int startBlock = 0;
    int sum = 0;
    int b = 0;
    int c = 0;
    for(int i=900;i<1024;i++){
        if(DiskManager().Map[i].isFree == true){
            if(sum==0)
                startBlock=i;
                //
            sum++;
            if(sum==blocksize)
            {
                for(int j=startBlock;j<startBlock+BlockSize;j++){
                    DiskManager().Map[j].isFree = false;
                }
                return startBlock;
            }
        }
        else sum=0;
    }
    printf("not found such series memory or memory is full\n");
    return -1;
}
//释放盘块
int DiskManager::ReleaseBlock(int blocknum,int blocksize){
    int endblock = blocknum + blocksize;
    for(int i=blocknum;i<endblock;i++)
    DiskManager().Map[i].isFree = true;
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
    for(int i=0;i<1024;i++)q.push(DiskManager().Map[i])
    return q;
}

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
 DIndex_File* indexFile(int filesize)
 {
     printf("文件大小为：%d B\n",filesize);
     //计算该文件需要多少盘块
     int block_num = filesize % BLOCK_SIZE == 0 ? filesize / BLOCK_SIZE : filesize / BLOCK_SIZE + 1;
     printf("共占 %d 个盘块\n",block_num);
     //定义保存所有盘块号的数组
     int *blocks = (int *) malloc(sizeof(int) * block_num);
     //初始化数组
     memset(blocks,0,sizeof(int) * block_num);

//     for(int i = 0; i < block_num; i++)
//        printf("%d ",blocks[i]);

     //模拟系统分配空闲盘块号
     //随机数种子
     srand(time(NULL));
     //map标记，避免产生重复的盘块号
     map<int,int> flag;
     for(int i = 0; i < block_num; i++)
     {
         int temp = rand() % MAX_BLOCK_NUMBER;
         while(DiskManager().Map[temp].isFree = false)
         {
            temp = rand() % MAX_BLOCK_NUMBER;
         }
         DiskManager().Map[temp].isFree = false;
         blocks[i] = temp;
     }

//     for(int i = 0; i < block_num; i++)
//        printf("%d ",blocks[i]);

     Index_File *indexfile;
     indexfile = (Index_File*) malloc(sizeof(Index_File));
     indexfile->fileSize = filesize;
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


//给定地址addrss和文件indexfile，找到地址对应的块号；
int findBlock(int addrss, Index_File *indexfile)
{
    addrss++;
    int block_num = addrss % BLOCK_SIZE == 0 ? addrss / BLOCK_SIZE : addrss / BLOCK_SIZE + 1;
    int ans;
    if(block_num <= 10)
    {
        ans = indexfile->addr[block_num - 1];
    }
    //一次间址
    else if(block_num <= MAX_NUMBER_IN_BLOCK + 10)
    {
        block_num -= 10;
        //计算盘块号
        int index = block_num - 1;
        //查找盘块
        ans = indexfile->addr10->blocks[index];
    }
    //二次间址
    else if(block_num <= MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK + MAX_NUMBER_IN_BLOCK + 10)
    {
        block_num -= MAX_NUMBER_IN_BLOCK + 10;
        //计算第三层索引块的序号
        int index_three = block_num % MAX_NUMBER_IN_BLOCK == 0 ? block_num / MAX_NUMBER_IN_BLOCK : block_num / MAX_NUMBER_IN_BLOCK + 1;
        //计算盘块号
        int index = block_num - ((index_three - 1) * MAX_NUMBER_IN_BLOCK);
        //查找盘块
        ans = indexfile->addr11->blocks[index_three - 1]->blocks[index - 1];
    }
    //三次间址
    else if(block_num <= MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK + MAX_NUMBER_IN_BLOCK * (MAX_NUMBER_IN_BLOCK + 1) + 10)
    {
        block_num -= MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK + MAX_NUMBER_IN_BLOCK + 10;
        //计算第二层索引块的序号
        int index_two = block_num % (MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK) == 0 ?
        block_num / (MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK) : block_num / (MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK) + 1;
        block_num -= (index_two - 1) * (MAX_NUMBER_IN_BLOCK * MAX_NUMBER_IN_BLOCK);
        //计算第二层索引块的序号
        int index_three = block_num % MAX_NUMBER_IN_BLOCK == 0 ? block_num / MAX_NUMBER_IN_BLOCK : block_num / MAX_NUMBER_IN_BLOCK + 1;
        //计算盘块号
        int index = block_num - (index_three - 1) * MAX_NUMBER_IN_BLOCK;
        //查找盘块
        ans = indexfile->addr12->blocks[index_two - 1]->blocks[index_three - 1]->blocks[index - 1];
    }
    return ans;
}