#ifndef STRING_TO_SEED_HPP
#define STRING_TO_SEED_HPP

#include <string>

unsigned int string_to_seed(const std::string seed)
{
  unsigned int result = 0;

  for (int i = 0; i < seed.length(); i++)
  {
    result += seed[i] * (i + 1);
  }

  return result;
}

#endif