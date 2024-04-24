#ifndef SELECTION_GENERATOR
#define SELECTION_GENERATOR

#include <string>
#include <fstream>

#include <boost/format.hpp>

#include "../external/json.hpp"

#include "../common/json.hpp"

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
    unsigned int seed = 0;
    unsigned int iterations = 1;
    bool generate_selection_json = true;
    bool generate_images = true;
    bool filesystem_write = true;
  } generator_options;

  class Generator
  {
  private:
    generator_options options;

    nlohmann::json get_input_selection_data()
    {
      if (options.generate_selection_json)
      {
        return read_json_from_file(get_file_relative_input_selection_directory_path("selection.json"));
      }
      else
      {
        return get_json_with_png_info_from_directory(options.input_selection_path);
      }
    }

    nlohmann::json generate_noise_selection(nlohmann::json &input_selection_data)
    {
      using namespace nlohmann;

      set_seed(options.seed);

      if (is_output_selection_directory_create_need())
      {
        create_directory(options.selection_save_path);
      }

      json result_data;

      for (int j = 0; j < options.iterations; j++)
      {
        for (int i = 0; i < input_selection_data.size(); i++)
        {
          result_data.push_back(generate_noise_image_with_name_by_json_data((boost::format("%1%.png") % (j * input_selection_data.size() + i)).str(), input_selection_data[i]));
        }
      }

      if (is_selection_json_save_need())
      {
        write_selection_json(result_data);
      }

      return result_data;
    }

    void set_seed(unsigned int seed)
    {
      srand((seed == 0) ? time(0) : seed);
    }

    bool is_output_selection_directory_create_need()
    {
      return options.filesystem_write && (options.generate_images || options.generate_selection_json);
    }

    nlohmann::json generate_noise_image_with_name_by_json_data(std::string filename, nlohmann::json &image_data)
    {
      std::string original_image_filename;
      image_data["filename"].get_to(original_image_filename);
      image::Image img = image::read_png_image(get_file_relative_input_selection_directory_path(original_image_filename));
      noisify_image(img);
      nlohmann::json mask_data = img.get_mask().to_json();
      mask_data["answer"] = image_data["answer"];
      mask_data["filename"] = filename;
      if (is_need_image_file_write())
      {
        image::write_png_image_to_file(img, get_file_relative_input_save_directory_path(filename));
      }
      return mask_data;
    }

    bool is_need_image_file_write()
    {
      return options.filesystem_write && options.generate_images;
    }

    bool is_selection_json_save_need()
    {
      return options.filesystem_write && options.generate_selection_json;
    }

    void write_selection_json(nlohmann::json &selection_data)
    {
      std::ofstream out(get_file_relative_input_save_directory_path("selection.json"));
      out << selection_data.dump();
      out.close();
    }

    std::string get_file_relative_input_selection_directory_path(std::string &filename)
    {
      return (boost::format("%1%/%2%") % options.input_selection_path % filename).str();
    }

    std::string get_file_relative_input_selection_directory_path(const char *filename)
    {
      std::string s(filename);
      return get_file_relative_input_selection_directory_path(s);
    }

    std::string get_file_relative_input_save_directory_path(std::string &filename)
    {
      return (boost::format("%1%/%2%") % options.selection_save_path % filename).str();
    }

    std::string get_file_relative_input_save_directory_path(const char *filename)
    {
      std::string s(filename);
      return get_file_relative_input_save_directory_path(s);
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

    nlohmann::json generate()
    {
      using namespace nlohmann;

      json input_selection_data = get_input_selection_data();
      json result_data = generate_noise_selection(input_selection_data);

      return result_data;
    }
  };
}

#endif