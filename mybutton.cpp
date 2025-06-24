#include "mybutton.h"


MyButton::MyButton(const QString text) {
    setText(text);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    setStyleSheet("font-size: 22px;");

}
