#ifndef WINDOW_GEN_DATA_H
#define WINDOW_GEN_DATA_H

#include <QMainWindow>

namespace Ui {
class window_gen_data;
}

class window_gen_data : public QMainWindow
{
    Q_OBJECT

public:
    explicit window_gen_data(QWidget *parent = nullptr);
    ~window_gen_data();

private:
    Ui::window_gen_data *ui;
};

#endif // WINDOW_GEN_DATA_H
