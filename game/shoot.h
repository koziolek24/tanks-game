#pragma once
#include "board.h"
#include "tank.h"
#include "User.h"
// void shoot(){}

void get_side(Tank& player, Tank& opponent, Board& board, User user);

bool shoot_right(Tank& player, Tank& opponent, Board& board, int power, int angle);

bool shoot_left(Tank& player, Tank& opponent, Board& board, int power, int angle);

void make_move(Tank& player, Board& board);

void make_obstacle(Board& board);
