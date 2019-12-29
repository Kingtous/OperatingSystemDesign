#ifndef WINDOW_DEL_DATA_H
#define WINDOW_DEL_DATA_H

#include <QMainWindow>

namespace Ui {
class window_del_data;
}

class window_del_data : public QMainWindow
{
    Q_OBJECT

public:
    explicit window_del_data(QWidget *parent = nullptr);
    ~window_del_data();

private:
    Ui::window_del_data *ui;
};

#endif // WINDOW_DEL_DATA_H
