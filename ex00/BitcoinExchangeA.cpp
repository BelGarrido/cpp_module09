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




bool validDate(int day, int month, int year) {

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int tmpYear = ltm ->tm_year;

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    if (month == 2) {
        if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            if (day > 28) 
                return false;
        }
        else {
            if (day > 29)
                return false;
        }
    }
    if (year < 2009){
        std::cout << "No data available" << std::endl;
        return false;
    }
    if ((year > (ltm ->tm_year + 1900)) && (month > ltm->tm_mon + 1) && day > ltm->tm_mday ) {
        std::cout << "No valid date!!!" << std::endl;
        return false;
    }
    return true;
}

bool validLine(std::string &line) {

    if(line.size() < 14) {
        //std::cout << "INVALID FORMAT: invalid length" << std::endl;
        return false;
    }

    if(line.find('|') != 11) {
        //std::cout << "INVALID FORMAT: missing '|'" << std::endl;
        return false;
    }
    return true;
}

bool processDate(std::string &date) {
    
    if(date.size() != 10) {return false;}

    if(date[4] != '-' && date[7] != '-') {return false;}

    // days
    int day;
    std::stringstream tmpD(date.substr(8, 2));
    tmpD >> day;

    // month
    int month;
    std::stringstream tmpM(date.substr(5, 2));
    tmpM >> month;

    // years
    int year;
    std::stringstream tmpY(date.substr(0, 4));
    tmpY >> year;

    if(!validDate(day, month, year)) {
        return false;
    }
    return true;
}

bool validValue(std::string &strValue) {
    if(strValue.empty()) {
        std::cout << "empty value" << std::endl;
        return false;
    }
    float value = std::stof(strValue);
    if (value > 1000) {
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }
    else if (value < 0) {
        std::cout << "Error: not a positive number." << std::endl;
        return false;        
    }
    return true;
}


bool processLine(std::string &line, std::string &date, float &value) {
    
    std::stringstream ss(line);
    
    if (!validLine(line)){
        std::cout << "Error: Bad input => " << line << std::endl;
        return false;
    }

    std::string tmpDate;
    getline(ss, tmpDate, '|');   // reads until it hits ','
    int start = tmpDate.find_first_not_of(' ');  // 3
    int final   = tmpDate.find_last_not_of(' ');   // 7
    date = tmpDate.substr(start, final + 1);
    if (!processDate(date)) {
        std::cout << date << std::endl;
        return false;
    }

    //-------------------------------------------------------------

    std::string tmpValue;
    getline(ss, tmpValue);
    if (!validValue(tmpValue)) {
        //std::cout << tmpValue << std::endl;
        return false;
    }
    value = std::stof(tmpValue);
    return true;
}
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

        std::string date;
        float value;
        if(processLine(line, date, value)) {
            std::map<std::string, float>::iterator key = _database.lower_bound(date);
            std::map<std::string, float>::iterator end = _database.end();
            if(key->first != date || key == end)
                --key;
            std::cout << date << " => " << value << " = " << key->second * value << std::endl;
        }
    }
    return true;
}