#ifndef DIALOG_DELETE_DATA_H
#define DIALOG_DELETE_DATA_H

#include <QDialog>
#include "cglobal.h"

namespace Ui {
class dialog_delete_data;
}

class dialog_delete_data : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_delete_data(QWidget *parent = nullptr);
    ~dialog_delete_data();

private:
    Ui::dialog_delete_data *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);

signals:
    void dataUpdated();

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_DELETE_DATA_H
