#include <string>
#include <iostream>
#include <sstream> 
#include <vector>

bool isValidNumber(std::string &s) {
    int i = 0;
    if(s[i] == '-' || s[i] == '+') {
        i++;
    }
    
    for (; i < s.size(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool processInput(std::string &input, std::vector<long> vec) {
    std::istringstream iss(input);
    std::string token;

    while(iss >> token) {
        if (isValidNumber(token)) {
            double tmpNum = atof(token.c_str());
            std::cout <<  "this is VALID tmpNum: " << tmpNum << std::endl;
            vec.push_back(tmpNum);
        }
        else {
            std::cerr << "Error => " << token << std::endl;
            return false;
        }
    }
    return true;
}


int main () {
    std::string nums = "1 2578474 3 4 -5";
    std::vector<long> vec;
    if (processInput(nums, vec))
        std::cout << "done" << std::endl;
    return 0;
}