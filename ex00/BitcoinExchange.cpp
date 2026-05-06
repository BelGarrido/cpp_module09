#include "BitcoinExchange.hpp"

// CONSTRUCTORS AND DESTRUCTORS

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other) {
    _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}


bool validYear(std::string &date) {
    std::string yearStr = date.substr(0, 4);
    int year;
    std::stringstream tmp(yearStr);
    tmp >> year;
    if (year < 2009 || year > 2100) {
        std::cout << "INVALID DATE: year not valid" << std::endl;
        return false;
    }
    return true;
}

bool validMonth(std::string &date) {
    std::string monthStr = date.substr(5, 2);
    int month;
    std::stringstream tmp(monthStr);
    tmp >> month;
    if (month < 1 || month > 12) {
        std::cout << "INVALID DATE: month not valid" << std::endl;
        return false;
    }
    return true;
}

bool validDay(std::string &date) {
    std::string dayStr = date.substr(8, 2);
    int day;
    std::stringstream tmp(dayStr);
    tmp >> day;
    if (day < 1 || day > 31) {
        std::cout << "INVALID DATE: day not valid" << std::endl;
        return false;
    }
    return true;
}


bool validLine(std::string &line) {

    if(line.size() < 14) {
        std::cout << "INVALID FORMAT: invalid length" << std::endl;
        return false;
    }

    if(line[4] != '-' && line[7] != '-') {
        std::cout << "INVALID FORMAT: missing '-'" << std::endl;
        return false;
    }

    if(line.find('|') != 11) {
        std::cout << "INVALID FORMAT: missing '|'" << std::endl;
        return false;
    }
    return true;
}

// bool validDate(std::string &date) {
    
//     if(date.size() != 11) {
//         std::cout << "INVALID FORMAT: date length" << std::endl;
//         return false;
//     }
    
//     if(!validYear(date) || !validMonth(date) || !validDay(date)) {
//         return false;
//     }
//     return true;
// }



//________________________________________________________________________


bool BitcoinExchange::loadDatabase(const std::string &filename) {
    
    std::ifstream data(filename);
    if(!data.is_open()) {
        std::cout << "ERROR: file could not be opened"  << std::endl; 
        return false;
    }

    std::string line;
    getline(data, line);
    if (line.empty()) {
        std::cout << "ERROR: file is empty, this is no super accurate i need to think about how to improve it"  << std::endl; 
        return false;
    }

    while (getline(data, line)) {
        std::stringstream ss(line);
        std::string date;
        std::string strValue;
        getline(ss, date, ',');   // reads until it hits ','
        getline(ss, strValue);       // reads the rest of the line
        
        float value = std::stof(strValue);
        _database.insert({date, value});
    }
    // for (std::map<std::string, float>::iterator record=_database.begin(); record != _database.end(); ++record) {
    //         std::cout << record->first << " => " << record->second << std::endl;
    // }
    return true;
}


bool BitcoinExchange::processInput(const std::string &filename) {

    std::ifstream input(filename);
    if(!input.is_open()) {
        std::cout << "ERROR: file could not be opened"  << std::endl; 
        return false;
    }

    std::string line;
    getline(input, line);
    while (getline(input, line)) {

        if(!validLine(line)) {
            std::cout << "INVALID" << std::endl;
            return 1;
        }
        
        std::stringstream ss(line);
        std::string strDate;
        std::string strValue;

        getline(ss, strDate, '|');   // reads until it hits ','
        
        int start = strDate.find_first_not_of(' ');  // 3
        int final   = strDate.find_last_not_of(' ');   // 7
        std::string date = strDate.substr(start, final + 1);
        // position
        getline(ss, strValue);       // reads the rest of the line
        float value = std::stof(strValue);
        
        if(validDate() && validValue()) {
            std::map<std::string, float>::iterator key = _database.lower_bound(date);
            std::map<std::string, float>::iterator end = _database.end();
            if(key->first != date || key == end) {
                --key;
            }
            std::cout << date << " => " << value << " = " << key->second * value << std::endl;
        }
    }
    return true;
}