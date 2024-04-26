#include <string>
#include <fstream>
#include <algorithm>

#include <boost/container/vector.hpp>

#include "../../external/json.hpp"

#ifndef IMAGE_HPP
#define IMAGE_HPP

typedef boost::container::vector<int> rgba_values_vector;
typedef boost::container::vector<rgba_values_vector> pixel_values_vector;

namespace image
{
  class ImageMask
  {
  private:
    pixel_values_vector *pixel_values;
    int width;
    int height;

    int get_mask_value(int i)
    {
      return get_mask_value((*pixel_values)[i]);
    }

    int get_mask_value(rgba_values_vector &v)
    {
      if (v[0] || v[1] || v[2])
      {
        return 0;
      }
      else
      {
        return 1;
      }
    }

  public:
    ImageMask(int width, int height, pixel_values_vector &pixel_values)
    {
      this->width = width;
      this->height = height;
      this->pixel_values = &pixel_values;
    }

    nlohmann::json to_json()
    {
      nlohmann::json j;
      j["width"] = this->width;
      j["height"] = this->height;
      int i = 0;
      for (pixel_values_vector::iterator it = this->pixel_values->begin(); it != this->pixel_values->end(); it++, i++)
      {
        rgba_values_vector v = *it;
        j["values"][i] = get_mask_value(v);
      }
      return j;
    }

    int operator[](int i)
    {
      return get_mask_value(i);
    }
  };

  class Image
  {
  private:
    pixel_values_vector pixel_values;
    int width;
    int height;

  public:
    Image(int width, int height)
    {
      this->width = width;
      this->height = height;
      const int pixel_count = get_pixels_count();
      for (int i = 0; i < pixel_count; i++)
      {
        this->pixel_values.push_back(rgba_values_vector{255, 255, 255, 255});
      }
    }

    int get_pixels_count()
    {
      return get_width() * get_height();
    }

    int get_width()
    {
      return this->width;
    }

    int get_height()
    {
      return this->height;
    }

    static Image from_json(nlohmann::json &json_data)
    {
      Image img(json_data["width"], json_data["height"]);
      int i = 0;
      for (nlohmann::json::iterator it = json_data["values"].begin(); it != json_data["values"].end(); it++, i++)
      {
        img[i][0] = (*it)[0];
        img[i][1] = (*it)[1];
        img[i][2] = (*it)[2];
        img[i][3] = (*it)[3];
      }
      return img;
    }

    nlohmann::json to_json()
    {
      nlohmann::json j;
      j["width"] = this->width;
      j["height"] = this->height;
      int i = 0;
      for (pixel_values_vector::iterator it = this->pixel_values.begin(); it != this->pixel_values.end(); it++, i++)
      {
        rgba_values_vector v = *it;
        j["values"][i] = {v[0], v[1], v[2], v[3]};
      }
      return j;
    }

    ImageMask get_mask()
    {
      return ImageMask(this->width, this->height, this->pixel_values);
    }

    rgba_values_vector &operator[](int i)
    {
      return this->pixel_values[i];
    }
  };

  Image read_png_image(const char *filename);
  Image read_png_image(const std::string &filename);

  void write_png_image_to_file(Image &img, const char *filename);
  void write_png_image_to_file(Image &img, const std::string &filename);
}

#endif // IMAGE_HPP
