#include "./includes/BitcoinExchange.hpp"

int main (int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Please try to run the Program with this Format [ ./prog  YourInputFile.txt] ";
        return 1;
    }
    try
    {
        std::string inputFileName(av[1]);
        BitcoinExchange *b = new BitcoinExchange();
        b->loadDatabase("/home/aghergho/Desktop/CPP/CPP09/ex00/data.csv");
        b->loadInputData(inputFileName);
        b->printResults();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}