#include "BitcoinExchange2.hpp"

// CONSTRUCTORS AND DESTRUCTORS

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other) {
    _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

eError BitcoinExchange::validValue(std::string &strValue) {
    if(strValue.empty()) {
        return ERR_BAD_INPUT;
    }
    float value = std::stof(strValue);
    //std::cout << value << std::endl;
    if (value > 1000) return ERR_TOO_LARGE;
    else if (value < 0) return ERR_NEGATIVE;
    return OK;
}

eError BitcoinExchange::validDate(std::string &date) {

    if(date.size() < 10) return ERR_BAD_DATE;
    if(date[4] != '-' || date[7] != '-') return ERR_BAD_DATE;

    int day;
    std::stringstream tmpD(date.substr(8, 2));
    tmpD >> day;
    int month;
    std::stringstream tmpM(date.substr(5, 2));
    tmpM >> month;
    int year;
    std::stringstream tmpY(date.substr(0, 4));
    tmpY >> year;

    //------------------------------------

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int tmpYear = ltm -> tm_year;

    if (month < 1 || month > 12) return ERR_BAD_DATE;
    if (day < 1 || day > 31) return ERR_BAD_DATE;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return ERR_BAD_DATE;
    if (month == 2) {
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            if (day > 29) return ERR_BAD_DATE;
        }
        else {
            if (day > 28) return ERR_BAD_DATE;
        }
    }
    if (year < 2009) return ERR_BAD_DATE;
    if ((year > (ltm -> tm_year + 1900))|| (month > ltm -> tm_mon + 1) || day > ltm -> tm_mday )
        return ERR_BAD_DATE;
    return OK;
}

eError BitcoinExchange::validLine(std::string &line, std::string &date, std::string &strValue) {
    
    if(line.find('|') == std::string::npos) return ERR_BAD_INPUT;

    std::stringstream ss(line);

    std::string tmpDate;
    getline(ss, tmpDate, '|');   // reads until it hits ','
    date = trim(tmpDate);
    //-------------------------------------------------------------
    std::string tmpValue;
    getline(ss, tmpValue);
    strValue = trim(tmpValue);
    return OK;
}

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
    return true;
}


float BitcoinExchange::lookUp(std::string &date) {
    std::map<std::string, float>::iterator key = _database.lower_bound(date);
    std::map<std::string, float>::iterator end = _database.end();
    std::map<std::string, float>::iterator begin = _database.begin();
    if(key == end || (key->first != date && key != begin))
        --key;
    return key -> second;
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
        std::string date;
        std::string strValue;
        eError error = validLine(line, date, strValue);
        if (error != OK) {printError(error, line); continue;}

        error = validDate(date);
        if (error != OK) {printError(error, date); continue;}

        error = validValue(strValue);
        if (error != OK) {printError(error, strValue); continue;}

        float value = stof(strValue);

        std::cout << date << " => " << value << " = " << lookUp(date) * value << std::endl;
    }
    return true;
}


std::string trim(const std::string &str) {
    int start = str.find_first_not_of(' ');  // 3
    int final = str.find_last_not_of(' ');   // 7
    std::string trimValue = str.substr(start, final - start + 1);
    return trimValue;
}


void BitcoinExchange::printError(eError error, std::string &context) {
    if (error == ERR_BAD_INPUT)
        std::cout << "Error: bad input => " << context << std::endl;
    if (error == ERR_BAD_DATE)
        std::cout << "Error: bad input => " << context << std::endl;
    if (error == ERR_NEGATIVE)
        std::cout << "Error: not a positive number." << std::endl;
    if (error == ERR_TOO_LARGE)
        std::cout << "Error: too large a number." << std::endl;
}

