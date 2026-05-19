#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(std::string &input) {
    _input = input;
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector) {
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
    _vector = other._vector;
    return *this;
}

PmergeMe::~PmergeMe() {}

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

bool PmergeMe::processInput() {

    std::istringstream iss(_input);
    std::string token;

    while(iss >> token) {
        if (isValidNumber(token)) {
            double tmpNum = atoi(token.c_str());
            std::cout <<  "this is VALID tmpNum: " << tmpNum << std::endl;
            _vector.push_back(tmpNum);
        }
        else {
            std::cerr << "Error => " << token << std::endl;
            return false;
        }
    }
    return true;
}


bool PmergeMe::makePairs() {
    int j = 0;
    for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it += 2) {
        if(*it > *it + 1)
        
        _pair[j].loser = *it;

    }
}