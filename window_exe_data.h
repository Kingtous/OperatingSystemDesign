#ifndef EXE_FORM_H
#define EXE_FORM_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class window_exe_data;
}

class window_exe_data : public QWidget
{
    Q_OBJECT

public:
    explicit window_exe_data(QWidget *parent = nullptr);
    ~window_exe_data();

    QPushButton *btnRead;

private:
    Ui::window_exe_data *ui;

signals:
    // 做一次操作后，通知主线程更新
    void notifyUpdate();

private slots:
    void on_pushButton_clicked();
    // 更新文件列表
    void updateFiles();

};

#endif // EXE_FORM_H
