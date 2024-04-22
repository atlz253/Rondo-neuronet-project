#ifndef ARGS_HPP
#define ARGS_HPP

#include <cmath>
#include <ctime>
#include <string>
#include <cstring>
#include <iostream>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "generator.hpp"

namespace noise_selection_generator
{
  class Arguments
  {
  private:
    int argc;
    char **argv;
    generator_options *arguments;

    std::string get_deafult_output_selection_directory_name()
    {
      std::time_t now = time(0);
      std::tm *ltm = localtime(&now);
      return (boost::format("noise_selection_%1%.%2%.%3%_%4%-%5%-%6%") % (1900 + ltm->tm_year) % (1 + ltm->tm_mon) % ltm->tm_mday % ltm->tm_hour % (1 + ltm->tm_min) % (1 + ltm->tm_sec)).str();
    }

    bool is_argument(char *input)
    {
      for (int i = 0; i < 2; i++)
      {
        if (input[i] != '-')
        {
          return false;
        }
      }

      return true;
    }

    void parse_argument(char *arg, int position)
    {
      if (strcmp(arg, "--precentage") == 0)
      {
        this->arguments->noise_precentage = parse_noise_precentage(this->argv[position + 1]);
      }
      else if (strcmp(arg, "--input") == 0)
      {
        this->arguments->input_selection_path = argv[position + 1];
      }
      else if (strcmp(arg, "--output") == 0)
      {
        this->arguments->selection_save_path = argv[position + 1];
      }
      else
      {
        std::cout << "Неизвестный аргумент: " << arg << std::endl;

        exit(-1);
      }
    }

    float parse_noise_precentage(char *precentage)
    {
      float p = parse_float(precentage);

      if (p > 1)
      {
        std::cout << "Процент зашумленности не может быть больше 100%" << std::endl;

        exit(-1);
      }
      else if (p < 0)
      {
        std::cout << "Процент зашумленности не может быть меньше 0%" << std::endl;

        exit(-1);
      }
      else
      {
        return p;
      }
    }

    float parse_float(char *s)
    {
      try
      {
        return boost::lexical_cast<float>(s);
      }
      catch (boost::bad_lexical_cast &)
      {
        std::cout << "Не удалось преобразовать аргумент к типу float: " << s << std::endl;

        exit(-1);
      }
    }

  public:
    generator_options parse_arguments(int argc, char *argv[])
    {
      this->argc = argc;
      this->argv = argv;
      this->arguments = new generator_options();

      for (int i = 1; i < argc; i++)
      {
        if (is_argument(argv[i]))
        {
          parse_argument(argv[i], i);
        }
      }

      if (this->arguments->selection_save_path.size() == 0)
      {
        this->arguments->selection_save_path = get_deafult_output_selection_directory_name();
      }

      if (this->arguments->input_selection_path.size() == 0)
      {
        std::cout << "Не была передана директория с входной выборкой --input" << std::endl;

        exit(-1);
      }

      return *arguments;
    }
  };
}

#endif