#ifndef DIALOG_GEN_DATA_H
#define DIALOG_GEN_DATA_H

#include <QDialog>
#include "cglobal.h"

namespace Ui {
class dialog_gen_data;
}

class dialog_gen_data : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_gen_data(QWidget *parent = nullptr);
    ~dialog_gen_data();

signals:
    // 数据更新了
    void dataUpdated();

private:
    Ui::dialog_gen_data *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_btn_submit_clicked();
};

#endif // DIALOG_GEN_DATA_H
