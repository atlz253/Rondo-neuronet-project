#include <boost/test/included/unit_test.hpp>

#include <fstream>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>

#include <boost/container/vector.hpp>

#include "../../external/json.hpp"

using namespace boost::gil;
using namespace boost::container;

BOOST_AUTO_TEST_CASE(чтение_изображения_должно_быть_корректным)
{
  std::ifstream f("tests/boost/image_read_test.json");
  nlohmann::json expect_data = nlohmann::json::parse(f);
  vector<vector<int>> expect(expect_data);

  rgba8_image_t img;
  read_image("selections/input/seven.png", img, png_tag());

  rgba8c_view_t img_view = const_view(img);
  const int pixels_count = img_view.width() * img_view.height();
  vector<vector<int>> result(pixels_count, vector<int>(4));

  for (int i = 0; i < pixels_count; i++) {
      result[i][0] = (int)at_c<0>(img_view[i]);
      result[i][1] = (int)at_c<1>(img_view[i]);
      result[i][2] = (int)at_c<2>(img_view[i]);
      result[i][3] = (int)at_c<3>(img_view[i]);
  }

  for (int i = 0; i < pixels_count; i++) {
    BOOST_CHECK_EQUAL_COLLECTIONS(result[i].begin(), result[i].end(), expect[i].begin(), expect[i].end());
  }
}