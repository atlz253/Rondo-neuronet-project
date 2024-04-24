#include "image.hpp"

#include <boost/gil.hpp>
#include <boost/gil/extension/io/png.hpp>

#include <boost/container/vector.hpp>

using namespace image;
using namespace boost::container;

void fill_vector_by_pixel_color_data(vector<int> &values, const boost::gil::detail::homogeneous_color_base<uint8_t, boost::gil::rgba_layout_t, 4> &color_data);

Image image::read_png_image(const char *filename)
{
  boost::gil::rgba8_image_t img;
  read_image(filename, img, boost::gil::png_tag());
  boost::gil::rgba8c_view_t img_view = const_view(img);
  Image parsed_image(img_view.width(), img_view.height());
  const int pixels_count = img_view.width() * img_view.height();
  for (int i = 0; i < pixels_count; i++)
  {
    fill_vector_by_pixel_color_data(parsed_image[i], img_view[i]);
  }
  return parsed_image;
}

void fill_vector_by_pixel_color_data(vector<int> &v, const boost::gil::detail::homogeneous_color_base<uint8_t, boost::gil::rgba_layout_t, 4> &color_data)
{
  v[0] = (int)boost::gil::at_c<0>(color_data);
  v[1] = (int)boost::gil::at_c<1>(color_data);
  v[2] = (int)boost::gil::at_c<2>(color_data);
  v[3] = (int)boost::gil::at_c<3>(color_data);
}

Image image::read_png_image(const std::string &filename)
{
  return read_png_image(filename.c_str());
}

void image::write_png_image_to_file(Image &img, const char *filename)
{
  using namespace boost::gil;

  rgba8_image_t png_image(img.get_width(), img.get_height());
  rgba8_image_t::view_t v = view(png_image);
  const int pixels_count = img.get_pixels_count();
  for (int i = 0; i < pixels_count; i++)
  {
    const int row = i / img.get_height();
    const int column = i % img.get_height();
    v(column, row) = rgba8_pixel_t(img[i][0], img[i][1], img[i][2], img[i][3]);
  }
  write_view(filename, v, png_tag());
}

void image::write_png_image_to_file(Image &img, const std::string &filename)
{
  return write_png_image_to_file(img, filename.c_str());
}