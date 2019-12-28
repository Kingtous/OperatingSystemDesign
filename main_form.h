#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include <QWidget>

namespace Ui {
    class main_form;
}

class main_form : public QWidget
{
    Q_OBJECT
public:
    explicit main_form(QWidget *parent = nullptr);

private:
    Ui::main_form *ui;

signals:

public slots:
};

#endif // MAIN_FORM_H
