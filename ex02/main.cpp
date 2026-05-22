#include "PmergeMe.hpp"

// Phase 1 → pair and compare ✓
// Phase 2 → sort winners recursively using binary search on full chain ✓
// Phase 3 → insert losers in Jacobsthal order using limited binary search ✓


// fase 1
// 🟢 processInput()  → fills the vector with the input numbers
// 🟢 makePairs()     → compares pairs and fills a vector of {winner, loser} structs

// fase 2
// sort recursively 
// 🟢sortWinners(pairs, 4):
//    sortWinners(pairs, 2):        ← recurse on first half
//         sortWinners(pairs, 1):    ← base case, return
//         insert pairs[1] into the sorted chain of [pairs[0]]
//     insert pairs[2], pairs[3] using Jacobsthal order


// void sortWinners(vector<int> &chain, vector<Pair> &pairs, int size)
// {
//     if (size <= 1)
//     {
//         chain.push_back(pairs[0].winner); // base case, start the chain
//         return ;
//     }
//     sortWinners(chain, pairs, size / 2);
//     // insert remaining pairs[size/2 .. size-1] winners into chain
//      Binary search → finds the correct index
//      Insert at that index → places the winner in the right position
// 
// }


// main chain contains all the winners

// insert
// insert with jacobsthal
// fase 3

// insert l0            ← always first, cost 1
// insert l3, l2        ← group 2, Jacobsthal gives 3
// insert l5, l4        ← group 3, Jacobsthal gives 5
// insert l11, l10, l9, l8, l7, l6  ← group 4, Jacobsthal gives 11
// ...


int main (int argc, char *argv[]) {

    if (argc < 2)
        return 1;
    int i = 1;
    std::vector<unsigned int> vec;
    while (i < argc) {
        std::string input = argv[i];
        if(processInput(input, vec)) {
            std::cerr << "Error (duplicate number) => " << token << std::endl;
            return 1;
        }
    }



    PmergeMe ford;

/*     int i = 1;
    while (i < argc) {
        std::string input = argv[i];
        if (ford.processInput(input))
            std::cout << "continue" << std::endl;
        else{
            return 1;  
        }
        i++;
    }

    ford.makePairs();
    ford.sortWinners(ford.getPairSize());
    std::cout << "sortWinners finished" << std::endl;
    ford.insertRemain();
    return 0; */

    std::vector<unsigned int> sortedVector = ford.sortVector(std::string &input);
    std::deque<unsigned int> sortedDeque = ford.sortVector(std::string &input);
}
