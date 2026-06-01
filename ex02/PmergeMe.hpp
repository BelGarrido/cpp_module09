#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cstdlib>
#include <limits.h>
#include <deque>
#include <sys/time.h>

struct pairNum {
    int loser;
    int winner;
};

struct vectorStruct {
    std::vector<unsigned int> _originalChain;
    std::vector<pairNum> _pair;
    std::vector<pairNum> _sortedPair;
    std::vector<unsigned int> _sortedChain;
};

struct dequeStruct {
    std::deque<unsigned int> _originalChain;
    std::deque<pairNum> _pair;
    std::deque<pairNum> _sortedPair;
    std::deque<unsigned int> _sortedChain;
};

class PmergeMe {
    
    private:
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        
        
    public:
        PmergeMe();
        ~PmergeMe();
        std::vector<unsigned int> sortVector(std::vector<unsigned int> &v);
        std::deque<unsigned int> sortDeque(dequeStruct &deq);

};

bool saveInput(std::string &input,vectorStruct &vec, dequeStruct &deq);

#endif
