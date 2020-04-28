//
// Created by daniel oconnell: date of completion, April 28th 2020
// function: the main function for the focus board game
//

#include <stdio.h>
#include "game_turn.h"


int main()    //main function
{
    int not_ended=1;
    int count=0;
    // declaration of the players and the board
    player players[PLAYERS_NUM];
    printf("WELCOME TO FOCUS\n");
    instructions();    //displays instructions
    initialize_players(players);
    initialize_board();    //initialise the game
    print_board();
    while(not_ended == 1)    //takes turns until the game is over
    {
        player *p_turn = &players[(count%2)];
        not_ended = make_turn(p_turn);    //player count mod 2 should be loser
        if (not_ended ==1)
        count++;
    }
    printf("PLAYER %d: NO MOVES LEFT. YOU LOSE\n\n***PLAYER %d: YOU WIN***\n\n\n", (count%2 +1), (count+1)%2 +1);//displays winner and loser
}
