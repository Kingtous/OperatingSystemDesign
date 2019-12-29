#include "window_gen_data.h"
#include "ui_window_gen_data.h"

window_gen_data::window_gen_data(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_gen_data)
{
    ui->setupUi(this);
}

window_gen_data::~window_gen_data()
{
    delete ui;
}
