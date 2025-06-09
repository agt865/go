// Name: Ariel Torrens James
// Student Number: 200482217

#include <iostream>
#include <string>
#include "TestHelper.h"
#include "PlaceString.h"
#include "Board.h"
#include "BoardValue.h"
#include "Game.h"
using namespace std;

int askBoardSize();

int main()
{
  string name;
  bool continueLoop = true;
  string move;
  StonesRemoved captured;
  
  // Opening messages
  cout<<"Welcome to the game of Go"<<endl;
  cout<<"What is your name?: ";
  getline(cin, name);
  Game mainBoard(askBoardSize());
  cout<<endl;
  cout<<"Hello "<<name<<". You will play black."<<endl;
  cout<<"You can enter \"quit\" to end the game"<<endl<<endl;

  while (continueLoop == true)
  {
    mainBoard.printBoard ();
    cout<<endl<<"What is your move: ";
    getline(cin, move);
    cout<<endl;
    if (move == "quit")
    {
      continueLoop = false;
    }
    else if (move == "new")
    {
      mainBoard.printWinner();
      mainBoard = askBoardSize();
    }
		else if (move == "load")
		{
			string filename;
      mainBoard.printWinner();
			cout << "Enter the file name: ";
			getline(cin, filename);
			mainBoard = Game(filename);
      cout<<endl;
    }
    else if (move == "pass")
    {
      cout<<"Black passed"<<endl;
      mainBoard.whiteAi();
    }
    else if (isPlaceStringWellFormed(move) == true)
    {
      mainBoard.blackPlay(placeStringToRow(move), placeStringToColumn(move));
      mainBoard.whiteAi();
    }
    else if (isPlaceStringWellFormed(move) == false)
    {
      cout<<move<<" is ill-formed"<<endl<<endl;
    }
  }
  
  mainBoard.printBoard ();
  cout<<endl;
  mainBoard.printWinner();

  // Closing message
  cout<<"Goodbye, "<<name<<".";
}

int askBoardSize()
{
  int newBoardSize;
  cout<<"What size do you want the board to be?: ";
  cin>>newBoardSize;
  cin.get();
  cin.clear();
  while (newBoardSize < BOARD_SIZE_MIN || newBoardSize > BOARD_SIZE_MAX)
  {
    cout<<"Invalid board size. Try again: ";
    cin>>newBoardSize;
    cin.get();
    cin.clear();
  }
  return newBoardSize;
}