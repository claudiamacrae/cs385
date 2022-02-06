/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Claudia MacRae
 * Date        : 2/28/2021
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    //Returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for(const auto &ch : s){
        if(ch < 'a' || ch > 'z') return false;
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    unsigned int storage = 0;
    for(const auto &ch : s){
        int index = ch - 'a';                       //index is n where ch is the nth letter of the alphabet
        if((storage & (1 << index)) != 0){
            return false;
        }
        storage = storage | (1 << index);       //mark letter seen in storage
    }
    return true;
}

int main(int argc, char * const argv[]) {
    //Reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc != 2){
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    }
    if(!is_all_lowercase(argv[1])){
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    if(all_unique_letters(argv[1])){
        cout << "All letters are unique." << endl;
    }else{
        cout << "Duplicate letters found." << endl;
    }
}
