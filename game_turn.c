//
// Created by danoc on 20/04/2020.
// Function: to implement the turn taking functionality for the focus board game
//

#include "game_turn.h"
#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>

int make_turn(player p_turn, square board[][BOARD_SIZE])
{
    bool has_stack = check_player_pieces(p_turn, board);    //boolean to check if the player has a stack
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
                        place_piece(p_turn, board);
                        break;
                    case 2:
                        choose_stack(p_turn, board);
                        break;
                    default:
                        inv();    //error message

                }
            }
        }    //ends condition for choosing
        else if (p_turn.own_kpt > 0 && has_stack == false)    //if they can only place a piece
        {
            printf("YOU HAVE NO PIECES ON THE BOARD, AND MUST PLACE A PIECE\n");
            place_piece(p_turn, board);    //calls correct function
        }
        else if (p_turn.own_kpt == 0 && has_stack == true)     //if they can only move a piece
        {
            printf("MOVE A PIECE\n");
            choose_stack(p_turn, board);    //calls correct function
        }
        return 1;    //returns 1 to indicate that the player was able to take a turn
    }    //ends conditional for if player can take a turn
    else
        return 0;   //return 0 to indicate a player can no longer make a move, and loses
}

int check_player_pieces(player p_turn, square board[][BOARD_SIZE])
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
    if(has_stack == true)
        return 1;
    else
        return 0;
}

void choose_stack(player p_turn, square board[][BOARD_SIZE]) {    //need to debug
    int x = 0, y = 0;
    int newx = 0, newy = 0;
    bool is_valid1 = false;
    bool is_same_colour1 = false;
    bool is_valid2 = false;
    bool is_same_colour2 = true;
    while (!is_valid1 || !is_same_colour1)
    {
        printf("WHICH PIECE WOULD YOU LIKE TO MOVE\n");
        scanf("%d %d\n\n\n", &x, &y);
        if (0 < x && x<9 && 0 < y && y < 9)
        {
            is_valid1 = (board[y - 1][x - 1].type == VALID);
            if (is_valid1)
            {
                is_same_colour1 = (board[x - 1][y - 1].stack->p_color == p_turn.player_color);
                if (is_same_colour1)
                {
                    while (is_same_colour2 || !is_valid2)    //doesnt loop
                    {
                        printf("WHAT SQUARE WOULD YOU LIKE TO MOVE IT TO\n");
                        scanf("%d%d", &newx, &newy);
                        is_valid2 = (board[newy - 1][newx - 1].type == VALID);
                        if (0 < x && x < 9 && 0 < y && y < 8)
                        {
                            if (is_valid2)
                            {
                                is_same_colour2 = (board[newy - 1][newx - 1].stack->p_color != p_turn.player_color);
                                if (is_same_colour2)    //code stops working here
                                {
                                    if(abs(newy-x)+abs(newx-y) == board[x-1][y-1].num_pieces)
                                    {
                                        move_stack(p_turn, board, x-1, newx-1, y-1, newy-1);
                                    }
                                    else
                                        {
                                        inv();
                                    }
                                }
                            }
                            else
                                {
                                inv();
                            }
                        }
                        else
                            {
                            inv();
                        }
                    }
                }
                else
                    {
                    inv();
                }
            }
            else
                {
                inv();
            }
        }
        else
            {
            inv();
        }
    }
}

void place_piece(player p_turn, square board[][BOARD_SIZE])    //function to place a piece on an empty square of the board
{
    int x=0,y=0;
    do
        {
        printf("WHERE DO YOU WANT TO PLACE YOUR PIECE\n");    //gets user input
        scanf("%d%d", &x, &y);
        if (board[y - 1][x - 1].type == VALID && board[y-1][x-1].num_pieces == 0)    //if on an emptty valid square
        {
            board[y-1][x-1].num_pieces =1;
            board[y-1][x-1].stack->p_color = p_turn.player_color;    //adds a piece of the players colour to the square
        }
        else
            inv();    //invalid choice
    }while(board[y-1][x-1].type != VALID || board[y-1][x-1].num_pieces != 0);    //loops ig not a valid square to place a piece on
}

void inv()
{
    printf("INVALID CHOICE\n");
}

void move_stack(player p_turn, square board[][BOARD_SIZE], int x1, int x2, int y1, int y2)
{
    int count, i;
    board[y2][x2].num_pieces += board[y1][x1].num_pieces;
    if(board[y2][x2].num_pieces >5)
    {
        count = (board[y2][x2].num_pieces-5);
        for(i=0;i<count;i++)
        {
            if(i%2 == 0)
            {
                p_turn.adv_cap++;
            }
            else
                {
                p_turn.own_kpt++;
            }
        }
        board[y2][x2].num_pieces = 5;
    }
    board[y1][x1].num_pieces = 0;
}