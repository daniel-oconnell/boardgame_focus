//
// Created by danoc on 20/04/2020.
// Function: to implement the turn taking functionality for the focus board game
//

#include "game_turn.h"
#include <stdio.h>
#include "stdbool.h"

int make_turn(player p_turn, square board[][BOARD_SIZE])
{
    bool has_stack=false;    //boolean to check if the player has a stack
    int i,j;

    for(i = 0; i < BOARD_SIZE; i ++)
    {
        for (j = 0; j < BOARD_SIZE; j++)    //goes through each square
        {
            if(board[i][j].num_pieces >0)    //if the square has a piece
            {
                if (board[i][j].stack->p_color == p_turn.player_color)    //if the piece is the players colour
                {
                    has_stack = true;
                    break;    //exits the loop
                }
            }
        }
        if (has_stack == true)
            break;
    }
    if(p_turn.own_kpt>0 || has_stack == true)    //if the player can either place a piece or move a piece
    {
        printf("%s: YOUR TURN\n", p_turn.p_name);
        if (p_turn.own_kpt > 0 && has_stack == true)    //if they can move a piece or place a piece
        {
            int choice=0;
            while(choice!=1 && choice !=2)    //loop while they haven't made a correct choice
            {
                printf("PRESS 1 TO PLACE A PIECE\nPRESS 2 TO MOVE A STACK\n");    //takes input
                scanf("%d", &choice);
                switch (choice)    //calls correct functions according to choice
                {
                    case 1:
                        place_piece(p_turn);
                        break;
                    case 2:
                        move_stack(p_turn);
                        break;
                    default:
                        printf("INVALID\n");    //error message

                }
            }
        }    //ends condition for choosing
        else if (p_turn.own_kpt > 0 && has_stack == false)    //if they can only place a piece
        {
            printf("YOU HAVE NO PIECES ON THE BOARD, AND MUST PLACE A PIECE\n");
            place_piece(p_turn);    //calls correct function
        }
        else if (p_turn.own_kpt == 0 && has_stack == true)     //if they can only move a piece
        {
            printf("MOVE A PIECE\n");
            move_stack(p_turn);    //calls correct function
        }
        return 1;    //returns 1 to indicate that the player was able to take a turn
    }    //ends conditional for if player can take a turn
    else
        return 0;   //return 0 to indicate a player can no longer make a move, and loses
}

void move_stack(player p_turn)
{

}

void place_piece(player p_turn)
{

}

