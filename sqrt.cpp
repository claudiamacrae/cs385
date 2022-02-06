/*
Claudia MacRae
I pledge my honor I have abided by the Stevens Honor System.
2/8/2021
*/

#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
using namespace std;

double sqrt(double num, double epsilon){
    if(num < 0){
        return numeric_limits<double>::quiet_NaN();
    }
    if (num == 1 || num == 0){
        return num;
    }
    double guess = num;
    double root;
    bool status = true;
    while(status){
        root = (guess + (num/guess))/2;
        if(abs(guess - root) <= epsilon) status = false;
        guess = root;
    }
    return root;
}

int main(int argc, char* argv[]){
    double n, e;
    istringstream iss;

    if (argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <value> [epsilon]"<< endl;
        return 1;
    }

    iss.str(argv[1]);
    if ( !(iss >> n)){         //parse num
        cerr << "Error: Value argument must be a double." << endl;
        return 1;   
    }
    if(argc > 2){              //if given, parse epsilon
        iss.clear();
        iss.str(argv[2]);
        if ( !(iss >> e) || e <= 0 ){
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;   
        }
    }else{
        e = 1e-7;
    }
    cout << fixed << setprecision(8) <<  sqrt(n, e) << endl;
    return 0;
}
