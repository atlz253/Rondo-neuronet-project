#ifndef OPTIONS_PARSER_HPP
#define OPTIONS_PARSER_HPP

#include <string>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/container/map.hpp>
#include <boost/container/list.hpp>

#include "../common/arguments.hpp"

#include "generator.hpp"
#include "string_to_seed.hpp"

namespace noise_selection_generator
{
  class OptionParserException: public std::exception
  {
  private:
    std::string message;

  public:
    OptionParserException(const std::string& message) : message(message){}
    virtual const char* what() const noexcept override
    {
        return message.c_str();
    }
  };

  class OptionsParser
  {
  private:
    Arguments *arguments;
    generator_options *options;

    void parse_argument_if_needed(const std::string &arg)
    {
      if (arg == "--precentage")
      {
        options->noise_precentage = parse_noise_precentage((*arguments)[arg].front());
      }
      else if (arg == "--input")
      {
        options->input_selection_path = (*arguments)[arg].front();
      }
      else if (arg == "--output")
      {
        options->selection_save_path = (*arguments)[arg].front();
      }
      else if (arg == "--seed")
      {
        options->seed = string_to_seed((*arguments)[arg].front());
      }
      else if (arg == "--iterations")
      {
        options->iterations = std::stoi((*arguments)[arg].front());
      }
      else if (arg == "--no-selection-json")
      {
        options->generate_selection_json = false;
      }
      else if (arg == "--no-image-generation")
      {
        options->generate_images = false;
      }
    }

    float parse_noise_precentage(const std::string &precentage)
    {
      float p = parse_float(precentage);

      if (p > 1)
      {
        throw OptionParserException("Процент зашумленности не может быть больше 100%");
      }
      else if (p < 0)
      {
        throw OptionParserException("Процент зашумленности не может быть меньше 0%");
      }
      else
      {
        return p;
      }
    }

    float parse_float(const std::string &s)
    {
      try
      {
        return boost::lexical_cast<float>(s);
      }
      catch (boost::bad_lexical_cast &)
      {
        throw OptionParserException((boost::format("Не удалось преобразовать аргумент к типу float: %%1") % s).str());
      }
    }

    static std::string get_deafult_output_selection_directory_name()
    {
      std::time_t now = time(0);
      std::tm *ltm = localtime(&now);
      return (boost::format("noise_selection_%1%.%2%.%3%_%4%-%5%-%6%") % (1900 + ltm->tm_year) % (1 + ltm->tm_mon) % ltm->tm_mday % ltm->tm_hour % (1 + ltm->tm_min) % (1 + ltm->tm_sec)).str();
    }
  public:
    generator_options parse_from_arguments(Arguments &arguments)
    {
      using namespace boost::container;

      this->arguments = &arguments;
      options = new generator_options();

      for (map<std::string, list<std::string>>::iterator it = arguments.begin(); it != arguments.end(); it++)
      {
        parse_argument_if_needed(it->first);
      }

      if (options->selection_save_path.size() == 0)
      {
        options->selection_save_path = get_deafult_output_selection_directory_name();
      }

      if (options->input_selection_path.size() == 0)
      {
        throw OptionParserException("Не была передана директория с входной выборкой --input");
      }

      return *options;
    }

    static generator_options get_options_without_filesystem_write()
    {
      generator_options options;
      options.filesystem_write = false;
      return options;
    }
  };
}

#endif