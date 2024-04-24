#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <boost/container/vector.hpp>

#include "../external/json.hpp"

namespace noise_selection_generator
{
  nlohmann::json get_json_with_png_info_from_directory(std::string path);

  void create_directory(std::string path);
}

#endif
