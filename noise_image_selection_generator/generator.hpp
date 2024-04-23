#ifndef SELECTION_GENERATOR
#define SELECTION_GENERATOR

#include <string>

#include <boost/format.hpp>

#include "random.hpp"
#include "image.hpp"
#include "filesystem.hpp"

namespace noise_selection_generator
{
  typedef struct generator_options
  {
    float noise_precentage = 0.1;
    std::string input_selection_path;
    std::string selection_save_path;
  } generator_options;

  class Generator
  {
  private:
    generator_options options;

    boost::container::vector<image::Image> noisify_images(boost::container::vector<image::Image> &images)
    {
      using namespace boost::container;

      for (vector<image::Image>::iterator it = images.begin(); it != images.end(); it++)
      {
        noisify_image(*it);
      }

      return images;
    }

    void noisify_image(image::Image &img)
    {
      using namespace boost::container;

      const int pixels_count = img.get_pixels_count();
      const int noise_pixels_count = (int)(pixels_count * options.noise_precentage);
      vector<int> noise_pixels_indexes = get_unique_random_numbers(0, pixels_count - 1, noise_pixels_count);

      for (vector<int>::iterator it = noise_pixels_indexes.begin(); it != noise_pixels_indexes.end(); it++)
      {
        switch_pixel_color(img[*it]);
      }
    }

    void switch_pixel_color(boost::container::vector<int> &rgba_values)
    {
      if (is_black_pixel(rgba_values))
      {
        rgba_values[0] = 255;
        rgba_values[1] = 255;
        rgba_values[2] = 255;
      }
      else
      {
        rgba_values[0] = 0;
        rgba_values[1] = 0;
        rgba_values[2] = 0;
      }
    }

    bool is_black_pixel(boost::container::vector<int> &rgba_values)
    {
      return rgba_values[0] == 0 && rgba_values[1] == 0 && rgba_values[2] == 0;
    }

    void write_images(boost::container::vector<image::Image> &images)
    {
      int i = 0;
      for (boost::container::vector<image::Image>::iterator it = images.begin(); it != images.end(); it++, i++)
      {
        image::write_png_image_to_file(*it, (boost::format("%1%/%2%.png") % options.selection_save_path % i).str().c_str());
      }
    }

  public:
    Generator(generator_options options)
    {
      this->options = options;
    }

    void generate()
    {
      boost::container::vector<image::Image> images = get_png_images_from_directory(options.input_selection_path);
      images.push_back(image::Image(8, 8));
      images = noisify_images(images);
      create_directory(options.selection_save_path);
      write_images(images);      
    }
  };
}

#endif