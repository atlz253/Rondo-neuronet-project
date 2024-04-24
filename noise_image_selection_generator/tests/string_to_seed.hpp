#include <boost/test/included/unit_test.hpp>

#include "../string_to_seed.hpp"

BOOST_AUTO_TEST_CASE(преобразование_строки_в_seed_должно_работать_корректно)
{
  unsigned int expect = 398;
  std::string input = "ABC";

  unsigned int result = string_to_seed(input);

  BOOST_TEST(result == expect);
}