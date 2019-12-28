#ifndef DATA_DEFINE_H
#define DATA_DEFINE_H

#include <string>
#include <time.h>
#include <queue>
#include <iostream>
// 目录项定义
using namespace std;

// 正常返回
#define STATUS_OK 0
// 线程阻塞状态
#define STATUS_BUSY -1
// 内存/磁盘已满
#define STATUS_FULL -2
// 错误
#define STATUS_ERR -3

typedef struct FCB{
    // 文件结构，文件为0，文件夹为1
    int type;
    string fileName;//文件名
    string owner;
    // tm为C++标准时间struct
    //     struct tm {
    //       int tm_sec;   // 秒，正常范围从 0 到 59，但允许至 61
    //       int tm_min;   // 分，范围从 0 到 59
    //       int tm_hour;  // 小时，范围从 0 到 23
    //       int tm_mday;  // 一月中的第几天，范围从 1 到 31
    //       int tm_mon;   // 月，范围从 0 到 11
    //       int tm_year;  // 自 1900 年起的年数
    //       int tm_wday;  // 一周中的第几天，范围从 0 到 6，从星期日算起
    //       int tm_yday;  // 一年中的第几天，范围从 0 到 365，从 1 月 1 日算起
    //       int tm_isdst; // 夏令时
    //     }
    tm createTime; // 创建的时间
    // 在磁盘中存放的地址
    queue<int> addrQueue;
}FCB;

typedef struct BlockTime{
    //提供数据块进入模拟内存的时间
    tm enterTime;
    //访问时间
    tm accessTime;
} BlockTime;

// 线程管理模块
typedef struct TCB{
    TCB();
    FCB * fcb;
    string data;
    bool isAlloc = false; //分配后要把isAlloc改为true
    int mBlock[4] = {-1,-1,-1,-1}; //4个block的内存块号
} TCB;

// 输出数据
void outputStr(string s);

#endif // DATA_DEFINE_H
