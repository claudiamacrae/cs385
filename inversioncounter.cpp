/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Claudia MacRae
 * Version     : 1.0
 * Date        : 3/31/21
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for(int i = 0; i < length; i++){
        for(int j = i + 1; j < length ; j++){
            if(array[i] > array[j]) count++;
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int* scratch = new int[length];
    long inversions = mergesort(array, scratch, 0, length - 1);
    delete [] scratch;
    return inversions;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long count = 0;
    if(low < high){
        int mid = (low + ((high - low))/2); 
        count = mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid + 1, high);
        int L = low;
        int H = mid + 1;
        int index = low;
        while(L <= mid && H <= high){
            if(array[L] <= array[H]){
                scratch[index] = array[L];
                L += 1;
                index +=1;
            }else{
                scratch[index] = array[H];
                count += (mid + 1 - L);
                H += 1;
                index +=1;
            }
        }
        while(L <= mid){
            scratch[index] = array[L];
            L += 1;
            index +=1;
        }
        while(H <= high){
            scratch[index] = array[H];
            H += 1;
            index +=1;
        }

        for(int i = low; i <= high; i++){
            array[i] = scratch[i];
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    bool slow = false;
    if(argc > 2){
        cerr << "Usage: ./inversioncounter [slow]";
        return 1;
    }
    if(argc == 2){
        if(strcmp(argv[1],"slow") == 0){
            slow = true;
        }else if(argv[1] != nullptr){
           cerr << "Error: Unrecognized option '" << argv[1] << "'.";
            return 1;
        }
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    if(values.size() > 0){
        cout << "Number of inversions: ";
        if(slow){
            cout << count_inversions_slow(&values[0], values.size());
        }else{
            cout << count_inversions_fast(&values[0], values.size());
        }
    }
    else{
        cerr << "Error: Sequence of integers not received.";
        return 0;
    }
}
