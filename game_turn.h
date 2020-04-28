//
// Created by daniel oconnell: date of completion, April 28th 2020
// header file for game_turn.c
//

#ifndef FOCUS_GAME_TURN_H
#define FOCUS_GAME_TURN_H

#endif //FOCUS_GAME_TURN_H

#include "input_output.h"

int make_turn(player *p_turn);    //function prototypes

int check_player_pieces(player *p_turn);

void choose_stack(player *p_turn);

void place_piece(player *p_turn);

void move_stack(player *p_turn, int x1, int x2, int y1, int y2);