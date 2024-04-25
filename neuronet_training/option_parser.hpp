#ifndef OPTION_PARSER_HPP
#define OPTION_PARSER_HPP

#include <string>

#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "../common/arguments.hpp"

namespace neuronet
{
  typedef struct trainer_options
  {
    neuronet_options neuronet_params;
    std::string input_selection_path;
    unsigned int epochs_count = 100;
  } trainer_options;

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

  class OptionParser
  {
  private:
    Arguments *arguments;
    trainer_options *options;

    void parse_argument_if_needed(const std::string &arg)
    {
      if (arg == "--input-selection")
      {
        options->input_selection_path = (*arguments)[arg].front();
      }
      else if (arg == "--learning-rate")
      {
        options->neuronet_params.learning_rate = parse_double((*arguments)[arg].front());
      }
      else if (arg == "--epochs-count")
      {
        options->epochs_count = std::stoi((*arguments)[arg].front());
      }
      else if (arg == "--first-layer-neurons-count")
      {
        options->neuronet_params.first_layer_neurons_count = std::stoi((*arguments)[arg].front());
      }
    }

    double parse_double(const std::string &s)
    {
      try
      {
        return boost::lexical_cast<double>(s);
      }
      catch (boost::bad_lexical_cast &)
      {
        throw OptionParserException((boost::format("Не удалось преобразовать аргумент к типу double: %1%") % s).str());
      }
    }
  public:
    trainer_options parse_from_arguments(Arguments &arguments)
    {
      this->arguments = &arguments;
      options = new trainer_options();

      for (auto it = arguments.begin(); it != arguments.end(); it++)
      {
        parse_argument_if_needed(it->first);
      }

      return *options;
    }
  };
}

#endif