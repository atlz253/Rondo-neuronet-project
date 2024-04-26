#include <boost/test/included/unit_test.hpp>

#include <string>
#include <fstream>

#include "../../../external/json.hpp"

#include "../../image/image.hpp"

#include <boost/container/vector.hpp>

BOOST_AUTO_TEST_CASE(сериализация_изображения_в_json_работает)
{
  nlohmann::json expect = nlohmann::json::parse(std::ifstream("tests/image/image_to_json_test.json"));
  image::Image img(1, 3);
  img[0][0] = 0;
  img[0][1] = 0;
  img[0][2] = 0;
  img[0][3] = 0;
  img[1][0] = 128;
  img[1][1] = 128;
  img[1][2] = 128;
  img[1][3] = 128;
  img[2][0] = 255;
  img[2][1] = 255;
  img[2][2] = 255;
  img[2][3] = 255;
  BOOST_TEST(img.to_json().dump() == expect.dump());
}

BOOST_AUTO_TEST_CASE(изображение_должно_создаваться_из_данных_json)
{
  nlohmann::json json_data;
  json_data["width"] = 2;
  json_data["height"] = 1;
  json_data["values"] = {{255, 255, 255, 255}, {0, 0, 0, 255}};
  image::Image result = image::Image::from_json(json_data);
  BOOST_TEST(result.to_json().dump() == json_data.dump());
}

BOOST_AUTO_TEST_CASE(изображение_должно_читаться_из_png_файла)
{
  nlohmann::json expect = nlohmann::json::parse(std::ifstream("tests/image/image_png_read_test.json"));
  image::Image result = image::read_png_image("../selections/clear/D.png");
  BOOST_TEST(result.to_json().dump() == expect.dump());
}

BOOST_AUTO_TEST_CASE(маска_изображения_должна_работать_корректно)
{
  nlohmann::json expect = nlohmann::json::parse(std::ifstream("tests/image/image_mask_test.json"));
  image::Image img = image::read_png_image("../selections/clear/O.png");
  nlohmann::json result = img.get_mask().to_json();
  BOOST_TEST(result.dump() == expect.dump());
}