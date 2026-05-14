#include "RPN.hpp"

//CONSTRUCTORS AND DESTRUCTORS

RPN::RPN() {}

RPN::RPN(std::string &input) {
    _input = input;
}

RPN::RPN(const RPN &other) : _stack(other._stack) {
}

RPN& RPN::operator=(const RPN &other) {
    _stack = other._stack;
    return *this;
}

RPN::~RPN() {}

 bool checkTwoItem(std::stack<int> &s) {
    if (s.size() != 2) return false;
    return true;
}

bool validOperand(std::string &token) {
    if (token.size() > 1) return false;
    if (!isdigit(token[0])) return false;
    return true;
}

bool validOperator(std::string &token) {
    if (token.size() > 1) return false;
    if (token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/') return false;
    return true;
}

int executeOperation(int a, int b, std::string &op) {
    if(op == "+")
        return a + b;
    else if (op == "-")
        return a - b;
    else if (op == "*")
        return a * b;
    else if (op == "/")
        return a / b;
    return 0;
}

int RPN::calculate() {
    std::istringstream iss(_input);
    std::string token;

    while (iss >> token) {
        if(validOperand(token)) {
            int tmpNum = atoi(token.c_str());
            //std::cout <<  "this is VALID OPERAND tmpNum: " << tmpNum << std::endl;
            _stack.push(tmpNum);
        }
        else if(validOperator(token)) {
            if(checkTwoItem(_stack)) {
                int b = _stack.top();
                //std::cout <<  "this is a: " << b << std::endl;
                _stack.pop();
                int a = _stack.top();
                //std::cout <<  "this is b: " << a << std::endl;
                _stack.pop();
                int result = executeOperation(a, b, token);
                _stack.push(result);
                //std::cout <<  "this is a result of " << a << token <<  b << ": " << result <<  std::endl;
            }
            else {
                std::cerr << "Error" << std::endl;
                return 1;
            }
        }
        else {
            std::cerr << "Error" << std::endl;
            return 1;
        }
    }
    std::cout << _stack.top() << std::endl;
    return 0;
}
