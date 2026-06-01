#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " + file.txt" << std::endl;
        return 1;
    }
    // create an object BitcoinExchange
    BitcoinExchange btc;
    // load the database in _database attribute of BTC
    if(!btc.loadDatabase("data.csv"))
        return 1;
    // open, read, validate and query of input key
    btc.processInput(argv[1]);
    
    return 0;
}

// Structure

// 1. open the file
// 2. read line by line
// 3. split each line at '|'
// 4. store in map<string, float>
// 4. open the file
// 5. read line by line
// 6. validate date ()
// 7. validate value (not negative, not > 1000)
// 8. use that date to look up the price in map

// Posible Errors

// - wrong format (missing -, wrong length, spaces)
// - month out of range (< 1 or > 12)
// - day out of range (< 1 or > 31)
// - value is negative
// - value is higher than 1000
// - empty value
// - missing |