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
    square board[BOARD_SIZE][BOARD_SIZE];
    printf("WELCOME TO FOCUS\n");
    instructions();
    initialize_players(players);
    initialize_board(board);
    print_board(board);
    while(not_ended == 1)
    {
        not_ended = make_turn(players[(count%2)], board);    //player count mod 2 should be loser
        print_board(board);
        count++;
    }
    return 0;
}
