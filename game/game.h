#pragma once
#include "tank.h"
#include "board.h"
#include "User.h"

void game_start(Tank player1, Tank player2, int probability, User& user);

void game_display(Tank& player1, Tank& player2, Board board, User& user);

User game_mode(User& player1);

void game_with_bot(Tank& player, Tank& bot, Board board, int probability, User& user);