#include <boost/test/included/unit_test.hpp>

#include <fstream>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>

#include <boost/container/vector.hpp>

#include "../../external/json.hpp"

BOOST_AUTO_TEST_CASE(чтение_изображения_должно_быть_корректным)
{

  std::ifstream f("tests/boost/image_read_test.json");
  nlohmann::json expect_data = nlohmann::json::parse(f);
  boost::container::vector<boost::container::vector<int>> expect(expect_data);

  boost::gil::rgba8_image_t img;
  read_image("selections/clear/C.png", img, boost::gil::png_tag());

  boost::gil::rgba8c_view_t img_view = const_view(img);
  const int pixels_count = img_view.width() * img_view.height();
  boost::container::vector<boost::container::vector<int>> result(pixels_count, boost::container::vector<int>(4));

  for (int i = 0; i < pixels_count; i++)
  {
    result[i][0] = (int)boost::gil::at_c<0>(img_view[i]);
    result[i][1] = (int)boost::gil::at_c<1>(img_view[i]);
    result[i][2] = (int)boost::gil::at_c<2>(img_view[i]);
    result[i][3] = (int)boost::gil::at_c<3>(img_view[i]);
  }

  for (int i = 0; i < pixels_count; i++)
  {
    BOOST_CHECK_EQUAL_COLLECTIONS(result[i].begin(), result[i].end(), expect[i].begin(), expect[i].end());
  }
}