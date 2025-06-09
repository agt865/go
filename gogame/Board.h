#pragma once
#include <string>
using namespace std;

const int STAR_POINT_SPACING = 6;
const int BOARD_SIZE_MIN = 1;
const int BOARD_SIZE_MAX = 24;
const int BOARD_SIZE_DEFAULT = 19;

struct StonesRemoved
{
  int us;
  int them;
};

//
//  Board
//
//  A Board will calculate all the necessary components of 
//  the board the user will be playing on. This includes setter and getter
//  functions, copying, placing, etc.
//
//  Class Invariant:
//    <1> boardSize >= BOARD_SIZE_MIN && boardSize <= BOARD_SIZE_MAX
//    <2> numBoardSpaces == calculatePlaceCount()
//    <3> p_twoDBoard != nullptr
//    <4> isBoardValueValid (p_twoDBoard[i]) == true where i is all numBoardSpaces
//
class Board
{
  private:
    char* p_twoDBoard;
    int boardSize;
    int numBoardSpaces;
  public:
    Board ();
    ~Board ();
    Board (const Board& board_in);
//
//  Board 
//
//  Purpose: Initializes boardSize member variable to passed
//           integer parameter to allow the board to be a user 
//           specified size         
//  Parameter(s):
//    <1> size_in: Size of desired board
//  Precondition(s):
//    <1> size_in >= BOARD_SIZE_MIN && BOARD_SIZE_MAX >= size_in
//  Returns: Nothing because it is a contructor
//  Side Effect: Sets boardSize to size_in, calculates numBoardSpaces by using
//               calculatePlaceCount() function. The member pointer dynamically 
//               allocates memory for a char array with a size of
//               numBoardSpaces. Every element in the char array
//               gets set to empty
//
    Board (int size_in);
    Board& operator= (const Board& board_in);
//
//  isOnBoard
//
//  Purpose: To check if the spot from row_in and column_in is on the board
//           
//  Parameter(s):
//    <1> row_in: Get the specific row on board
//    <2> column_in: Get the specific column on board
//  Precondition(s):
//    None
//  Returns: True or false depending whether or not the spot is on the board
//  Side Effect: N/A
//
    bool isOnBoard (int row_in, int column_in) const;
//
//  getAt
//
//  Purpose: To get a specific board position at a
//           specified row and column. 
//  Parameter(s):
//    <1> row_in: Get the specific row on board
//    <2> column_in: Get the specific column on board
//  Precondition(s):
//    <1> isOnBoard(row_in, column_in)
//  Returns: The character/board_value associated at the wanted place on the board 
//  Side Effect: N/A
//
    char getAt (int row_in, int column_in) const;
    void setAt (int row_in, int column_in, char value_in);
    void load (const string& filename_in);
    int countWithValue (char value_in) const;
    int calculateScore (char us_value_in) const;
    void print () const;
//
//  playStone
//
//  Purpose: To change a spot on the board with the player's
//           value and captures the other player's stone.
//  Parameter(s):
//    <1> row_in: The row of the place to change
//    <2> column_in: The column of the place to change
//    <3> us_value_in: player's value (black or white)
//  Precondition(s):
//    <1> isBoardValueValid(getAt(row_in, column_in)
//    <2> getAt(row_in, column_in) == BOARD_VALUE_EMPTY
//    <3> isBoardValuePlayer(us_value_in)
//  Returns: A struct which contains new us and them values
//  Side Effect: Sets players value at designated spot.
//               Sets value them to the number of opponent
//               stones captured. Sets us to the number of
//               stones suicided.
//
    StonesRemoved playStone (int row_in, int column_in, char us_value_in);
    void replaceAll (char old_value_in, char new_value_in);
    void fillConnected (char old_value_in, char new_value_in, char neighbour_value_in);
    bool isANeighbourWithValue (int row_in, int column_in, char value_in) const;
//
//  getSize
//
//  Purpose: To access boardSize by returning it (getter)     
//  Parameter(s): None
//  Precondition(s): None
//  Returns: boardSize which is the size of the board
//  Side Effect: None
//
    int getSize () const;
  private:
    bool isAlignedForStarPoint (int index_in) const;
    void printRowNumber (int row_in) const;
    void printColumnLetters () const;
    int capturePlayer (char player_value_in);
    bool isInvariantTrue () const;
    int toIndex (int row_in, int column_in) const;
    void destroyData ();
    void copyData (const Board& board_in);
    int calculatePlaceCount () const;
};

