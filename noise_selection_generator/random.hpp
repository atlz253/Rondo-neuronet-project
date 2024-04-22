#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <boost/container/vector.hpp>

namespace noise_selection_generator
{
  boost::container::vector<int> get_unique_random_numbers(int from, int to, int count = 1);
}

#endif
