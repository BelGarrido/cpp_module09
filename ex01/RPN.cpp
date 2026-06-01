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
    if (s.size() < 2) return false;
    return true;
}

// -----------------------------------


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

int RPN::calculate() {
    std::istringstream iss(_input);
    std::string token;

    while (iss >> token) {
        if(validOperand(token)) {
            char *endptr;
            errno = 0;
            int tmpNum = strtol(token.c_str(), &endptr, 10);
            if (errno == ERANGE || *endptr != '\0' || endptr == token.c_str()) {
                std::cerr << "Error" << std::endl;
                return 1;
            }
            _stack.push(tmpNum);
        }
        else if(validOperator(token)) {
            if(checkTwoItem(_stack)) {
                int b = _stack.top();
                _stack.pop();
                int a = _stack.top();
                _stack.pop();
                int result;
                switch(token[0]) {
                    case '+': result = a + b;
                        break;
                    case '-': result = a - b;
                        break;
                    case '*': result = a * b;
                        break;
                    case '/': 
                        if( b == 0) {
                            std::cerr << "Error" << std::endl;
                            return 1;
                        }
                        result = a / b;
                            break;
                    default:
                        std::cerr << "Error" << std::endl;
                        return 1;
                }
                _stack.push(result);
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
    if (_stack.size() != 1){
        std::cerr << "Error" << std::endl;
        return 1;    
    }
    std::cout << _stack.top() << std::endl;
    return 0;
}
