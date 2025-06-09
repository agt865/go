#pragma once
#include "Board.h"
#include "BoardValue.h"
#include "Move.h"
#include <cassert>
#include "Search.h"
#include <cstdlib>
#include <iostream>
using namespace std;
class Game;

struct MoveResult
{
  bool isMoveLegal;
  float valueNetScore;
};

//
//  ArtificialIntelligence
//
//  Artificial Intellignece is what makes player white
//    (the computer) have the ability to play pieces on
//    the board.
//
//  Class Invariant:
//    <1> isBoardValuePlayer(boardValue) == true
//
class ArtificialIntelligence
{
  char boardValue;
  public:
//
//  ArtificialIntelligence
//
//  Purpose: Initalizes user's input (us_value_in) to the member variable boardValue
//  Parameter(s):
//    <1> us_value_in: Determines what board value is the AI
//  Precondition(s):
//    <1> isBoardValuePlayer(us_value_in) == true
//  Returns: Nothing because it is a constructor
//  Side Effect: Sets boardValue to us_value_in
//

    ArtificialIntelligence (char us_value_in);
//
//  chooseMove
//
//  Purpose: Allows the AI to choose a move with
//           a high net value. This value is 
//           calculated by finding the highest net score 
//           values that are all equal and returning the
//           class that stores values tied to the index.
//  Parameter(s):
//    <1> board_in: A Board type variable to access
//  Precondition(s):
//    <1> None
//  Returns: A Move (struct) with an updated net score 
//  Side Effect: Creates a SortableMove array that holds 362 indices
//               for all the possible places on the board the AI can play.
//               it sets the pass move to index 0 and sets the isPlayed
//               to false. Counter integer is made that increases by 1 when
//               there is a playable tile. The array updates its
//               net score, row, and column if the tile is legal. 
//               The array is sorted using the mySort function.
//               Creates a SortedMoves max_move variable that finds
//               the last index value. Finds the lowest index in the aray 
//               of where the high net score is and sets that to 
//               first_max_index. Finds the range wanted for the AI to play.
//               Finds random index to play.
//  
    Move chooseMove (const Board& board_in) const;
  private:
    float calculateNetScore (const Board& board_in) const;
    MoveResult getPlayResult (const Board& board_in, int row_in, int column_in) const;
    bool isInvariantTrue () const;
};