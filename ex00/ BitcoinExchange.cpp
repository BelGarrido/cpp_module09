#include "BitcoinExchange.hpp"

// CONSTRUCTORS AND DESTRUCTORS

BitcoinExchange::BitcoinExchange() {

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other) {

}

Bitcoin::~Bitcoin() {}



bool validYear(std::string &date) {
    std::string yearStr = date.substr(0, 4);
    int year;
    std::stringstream tmp(yearStr);
    tmp >> year;
    if (year < 2009 || year > 2100) {
        std::cout << "INVALID DATE: year not valid" << std::endl;
        return false;
    }
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

bool validDate(std::string &date) {
    
    if(date.size() != 11) {
        std::cout << "INVALID FORMAT: date length" << std::endl;
        return false;
    }
    
    if(!validYear(date) || !validMonth(date) || !validDay(date)) {
        return false;
    }
    return true;
}



//________________________________________________________________________


bool loadDatabase(std::string &filename) {
    std::ifstream data("filename");
    if(!data.is_open()) {
        std::cout << "ERROR: file could not be opened"  << std::endl; 
        return 1;
    }

    std::string line;
    getline(data, line);
    if (line.empty()) {
        std::cout << "ERROR: file is empty, this is no super accurate i need to think about how to improve it"  << std::endl; 
        return 1;
    }
    std::map<std::string, float> dataHistory;
    while (getline(data, line)) {
        std::stringstream ss(line);
        std::string date;
        std::string strValue;
        getline(ss, date, ',');   // reads until it hits ','
        getline(ss, strValue);       // reads the rest of the line
        
        //transform string to float (not sure is i have to ste the precision?)
        float value = std::stof(strValue);

        std::cout << "date: " << date << " value: " << strValue << "float: " << value << std::endl;
        dataHistory.insert({date, value});
    }
    for (std::map<std::string, float>::iterator record=dataHistory.begin(); record != dataHistory.end(); ++record) {
            std::cout << record->first << " => " << record->second << std::endl;
    }
    std::cout << "here" << std::endl;
}