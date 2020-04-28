//
// Created by daniel oconnell: date of completion, April 28th 2020
// function: to implement input/output functions for the focus board game

#include <stdio.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board()
{
    printf("****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if(board[i][j].type == VALID)
            {
                if(board[i][j].stack == NULL)
                    printf("|     ");
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G");
                    else
                        printf("| R");
                    printf("(%d)", board[i][j].num_pieces);
                }
            }
            else
                printf("|  -  ");
        }
        printf("|\n");
    }
}

void inv()    //function to print invalid choice to the screen
{
    printf("INVALID CHOICE\n");
}