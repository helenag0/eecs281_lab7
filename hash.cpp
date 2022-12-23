// Testing file provided for EECS 281 Lab 7

#include "hashtable.h"
#include <string>
#include <iostream>

int main() {

    // VERY BASIC EXAMPLE (will likely not compile with default/empty hashtable.h file)
    HashTable<std::string, int> midterm;
    std::cout << midterm.insert("sam", 50) << " ";
    std::cout << midterm.insert("fee", 100) << " ";
    std::cout << midterm.insert("milo", 95) << " ";
    std::cout << midterm.insert("gabe", 88) << " \n";
    std::cout << midterm["sam"] << " ";
    std::cout << midterm["fee"] << " ";
    std::cout << midterm["milo"] << " ";
    std::cout << midterm["gabe"] << " \n";
    std::cout << midterm.erase("sam") << " ";
    std::cout << midterm["sam"] << "\n";
    
    // ADD MORE TESTS OF YOUR OWN
    
    midterm["me"] = 20;
    std::cout << midterm["me"] << "\n";
    
    HashTable<std::string, int> test;
    std::cout << test.insert("CCC", 8) << " ";
    std::cout << test["CCC"] << " ";
    test["AAA"] = 2;
    std::cout << test["AAA"] << " ";
    std::cout << test.insert("DDD", 9) << " ";
    std::cout << test["DDD"] << " ";
    
    return 0;
}
