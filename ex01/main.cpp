#include "RPN.hpp"

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " + operation in RPN format" << std::endl;
        return 1;
    }
    
    std::string input = argv[1];

    RPN polish(input);
    return (polish.calculate());
}
