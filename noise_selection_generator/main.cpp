#include "args.hpp"
#include "generator.hpp"

int main(int argc, char* argv[])
{
  noise_selection_generator::Arguments arguments;
  noise_selection_generator::generator_options options = arguments.parse_arguments(argc, argv);
  noise_selection_generator::Generator generator(options);
  generator.generate();
  return 0;
}