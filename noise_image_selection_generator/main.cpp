#include <iostream>

#include "../common/arguments.hpp"

#include "generator.hpp"
#include "help_message.hpp"
#include "options_parser.hpp"

int main(int argc, char* argv[])
{
  Arguments arguments(argc, argv);

  if (arguments.contains("--help") || arguments.count() == 0)
  {
    std::cout << HELP_MESSAGE << std::endl;
    
    return 0;
  }

  noise_selection_generator::OptionsParser parser;
  noise_selection_generator::generator_options options = parser.parse_from_arguments(arguments);
  noise_selection_generator::Generator generator(options);
  generator.generate();

  return 0;
}