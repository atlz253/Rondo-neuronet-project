#include <boost/test/included/unit_test.hpp>

#include <string>

#include <boost/container/list.hpp>

#include "../arguments.hpp"

#include <iostream>

BOOST_AUTO_TEST_CASE(аргументы_должны_парситься_корректно)
{
  using namespace boost::container;

  int argc = 8;
  char *argv[] = {"test", "--input", "foo", "--multiple", "hello", "world", "-f", "work"};
  list<std::string> input{"foo"};
  list<std::string> multiple{"hello", "world"};
  list<std::string> f{"work"};

  Arguments args(argc, argv);

  BOOST_CHECK_EQUAL_COLLECTIONS(args["--input"].begin(), args["--input"].end(), input.begin(), input.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(args["--multiple"].begin(), args["--multiple"].end(), multiple.begin(), multiple.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(args["-f"].begin(), args["-f"].end(), f.begin(), f.end());
}

BOOST_AUTO_TEST_CASE(одинаковые_аргументы_перезаписывают_друг_друга)
{
  using namespace boost::container;

  int argc = 7;
  char *argv[] = {"test", "--input", "foo", "bar", "--input", "zig", "zag"};
  list<std::string> expect{"zig", "zag"};

  Arguments args(argc, argv);

  BOOST_CHECK_EQUAL_COLLECTIONS(args["--input"].begin(), args["--input"].end(), expect.begin(), expect.end());
}