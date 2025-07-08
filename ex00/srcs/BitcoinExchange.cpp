# include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    this->_dataBase.clear();
    this->_inputData.clear();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
    *this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
    if (this != &src)
    {
        this->_dataBase = src._dataBase;
        this->_inputData = src._inputData;
    }
    return *this;
}

void BitcoinExchange::trimWhiteSpaces(std::string &str)
{
    size_t start_pos = str.find_first_not_of(" \t");
    size_t end_pos = str.find_last_not_of(" \t");
    str = str.substr(start_pos, end_pos - start_pos + 1);
}

bool BitcoinExchange::isValidDate(std::string &date) const
{
    struct tm time;
    const char* date_cstr = date.c_str();

    if (!strptime(date_cstr, "%Y-%m-%d", &time))
        return false;
    return true;
}

double BitcoinExchange::dateToDoubleFormat(std::string &date) const
{
    if (!isValidDate(date))
        return -1;

    std::string tmp;
    for (size_t i = 0; i < date.length(); ++i)
    {
        if (date[i] == '-')
            continue;
        tmp += date[i];
    }
    long date_long = std::atol(tmp.c_str()); 
    return static_cast<double>(date_long);
}

void BitcoinExchange::loadDatabase(const std::string &fileName)
{
    std::ifstream file(fileName.c_str());

    if (!file.is_open())
    {
        throw std::runtime_error("DATABASE FILE COULDN'T BE OPENED!!!");
    }
    std::string line;

    std::getline(file, line);
    trimWhiteSpaces(line);
    if (line != "date,exchange_rate")
        throw std::runtime_error("DATABASE SCHEMEA MUST START WITH [date,exchange_rate]");
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        trimWhiteSpaces(line);
        size_t pos = line.find(",");
        if (pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos);
        trimWhiteSpaces(date);
        std::string rate = line.substr(pos + 1);
        trimWhiteSpaces(rate);
        double date_double = dateToDoubleFormat(date);
        double rate_double = std::atof(rate.c_str());
        this->_dataBase.insert(std::make_pair(date_double, rate_double));
    }
}

void BitcoinExchange::loadInputData(const std::string &input_file_name)
{
    std::ifstream file(input_file_name.c_str());
    std::string line;
    
    if (!file.is_open())
        throw std::runtime_error ("Couldn't Open Input File ");
    std::getline(file, line);
    trimWhiteSpaces(line);
    if ( line != "date | value")
        throw std::runtime_error ("Invalid syntax input file should Start With [date | value]");
    while (std::getline(file, line))
    {
        size_t pos = line.find('|');
        if (pos != std::string::npos)
        {
            std::string date = line.substr(0, pos);
            std::string value =  line.substr(pos + 1);
            this->_inputData.insert(std::make_pair(date, std::atof(value.c_str())));
        }
        else
            this->_inputData.insert(std::make_pair(line, std::numeric_limits<double>::max()));
    }    
}

double BitcoinExchange::getLowestRate(double date) const
{
    if (this->_dataBase.empty()) return -1;
    
    std::multimap<double, double>::const_iterator exactMatch = this->_dataBase.find(date);
    if (exactMatch != this->_dataBase.end()){
        return exactMatch->second;
    }
    std::multimap<double, double>::const_iterator upper = this->_dataBase.upper_bound(date);
    --upper;
    return upper->second;
}

void BitcoinExchange::printResults() const
{
    std::cout << "====== [Start Printing Results] =====\n";
    for (std::multimap<std::string, double>::const_iterator iter = this->_inputData.begin(); iter != this->_inputData.end(); iter++)
    {
        std::string tmp = (*iter).first;
        if (!isValidDate(tmp))
        {
            std::cerr << "Error : Bad input => " << (*iter).first << std::endl;
            continue;
        }
        else if ((*iter).second < 0 )
        {
            std::cerr << "Error : not a positive number" << std::endl;
            continue;
        }
        else if ((*iter).second > 1000)
        {
            std::cerr << "Error : Too large number";
            continue;
        }
        std::string date = (*iter).first ;
        double input_date = dateToDoubleFormat(tmp);
        std::multimap<double, double>::const_iterator last_date = this->_dataBase.end();
        last_date--;
        if (last_date->first <= input_date)
            std::cout << iter->first <<  " => " << iter->second << " = " << iter->second * last_date->second << std::endl;
        else if (this->_dataBase.begin()->first > input_date)
            std::cout << "Error : Too Early Date " << iter->first << std::endl;
        else
            std::cout << iter->first << " => " << iter->second << " = " << iter->second * getLowestRate(input_date) << std::endl;
    }
    std::cout << "====== [End of Printing Results] =====\n";
}

BitcoinExchange::~BitcoinExchange()
{
    this->_dataBase.clear();
    this->_inputData.clear();
}