#include "window_exe_data.h"
#include "ui_window_exe_data.h"

window_exe_data::window_exe_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::window_exe_data)
{
    ui->setupUi(this);
    this->setWindowTitle("数据执行");
}

window_exe_data::~window_exe_data()
{
    delete ui;
}

// 调入内存按钮被按下
void window_exe_data::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);
}
