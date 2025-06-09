#pragma once
#include "Board.h"
#include "BoardValue.h"
#include "ArtificialIntelligence.h"
#include <string>
#include <iostream>

using namespace std;

class Game
{
  private:
    Board gameBoard;
    ArtificialIntelligence AI;
  public:
    Game ();
    Game (const std::string& filename_in);
    Game (int boardSizeIn);
    void printBoard () const;
    void printWinner () const;
    const Board& getBoard () const;
    void blackPass ();
    bool blackPlay (int row_in, int column_in);
    bool whiteAi ();
  private:
     void printRemoved (const StonesRemoved& removed_in) const;
};