#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <stack>
#include <cstdlib>


class RPN {
    private:
        std::stack<int> _stack;
        std::string _input;
        RPN();
    public:
        RPN(std::string &input);
        RPN(const RPN &other);
        RPN& operator=(const RPN &other);
        ~RPN();
        int calculate();        
} ;

 bool checkTwoItem(std::stack<int> &s);
 bool validOperand(std::string &token);
 bool validOperator(std::string &token);
 int executeOperation(int a, int b, std::string &op);

#endif