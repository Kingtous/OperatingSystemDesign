#include "disk_manager.h"
#include "folder_manager.h"
#include <iostream>
using namespace std;
int main()
{
    DiskManager * dManager = new DiskManager();
    FolderManager w = FolderManager(dManager);
    w.lockFile(w.fileTable[5]);
    cout<<w.fileLocks[5]<<endl;
    w.unlockFile(w.fileTable[5]);
    cout<<w.fileLocks[5]<<endl;
    string aa = "abgdvdtgdgtdss";
    string filenamea = "hgm";
    w.generateData(aa,filenamea);
    string bb = w.getData(w.fileTable[0]);
    cout<<bb<<endl;
    cout<<w.fileTable[0]->createTime->tm_hour;
}
