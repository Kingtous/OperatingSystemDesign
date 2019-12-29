#include "window_del_data.h"
#include "ui_window_del_data.h"

window_del_data::window_del_data(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_del_data)
{
    ui->setupUi(this);
}

window_del_data::~window_del_data()
{
    delete ui;
}
