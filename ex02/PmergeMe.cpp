#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)  {
    (void)other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe() {}

// ------------------------ process input  ------------------------ //

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

bool saveInput(std::string &input,vectorStruct &vec, dequeStruct &deq) {

    std::istringstream iss(input);
    std::string token;
    while(iss >> token) {

        if (isValidNumber(token)) {
            char *endptr;
            errno = 0;
            long tmpNum = strtol(token.c_str(), &endptr, 10);
            if (errno == ERANGE || tmpNum > INT_MAX || *endptr != '\0' || endptr == token.c_str()) {
                std::cerr << "Error => " << token << std::endl;
                return false;
            }
            std::vector<unsigned int>::iterator it = std::find(vec._originalChain.begin(), vec._originalChain.end(), tmpNum);
            if(vec._originalChain.empty() || it == vec._originalChain.end()) {
                vec._originalChain.push_back(tmpNum);
                deq._originalChain.push_back(tmpNum);
            }
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

// VECTORS VECTORS VECTORS VECTORS VECTORS VECTORS VECTORS 
// ------------------------ make pairs  ------------------------ //

std::vector<pairNum> makePairs(std::vector<unsigned int> &v) { //puedo pasar el vector por argumento
    
    std::vector<pairNum> pair;
    pairNum p;
    for (std::vector<unsigned int>::iterator it = v.begin(); it < v.end(); it += 2) {       
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
    return pair;
}

// ------------------------ algorithms  ------------------------ //

int binarySearch(vectorStruct vec, unsigned searchValue, int high) {
    int low = 0;
    int mid = 0;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (searchValue == vec._sortedChain[mid])
            return mid;
        else if (searchValue > vec._sortedChain[mid]) { //is on the right side of the chain
            low = mid + 1;
        }
        else if (searchValue < vec._sortedChain[mid]) { // is on the left side of the chain
            high = mid - 1;
        }
    }
    return low;
}

void sortWinners(vectorStruct &vec, int size) {
    if(size <= 1) {
        vec._sortedChain.push_back(vec._pair[0].winner);
        vec._sortedPair.push_back(vec._pair[0]);
        return;
    }
    sortWinners(vec, size/2);

    for (int i = size/2; i < size; i++ ) {

        int insertion = binarySearch(vec, vec._pair[i].winner, vec._sortedChain.size() - 1);

        vec._sortedChain.insert(vec._sortedChain.begin() + insertion, vec._pair[i].winner);
        vec._sortedPair.insert(vec._sortedPair.begin() + insertion, vec._pair[i]);
    }
}

void insertLoser(vectorStruct &vec, int jIndex) {
    if(vec._sortedPair[jIndex].loser < 0)
        return;
    int winnerPos = binarySearch(vec, vec._sortedPair[jIndex].winner, vec._sortedChain.size() - 1);
    int insertion = binarySearch(vec, vec._sortedPair[jIndex].loser, winnerPos - 1);

    vec._sortedChain.insert(vec._sortedChain.begin() + insertion, vec._sortedPair[jIndex].loser); 
}

void insertRemain(vectorStruct &vec) {

    int prev = 1;
    int curr = 3;
    insertLoser(vec, 0);
    insertLoser(vec, 1);

    while (prev <= (int)vec._sortedPair.size()) {

        int insertionIndex = std::min(curr, (int)vec._sortedPair.size() - 1);
        for(int i = insertionIndex; i > prev; i--)
            insertLoser(vec, i);

        // find the next Jacobsthal index
        int tmpIndex = curr + 2 * prev;
        prev = curr;
        curr = tmpIndex;
    }
}

std::vector<unsigned int> PmergeMe::sortVector(std::vector<unsigned int> &v) {

    vectorStruct vec;
    vec._pair = makePairs(v);
    sortWinners(vec, vec._pair.size());
    insertRemain(vec);
    return vec._sortedChain;
}

// DEQUE DEQUE DEQUE DEQUE DEQUE DEQUE DEQUE DEQUE DEQUE DEQUE DEQUE 
// ------------------------ make pairs  ------------------------ //

std::deque<pairNum> makePairs(std::deque<unsigned int> &d) {
    
    std::deque<pairNum> pair;
    pairNum p;
    for (std::deque<unsigned int>::iterator it = d.begin(); it < d.end(); it += 2) {       
        p.winner = *it;
        if((it + 1) != d.end()) p.loser = *(it + 1);
        else p.loser = -1;
        if(p.loser > p.winner) {
            int tmp;
            tmp = p.loser;
            p.loser = p.winner;
            p.winner = tmp; 
        }
        pair.push_back(p);
    }
    return pair;
}

// ------------------------ algorithms  ------------------------ //

int binarySearch(dequeStruct deq, unsigned searchValue, int high) {
    int low = 0;
    int mid = 0;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if (searchValue == deq._sortedChain[mid])
            return mid;
        else if (searchValue > deq._sortedChain[mid]) { //is on the right side of the chain
            low = mid + 1;
        }
        else if (searchValue < deq._sortedChain[mid]) { // is on the left side of the chain
            high = mid - 1;
        }
    }
    return low;
}

void sortWinners(dequeStruct &deq, int size) {
    if(size <= 1) {
        deq._sortedChain.push_back(deq._pair[0].winner);
        deq._sortedPair.push_back(deq._pair[0]);
        return;
    }
    sortWinners(deq, size/2);

    for (int i = size/2; i < size; i++ ) {

        int insertion = binarySearch(deq, deq._pair[i].winner, deq._sortedChain.size() - 1);

        deq._sortedChain.insert(deq._sortedChain.begin() + insertion, deq._pair[i].winner);
        deq._sortedPair.insert(deq._sortedPair.begin() + insertion, deq._pair[i]);
    }
}

void insertLoser(dequeStruct &deq, int jIndex) {
    if(deq._sortedPair[jIndex].loser < 0) {
        //std::cout << "JACOBSTHAL CHECK, insert: (" << jIndex << ") ❌ loser=" << deq._sortedPair[jIndex].loser << " winner=" << deq._sortedPair[jIndex].winner << std::endl;
        return;
    }
        
    int winnerPos = binarySearch(deq, deq._sortedPair[jIndex].winner, deq._sortedChain.size() - 1);
    int insertion = binarySearch(deq, deq._sortedPair[jIndex].loser, winnerPos - 1);

    //std::cout << "JACOBSTHAL CHECK, insert: (" << jIndex << ") ✔️  loser=" << deq._sortedPair[jIndex].loser << " winner=" << deq._sortedPair[jIndex].winner << std::endl;
    deq._sortedChain.insert(deq._sortedChain.begin() + insertion, deq._sortedPair[jIndex].loser); 
}

void insertRemain(dequeStruct &deq) {

    int prev = 1;
    int curr = 3;
    insertLoser(deq, 0);
    //std::cout << "sortedPair size: " << deq._sortedPair.size() << std::endl;
    if(deq._sortedPair.size() > 1) {
        //std::cout << "calling insertLoser(1)" << std::endl;
        insertLoser(deq, 1);
}
    while (prev <= (int)deq._sortedPair.size()) {

        int insertionIndex = std::min(curr, (int)deq._sortedPair.size() - 1);
        //std::cout << "INSERTION INDEX: " << insertionIndex << ") ⬅️ " << std::endl;
        for(int i = insertionIndex; i > prev; i--)
            insertLoser(deq, i);

        // find the next Jacobsthal index
        int tmpIndex = curr + 2 * prev;
        prev = curr;
        curr = tmpIndex;
    }
}

std::deque<unsigned int> PmergeMe::sortDeque(dequeStruct &deq) {

    deq._pair = makePairs(deq._originalChain);
    sortWinners(deq, deq._pair.size());
    insertRemain(deq);
    return deq._sortedChain;
}
