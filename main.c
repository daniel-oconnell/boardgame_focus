//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>
#include "game_turn.h"


int main()
{
    int not_ended=1;
    int count=0;
    // declaration of the players and the board
    player players[PLAYERS_NUM];
    printf("WELCOME TO FOCUS\n");
    instructions();
    initialize_players(players);
    initialize_board();
    print_board();
    while(not_ended == 1)
    {
        player *p_turn = &players[(count%2)];
        not_ended = make_turn(p_turn);    //player count mod 2 should be loser
        if (not_ended ==1)
        count++;
    }
    printf("PLAYER %d: NO MOVES LEFT. YOU LOSE\n\n***PLAYER %d: YOU WIN***\n\n\n", (count%2 +1), (count+1)%2 +1);
    return 0;
}
