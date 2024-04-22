#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include <boost/container/vector.hpp>

#include "../random.hpp"

BOOST_AUTO_TEST_CASE(должны_генерироваться_уникальные_числовые_значения)
{
  using namespace boost::container;

  std::time_t seed = 123;
  time(&seed);

  vector<int> expect{28, 10, 6, 13, 23};
  vector<int> result = noise_selection_generator::get_unique_random_numbers(0, 32, 5);

  BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expect.begin(), expect.end());
}