#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <map>

// pseudocode

// 1) divide with getline and stores the date in a string date and string value
// 2) parse the format in the string date to see if valid date
//        IF is valid
//        2.1) parse the value and if valid use stringstream to ss >> float
// 3) if both valids, we save it in a pair of map <string, float>



// 1. open the file
// 2. read line by line
// 3. split each line at '|'
// 4. store in map<string, float>
// 4. open the file
// 5. read line by line
// 6. validate date ()
// 7. validate value (not negative, not > 1000)
// 8. use that date to look up the price in map

// - wrong format (missing -, wrong length, spaces)
// - month out of range (< 1 or > 12)
// - day out of range (< 1 or > 31)
// - value is negative
// - value is higher than 1000
// - empty value
// - missing |

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


int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    std::ifstream input("../input.txt");
    if(!input.is_open()) {
        std::cout << "ERROR: file could not be opened"  << std::endl; 
        return 1;
    }
    std::string line;
    getline(input, line);
    while (getline(input, line)) {
        if(!validLine(line)) {
            std::cout << "INVALID" << std::endl;
            return 1;
        }
        std::stringstream ss(line);
        std::string date;
        std::string strValue;
        std::cout << "INPUT" << std::endl;
        getline(ss, date, '|');   // reads until it hits ','
        getline(ss, strValue);       // reads the rest of the line
        
        if(!validDate(date)) {
            std::cout << "valid date" << std::endl;
        }
        //if(!validValue(strValue)) {

        //}
        //transform string to float (not sure is i have to ste the precision?)
        //float value = std::stof(strValue);
        //validate format
        
        //compare
    }
    std::cout << "Hasta aqui bien" << std::endl;
    return 0;
}


// map<string, vector<int>> data;
// data["numbers"] = {10, 20, 30};
// data["others"] = {40, 50, 60};

// map<string, vector<int>>::iterator eso;
// vector<int>::iterator it;

// for(eso = data.begin(); eso != data.end(); ++eso){
//     for(it = eso->second.begin(); it != eso->second.end(); ++it){
//         cout << eso->first << " => " << *it << '\n';
//     }
// }



// int main() {

// std::cout << "Por favor, introduce la cadena de caracteres\n";
// std::string input  = " ";
// std::getline(std::cin, input);
// cout << input << endl;
// }