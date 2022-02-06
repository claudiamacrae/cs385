/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Claudia MacRae 
 * Date        : 3/8/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector< vector <int> > ways;
    if(num_stairs <= 0){
        ways.push_back(vector<int>());
    }
    for(int i = 1; i <= 3; i++){
        if(num_stairs >= i){
            vector< vector <int> > result = get_ways(num_stairs - i);
            for(int j = 0; j < (int)result.size(); j++){
                result[j].insert(result[j].begin(), i);     //insert i to front of each list
                ways.push_back(result[j]);
            }
        }
    }
    return ways;
}

int num_digits(int num) {
    int dig = 0;
    while(num > 0){
        num = num / 10;     //eliminate digit
        dig++;              //add to count
    }
    return dig;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int way_count_dig = num_digits(ways.size());
    for(int i = 0; i < (int)ways.size(); i++){
        cout << string(way_count_dig - num_digits(i + 1), ' ') << i + 1 << ". [";
        for(int j = 0; j < (int)ways[i].size(); j++){
            cout << ways[i][j];
            if(j + 1 != (int)ways[i].size()) cout << ", ";
        }
        cout << ']' << endl;
    }
}

int main(int argc, char * const argv[]) {
    cout << "HERE"<< endl;
    int stairs;
    istringstream iss;
    if(argc != 2){
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if(!(iss >> stairs) || stairs <= 0){
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    vector< vector<int> > ways = get_ways(stairs);
    if(stairs == 1) cout << ways.size() << " way to climb " << stairs << " stair." << endl;
    else cout << ways.size() << " ways to climb " << stairs << " stairs." << endl;
    display_ways(ways);
    return 0;
}
