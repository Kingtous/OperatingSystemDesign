#include "dialog_delete_data.h"
#include "ui_dialog_delete_data.h"

dialog_delete_data::dialog_delete_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_delete_data)
{
    ui->setupUi(this);
    // 关闭即销毁
    this->setAttribute  (Qt::WA_DeleteOnClose,true);
    model = new QStandardItemModel(this);
    row_selected = -1;
    lv_fileLists = ui->lv_fileLists;
    ll_owner = ui->text_owner;
    ll_fileSize = ui->text_fileSize;
    lv_fileLists->setModel(model);
    connect(lv_fileLists,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
    getFileList();
}

dialog_delete_data::~dialog_delete_data()
{
    delete ui;
}

void dialog_delete_data::closeEvent(QCloseEvent *event)
{
    CGlobal::delThreadSem->release();
}

// 获取文件列表
void dialog_delete_data::getFileList()
{
    // 清空缓存数据
    model->clear();
    tmpFCB.clear();
    row_selected = -1;
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

void dialog_delete_data::on_pushButton_clicked()
{
    int row = row_selected;
    QMessageBox * mBox = new QMessageBox(this);
    if (row != -1){
        FCB* fcb = tmpFCB.at(row);
        int status = CGlobal::fManager->deleteData(fcb);
        switch (status) {
        case STATUS_OK:
            mBox->setText("删除成功");
            break;
        case STATUS_BUSY:
            mBox->setText("文件正在使用，请稍后再试");
            break;
        case STATUS_ERR:
            mBox->setText("删除失败");
            break;
        }
        mBox->exec();
        emit dataUpdated();
        refresh();
    } else {
        mBox->setText("请选择要删除的文件");
        mBox->exec();
    }
}

void dialog_delete_data::showClick(QModelIndex index)
{
    qDebug() << "点击了一个文件:行数"+QString::number(index.row());
    row_selected = index.row();
    ll_fileSize->setText(QString::number(tmpFCB.at(row_selected)->fileSize));
    ll_owner->setText(QString::fromStdString(tmpFCB.at(row_selected)->owner));
}

void dialog_delete_data::refresh()
{
    ll_owner->clear();
    ll_fileSize->clear();
    getFileList();
}
