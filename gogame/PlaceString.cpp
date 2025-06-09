#include <string>
#include "PlaceString.h"
using namespace std;

int stringToInteger (const string str)
{
  int a = 0;

  if (str == "")
  {
    return INVALID_COORDINATE;
  }

  for (int i = 0; i <str.length(); i++)
  {
    if (str[i] < '0' || str[i] > '9')
    {
      return INVALID_COORDINATE;
    }
  }
  
  for (int i = 0; i < str.length(); i++)
  {
    a = a * 10 + (str[i] - '0');
  }
  return a;
}

int placeStringToRow(const string str)
{
  if (str.length() < 2)
  {
    return INVALID_COORDINATE;
  }
  string rowNumber = str.substr(1, str.length());
  return stringToInteger(rowNumber);
}

int placeStringToColumn(const string str)
{
  int columnInt;
  if (str.length() == 0)
  {
    return INVALID_COORDINATE;
  }
  
  if (str[0] == 'I' || str[0] == 'O')
  {
    return INVALID_COORDINATE;
  }

  if (str[0] >= 65 && str[0] <= 90)
  {
    if (str[0] >= 65 && str[0] <= 72)
    {
      columnInt = str[0] - 65;
    }
    
    else if (str[0] >= 74 && str[0] <= 78)
    {
      columnInt = str[0] - 66;
    }
    
    else //if (str[0] >= 80 && str[0] <= 90)
    {
      columnInt = str[0] - 67;
    }
  }
  else
  {
    return INVALID_COORDINATE;
  }
  return columnInt;
}

bool isPlaceStringWellFormed(const string str)
{
  if (placeStringToRow(str) == INVALID_COORDINATE || placeStringToColumn(str) == INVALID_COORDINATE)
  {
    return false;
  }
  else  
  {
    return true;
  }
}