//
// Created by Lili on 26/03/2020.
//

//
// Created by daniel oconnell: date of completion, April 28th 2020
// function: to initialise the game focus, ie the board and players
//

#include <stdio.h>
#include <stdlib.h>
#include "game_init.h"

void initialize_players(player players[PLAYERS_NUM])    //function to initialise the players
{
    int i;
    for(i=0;i<PLAYERS_NUM;i++)    //for each player
    {
        printf("PLAYER %d: ENTER NAME (10 CHARACTERS OR LESS)\n", i+1);
        fgets(players[i].p_name, 10, stdin);   //reads in player name and sets attributes for that player
        players[i].player_color = i;
        players[i].adv_cap = 0;
        players[i].own_kpt = 0;
        if(players[i].player_color ==0)    //sets correct colour
        {
            printf("YOUR COLOUR IS: RED\n");
        }
        if(players[i].player_color ==1)
        {
            printf("YOUR COLOUR IS: GREEN\n");
        }
    }
    printf("\n\n\n\n");
}

//Set Invalid Squares (where it is not possible to place stacks)
void set_invalid(square * s)
{
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
void set_empty(square * s)
{
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set squares  with a GREEN piece
void set_green(square * s)
{
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
}

//Set squares with a RED piece
void set_red(square * s)
{
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
}

//initializes the board
void initialize_board()
{

    for(int i=0; i< BOARD_SIZE; i++)
    {
        for(int j=0; j< BOARD_SIZE; j++)
        {
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else
                {
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else
                    {
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}

void instructions()    //function to print the instructions for the players
{
    printf("THE RULES ARE:\nEACH PLAYER TAKES TURNS MOVING/PLACING PIECES\n");
    printf("TO SELECT SQUARES ON THE BOARD, GIVE INPUT AS CO ORDINATE FORM, 1-8 ACROSS FOLLOWED BY 1-8 DOWN EG 1 5\n");
    printf("YOU CAN ONLY MOVE A STACK AS MANY SQUARES AS IT HAS PIECES\n");
    printf("YOU LOSE WHEN YOU CANNOT PLACE A PIECE OR MOVE A STACK\n");
    printf("ENJOY\n");
}
