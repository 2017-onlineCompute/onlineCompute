#ifndef COMPUTE_H
#define COMPUTE_H

#include <iostream>
#include <boost/asio.hpp>
#include <stack>
#include <string>

#define BUFSIZE 1024

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

int priority(int status, char a) //定义优先级 status=1表示还未进栈，state=0表示栈内优先级，只对‘（’起作用
{
    int priority;
    switch (a){
    case '+':
    case '-':
        priority = 1;
        break;
    case '*':
    case '/':
        priority = 2;
        break;
    case '(':
        if (status == 0)
            priority = 3;
        else
            priority = 0;
        break;
    case '#':
        priority = 0;
        break;
    default:
        break;
    }
    return priority;
}

double compute(char operation, double express1, double express2)
{
    double result;
    switch (operation){

    case '+':
        result = express1 + express2;
        break;

    case '-':
        result = express1 - express2;
        break;

    case '*':
        result = express1 * express2;
        break;

    case '/':
        result = express1 / express2;
        break;

    default:
        break;
    }
    return result;
}

void client_session(socket_ptr sock)
{
    std::stack<char> operateChar;
    std::stack<double> number;

    char buf[BUFSIZE];
    sock->read_some(boost::asio::buffer(buf));

    operateChar.push('#');
    std::string str = buf;
    std::string charNum;

    for (size_t i = 0; i < str.length(); i++){
        if (isdigit(str[i])){
            while (isdigit(str[i])){
                charNum.push_back(str[i]);
                i++;
            }
            double a = atof(charNum.c_str());             // 把字符转换为数字然后压入栈
            number.push(a);
            charNum.clear();
            i--;
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '('){
            if (priority(0, str[i]) > priority(1, operateChar.top())) //优先级比较
                operateChar.push(str[i]);
            else{
                while (priority(0, str[i]) <= priority(1, operateChar.top())){
                    char operate = operateChar.top();
                    operateChar.pop();
                    double op2 = number.top();
                    number.pop();
                    double op1 = number.top();
                    number.pop();
                    number.push(compute(operate, op1, op2));
                }
                operateChar.push(str[i]);                         //操作符入栈
            }
        }
        else if (str[i] == ')'){
            while (operateChar.top() != '('){
                char operate = operateChar.top();
                operateChar.pop();
                double operateNum2 = number.top();
                number.pop();
                double operateNum1 = number.top();
                number.pop();
                number.push(compute(operate, operateNum1, operateNum2));
            }
            operateChar.pop();
        }
        else{
            std::cout << "Operation error!" << std::endl;
        }
    }
    while (operateChar.top() != '#'){
        char operate = operateChar.top();
        operateChar.pop();
        double operateNum2 = number.top();
        number.pop();
        double operateNum1 = number.top();
        number.pop();
        number.push(compute(operate, operateNum1, operateNum2));
    }
    std::string result = std::to_string(number.top());
    std::cout << str << " = "<< number.top() << std::endl;
    sock->write_some(boost::asio::buffer(result));
}

#endif // COMPUTE_H
