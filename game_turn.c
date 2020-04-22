//
// Created by danoc on 20/04/2020.
//

#include "game_turn.h"
#include <stdio.h>
#include "stdbool.h"

int make_turn(player p_turn, square board[][BOARD_SIZE])
{
    bool has_stack=false;
    int i,j;

    for(i = 0; i < BOARD_SIZE; i ++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if(board[i][j].num_pieces >0)
            {
                if (board[i][j].stack->p_color == p_turn.player_color)
                {
                    has_stack = true;
                    break;
                }
            }
        }
        if (has_stack == true)
            break;
    }
    if(p_turn.own_kpt>0 || has_stack == true)
    {
        printf("%s: YOUR TURN\n", p_turn.p_name);
        if (p_turn.own_kpt > 0 && has_stack == true)    //need condition for if they can move a stack   maybe bool with for loop for the board to check if theyve anything?
        {
            int choice=0;
            while(choice!=1 && choice !=2)
            {
                printf("PRESS 1 TO PLACE A PIECE\nPRESS 2 TO MOVE A STACK\n");//needs switch statement
                scanf("%d", &choice);
                switch (choice)
                {
                    case 1:
                        place_piece(p_turn);
                        break;
                    case 2:
                        move_stack(p_turn);
                        break;
                    default:
                        printf("INVALID\n");

                }
            }
        }
        else if (p_turn.own_kpt > 0 && has_stack == false)
        {
            printf("YOU HAVE NO PIECES ON THE BOARD, AND MUST PLACE A PIECE\n");
            place_piece(p_turn);
        }
        else if (p_turn.own_kpt == 0 && has_stack == true)
        {
            printf("MOVE A PIECE\n");
            move_stack(p_turn);
        }
        return 1;
    }
    else
        return 0;
}

void move_stack(player p_turn)
{

}

void place_piece(player p_turn)
{

}

