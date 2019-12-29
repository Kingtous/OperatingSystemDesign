#include "dialog_delete_data.h"
#include "ui_dialog_delete_data.h"

dialog_delete_data::dialog_delete_data(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_delete_data)
{
    ui->setupUi(this);
}

dialog_delete_data::~dialog_delete_data()
{
    delete ui;
}

void dialog_delete_data::closeEvent(QCloseEvent *event)
{
    CGlobal::delThreadSem->release();
}

void dialog_delete_data::on_pushButton_clicked()
{
    CGlobal::delThreadSem->release();

    emit dataUpdated();

    this->close();
}
