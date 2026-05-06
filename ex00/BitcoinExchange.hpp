#ifndef BITCOIN_HPP
#define BITCOIN_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <map>

class BitcoinExchange {
    private:
        std::map<std::string, float> _database;
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