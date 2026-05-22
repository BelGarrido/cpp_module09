#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

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


    while(iss >> token) {
        if(token.empty()) {
            std::cerr << "Error (empty string)" << std::endl;
            return false;
        }
        if (isValidNumber(token)) {
            char *endptr;
            errno = 0;
            long tmpNum = strtol(token.c_str(), &endptr, 10);
            if (errno == ERANGE || tmpNum > INT_MAX || tmpNum < INT_MIN || *endptr != '\0' || endptr == token.c_str()) {
                std::cerr << "Error => " << token << std::endl;
                return false;
            }
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

std::vector<pairNum> PmergeMe::makePairs(std::vector<unsigned int> &v) { //puedo pasar el vector por argumento
    std::vector<pairNum> pair;
    pairNum p;
    for (std::vector<int>::iterator it = v.begin(); it < v.end(); it += 2) {       
        p.winner = *it;
        if((it + 1) != v.end()) p.loser = *(it + 1);
        else p.loser = -1;
        if(p.loser > p.winner) {
            int tmp;
            tmp = p.loser;
            p.loser = p.winner;
            p.winner = tmp; 
        }
        pair.push_back(p);
    }

    for (size_t i = 0; i < pair.size(); i++)
        std::cout << "(PHASE 1) pair: winner ==> " << pair[i].winner << " loser ==> " << _pair[i].loser << std::endl;
}

int PmergeMe::binarySearch(int searchValue, int high) {
    int low = 0;
    int mid = 0;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (searchValue == _sortedChain[mid])
            return mid;
        else if (searchValue > _sortedChain[mid]) { //is on the right side of the chain
            low = mid + 1;
        }
        else if (searchValue < _sortedChain[mid]) { // is on the left side of the chain
            high = mid - 1;
        }
    }
    return low;
}

void PmergeMe::sortWinners(vectorS &vec, int size) {
    if(size <= 1) {
        vec._sortedChain.push_back(vec._pair[0].winner);
        vec._sortedPair.push_back(vec._pair[0]);
        return;
    }
    sortWinners(vec, size/2);

    for (int i = size/2; i < size; i++ ) {

        int insertion = binarySearch(vec._pair[i].winner, _sortedChain.size() - 1);

        _sortedChain.insert(vec._sortedChain.begin() + insertion, vec._pair[i].winner);
        _sortedPair.insert(vec._sortedPair.begin() + insertion, vec._pair[i]);
        std::cout << "(PHASE 2) _sortedChain at " << i << " iteration => ";
        for (size_t x = 0; x < vec._sortedChain.size(); x++) 
            std::cout << vec._sortedChain[x] << " ";
        std::cout << std::endl; 
    }

    for (size_t i = 0; i < vec._sortedPair.size(); i++)
        std::cout << "(PHASE 2) pair sorted: winner ==> " << vec._sortedPair[i].winner << " loser ==> " << vec._sortedPair[i].loser << std::endl;
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
    _sortedChain.insert(_sortedChain.begin() + insertion, _sortedPair[jIndex].loser); 
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

        int insertionIndex = std::min(curr, (int)_sortedPair.size() - 1);
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





std::vector<unsigned int> PmergeMe::sortVector(std::vector<unsigned int> &v) {
    
    vectorS vec;
    int i = 1;
    while (i < argc) {
        std::string input = argv[i];
        if (ford.processInput(input))
            std::cout << "continue" << std::endl;
        else{
            return 1;  
        }
        i++;
    }
    vec._pair= makePairs(v);
    sortWinners(vec, vec._pair.size());
    std::cout << "sortWinners finished" << std::endl;
    insertRemain();
}