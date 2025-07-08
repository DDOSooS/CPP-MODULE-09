#include "./includes/RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "INVALID ARGUMENT :  TRY WITH AT LEAST 3 PARAMETERS : [2 3 +]";
        return 1;
    }
    try
    {
        RPN example;
        std::string args = av[1];
        example.trimWhiteSpaces(args);
        example.evaluate(args);
        example.printResult();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}