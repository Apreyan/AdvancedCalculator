#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <mybutton.h>

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator();

private:
    short int m_count_of_brackets; //jnjvox
    bool      m_floatClicked;

    QLineEdit* m_display;
    QLineEdit* m_display_answer;

    MyButton* m_numbers[10];

    MyButton* m_clear_button;
    MyButton* m_backspace_button;
    MyButton* m_open_bracket_button;
    MyButton* m_close_bracket_button;

    MyButton* m_add_button;
    MyButton* m_minus_button;
    MyButton* m_multi_button;
    MyButton* m_div_button;
    MyButton* m_equal_button;
    MyButton* m_power_button;
    MyButton* m_sqrt_button;
    MyButton* m_pi_button;
    MyButton* m_inverse_button;

    MyButton* m_float_button;

private slots:

    void numberClicked();
    void operatorClicked();
    void clearClicked();
    void backspaceClicked();
    void openBracketClicked();
    void closeBracketClicked();
    void floatButtonClicked();
    void powerButtonClicked();
    void calculate();
    void calculation();
    void equalClicked();
    int priorityOperator(QChar&);
    double maths(QChar& op, double a = 0,double b = 0);

};

#endif // CALCULATOR_H
