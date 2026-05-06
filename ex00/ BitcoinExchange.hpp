#ifndef BITCOIN_HPP
#define BITCOIN_HPP
#include <map>
#include <string>

class BitcoinExchange {
    private:
        std::map<std::string, float> _database;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange& operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        bool loadDatabase (std::string &filename);
        bool processInput(std::string &filename);
} ;


#endif