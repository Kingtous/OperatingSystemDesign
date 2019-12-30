#ifndef EXE_FORM_H
#define EXE_FORM_H

#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QQueue>

#include "data_define.h"
#include "cglobal.h"

namespace Ui {
class window_exe_data;
}

class window_exe_data : public QWidget
{
    Q_OBJECT

public:
    explicit window_exe_data(QWidget *parent = nullptr,TCB* tcb=nullptr);
    ~window_exe_data();

    QPushButton *btnRead;

private:
    Ui::window_exe_data *ui;

    QListView* lv_fileList;
    QLabel * ll_createTime;
    QLabel * ll_owner;
    QLabel * ll_fileSize;
    QLabel * ll_fileName;
    QLabel * ll_loadFile;
    QStandardItemModel * model;

    QQueue<FCB*> tmpFCB;
    TCB* tcb;
    FCB* fileSelected;

signals:
    // 做一次操作后，通知主线程更新
    void notifyUpdate();

private slots:
    void on_pushButton_clicked();
    // 更新文件列表
    void updateFiles();

    void on_btn_load_clicked();
    // 选择了文件
    void showClick(QModelIndex index);
};

#endif // EXE_FORM_H
