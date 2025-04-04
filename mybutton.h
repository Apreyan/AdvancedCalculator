#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QToolButton>
#include <QPushButton>
#include <QString>
class MyButton : public QToolButton
{
public:
    MyButton(const QString text);
};

#endif // MYBUTTON_H
