#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

/* PmergeMe::PmergeMe(std::string &input) {
    _input = input;
} */

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector) {
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
    _vector = other._vector;
    return *this;
}

PmergeMe::~PmergeMe() {}

bool isValidNumber(std::string &s) {
    size_t i = 0;
    if(s[i] == '-' || s[i] == '+') {
        return false;
    }
    for (; i < s.size(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool PmergeMe::processInput(std::string &input) {

    std::istringstream iss(input);
    std::string token;

    if(token.empty()) {
        std::cerr << "Error (empty string)" << std::endl;
        return false;
    }
    while(iss >> token) {
        if (isValidNumber(token)) {
            int tmpNum = atoi(token.c_str());
            std::vector<int>::iterator it = std::find(_vector.begin(), _vector.end(), tmpNum);
            if(_vector.empty() || it == _vector.end())
                _vector.push_back(tmpNum);
            else {
                std::cerr << "Error (duplicate number) => " << token << std::endl;
                return false;
            }
        }
        else {
            std::cerr << "Error => " << token << std::endl;
            return false;
        }
    }
    return true;
}


void PmergeMe::makePairs() {
    pairNum p;
    for (std::vector<int>::iterator it = _vector.begin(); it < _vector.end(); it += 2) {       
        p.winner = *it;
        if((it + 1) != _vector.end()) p.loser = *(it + 1);
        else p.loser = -1;
        if(p.loser > p.winner) {
            int tmp;
            tmp = p.loser;
            p.loser = p.winner;
            p.winner = tmp; 
        }
        _pair.push_back(p);
    }
    
    for (size_t i = 0; i < _pair.size(); i++)
        std::cout << "(PHASE 1) pair: winner ==> " << _pair[i].winner << " loser ==> " << _pair[i].loser << std::endl;
}


int PmergeMe::binarySearch(int searchValue, int high) {
    int low = 0;
    //int high = _sortedChain.size() - 1;
    int mid = 0;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (searchValue == _sortedChain[mid])
            return mid;
        else if (searchValue > _sortedChain[mid]) { //is on the right side of the chain
            low = mid + 1;
            //mid = (low + high) / 2; 
        }
        else if (searchValue < _sortedChain[mid]) { // is on the left side of the chain
            high = mid - 1;
            //mid = (low + high) / 2; 
        }
/*         else
            return -1; */
    }
    return low;
}

void PmergeMe::sortWinners(int size) {
    if(size <= 1) {
        _sortedChain.push_back(_pair[0].winner);
        _sortedPair.push_back(_pair[0]);
        return;
    }
    sortWinners(size/2);

    for (int i = size/2; i < size; i++ ) {

        int insertion = binarySearch(_pair[i].winner, _sortedChain.size() - 1);

        _sortedChain.insert(_sortedChain.begin() + insertion, _pair[i].winner);
        _sortedPair.insert(_sortedPair.begin() + insertion, _pair[i]);
        std::cout << "(PHASE 2) _sortedChain at " << i << " iteration => ";
        for (size_t x = 0; x < _sortedChain.size(); x++) 
            std::cout << _sortedChain[x] << " ";
        std::cout << std::endl; 
    }

    for (size_t i = 0; i <  _sortedPair.size(); i++)
        std::cout << "(PHASE 2) pair sorted: winner ==> " << _sortedPair[i].winner << " loser ==> " << _sortedPair[i].loser << std::endl;
    /* for (int i = 0; i < _sortedPair.size(); i++)
        std::cout << "this is aux: winner ==> " << _sortedPair[i].winner << " loser ==> " << _sortedPair[i].loser << std::endl; */

}

int PmergeMe::getPairSize() {
    return _pair.size();
}

void PmergeMe::insertLoser(int jIndex) {
    if(_sortedPair[jIndex].loser < 0)
        return;
    int winnerPos = binarySearch(_sortedPair[jIndex].winner, _sortedChain.size() - 1);
    int insertion = binarySearch(_sortedPair[jIndex].loser, winnerPos - 1);
    std::cout << "insertLoser(" << jIndex << ") loser=" << _sortedPair[jIndex].loser << " winner=" << _sortedPair[jIndex].winner << std::endl;
    _sortedChain.insert(_sortedChain.begin() + insertion, _sortedPair[jIndex].loser); //always first special case
    std::cout << "(PHASE 3) pair inserted: winner ==> " << _sortedPair[jIndex].winner << " loser ==> " << _sortedPair[jIndex].loser << std::endl;
}

void PmergeMe::insertRemain() {
    
    int prev = 1;
    int curr = 3;
    insertLoser(0);
    insertLoser(1);
    std::cout << "outside while loop, curr = " << curr << std::endl;
    std::cout << "outside while loop, _pair.size() = " << _sortedPair.size() << std::endl;
    while (prev <= (int)_sortedPair.size()) {
        std::cout << "curr=" << curr << " prev=" << prev << std::endl;
        std::cout << "inside while loop, curr = " << curr << std::endl;
        int insertionIndex = std::min(curr, (int)_sortedPair.size() - 1);
/*         if (curr == 3) {
            for(int i = insertionIndex; i >= prev; i--)
                insertLoser(i);
        }
        else {
            for(int i = insertionIndex; i > prev; i--)
                insertLoser(i);
        } */
        for(int i = insertionIndex; i > prev; i--)
            insertLoser(i);

        // find the next Jacobsthal index
        int tmpIndex = curr + 2 * prev;
        prev = curr;
        curr = tmpIndex;
    }
    std::cout << "_vector      => ";
    for (size_t y = 0; y < _vector.size(); y++) 
            std::cout << _vector[y] << " ";
    std::cout << std::endl;
    std::cout << "_sortedChain => ";
    for (size_t x = 0; x < _sortedChain.size(); x++) 
            std::cout << _sortedChain[x] << " ";
    std::cout << std::endl; 
}