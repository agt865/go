#pragma once
#include <cassert>
#include <string>
#include <climits>

const char BOARD_VALUE_EMPTY  = '.';
const char BOARD_VALUE_BLACK = 'O';
const char BOARD_VALUE_WHITE = '@';
const char BOARD_VALUE_MARKED = '#';

bool isBoardValueValid (char value_in);
bool isBoardValuePlayer (char value_in);
char getOtherPlayer (char player_value_in);