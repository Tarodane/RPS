#include <iostream>
#include <vector>
using namespace std;

class player{
    public:

        int test_int;

};




int main() {
    
    // int n = 10;
    // vector<player> player_vect;

    // /player_vect.test_int = 2;

    vector<int> a = {3,4,5};
    vector<int> b = {2, 2, 4};

    // vector<int> myVector = (a - b);

    vector<int> movement_vector = vector<int>(10, 0); 
    for (std::vector<int>::iterator it = movement_vector.begin() ; it != movement_vector.end(); ++it){
        cout << *it << endl;
    }


    return 0;
}