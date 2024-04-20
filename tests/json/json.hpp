#include <boost/test/included/unit_test.hpp>

#include <fstream>

#include "../../external/json.hpp"

#include <boost/container/vector.hpp>

BOOST_AUTO_TEST_CASE(должно_работать_редактирование_json)
{
  nlohmann::json test_json;
  test_json["message"] = "hello world!";
  BOOST_TEST(std::string(test_json["message"]) == std::string("hello world!"));
}

BOOST_AUTO_TEST_CASE(должно_работать_чтение_json)
{
  std::ifstream f("tests/json/read_test.json");
  nlohmann::json data = nlohmann::json::parse(f);
  BOOST_TEST(std::string(data["message"]) == std::string("read success!"));
}

BOOST_AUTO_TEST_CASE(должно_работать_чтение_массива_json)
{
  boost::container::vector<int> expect{1, 2, 3, 4, 5};
  std::ifstream f("tests/json/array_read_test.json");
  nlohmann::json data = nlohmann::json::parse(f);
  boost::container::vector<int> result(data);
  BOOST_CHECK_EQUAL_COLLECTIONS(result.begin(), result.end(), expect.begin(), expect.end());
}
