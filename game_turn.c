//
// Created by daniel oconnell: date of completion, April 28th 2020
// Function: to implement the turn taking functionality for the focus board game, ie the game logic
//

#include "game_turn.h"
#include <stdio.h>
#include "stdbool.h"
#include <stdlib.h>

int make_turn(player *p_turn)
{
    bool has_stack = check_player_pieces(p_turn);    //boolean to check if the player has a stack
    if(p_turn->own_kpt>0 || has_stack == true)    //if the player can either place a piece or move a piece
    {
        printf("%s: YOUR TURN\n", p_turn->p_name);
        if (p_turn->own_kpt >= 1 && has_stack == true)    //if they can move a piece or place a piece
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
                        choose_stack(p_turn);
                        break;
                    default:
                        inv();    //error message

                }
            }
        }    //ends condition for choosing
        else if (p_turn->own_kpt > 0 && has_stack == false)    //if they can only place a piece
        {
            printf("YOU HAVE NO PIECES ON THE BOARD, AND MUST PLACE A PIECE\n");
            place_piece(p_turn);    //calls correct function
        }
        else if (p_turn->own_kpt == 0 && has_stack == true)     //if they can only move a piece
        {
            printf("MOVE A PIECE\n");
            choose_stack(p_turn);    //calls correct function
        }
        print_board();
        return 1;    //returns 1 to indicate that the player was able to take a turn
    }    //ends conditional for if player can take a turn
    else
        return 0;   //return 0 to indicate a player can no longer make a move, and loses
}

int check_player_pieces(player *p_turn)
{
    bool has_stack=false;    //boolean to check if the player has a stack
    int i,j;

    for(i = 0; i < BOARD_SIZE; i ++)
    {
        for (j = 0; j < BOARD_SIZE; j++)    //goes through each square
        {
            if(board[i][j].num_pieces >0)    //if the square has a piece
            {
                if (board[i][j].stack->p_color == p_turn->player_color)    //if the piece is the players colour
                {
                    has_stack = true;
                    break;    //exits the loop
                }
            }
        }
        if (has_stack == true)    //exits loop
            break;
    }
    if(has_stack == true)
        return 1;    //returns true or false
    else
        return 0;
}

void choose_stack(player *p_turn)    //function for the user to choose a stack to move
{    //need to debug
    int x = 0, y = 0;
    int newx = 0, newy = 0;     //declaring variables
    bool is_valid1 = false;
    bool is_same_colour1 = false;
    bool is_valid2 = false;
    bool is_same_colour2 = true;
    while (!is_valid1 || !is_same_colour1)
    {
        printf("WHICH PIECE WOULD YOU LIKE TO MOVE\n");
        scanf("%d%d", &x, &y);
        if (0 < x && x<9 && 0 < y && y < 9)
        {
            is_valid1 = (board[y - 1][x - 1].type == VALID);
            if (is_valid1)
            {
                is_same_colour1 = (board[x - 1][y - 1].stack->p_color == p_turn->player_color);
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
                                is_same_colour2 = (board[newy - 1][newx - 1].stack->p_color != p_turn->player_color);
                                if (is_same_colour2)    //code stops working here
                                {
                                    if(abs(newy-x)+abs(newx-y) == board[x-1][y-1].num_pieces)
                                    {
                                        move_stack(p_turn, x-1, newx-1, y-1, newy-1);
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

void place_piece(player *p_turn)    //function to place a piece on an empty square of the board
{
    int x=1,y=1;
    while(board[y-1][x-1].type != VALID || board[y-1][x-1].num_pieces != 0)    //loops ig not a valid square to place a piece on
        {
        printf("WHERE DO YOU WANT TO PLACE YOUR PIECE\n");    //gets user input
        scanf("%d%d", &x, &y);
        if (board[y - 1][x - 1].type == VALID && board[y-1][x-1].num_pieces == 0)    //if on an empty valid square
        {
            square *curr = &board[y-1][x-1];
            if (p_turn->player_color == GREEN)
                set_green(curr);
            else
                set_red(curr);
            break;
        }
        else
            inv();    //invalid choice
    }
    p_turn->own_kpt-=1;
}

void move_stack(player *p_turn, int x1, int x2, int y1, int y2)    //function to move a stack
{
    int count=1;    //declaring variables
    piece * top;
    piece * curr;
    piece * last = NULL;
    piece * tmp;
    top = board[y1][x1].stack;    //make top = the top piece of the moved stack
    square *remove = &board[y1][x1];
    set_empty(remove);    //set the old square as empty
    curr = top;
    while(curr->next != NULL)    //step to the last piece of the stack
    {
        curr = curr->next;
    }
    curr->next = board[y2][x2].stack;    //the last piece's next piece becomes the moved to'd stacks top piece
    board[y2][x2].stack = top;    //the top piece becomes the top piece of the moved stack
    curr = top;
    while(last!= curr && curr != NULL)
    {
        if(count<5)
        {
            curr = curr->next;    //steps to the 5th piece
            count++;
        }
        else
            {
            last = curr;
        }
    }
    if(last != NULL)
    {
        curr = curr->next;   //from the 6th piece
        while(curr != NULL)    //while the list hasn't ended
        {
            if(curr->p_color == p_turn->player_color)      //adds pieces to right counts
                p_turn->own_kpt++;
            else
                p_turn->adv_cap++;
            tmp = curr;
            curr = curr->next;    //steps to next piece and frees memory
            free(tmp);
        }
        last->next = NULL;    //makes the 5last piece's next piece null
    }
    board[y2][x2].num_pieces = count;    //the number of pieces becomes count;
}