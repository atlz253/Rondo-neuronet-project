#include <boost/test/included/unit_test.hpp>

#include <fstream>

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>

#include <boost/container/vector.hpp>

#include "../../external/json.hpp"

boost::container::vector<boost::container::vector<int>> get_expect_image_values_from_file(const char *path);
boost::container::vector<boost::container::vector<int>> get_pixel_values_from_image(boost::gil::rgba8_image_t &img);
void check_image_values_equal(boost::container::vector<boost::container::vector<int>> &result, boost::container::vector<boost::container::vector<int>> &expect);

BOOST_AUTO_TEST_CASE(чтение_изображения_должно_быть_корректным)
{
  boost::container::vector<boost::container::vector<int>> expect = get_expect_image_values_from_file("tests/boost/image_read_test.json");

  boost::gil::rgba8_image_t img;
  read_image("selections/clear/C.png", img, boost::gil::png_tag());

  boost::container::vector<boost::container::vector<int>> result = get_pixel_values_from_image(img);
  check_image_values_equal(result, expect);
}

BOOST_AUTO_TEST_CASE(изменение_изображения_должно_работать)
{
  boost::container::vector<boost::container::vector<int>> expect = get_expect_image_values_from_file("tests/boost/image_create_test.json");

  boost::gil::rgba8_image_t img(8, 8);
  boost::gil::rgba8_pixel_t black_pixel(0, 0, 0, 255);
  boost::gil::rgba8_image_t::view_t v = boost::gil::view(img);
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (i == j)
      {
        v(i, j) = black_pixel;
      }
    }
  }

  boost::container::vector<boost::container::vector<int>> result = get_pixel_values_from_image(img);
  check_image_values_equal(result, expect);
}

boost::container::vector<boost::container::vector<int>> get_expect_image_values_from_file(const char *path)
{
  std::ifstream f(path);
  nlohmann::json expect_data = nlohmann::json::parse(f);
  f.close();
  return boost::container::vector<boost::container::vector<int>>(expect_data);
}

boost::container::vector<boost::container::vector<int>> get_pixel_values_from_image(boost::gil::rgba8_image_t &img)
{
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
  return result;
}

void check_image_values_equal(boost::container::vector<boost::container::vector<int>> &result, boost::container::vector<boost::container::vector<int>> &expect)
{
  for (int i = 0; i < expect.size(); i++)
  {
    BOOST_CHECK_EQUAL_COLLECTIONS(result[i].begin(), result[i].end(), expect[i].begin(), expect[i].end());
  }
}