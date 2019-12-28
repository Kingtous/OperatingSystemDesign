#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <main_form.h>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

    main_form form1;
    main_form form2;

};

#endif // MAINWINDOW_H
