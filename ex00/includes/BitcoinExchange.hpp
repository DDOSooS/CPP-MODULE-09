#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <time.h>
#include <limits>


class BitcoinExchange
{
    private:
        std::multimap<double , double>      _dataBase;
        std::multimap<std::string , double> _inputData;


    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &src);
        BitcoinExchange &operator=(const BitcoinExchange &rhs);
        ~BitcoinExchange();

        void loadDatabase(const std::string &);
        void loadInputData(const std::string &);
        void processInputData();
        void printResults() const;
        
        void trimWhiteSpaces(std::string &str);
        double dateToDoubleFormat(std::string &date) const;
        bool parseValue(double &value) const;
        bool isValidDate(std::string &date) const;
        double getLowestRate(double date) const;
};
