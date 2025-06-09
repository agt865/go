#include "Move.h"
#include <iostream>
#include <string>
using namespace std;

bool operator== (const SortableMove& lhs_in, const SortableMove& rhs_in)
{
  if (rhs_in.net_score == lhs_in.net_score )
  {
    return true;
  }
  return false;
}

bool operator< (const SortableMove& lhs_in, const SortableMove& rhs_in)
{
  if (lhs_in.net_score < rhs_in.net_score )
  {
    return true;
  }
  return false;
}