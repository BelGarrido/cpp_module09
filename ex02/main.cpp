#include "PmergeMe.hpp"

int main (int argc, char *argv[]) {
    
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " + number sequence" << std::endl;
        return 1;
    }

    struct timeval startv, endv;
    struct timeval startd, endd;

    vectorStruct vec;
    dequeStruct deq;

    int i = 1;
    while (i < argc) {
        std::string input = argv[i];
        if(!saveInput(input, vec, deq)) {
            return 1;
        }
       i++;
    }

    std::cout << "Before => ";
    for (size_t y = 0; y < deq._originalChain.size(); y++) 
            std::cout << deq._originalChain[y] << " ";
    std::cout << std::endl;
    //std::cout << std::endl;
    
    PmergeMe ford;

    // vector timing start
    gettimeofday(&startv, NULL);
    
    if (vec._originalChain.empty()) {
        std::cerr << "Error (empty input)" << std::endl;
        return 1;
    }
    std::vector<unsigned int> sortedVec = ford.sortVector(vec._originalChain);
    
    // vector timing end
    gettimeofday(&endv, NULL);

    long elapsed_seconds = endv.tv_sec  - startv.tv_sec;
    long elapsed_useconds = endv.tv_usec - startv.tv_usec;

    // deque timing start
    gettimeofday(&startd, NULL);

    if (vec._originalChain.empty()) {
        std::cerr << "Error (empty input)" << std::endl;
        return 1;
    }

    std::deque<unsigned int> sortedDeque = ford.sortDeque(deq);
    
    // deque timing end
    gettimeofday(&endd, NULL);

    long elapsed2_seconds = endd.tv_sec  - startd.tv_sec;
    long elapsed2_useconds = endd.tv_usec - startd.tv_usec;
    
    std::cout << "After  => ";
    for (size_t x = 0; x < deq._sortedChain.size(); x++) 
            std::cout << deq._sortedChain[x] << " ";
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Time to process a range of " << vec._originalChain.size() << " elements with std::[vector]: " << ((elapsed_seconds) * 1000 + elapsed_useconds / 1000.0) + 0.5 << std::endl;
    std::cout << "Time to process a range of " << deq._originalChain.size() << " elements with std::[deque]: " << ((elapsed2_seconds) * 1000 + elapsed2_useconds / 1000.0) + 0.5 << std::endl;
    return 0;
}

// Phase 1 → pairs and compare ✓
// Phase 2 → sort winners recursively using binary search on full chain ✓
// Phase 3 → insert losers in Jacobsthal order using limited binary search ✓



// insert l0            ← always first, cost 1
// insert l3, l2        ← group 2, Jacobsthal gives 3
// insert l5, l4        ← group 3, Jacobsthal gives 5
// insert l11, l10, l9, l8, l7, l6  ← group 4, Jacobsthal gives 11
// ...
