/**
 * Claudia MacRae
 * 3/19/21
 * Solves the waterjug problem with variable jug sizes. Jugs A and B are empty and C is filled to capacity.
 * I pledge my honor that I have abided by the Stevens Honor System.
*/
#include <iostream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    State(int _a, int _b, int _c, string _directions, State* _parent) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} { }
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

State* goal;

string bfs(int a, int b, int c){
    queue<State*> q;
    State* s = new State(0, 0, c, "Initial state");
    q.push(s);
    bool ** visited = new bool* [a+1];
    for(int i = 0; i < a+1; i++){
        visited[i] = new bool[b+1];
        for(int j = 0; j < b+1; j++){
            visited[i][j] = false;
        }
    }
    while(!q.empty()){
        State* current = q.front();
        q.pop();
        if(current->a == goal->a && current->b == goal->b){ //WE FOUND THE END STATE !!!
            stack<string> builder;
            while(current !=nullptr){
                builder.push(current->directions + ". " + current->to_string());
                current = current->parent;
            }
            string str = "";
            while(!builder.empty()){
                str+= builder.top() + "\n";
                builder.pop();
            }
            for(int i = 0; i < a+1; i++){   //empty visited
                delete [] visited[i];
            }
            delete [] visited;          //delete visited structure
            return str;
        }
        if(visited[current->a][current->b] == true){    //This State has been visited already
            continue;
        }
        visited[current->a][current->b] = true;
        string des;
        //TRY
        //C to A
        if(current->c != 0 && current->a != a){
            int diff = min(a - current->a, current->c);  //picks the smallest between vacancy in a and volume of c
            if(diff == 1){
                des = "Pour " + to_string(diff) + " gallon from C to A";
            }else{
                des = "Pour " + to_string(diff) + " gallons from C to A";
            }
            State * next = new State(current->a + diff, current->b, current->c - diff, des, current);
            q.push(next);
        }
        //B to A
        if(current->b != 0 && current->a != a){
            int diff = min(a - current->a, current->b);
            if(diff == 1){
                des = "Pour " + to_string(diff) + " gallon from B to A";
            }else{
                des = "Pour " + to_string(diff) + " gallons from B to A";
            } 
            State * next = new State(current->a + diff, current->b - diff, current->c, des, current);
            q.push(next);
        }
        //C to B
        if(current->c != 0 && current->b != b){
            int diff = min(b - current->b, current->c);
            if(diff == 1){
                des = "Pour " + to_string(diff) + " gallon from C to B";
            }else{
                des = "Pour " + to_string(diff) + " gallons from C to B";
            }
            State * next = new State(current->a, current->b + diff, current->c - diff, des, current);
            q.push(next);
        }
        //A to B
        if(current->a != 0 && current->b != b){
            int diff = min(b - current->b, current->a); 
            if(diff == 1){
                des = "Pour " + to_string(diff) + " gallon from A to B";
            }else{
                des = "Pour " + to_string(diff) + " gallons from A to B";
            }
            State * next = new State(current->a - diff, current->b + diff, current->c, des, current);
            q.push(next);
        }
        //B to C
        if(current->b != 0 && current->c != c){
            int diff = min(c - current->c, current->b);
            if(diff == 1){
                des = "Pour " + to_string(diff) + " gallon from B to C";
            }else{
                des = "Pour " + to_string(diff) + " gallons from B to C";
            } 
            State * next = new State(current->a, current->b - diff, current->c + diff, des, current);
            q.push(next);
        }
        //A to C
        if(current->a != 0 && current->c != c){
            int diff = min(c - current->c, current->a);
            if(diff == 1){
                des = "Pour " + to_string(diff) + " gallon from A to C";
            }else{
                des = "Pour " + to_string(diff) + " gallons from A to C";
            }  
            State * next = new State(current->a - diff, current->b, current->c + diff, des, current);
            q.push(next);
        }
    }
    if(q.empty()){
        return "No solution.";
    }
    else{
        return "HELP";
    }
}

int main(int argc, char * const argv[]){
    //Error for improper use
    if(argc != 7){  
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    //Errors for invalid acities/goals , fills jugVolumes with 6 given volumes
    int jugVolumes[6];
    istringstream iss;
    for(int i = 0; i < 6; i++){
        iss.str(argv[i+1]);
        if(!(iss >> jugVolumes[i]) || jugVolumes[i] < 0){
            cout << "Error: Invalid ";
            if(i < 3)cout << "capacity '";
            else cout << "goal '";
            cout << argv[i+1] << "' for jug ";
            switch(i){
                case 0 : cout << "A." << endl; break;
                case 1 : cout << "B." << endl; break;
                case 2 : cout << "C." << endl; break;
                case 3 : cout << "A." << endl; break;
                case 4 : cout << "B." << endl; break;
                case 5 : cout << "C." << endl; break;
            }
            return 1;
        }
        iss.clear();
    }
    if(jugVolumes[2] < 1){
        cout << "Error: Invalid capacity '0' for jug C." << endl;
        return 1;
    }
    //Errors for goals larger than acities
    if(jugVolumes[0] < jugVolumes[3]){
        cout << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if(jugVolumes[1] < jugVolumes[4]){
        cout << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if(jugVolumes[2] < jugVolumes[5]){
        cout << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    //Errors for total jug volumes
    if((jugVolumes[3] + jugVolumes[4] + jugVolumes[5]) != jugVolumes[2]){
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }


    goal = new State(jugVolumes[3], jugVolumes[4], jugVolumes[5], "Goal state");
    cout << bfs(jugVolumes[0], jugVolumes[1], jugVolumes[2]) << endl;
    delete goal;
}