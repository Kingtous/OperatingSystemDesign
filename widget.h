#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "main_form.h"

namespace Ui{
    class Widget;
}

class Widget : public QWidget
{
public:
    explicit Widget(QWidget * parent = nullptr);

private:
    Ui::Widget *ui;
    main_form * mform;
};

#endif // WIDGET_H
