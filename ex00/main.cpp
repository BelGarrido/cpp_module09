#include "BitcoinExchange.hpp"
// pseudocode

// 1) divide with getline and stores the date in a string date and string value
// 2) parse the format in the string date to see if valid date
//        IF is valid
//        2.1) parse the value and if valid use stringstream to ss >> float
// 3) if both valids, we save it in a pair of map <string, float>



// 1. open the file
// 2. read line by line
// 3. split each line at '|'
// 4. store in map<string, float>
// 4. open the file
// 5. read line by line
// 6. validate date ()
// 7. validate value (not negative, not > 1000)
// 8. use that date to look up the price in map

// - wrong format (missing -, wrong length, spaces)
// - month out of range (< 1 or > 12)
// - day out of range (< 1 or > 31)
// - value is negative
// - value is higher than 1000
// - empty value
// - missing |

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        return 1;
    }
    // create an object BitcoinExchange
    BitcoinExchange btc;
    // load the database in _database attribute of BTC
    btc.loadDatabase("../data.csv");
    // open, read, validate and query of input key
    btc.processInput("../input.txt");
    
    return 0;
}


// map<string, vector<int>> data;
// data["numbers"] = {10, 20, 30};
// data["others"] = {40, 50, 60};

// map<string, vector<int>>::iterator eso;
// vector<int>::iterator it;

// for(eso = data.begin(); eso != data.end(); ++eso){
//     for(it = eso->second.begin(); it != eso->second.end(); ++it){
//         cout << eso->first << " => " << *it << '\n';
//     }
// }



// int main() {

// std::cout << "Por favor, introduce la cadena de caracteres\n";
// std::string input  = " ";
// std::getline(std::cin, input);
// cout << input << endl;
// }