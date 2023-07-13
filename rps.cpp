#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
using namespace std;

//TODO:
// Ways to score best target
// Able to change hard-coded 3 teams into a dynamic # of teams?
// Have the player run away from groups of enemy players vs just a single one
// Add a better fxn for changing teams


//Make a class for players instead of having a vector in a vector]
//Velocity

//Class of a game state?

//Global vars:
int player_count; //# of players
vector<vector<int>> players; //Vector containing coordinates of all players. First number indicates type status



//Hard coded min & max values for size of arena (square), as well as dimensions
int constexpr min_cord = 0;
int constexpr max_cord = 1000; 
int arena_dim = 2;


//Rock = 1, Paper = 2, Scissors = 3

void place_players();

void move(const int player_numb, bool* close_enough); //Returns the number of the closest player to a particular player
vector<int> direction(const vector<int> player_cords, const vector<int> closest_cords);


bool game_end_check();



int main(){

    srand(time(0));
    player_count = 10;

    //Get number of players
    //Will round up to nearest multiple of 3 to keep game fair

    place_players();

    bool close_enough; //A standing bool, modified each 

    //Prints player statuses:
    while(!game_end_check()){
        for (int i = 0; i < player_count; i++){


            close_enough = 0;
        }
    }


    return 0;
}


void place_players(){ //Name this initialize_game?

    player_count += player_count%3;

    int team_size = player_count/3;


    // TODO: Instead of initializing and then changing, just pushback when we randomize their coords.  
    // Look into enums (enumerators)

    //Rock
    for (int i = 0; i < team_size; i++){
        players.push_back({1,0,0});
        for (int j = 1; j <= arena_dim; j++){
            players[i][j] = rand()%max_cord;

        }
    }


    //Paper
    for (int i = team_size; i < 2*team_size; i++){
        players.push_back({2,0,0});
        for (int j = 1; j <= arena_dim; j++){
            players[i][j] = rand()%max_cord;

        }
    }

    //Scisors
    for (int i = 2*team_size; i < player_count; i++){
        players.push_back({3,0,0});
        for (int j = 1; j <= arena_dim; j++){
            players[i][j] = rand()%max_cord;

        }
    }


    return;
}

// Checks every single player's distance from current player and returns the closest
void move(const int player_numb, bool &close_enough){ //Distance field is better?

    
    float smallest_dist = max_cord*sqrt(2); //Hard code sqrt(2)?

    int closest_player;

    for (int i = 0; i < player_count; i++){

        float sum_squares = 0;
        
        if (i != player_numb){
            for (int j = 1; j <= arena_dim; j++){
                sum_squares = pow((players[i][j] - players[player_numb][j]),2);
            }

            if (sqrt(sum_squares) < smallest_dist){
                
                
                close_enough = 1;
                closest_player = i;
            }

            if(sum_squares < 1){
                    //Changes state
                }
        }
    }

    return;

}





//Checks if every player is of the same team yet
bool game_end_check(){

    int team_check = players[0][0]; //Team type of the first person
    for (int i = 1; i < player_count; i++){
        if(players[i][0] != team_check){
            return false;
        }
    }
    return true;
}





// USE THIS: for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
// turned to: for(vector<int>::iterator it = myvector.rbegin(); it != myvector.rend(); ++it)
// Remember that it is a pointer (I think?), have to use *it to get the value at the iterator