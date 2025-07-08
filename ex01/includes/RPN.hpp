/*
    - check if it a valid RPN expression
    - evaluate the RPN expression
    - print the result of the evaluation
    - handle errors gracefully
*/

#pragma once

#include <iostream>
#include <stack>
#include <ctype.h>
#include <cstdlib>  

class RPN
{
    private:
        std::stack<double>  _rpn_stack;
    
    public:
        RPN();
        RPN(const RPN &other);
        RPN& operator=(const RPN &other);
        ~RPN();

        void evaluate(std::string &);
        void printResult() const;

        bool    isNumber(std::string &number);
        bool    isOperator(std::string &oper);
        double  doOperation(std::string &oper, double a, double b);
        void    trimWhiteSpaces(std::string &str);

};
