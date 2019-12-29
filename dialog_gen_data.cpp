#include "dialog_gen_data.h"
#include "ui_dialog_gen_data.h"

dialog_gen_data::dialog_gen_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_gen_data)
{
    ui->setupUi(this);



}

dialog_gen_data::~dialog_gen_data()
{
    delete ui;
}

void dialog_gen_data::closeEvent(QCloseEvent *event)
{
    CGlobal::genThreadSem->release();
}

void dialog_gen_data::on_btn_submit_clicked()
{
    CGlobal::genThreadSem->release();
    // 发出信号给主线程
    emit dataUpdated();
    this->close();
}
