#include <string>
#include <climits>
#include <cassert>
#include "Search.h"
using namespace std;

int linearSearch (const SortableMove data_in[], int count_in, const SortableMove& value_in)
{
  for (int i = 0;  i < count_in; i++)
  {
    if (data_in[i] == value_in)
    {
      return i;
    }
  }
  return VALUE_NOT_FOUND;
}

int unsortedFindSmallest (const SortableMove data_in[], int count_in)
{
  SortableMove minValue = data_in[0];
  int minIndex = 0;
  for (int i = 1;  i < count_in; i++)
  {
    if (data_in[i] < minValue)
    {
      minValue = data_in[i];
      minIndex = i;
    }
  }
  return minIndex;
}

int unsortedFindLargest (const SortableMove data_in[], int count_in)
{
  SortableMove maxValue = data_in[0];
  int maxIndex = 0;
  for (int i = 1;  i < count_in; i++)
  {
    if (maxValue < data_in[i])
    {
      maxValue = data_in[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}

void mySort (SortableMove data_in[], int count_in)
// implements selection sorting
{
  int i, j, search_min;
  SortableMove temp;

  for (i = 0; i < count_in - 1; i++)
  {
    search_min = i;
    for (j = i + 1; j < count_in; j++)
    {
      if (data_in[j] < data_in[search_min])
      {
        search_min = j;
      }
    }
    temp = data_in[search_min];
    data_in[search_min] = data_in[i];
    data_in[i] = temp;
  }
}

bool isSorted (const SortableMove data_in[], int count_in)
{
  for (int i = 0; i < count_in - 1; i++)
  {
    if (data_in[i+1] < data_in[i])
    {
      return false;
    }
  }
  return true;
}

int sortedFindSmallest (const SortableMove data_in[], int count_in)
{
  assert(isSorted(data_in, count_in) == true);
  assert(count_in >= 1);
  return 0;
}

int sortedFindLargest (const SortableMove data_in[], int count_in)
{
  assert(isSorted(data_in, count_in) == true);
  assert(count_in >= 1);
  return count_in - 1;
}

int binarySearch (const SortableMove data_in[], int count_in, const SortableMove& value_in)
{
  assert(isSorted(data_in, count_in) == true);
  int low = 0;
  int high = count_in - 1;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    if (value_in == data_in[mid])
    {
      return mid;
    }
    else if (value_in < data_in[mid])
    {
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }
  return VALUE_NOT_FOUND;
}

int binarySearchFirst (const SortableMove data_in[], int count_in, const SortableMove& value_in)
{
  assert(isSorted(data_in, count_in) == true);
  int low = 0;
  int high = count_in - 1;
  while  (low <= high)
  {
    int mid = (low + high) / 2;
    if (value_in == data_in[mid]) 
    {
      if (data_in[mid] == data_in[0])
      {
        return 0;
      }
      else if (!(value_in == data_in[mid -1]))
      {
        return mid;
      }
      else if (value_in == data_in[mid - 1])
      {
        for(int i = 0; i < count_in - 1; i++)
        {
          if (data_in[i] == value_in)
          {
            return i;
          }
        }
      }
    }
    else if (value_in < data_in[mid])
    {
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }
  
  return VALUE_NOT_FOUND;
}