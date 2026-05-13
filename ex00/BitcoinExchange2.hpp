#ifndef BITCOIN_HPP
#define BITCOIN_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <map>
#include <ctime>


enum eError {
    OK,
    ERR_TOO_LARGE,
    ERR_NEGATIVE,
    ERR_BAD_INPUT,
    ERR_BAD_DATE
};

class BitcoinExchange {
    private:
        std::map<std::string, float> _database;
        eError validValue(std::string &strValue);
        eError validDate(std::string &date);
        eError validLine(std::string &line, std::string &date, std::string &strValue);
        float lookUp(std::string &date);
        void printError(eError error, std::string &context);
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange& operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        bool loadDatabase (const std::string &filename);
        bool processInput(const std::string &filename);
        
} ;

std::string trim(const std::string &str);

#endif