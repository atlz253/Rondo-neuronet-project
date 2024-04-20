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
