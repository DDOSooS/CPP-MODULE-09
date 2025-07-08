#include "../includes/RPN.hpp"

RPN::RPN()
{
    std::cout << "[RPN default constructor called]" << std::endl;
}

RPN::RPN(const RPN &other) : _rpn_stack(other._rpn_stack)
{
    std::cout << "[RPN copy constructor called]" << std::endl;
}

RPN& RPN::operator=(const RPN &other)
{
    std::cout << "[RPN assignment operator called]" << std::endl;
    if (this != &other)
    {
        _rpn_stack = other._rpn_stack;
    }
    return *this;
}

RPN::~RPN()
{
    std::cout << "[RPN destructor called]" << std::endl;
    this->_rpn_stack = std::stack<double> ();
}

void RPN::trimWhiteSpaces(std::string &str)
{
    size_t start_pos = str.find_first_not_of(" \t");
    size_t end_pos = str.find_last_not_of(" \t");
    str = str.substr(start_pos, end_pos - start_pos + 1);
}

bool RPN::isNumber(std::string &number)
{
    trimWhiteSpaces(number);
    for (size_t i = 0; i < number.length(); i++)
    {
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

bool RPN::isOperator(std::string &oper)
{
    trimWhiteSpaces(oper);
    if (oper.length() != 1)
        return false;
    if (oper == "+" || oper == "-" || oper == "/" || oper == "*")
        return true;
    return false;
}

double RPN::doOperation(std::string &oper, double a, double b)
{
    if (oper == "+")
        return a + b;
    if (oper == "*")
        return a * b;
    if (oper == "/")
        return a / b;
    return a - b;
}

//$> ./RPN "1 2 * 2 / 2 * 2 4 - +"
void RPN::evaluate(std::string &args)
{
    int number_counter;
    int operation_counter;

    number_counter = 0;
    operation_counter = 0;
    for (size_t i = 0; i < args.length(); i++)
    {
        std::string token;
        size_t pos = args.find_first_of(" \t", i);
        if (pos != std::string::npos)
        {
            token = args.substr(i, pos - i);
            i = pos;
        }
        else
        {
            token = args.substr(i);
            i = args.length(); 
        }
        if (isNumber(token))
        {
            this->_rpn_stack.push(std::atof(token.c_str()));
            number_counter++;
        }
        else if (isOperator(token))
        {
            operation_counter++;
            if (this->_rpn_stack.size() < 2)
                throw std::runtime_error("INVALID INPUT SYNATAX PLESE TRY WITH THIS FORMULATE [ab+ => a+b or abc+- => a-b+c]");
            double a = this->_rpn_stack.top();
            this->_rpn_stack.pop();
            double b = this->_rpn_stack.top();
            this->_rpn_stack.pop();
            this->_rpn_stack.push(doOperation(token, b, a));
        }
        else
            throw std::runtime_error("INVALID INPUT : TRY WITHOUT DECIMAL NUMBERS , PARENTHISES AND WITH VALID OPERATOR [+-/*]");
    }
    if ( number_counter != operation_counter + 1)
        throw std::runtime_error("INVALID INPUT : TRY WITH A VALID RPN EXPRESSION");
}

void RPN::printResult() const
{
    std::cout << "result => " <<this->_rpn_stack.top() << std::endl;
}

