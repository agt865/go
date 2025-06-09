#include "Board.h"
#include "BoardValue.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

bool Board::isOnBoard (int row_in, int column_in) const
{
  if (row_in < boardSize && row_in >= 0)
  {
    if (column_in < boardSize && column_in >= 0)
    {
      return true;
    }
  }
  return false;
}

char Board::getAt (int row_in, int column_in) const
{
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  return p_twoDBoard[toIndex(row_in, column_in)];
}

void Board::setAt (int row_in, int column_in, char value_in)
{
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  assert(isBoardValueValid(value_in));
  p_twoDBoard[toIndex(row_in, column_in)] = value_in;
  assert(isInvariantTrue());
}

Board::Board ()
{
  boardSize = BOARD_SIZE_DEFAULT;
  numBoardSpaces = calculatePlaceCount();
  p_twoDBoard = new char[numBoardSpaces];
  
  for (int i = 0; i < numBoardSpaces; i++)
  {
    p_twoDBoard[i] = BOARD_VALUE_EMPTY;
  }
  assert(isInvariantTrue());
}

Board::Board (const Board& board_in)
{
  assert(board_in.isInvariantTrue());
  p_twoDBoard = nullptr;
  copyData(board_in);
  assert(isInvariantTrue());
}

Board::Board (int size_in)
{
  assert(size_in >= BOARD_SIZE_MIN && BOARD_SIZE_MAX >= size_in);
  boardSize = size_in;
  numBoardSpaces = calculatePlaceCount();
  p_twoDBoard = new char[numBoardSpaces];
  for (int i = 0; i < numBoardSpaces; i++)
  {
    p_twoDBoard[i] = BOARD_VALUE_EMPTY;
  }
  assert(isInvariantTrue());
}

Board& Board::operator= (const Board& board_in)
{
  assert(board_in.isInvariantTrue());
  assert(isInvariantTrue());
  if (&board_in != this)
  {
    destroyData();
    copyData(board_in);  
  }
  assert(isInvariantTrue());
  return *this;
}

int Board::countWithValue (char value_in) const
{
  assert(isInvariantTrue());
  assert(isBoardValueValid(value_in));
  int count = 0;
  for (int i = 0; i < boardSize; i++)
    {
      for (int j = 0; j < boardSize; j++)
      {
        if (getAt(i, j) == value_in)
        {
          count = count + 1;
        }
      }
    }
  return count;
}  

void Board::print () const
{
  assert(isInvariantTrue());
  printColumnLetters();
  for (int i = 0; i < boardSize; i++)
  {
    printRowNumber(i);
    cout<<" ";
    for (int j = 0; j < boardSize; j++)
    {
      if(getAt(i, j) == BOARD_VALUE_EMPTY && isAlignedForStarPoint(i) && isAlignedForStarPoint(j))
      {
        cout<<"*"<<" ";
      }
      else
      {
        cout<<getAt(i, j)<<" ";
      }
    }
    printRowNumber(i);
    cout<<endl;
  }
  printColumnLetters();
}

// Copied boardload function

void Board:: load (const string& filename_in)
{
	assert(isInvariantTrue());
	assert(filename_in != "");

	// open file with name filename_in
	// fin will read from that file
	// use fin like you use cin
	ifstream fin(filename_in);

	if(!fin)
	{
		cout << "Error: Could not open file \"" << filename_in << "\"" << endl;
		return;  // end function immediately
	}

	// read in the board size
	string line;
	int board_size_read;
	fin >> board_size_read;
	if(!fin)
	{
		cout << "Error: File \"" << filename_in << "\" does not start with board size" << endl;
		return;  // end function immediately
	}
	if(board_size_read > BOARD_SIZE_MAX)
	{
		cout << "Error: File \"" << filename_in << "\" has board size "
		     << board_size_read << ", but maximum is " << BOARD_SIZE_MAX << endl;
		return;  // end function immediately
	}
	if(board_size_read < BOARD_SIZE_MIN)
	{
		cout << "Error: File \"" << filename_in << "\" has board size "
		     << board_size_read << ", but minimum is " << BOARD_SIZE_MIN << endl;
		return;  // end function immediately
	}
	assert(fin);
	string dummy;
	getline(fin, dummy);  // throw away whatever else is on the line

	// replace this board with a new one of the correct size
	*this = Board(board_size_read);

	// read in board state
	bool is_print_error = true;
	for(int r = 0; r < getSize(); r++)
	{
		string line;
		getline(fin, line);
		if(!fin)
		{
			if(is_print_error)
			{
				cout << "Error: Could not read line " << r
				     << " of file \"" << filename_in << "\"" << endl;
				cout << "       Replacing with '" << BOARD_VALUE_EMPTY << "'s" << endl;
				is_print_error = false;
			}
			line = string(BOARD_VALUE_EMPTY, getSize());  // set to '.'s
		}
		else if((int)(line.length()) < getSize())
		{
			if(is_print_error)
			{
				cout << "Error: Line " << r << " of file \"" << filename_in
				     << "\" only contains " << line.length()
				     << " / " << getSize() << " characters" << endl;
				cout << "       Adding '" << BOARD_VALUE_EMPTY << "'s to end" << endl;
				is_print_error = false;
			}
			line += string(BOARD_VALUE_EMPTY, getSize());  // add '.'s
		}

		for(int c = 0; c < getSize(); c++)
		{
			if(isBoardValueValid(line[c]))
				setAt(r, c, line[c]);
			else
			{
				setAt(r, c, BOARD_VALUE_EMPTY);
				if(is_print_error)
				{
					cout << "Error: Line " << r << ", character " << c
						 << " of file \"" << filename_in
						 << "\" is an invalid '" << line[c] << "' character" << endl;
					cout << "       Substituting '" << BOARD_VALUE_EMPTY << "'" << endl;
					is_print_error = false;
				}
			}
		}
	}

	assert(isInvariantTrue());
	// file will be closed automatically when fin goes out of scope
}

bool Board::isAlignedForStarPoint (int index_in) const
{
  if (index_in % STAR_POINT_SPACING == (boardSize / 2) % STAR_POINT_SPACING)
  {
    return true;
  }
  return false;
}

void Board::printRowNumber (int row_in) const
{
  cout<<setw(2)<<row_in;
}

void Board::printColumnLetters () const
{
  cout<<"  ";
  for(int i = 0; i < boardSize; i++)
  {
    if (i >= 0 && i <= 7)
    {
      cout<<setw(2)<<char(i+65);
    }
    else if (i > 7 && i <= 12)
    {
      cout<<setw(2)<<char(i+66);
    }
    else if (i > 12 && i <= 23)
    {
      cout<<setw(2)<<char(i+67);
    }
  }
  cout<<endl;
}

bool Board::isInvariantTrue () const
{
  if (boardSize >= BOARD_SIZE_MIN && boardSize <= BOARD_SIZE_MAX)
  {
    if (numBoardSpaces == calculatePlaceCount())
    {
      if (p_twoDBoard == nullptr)
      {
        return false;
      }
      for (int i = 0; i < numBoardSpaces; i++)
      {
        if (isBoardValueValid (p_twoDBoard[i]) == false)
        {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  return false;
}

void Board::replaceAll (char old_value_in, char new_value_in)
{
  assert(isInvariantTrue());
  assert(isBoardValueValid (old_value_in) && isBoardValueValid (new_value_in));
  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      if (getAt(i, j) == old_value_in)
      {
        setAt(i, j, new_value_in);
      }
    }
  }
  assert(isInvariantTrue());
}

bool Board::isANeighbourWithValue (int row_in, int column_in, char value_in) const
{
  assert(isInvariantTrue());
  assert(isOnBoard(row_in,column_in));
  assert(isBoardValueValid(value_in));
  if (isOnBoard(row_in - 1, column_in) == true)
  {
    if (getAt(row_in - 1, column_in) == value_in)
    {
      return true;
    }
  }
  if (isOnBoard(row_in + 1, column_in) == true)
  {
    if (getAt(row_in + 1, column_in) == value_in)
    {
      return true;
    }
  }
  if (isOnBoard(row_in, column_in - 1) == true)
  {
    if (getAt(row_in, column_in - 1) == value_in)
    {
      return true;
    }
  }
  if (isOnBoard(row_in, column_in + 1) == true)
  {
    if (getAt(row_in, column_in + 1) == value_in)
    {
      return true;
    }
  }
  return false;
}

int Board::getSize () const
{
  assert(isInvariantTrue());
  return boardSize;
}

void Board::fillConnected (char old_value_in, char new_value_in, char neighbour_value_in)
{
  assert(isInvariantTrue());
  assert(isBoardValueValid(old_value_in) && isBoardValueValid(new_value_in) && isBoardValueValid(neighbour_value_in));
  bool stop = false;
  do
  { 
    stop = true;
    for (int i = 0; i < boardSize; i++)
    {
      for (int j = 0; j < boardSize; j++)
      {
        if (getAt(i, j) == old_value_in)
        {
          if (isANeighbourWithValue (i, j, neighbour_value_in))
          {
            setAt(i, j, new_value_in);
            stop = false;
          }
          else if (isANeighbourWithValue (i, j, new_value_in))
          {
            setAt(i, j, new_value_in);
            stop = false;
          }
        }
      }
    }
  } while (stop == false);
  assert(isInvariantTrue());
}

int Board::calculateScore (char us_value_in) const
{
  assert(isInvariantTrue());
  assert(isBoardValuePlayer(us_value_in));
  
  char otherPlayerValue = getOtherPlayer (us_value_in); 
  Board copy = *this;
  copy.fillConnected(BOARD_VALUE_EMPTY, otherPlayerValue, otherPlayerValue);
  copy.fillConnected(BOARD_VALUE_EMPTY, us_value_in, us_value_in);

  int scoreCount = 0;
  for (int i = 0; i < boardSize; i++)
    {
      for (int j = 0; j < boardSize; j++)
      {
        if (copy.getAt(i, j) == us_value_in)
        {
          scoreCount++;
        }
      }
    }
  return scoreCount;
}

int Board::capturePlayer (char player_value_in)
{
  assert(isBoardValuePlayer(player_value_in));
  
  replaceAll(player_value_in, BOARD_VALUE_MARKED);
  fillConnected(BOARD_VALUE_MARKED, player_value_in, BOARD_VALUE_EMPTY);
  
  int marked_places = countWithValue(BOARD_VALUE_MARKED);
  
  replaceAll(BOARD_VALUE_MARKED, BOARD_VALUE_EMPTY);
  return marked_places;
}

StonesRemoved Board::playStone (int row_in, int column_in, char us_value_in)
{
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  assert(getAt(row_in, column_in) == BOARD_VALUE_EMPTY);
  assert(isBoardValuePlayer(us_value_in));

  StonesRemoved result;

  setAt(row_in, column_in, us_value_in);
  result.them = capturePlayer(getOtherPlayer(us_value_in));
  result.us = capturePlayer(us_value_in);
  
  assert(isInvariantTrue());
  
  return result;
}

int Board::toIndex (int row_in, int column_in) const
{
  assert(isOnBoard(row_in, column_in));
  int index = row_in * boardSize + column_in;
  return index;
}

void Board::destroyData ()
{
  assert(p_twoDBoard != nullptr);
  delete [] p_twoDBoard;
  p_twoDBoard = nullptr;
  assert(p_twoDBoard == nullptr);
}

Board::~Board ()
{
  assert(isInvariantTrue());
  destroyData ();
}

void Board::copyData (const Board& board_in)
{
  assert(p_twoDBoard == nullptr);
  assert(board_in.isInvariantTrue());
  boardSize = board_in.boardSize;
  numBoardSpaces = board_in.numBoardSpaces;
  p_twoDBoard = new char[numBoardSpaces];
  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardSize; j++)
    {
      p_twoDBoard[toIndex(i, j)] = board_in.p_twoDBoard[toIndex(i, j)];
    }
  }
  assert(p_twoDBoard != nullptr);
}

int Board::calculatePlaceCount () const
{
  return boardSize * boardSize;
}