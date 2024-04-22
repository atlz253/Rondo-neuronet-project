#include "random.hpp"

#include <iostream>

using namespace boost::container;

bool is_vector_contains_num(vector<int> &v, int num);

vector<int> noise_selection_generator::get_unique_random_numbers(int from, int to, int count)
{
  vector<int> result;

  while (result.size() != count)
  {
    int num = rand() % (to - from + 1) + from;

    if (!is_vector_contains_num(result, num))
    {
      result.push_back(num);
    }
  }

  return result;
}

bool is_vector_contains_num(vector<int> &v, int num)
{
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
  {
    if (*it == num)
    {
      return true;
    }
  }

  return false;
}