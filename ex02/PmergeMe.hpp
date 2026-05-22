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

struct pairNum {
    int loser;
    int winner;
};

struct vectorS {
    std::vector<int> _vector;
    std::vector<pairNum> _pair;
    std::vector<pairNum> _sortedPair;
    std::vector<int> _sortedChain;
};

class PmergeMe {
    private:
        std::vector<int> _vector;
        std::string _input;
        std::vector<pairNum> _pair;
        std::vector<pairNum> _sortedPair;
        std::vector<int> _sortedChain;
        
        int binarySearch(int searchValue, int high);
        void insertLoser(int jIndex);
    public:
        PmergeMe();
        //PmergeMe(std::string &input);
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);
        ~PmergeMe();

        std::vector<unsigned int> sortVector(std::vector<unsigned int> &v);
        static void sort(const std::deque<unsigned int> &in, std::deque<unsigned int> &out);

        bool processInput(std::string &input);
        //void makePairs();
        std::vector<pairNum> makePairs(std::vector<unsigned int> &v);
        //void sortWinners(int size);
        void sortWinners(vectorS &vec, int size);
        int getPairSize();
        void insertRemain();
};

bool isValidNumber(std::string &s);

#endif


