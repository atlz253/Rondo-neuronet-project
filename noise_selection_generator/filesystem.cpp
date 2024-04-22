#include "filesystem.hpp"

#include <iostream>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;

boost::container::vector<std::string> get_png_files_from_directory(std::string path);

boost::container::vector<image::Image> noise_selection_generator::get_png_images_from_directory(std::string path)
{
  if (!exists(path))
  {
    std::cout << "Не удалось открыть директорию: " << path << std::endl;

    exit(-1);
  }

  boost::container::vector<std::string> image_paths = get_png_files_from_directory(path);
  boost::container::vector<image::Image> images;
  for (boost::container::vector<std::string>::iterator it = image_paths.begin(); it != image_paths.end(); it++)
  {
    images.push_back(image::read_png_image(it->c_str()));
  }
  return images;
}

boost::container::vector<std::string> get_png_files_from_directory(std::string path)
{
  boost::container::vector<std::string> result;

  directory_iterator end_it;

  for (directory_iterator it(path); it != end_it; it++)
  {
    if (is_directory(it->status()))
    {
      continue;
    }
    else if (it->path().extension() == ".png")
    {
      result.push_back(std::string(it->path().c_str()));
    }
  }
  return result;
}

void noise_selection_generator::create_directory(std::string path)
{
  boost::filesystem::create_directory(path);
}