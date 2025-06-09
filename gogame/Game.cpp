#include "Game.h"

using namespace std;

Game::Game ()
  : AI(BOARD_VALUE_WHITE)
{
  
}

Game::Game (const std::string& filename_in)
  : AI(BOARD_VALUE_WHITE)
{
  assert(filename_in != "");
  gameBoard.load(filename_in);
}

Game::Game (int boardSizeIn)
  : AI(BOARD_VALUE_WHITE), gameBoard(boardSizeIn)
{
  
}

void Game::printBoard () const
{
  gameBoard.print();
}

void Game::printWinner () const
{
  double blackScore = gameBoard.calculateScore (BOARD_VALUE_BLACK);
  double whiteScore = gameBoard.calculateScore (BOARD_VALUE_WHITE) + 7.5;

  if (blackScore < whiteScore)
  {
    cout<<"White won with "<<whiteScore<<" points."<<endl;
    cout<<"Black lost with "<<blackScore<<" points."<<endl<<endl;
  }
  else if (blackScore > whiteScore)
  {
    cout<<"Black won with "<<blackScore<<" points."<<endl;
    cout<<"White lost with "<<whiteScore<<" points."<<endl<<endl;
  }
  else if (blackScore == whiteScore)
  {
    cout<<"White and black tied with "<<blackScore<<" points."<<endl<<endl;
  }
}

const Board& Game::getBoard () const
{
  return gameBoard;
}

void Game::blackPass ()
{
  cout<<"Black passed."<<endl;
}

bool Game::blackPlay (int row_in, int column_in)
{
  Board copied = gameBoard;
  
  if (gameBoard.isOnBoard(row_in, column_in) == false)
  {
    cout<<"Forbidden: Place row "<<row_in<<", column "<<column_in<<" is outside the board."<<endl<<endl;
    return false;
  }
  else if (gameBoard.isOnBoard(row_in, column_in == true))
  {
    if (gameBoard.getAt (row_in, column_in) != BOARD_VALUE_EMPTY)
    {
      cout<<"Forbidden: Place row "<<row_in<<", column "<<column_in<<" is not empty."<<endl<<endl;
      return false;
    }
    else if (gameBoard.getAt (row_in, column_in) == BOARD_VALUE_EMPTY)
    {
      if (copied.playStone(row_in, column_in, BOARD_VALUE_BLACK).us >= 1)
      {
        cout<<"Forbidden: Suicide rule"<<endl;
      }
      else
      {
        StonesRemoved captured = gameBoard.playStone (row_in, column_in, BOARD_VALUE_BLACK);
        cout<<"Black played a stone at row "<<row_in<<","<<" column "<<column_in<<endl;
        printRemoved(captured);
        return true;
      }
    }
  }
  return false;
}

bool Game::whiteAi ()
{
  if (AI.chooseMove(gameBoard).is_played == true)
  {
    int row = AI.chooseMove(gameBoard).row;
    int column = AI.chooseMove(gameBoard).column;
    gameBoard.playStone(row, column, BOARD_VALUE_WHITE);
    cout<<"White placed a stone at row "<<row<<", column "<<column<<endl<<endl;
    return true;
  }
    return false;
}

void Game::printRemoved (const StonesRemoved& removed_in) const
{
  cout<<"Captured "<<removed_in.them<<" stones."<<endl;
  cout<<"Lost "<<removed_in.us<<" stones to suicide."<<endl;
}