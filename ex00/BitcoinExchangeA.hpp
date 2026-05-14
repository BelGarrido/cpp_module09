#ifndef BITCOIN_HPP
#define BITCOIN_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <map>
#include <ctime>


class BitcoinExchange {
    private:
        std::map<std::string, float> _database;
        static bool validValue(std::string &strValue);
        static bool validDate(int day, int month, int year);
        static bool processDate(std::string &date);
        static bool validLine(std::string &line);
        static bool processLine(std::string &line, std::string &date, float &value);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange& operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        bool loadDatabase (const std::string &filename);
        bool processInput(const std::string &filename);
        
} ;

bool validLine(std::string &line);

#endif