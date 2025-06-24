#include "calculator.h"
#include <QGridLayout>
#include <QChar>
#include <QDebug>
#include <QFont>
#include <QString>
#include <QStack>

#include <QLocale>


Calculator::Calculator() {


    ////////////////////////////////////////////////////////
    m_count_of_brackets = 0; // jnjvox

    m_display        = new QLineEdit();
    m_display_answer = new QLineEdit();

    QFont font("Arial", 15);

    m_display->setFont(font);
    m_display_answer->setFont(font);


    m_display->setText("0");
    m_display->setReadOnly(true);
    m_display->setAlignment(Qt::AlignRight);

    m_display_answer->setAlignment(Qt::AlignRight);
    m_display_answer->setReadOnly(true);

    setMinimumSize(300,400);



    m_clear_button         = new MyButton("C");
    m_backspace_button     = new MyButton(QChar(0x232B));
    m_open_bracket_button  = new MyButton("(");
    m_close_bracket_button = new MyButton(")");
    m_power_button         = new MyButton('x' + QChar(0x000002B8));
    m_sqrt_button          = new MyButton(QChar(0x221A));
    m_inverse_button       = new MyButton("1/x");
    m_pi_button            = new MyButton(QChar(0x03C0));
    m_add_button           = new MyButton("+");
    m_minus_button         = new MyButton(QChar(0x2212));
    //m_div_button           = new MyButton("/");
    m_div_button           = new MyButton(QChar(0x00F7));
    m_multi_button         = new MyButton(QChar(0x00D7));
    m_equal_button         = new MyButton("=");
    m_float_button         = new MyButton(".");

    for(int i = 0; i < 10; i++){
        m_numbers[i] = new MyButton(QString::number(i));
    }



    // COnections

    for(int i = 0; i < 10; i++){
        connect(m_numbers[i], SIGNAL(clicked()), this, SLOT(numberClicked()));
    }
    connect(m_clear_button, SIGNAL(clicked()), this, SLOT(clearClicked()));
    connect(m_open_bracket_button, SIGNAL(clicked()), this, SLOT(openBracketClicked()));
    connect(m_close_bracket_button, SIGNAL(clicked()), this, SLOT(closeBracketClicked()));
    connect(m_backspace_button,SIGNAL(clicked()), this, SLOT(backspaceClicked()));

    connect(m_add_button, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(m_minus_button, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(m_multi_button, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(m_div_button, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(m_power_button, SIGNAL(clicked()), this, SLOT(powerButtonClicked()));
    //connect(m_sqrt_button, SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(m_equal_button, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(m_float_button, SIGNAL(clicked()), this, SLOT(floatButtonClicked()));

    // Layout

    QGridLayout* mainLayout = new QGridLayout;

    mainLayout->addWidget(m_display,0,0,1,5);
    mainLayout->addWidget(m_display_answer,1,0,1,5);

    mainLayout->addWidget(m_clear_button, 2,0);
    mainLayout->addWidget(m_backspace_button, 2,1);
    mainLayout->addWidget(m_sqrt_button, 2,2);
    mainLayout->addWidget(m_open_bracket_button, 2,3);
    mainLayout->addWidget(m_close_bracket_button, 2,4);
    mainLayout->addWidget(m_power_button, 3,0);
    mainLayout->addWidget(m_numbers[7], 3,1);
    mainLayout->addWidget(m_numbers[8], 3,2);
    mainLayout->addWidget(m_numbers[9], 3,3);
    mainLayout->addWidget(m_add_button, 3,4);
    mainLayout->addWidget(m_inverse_button, 4,0);
    mainLayout->addWidget(m_numbers[4], 4,1);
    mainLayout->addWidget(m_numbers[5], 4,2);
    mainLayout->addWidget(m_numbers[6], 4,3);
    mainLayout->addWidget(m_minus_button, 4,4);
    mainLayout->addWidget(m_pi_button, 5,0);
    mainLayout->addWidget(m_numbers[1], 5,1);
    mainLayout->addWidget(m_numbers[2], 5,2);
    mainLayout->addWidget(m_numbers[3], 5,3);
    mainLayout->addWidget(m_multi_button, 5,4);
    mainLayout->addWidget(m_float_button, 6,1);
    mainLayout->addWidget(m_numbers[0], 6,2);
    mainLayout->addWidget(m_equal_button, 6,3);
    mainLayout->addWidget(m_div_button, 6,4);

    setLayout(mainLayout);
}

void Calculator::numberClicked()
{
    MyButton* btn = (MyButton*)sender();
    if(m_display->text() == "0"){
        m_display->clear();
    }
    m_display->setText(m_display->text() + btn->text());

}

void Calculator::floatButtonClicked()
{
    MyButton* btn = (MyButton*)sender();
    if(!m_floatClicked && m_display->text().back().isDigit()){
        m_display->setText(m_display->text() + btn->text());
        m_floatClicked = true;
    }
}

void Calculator::powerButtonClicked()
{
    if(m_display->text().back().isDigit() || m_display->text().endsWith(')')){
        m_display->setText(m_display->text() + '^');

    }

    else if (m_display->text().back().isSymbol()){
        m_display->setText(m_display->text().removeLast() + '^');

    }

    m_floatClicked = false;
}

void Calculator::operatorClicked()
{
    MyButton* btn = (MyButton*)sender();
    if(m_display->text().back().isDigit() || m_display->text().endsWith(')')){
        m_display->setText(m_display->text() + btn->text());

    }

    else if (m_display->text().back().isSymbol()){
        m_display->setText(m_display->text().removeLast() + btn->text());

    }

    m_floatClicked = false;
}



void Calculator::clearClicked()
{
    m_display->setText("0");
    m_display_answer->clear();
    m_floatClicked = false;
}

void Calculator::backspaceClicked()
{
    if(m_display->text().endsWith('.')){
        m_floatClicked = false;
    }
    m_display->setText(m_display->text().removeLast());
    if(m_display->text() == "")
        m_display->setText("0");
}

void Calculator::openBracketClicked()
{
    if(m_display->text() == "0"){
        m_display->clear();
    }
    else if(m_display->text().back() == ')' || m_display->text().back().isDigit()){
        m_display->setText(m_display->text() + QChar(0x00D7));
    }

    m_display->setText(m_display->text() + '(');
    m_count_of_brackets++; // jnjvox

}

void Calculator::closeBracketClicked()
{
    if((m_display->text().back().isDigit() || m_display->text().back() == ")") && m_display->text() != "0" && m_count_of_brackets){
        m_display->setText(m_display->text() + ')');
        m_count_of_brackets--; // jnjvox
    }
}

void Calculator::calculate()
{
    QString exp = m_display->displayText();
    QString temp = "";
    QStack<double> operands;
    QStack<QChar> operators;

    while(!exp.isEmpty()){

        while(!exp.isEmpty() && (exp.front().isDigit()|| exp.front() == '.')){
            temp += exp.front();
            exp.removeFirst();
        }

        operands.push(temp.toDouble());
        temp.clear();

        while(!(exp.isEmpty() || exp.front().isDigit())){

            if(!operators.empty() && (priorityOperator(operators.top()) >= priorityOperator(exp.front()))){
                double b = operands.pop();
                double a = operands.pop();
                operands.push(maths(operators.top(), a, b));
                operators.pop();

            }

            if(!exp.isEmpty() && exp.front() == '('){
                operators.push('(');
                exp.removeFirst();
            }

            else if(!exp.isEmpty() && exp.front() == ')'){
                while(operators.top() != '('){
                    double b = operands.pop();
                    double a = operands.pop();
                    operands.push(maths(operators.top(), a, b));
                    operators.pop();
                }
                operators.pop();
            }

            operators.push(exp.front());
            exp.removeFirst();
        }



    }

    if (exp.isEmpty()){
        while(!operators.empty()){

            double b = operands.pop();
            double a = operands.pop();
            operands.push(maths(operators.top(), a, b));
            operators.pop();

        }

    }
    m_display_answer->setText(QString::number(operands.top()));


    while(!operands.empty()){
        qDebug() << operands.top();
        operands.pop();
    }


}


int Calculator::priorityOperator(QChar& op){

    if(op == '+')
        return 1;

    else if(op == QChar(0x2212))
        return 1;
    else if(op == QChar(0x00D7) || op == QChar(0x00F7))
        return 2;
    else if(op == '^' || op == QChar(0x221A))
        return 3;


    return 0;
}

double Calculator::maths(QChar &op, double a, double b)
{
    double ans = 0;
    if(op == '+')
        ans = a+b; //return a+b;

    else if(op == QChar(0x2212))
        ans = a-b; //return a-b;

    else if(op == QChar(0x00D7))
        ans = a*b; //return a*b;

    else if (op == QChar(0x00F7))
        ans = a/b; //return a/b;

    else if(op == '^')
        ans = pow(a,b); //return pow(a,b);

    else if(op == QChar(0x221A))
        ans = sqrt(b); //return sqrt(b);

    return ans;
}




