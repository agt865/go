#include "ArtificialIntelligence.h"

ArtificialIntelligence::ArtificialIntelligence (char us_value_in)
{
  assert(isBoardValuePlayer(us_value_in));
  boardValue = us_value_in;
  assert(isInvariantTrue ());
}

bool ArtificialIntelligence::isInvariantTrue () const
{
  if (isBoardValuePlayer(boardValue))
  {
    return true;
  }
  return false;
}

float ArtificialIntelligence::calculateNetScore (const Board& board_in) const
{
  float diff = board_in.calculateScore(boardValue) - board_in.calculateScore(getOtherPlayer(boardValue));
  return diff;
}

MoveResult ArtificialIntelligence::getPlayResult (const Board& board_in, int row_in, int column_in) const
{
  Board copyBoard = board_in;
  MoveResult result;

  if (board_in.isOnBoard(row_in, column_in) && board_in.getAt (row_in, column_in) == BOARD_VALUE_EMPTY)
  {
    StonesRemoved playStone = copyBoard.playStone(row_in, column_in, boardValue);
    if (playStone.us >= 1)
    {
     result.isMoveLegal = false;
    }
    else
    {
      result.valueNetScore = calculateNetScore(copyBoard);
      result.isMoveLegal = true;
    }
  }
  else
  {
    result.isMoveLegal = false;
  }
  return result;
}

Move ArtificialIntelligence::chooseMove(const Board &board_in) const 
{
  const int BOARD_SIZE_MAX = board_in.getSize() * board_in.getSize() + 1; //boardSize * BOARD_SIZE + 1;
  SortableMove possible_moves[BOARD_SIZE_MAX];
  int num_moves = 0;

  //pass move
  possible_moves[num_moves].is_played = false;
  possible_moves[num_moves].net_score = calculateNetScore(board_in) + 0.5;
  num_moves++;
  
  //legal moves
  for (int i = 0; i < board_in.getSize(); i++) 
  {
    for (int j = 0; j < board_in.getSize(); j++) 
    {
      if (getPlayResult(board_in, i, j).isMoveLegal == true)
      {
        possible_moves[num_moves].row = i;
        possible_moves[num_moves].column = j;
        possible_moves[num_moves].is_played = true;
        possible_moves[num_moves].net_score = getPlayResult(board_in, i, j).valueNetScore;
        num_moves++;
      } 
    }
  }

  mySort(possible_moves, num_moves);
  SortableMove max_move = possible_moves[num_moves - 1];
  int first_max_index = binarySearchFirst(possible_moves, num_moves, max_move);
  int good_moves_range = num_moves - first_max_index;
  srand(time(0));
  int random_index = first_max_index + rand() % good_moves_range;
  
  return possible_moves[random_index];
}