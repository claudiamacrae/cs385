/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Claudia MacRae
 * Date        : 2/19/21
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const; 
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    cout <<"\nNumber of primes found: " << count_num_primes() << endl << "Primes up to " << limit_ << ":" << endl;
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    if(num_primes_ <= primes_per_row){
        for(int i = 2; i < limit_ + 1; i++) if(is_prime_[i] == true){
            cout << i;    
            if(i != max_prime_) cout << ' ';
        }
    }else{ 
        int printed_primes = 0;                 //count primes displayed in order to organize rows
        for(int i = 2; i < limit_ + 1; i++){
            if(is_prime_[i] == true){
                cout << string(max_prime_width - num_digits(i), ' ') << i;          //print number of spaces needed to fill digits, then i
                printed_primes++;
                if(printed_primes%primes_per_row == 0) cout << endl;                //if at end of row, carriage return
                else if(i != max_prime_) cout << ' ';                               // if not last to be printed, print a space
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    int count = 0;
    for(int i = 2; i < limit_ + 1; i++){        //iterate through array
        if(is_prime_[i] == true) count++;              //if prime add to the count
    }
    return count;
}

void PrimesSieve::sieve() {
    for(int i = 2; i < limit_ + 1; i++) is_prime_[i] = 1; //set all values > 1 to true
    for(int i = 2; i <= sqrt(limit_); i++){
        if(is_prime_[i] == true){                               //If i is prime
            for(int j = i*i; j<= limit_; j += i) is_prime_[j] = false;   //numbers with a factor of i are not prime;
        }
    }
    num_primes_ = count_num_primes();       //update num_primes_
    for(int i = limit_; i >= 0; i--){       //parse array backwards
        if(is_prime_[i]){
            max_prime_ = i;                 //first prime found is the largest
            break;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    int dig = 0;
    while(num > 0){
        num = num / 10;     //eliminate digit
        dig++;              //add to count
    }
    return dig;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve a = PrimesSieve(limit);
    a.display_primes();
    return 0;
}
