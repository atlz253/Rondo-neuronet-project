#include <boost/test/included/unit_test.hpp>

#include "../activation_functions.hpp"

BOOST_AUTO_TEST_CASE(ReLU_выдает_само_значение_если_оно_положительно)
{
  BOOST_TEST(neuronet::ReLU(0) == 0);
  BOOST_TEST(neuronet::ReLU(1) == 1);
  BOOST_TEST(neuronet::ReLU(10) == 10);
  BOOST_TEST(neuronet::ReLU(64) == 64);
}

BOOST_AUTO_TEST_CASE(ReLU_выдает_ноль_если_значение_отрицательно)
{
  BOOST_TEST(neuronet::ReLU(-1) == 0);
  BOOST_TEST(neuronet::ReLU(-10) == 0);
  BOOST_TEST(neuronet::ReLU(-64) == 0);
}