#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

#define ROCK 0
#define PAPER 1
#define SCISSORS 2


class Player {       // The class
    public:

        //Vars
        vector<float> position;
        int team; //This is assigned external from constructor


        //Methods
        vector<float> get_position();
        int get_team();     

        void set_position(int arena_dim, int arena_size);

        void assign_team(int team_name);
        void move_position(vector<float> move_vect, int arena_size);


};



// Method/function definition outside the class
void Player::set_position(int arena_dim, int arena_size) {

    for (int i = 0; i < arena_dim; i++){
        position.push_back(rand()%arena_size);
    }

}

vector<float> Player::get_position(){
    return position;
} 

int Player::get_team(){
    return team;
}

void Player::assign_team(int team_name){
    team = team_name;
}

void Player::move_position(vector<float> move_vect, int arena_size){
    
    for (int i = 0; i < position.size(); i++){ 
        position[i] += move_vect[i];

        //Makes sure we stay within bounds of the arena
        if (position[i] < 0){
            position[i] = 0;
        }
        else if (position[i] > arena_size){
            position[i] = static_cast<float>(arena_size);
        }
    } 
}


//Global Fxns


vector<float> get_move_vector(int moving_player, vector<Player> &player_vect, int player_count, int arena_dim, int numb_of_teams);

float distance_ab(Player &a, Player &b, int arena_dim, int numb_of_teams);
void a_tagged_b(Player &a, Player &b, int numb_of_teams);

bool sim_end_check(int player_count, vector<Player> player_vect);

string team_to_string(int team);

void draw_game(vector<Player> &player_vect, int arena_size);

void on_end(){
    endwin(); // Calls the fxn in the argument when the program ends (nonspecific to ncurses)
}


int main(){

    initscr(); // ncurses
    curs_set(0); //Makes so that the curser isn't visible in render
    refresh(); //Clears screen
    atexit(&on_end); 

    srand(time(0));

    int player_count = 12; //Hard coded now, but want to make this dynamic later
    int numb_of_teams = 3; // Dido above ^^^
    int arena_dim = 2; //Dido above
    int arena_size = 50; //Dido above

    player_count += player_count%numb_of_teams; // Makes sure team sizes are equal

    vector<Player> player_vect = vector<Player>(player_count);
    for (int i = 0; i < player_count; i++){
        player_vect[i].set_position(arena_dim, arena_size);
        player_vect[i].assign_team(i%numb_of_teams);
    }


    int frame_counter = 0;

    while(!sim_end_check(player_count, player_vect)){

        frame_counter += 1;
        // if (frame_counter > 2000){
        //     return 0;
        // }

        for (int i = 0; i < player_count; i++){
            //cout << "Player" << i <<": "; 
            for (int j = 0; j < arena_dim; j++){
                //cout << player_vect[i].get_position()[j] << ", ";
            } 
                //cout << endl;

            vector<float> move_vector = get_move_vector(i, player_vect, player_count, arena_dim, numb_of_teams);
            player_vect[i].move_position(move_vector, arena_size);

        }

        draw_game(player_vect, arena_size);
        usleep(1e5); //Pauses in microseconds

        // if (frame_counter%5000 == 0)
        //     cout << "=====: " << frame_counter << endl;

        

    }

    endwin();

    cout << team_to_string(player_vect[0].get_team()) << " Won!" << endl;


    return 0;
}



vector<float> get_move_vector(int moving_player, vector<Player> &player_vect, int player_count, int arena_dim, int numb_of_teams){ //Should I be passing by reference to save on space?
    
    vector<float> movement_vector = vector<float>(arena_dim, 0); 

    for (int other_player = 0; other_player < player_count; other_player++){
        if (other_player != moving_player){
            float distance = distance_ab(player_vect[moving_player], player_vect[other_player], arena_dim, numb_of_teams);
            vector<float> player_pos = player_vect[moving_player].get_position();
            vector<float> other_pos = player_vect[other_player].get_position();
            for (int i = 0; i < arena_dim; i++){
                
                if(distance != 0){

                    if ((player_vect[moving_player].get_team() + numb_of_teams - 1)%numb_of_teams == player_vect[other_player].get_team()){ //Teams beat those whose teams are immediately below them
                        movement_vector[i] = other_pos[i] - player_pos[i]; //Moves towards other player
                    }
                    else if ((player_vect[moving_player].get_team() + 1)%numb_of_teams == player_vect[other_player].get_team()){ //Teams lose to the teams immediately above them
                        movement_vector[i] = player_pos[i] - other_pos[i]; //Moves away from other player
                    }

                    //movement_vector[i] /= sqrtf(distance_ab(player_vect[moving_player], player_vect[other_player], arena_dim, numb_of_teams)); //Scales movement based on distance
                    
                     if(movement_vector[i] > 2){
                         movement_vector[i] = 2;
                     }
                    
                    
                    //movement_vector[i] /= 10;
                }
            }
        }
    } 
    return movement_vector;
}


float distance_ab(Player &a, Player &b, int arena_dim, int numb_of_teams){
    vector<float> pos_a = a.get_position();
    vector<float> pos_b = b.get_position();

    float sum_squares = 0;

    for (int i = 0; i < arena_dim; i++){
        sum_squares += pow(pos_b[i] - pos_a[i],2); //Hate how I'm not using an iterator here but what else is a man to do when looking at two vectors
    } 

    float distance = sqrtf(sum_squares);

    if (distance < 1.5){
        a_tagged_b(a, b, numb_of_teams);
    }

    return distance;

}


void a_tagged_b(Player &a, Player &b, int numb_of_teams){

    int a_team = a.get_team();
    int b_team = b.get_team();

    if((a_team-1)%numb_of_teams == b_team){ //Teams beat those whose teams are immediately below them
        b.assign_team(a_team);
    }
    else if((a_team+1)%numb_of_teams == b_team){ //Teams lose to the teams immediately above them

        a.assign_team(b_team);

    }
    
}



//Checks if every Player is of the same team
bool sim_end_check(int player_count, vector<Player> player_vect){

    int team_check = player_vect[0].get_team(); //Team type of the first person
    for (int i = 1; i < player_count; i++){
        if(player_vect[i].get_team() != team_check){
            return false;
        }
    }
    return true;
}




string team_to_string(int team){

    string winner_str;

    switch (team){
        case 0:
        winner_str = "Rock";
        break;

        case 1:
        winner_str = "Paper";
        break;
        
        case 2:
        winner_str = "Scissors";
        break;
    }

    return winner_str;
}


void draw_game(vector<Player> &player_vect, int arena_size){

     

    erase(); //Clears last screen

    for (size_t i = 0; i < player_vect.size(); i++){ // Look into size_t's & range-based for loops
        
        mvaddch(static_cast<float>(arena_size) - player_vect[i].get_position()[1], player_vect[i].get_position()[0], team_to_string(player_vect[i].get_team())[0]);

    } 

    refresh();
}


