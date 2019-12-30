#include "window_exe_data.h"
#include "ui_window_exe_data.h"

window_exe_data::window_exe_data(QWidget *parent,TCB* tcb) :
    QWidget(parent),
    ui(new Ui::window_exe_data)
{
    ui->setupUi(this);
    this->tcb = tcb;
    fileSelected = nullptr;
    this->setWindowTitle("数据执行");
    // 关闭即销毁
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    // 定义
    lv_fileList = ui->lv_fileList;
    ll_owner = ui->text_owner;
    ll_fileName = ui->text_fileName;
    ll_fileSize = ui->text_fileSize;
    ll_createTime = ui->text_createTime;
    ll_loadFile = ui->text_loadFiles;
    model = new QStandardItemModel();
    lv_fileList->setModel(model);
    connect(lv_fileList,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));

    updateFiles();
}

window_exe_data::~window_exe_data()
{
    delete ui;
}

// 调入内存按钮被按下
void window_exe_data::on_pushButton_clicked()
{
    // 在创建数据执行线程时，已经在FCB中分配了4个内存
    ui->pushButton->setDisabled(true);


}

// 更新文件列表
void window_exe_data::updateFiles()
{
    model->clear();
    queue<FCB*> q = CGlobal::fManager->getFiles();
    // 备份一份
    while(!q.empty()){
        FCB* fcb = q.front();
        QStandardItem * item = new QStandardItem();
        item->setEditable(false);
        item->setText(QString::fromStdString(fcb->fileName));
        model->appendRow(item);
        q.pop();
        tmpFCB.push_back(fcb);
    }

}

// 调入内存
void window_exe_data::on_btn_load_clicked()
{
    ((QPushButton*)sender())->setEnabled(false);
}

void window_exe_data::showClick(QModelIndex index)
{
    FCB* fcb = tmpFCB.at(index.row());
    ll_owner->setText(QString::fromStdString(fcb->owner));
    ll_fileName->setText(QString::fromStdString(fcb->fileName));
    ll_fileSize->setText(QString::number(fcb->fileSize));
    ll_createTime->setText(parseTM(fcb->createTime));
    fileSelected = fcb;
}
