#include <boost/test/included/unit_test.hpp>

#include <boost/container/vector.hpp>

#include <fstream>

#include "../../external/json.hpp"

#include "../../image.hpp"
#include "../filesystem.hpp"

BOOST_AUTO_TEST_CASE(чтение_png_изображений_должно_быть_корректно)
{
  using namespace boost::container;

  std::ifstream f("tests/png_read_test.json");
  nlohmann::json expected_data = nlohmann::json::parse(f);
  f.close();

  vector<image::Image> images = noise_selection_generator::get_png_images_from_directory("../selections/clear");
  nlohmann::json result;

  for (vector<image::Image>::iterator it = images.begin(); it != images.end(); it++)
  {
    result.push_back(it->to_json());
  }

  BOOST_TEST(result.dump() == expected_data.dump());
}