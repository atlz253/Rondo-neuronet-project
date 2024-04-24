#ifndef JSON_COMMON_HPP
#define JSON_COMMON_HPP

#include <fstream>

#include "../external/json.hpp"

nlohmann::json read_json_from_file(const std::string &path)
{
  std::fstream f(path);
  nlohmann::json j = nlohmann::json::parse(f);
  f.close();
  return j;
}

#endif
