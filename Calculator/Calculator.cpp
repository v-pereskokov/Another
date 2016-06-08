#include "Calculator.h"

Calculator::Calculator(const std::string &target)
:_target(target)
{
    calculation();
}

void Calculator::setTarget(const std::string &target)
{
    _target = target;
    calculation();
}

double Calculator::result()
{
    return _result;
}

void Calculator::calculation()
{
    for (std::size_t i = 0; i < _target.length(); ++i) {
        if (_target[i] == '(')
            _operators.push ('(');
        else if (_target[i] == ')') {
            while (_operators.top() != '(') {
                action(_operators.top());
                _operators.pop();
            }
            _operators.pop();
        }
        else if (isOperator(_target[i])) {
            while (!_operators.empty() && priority(_operators.top()) >= priority(_target[i])) {
                action(_operators.top());
                _operators.pop();
            }
            _operators.push(_target[i]);
        }
        else if (isdigit(_target[i])){
            std::string operand;
            while (i < _target.length() &&
                   (isdigit(_target[i]) || _target[i] == '.'))
                operand += _target[i++];
            --i;
            _values.push(std::atof(operand.c_str()));
        }
        else {
            std::cout << "Incorrect input!\nEnter the string again!" << std::endl;
            return;
        }
    }
    while (!_operators.empty()) {
        action(_operators.top());
        _operators.pop();
    }
    _result = _values.top();
}

bool Calculator::isOperator(char operators)
{
    return operators == '+' || operators == '-' || operators == '*'
    || operators == '/' || operators == '^';
}

Priority Calculator::priority(char operators)
{
    return
    operators == '+' || operators == '-' ? low :
    operators == '*' || operators == '/' ? medium :
    operators == '^' ? high : error;
    
}

void Calculator::action(char operators)
{
    double rhs = _values.top();
    _values.pop();
    double lhs = _values.top();
    _values.pop();
    switch (operators) {
        case '+':
            _values.push(lhs + rhs);
            break;
        case '-':
            _values.push(lhs - rhs);
            break;
        case '*':
            _values.push(lhs * rhs);
            break;
        case '/':
            _values.push(lhs / rhs);
            break;
        case '^':
            _values.push(pow(lhs, rhs));
            break;
    }
}
