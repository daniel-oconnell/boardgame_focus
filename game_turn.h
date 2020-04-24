//
// Created by danoc on 20/04/2020.
//

#ifndef FOCUS_GAME_TURN_H
#define FOCUS_GAME_TURN_H

#endif //FOCUS_GAME_TURN_H

#include "input_output.h"

int make_turn(player p_turn, square board[][BOARD_SIZE]);

int check_player_pieces(player p_turn, square board[][BOARD_SIZE]);

void choose_stack(player p_turn, square board[][BOARD_SIZE]);

void place_piece(player p_turn, square board[][BOARD_SIZE]);

void inv();

void move_stack(player p_turn, square board[][BOARD_SIZE], int x1, int x2, int y1, int y2);