#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <boost/container/vector.hpp>

#include "image.hpp"

namespace noise_selection_generator
{
  boost::container::vector<image::Image> get_png_images_from_directory(std::string path);

  void create_directory(std::string path);
}

#endif
