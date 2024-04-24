#include "filesystem.hpp"

#include <boost/format.hpp>
#include <boost/filesystem.hpp>

using namespace nlohmann;
using namespace boost::container;
using namespace boost::filesystem;

vector<std::string> get_png_file_names_from_directory(std::string path);
json get_png_json_data_by_filename(std::string &filename);

json noise_selection_generator::get_json_with_png_info_from_directory(std::string path)
{
  if (!exists(path))
  {
    throw std::invalid_argument((boost::format("Не удалось открыть директорию: %1%") % path).str());
  }

  vector<std::string> png_file_names = get_png_file_names_from_directory(path);
  json result;
  for (vector<std::string>::iterator it = png_file_names.begin(); it != png_file_names.end(); it++)
  {
    result.push_back(get_png_json_data_by_filename(*it));
  }
  return result;
}

vector<std::string> get_png_file_names_from_directory(std::string path)
{
  vector<std::string> result;

  directory_iterator end_it;

  for (directory_iterator it(path); it != end_it; it++)
  {
    if (is_directory(it->status()))
    {
      continue;
    }
    else if (it->path().extension() == ".png")
    {
      result.push_back(std::string(it->path().filename().c_str()));
    }
  }
  return result;
}

json get_png_json_data_by_filename(std::string &filename)
{
  json img_data;
  img_data["filename"] = filename;
  return img_data;
}

void noise_selection_generator::create_directory(std::string path)
{
  boost::filesystem::create_directory(path);
}