#include <iostream>
#include <vector>
using namespace std;

//TODO:
// Ways to score best target

//Global vars:
int player_count = 12; //# of players
vector<vector<int>> players; //Vector containing coordinates of all players. First number indicates type status

//Hard coded min & max values for size of arena (square), as well as dimensions
int min_cord = 0;
int max_cord = 1000; 
int arena_dim = 2;


//Rock = 1, Paper = 2, Scissors = 3

void place_players();
 
vector<int> distances(int player_numb); //Returns ranks of closest players to a particular player
int move(int player_numb, vector<int> ranks);

int main(){

    //Get number of players
    //Will round up to nearest multiple of 3 to keep things fair

    place_players();





    return 0;
}


void place_players(){

    if (player_count%3 == 1){
        player_count += 2;
    }
    else if (player_count%3 == 2){
        player_count++;
    }



    int team_size = player_count/3;

    //Rock
    for (int i = 0; i < team_size; i++){

    }

    //Paper
    for (int i = team_size; i < 2*team_size; i++){
        
    }

    //Scisors
    for (int i = 2*team_size; i < player_count; i++){
        
    }


    return;
}


