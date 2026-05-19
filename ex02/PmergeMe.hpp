#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

struct pairNum {
    int loser;
    int winner;
};

class PmergeMe {
    private:
        std::vector<int> _vector;
        std::string _input;
        std::vector<pairNum> _pair;
        PmergeMe();
    public:
        PmergeMe(std::string &input);
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();
        bool processInput();
        bool makePairs();     
};

bool isValidNumber(std::string &s);

#endif