#include <boost/test/included/unit_test.hpp>

#include <boost/container/vector.hpp>

#include <fstream>

#include "../../../external/json.hpp"

#include "../../filesystem.hpp"

BOOST_AUTO_TEST_CASE(чтение_png_изображений_должно_быть_корректно)
{
  using namespace boost::container;

  std::ifstream f("tests/filesystem/png_read_test.json");
  nlohmann::json expected_data = nlohmann::json::parse(f);
  f.close();

  nlohmann::json result = noise_selection_generator::get_json_with_png_info_from_directory("../selections/clear");

  BOOST_TEST(result.dump() == expected_data.dump());
}