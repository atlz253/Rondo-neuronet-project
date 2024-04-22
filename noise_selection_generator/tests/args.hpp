#include <boost/test/included/unit_test.hpp>

#include "../../noise_selection_generator/args.hpp"
#include "../../noise_selection_generator/generator.hpp"

BOOST_AUTO_TEST_CASE(аргументы_должны_обрабатываться_корректно)
{
  noise_selection_generator::generator_options expected;
  expected.noise_precentage = 0.23;
  expected.input_selection_path = "selection/clear";
  expected.selection_save_path = "test_selection";

  noise_selection_generator::Arguments arguments;
  char *args[] = {"test", "--precentage", "0.23", "--input", "selection/clear", "--output", "test_selection"};
  noise_selection_generator::generator_options result = arguments.parse_arguments(7, args);

  BOOST_TEST(result.noise_precentage == expected.noise_precentage);
  BOOST_TEST(result.input_selection_path == expected.input_selection_path);
  BOOST_TEST(result.selection_save_path == expected.selection_save_path);
}