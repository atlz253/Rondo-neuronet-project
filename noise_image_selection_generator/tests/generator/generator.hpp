#include <boost/test/included/unit_test.hpp>

#include "../../../external/json.hpp"

#include "../../../common/json.hpp"

#include "../../generator.hpp"
#include "../../options_parser.hpp"
#include "../../string_to_seed.hpp"

BOOST_AUTO_TEST_CASE(генератор_должен_работать_исправно)
{
  using namespace noise_selection_generator;
  
  nlohmann::json expected = read_json_from_file("tests/generator/generator_test.json");
  generator_options options = OptionsParser::get_options_without_filesystem_write();
  options.input_selection_path = "../selections/clear";
  options.seed = string_to_seed("test");
  Generator generator(options);
  
  nlohmann::json result = generator.generate();
  
  BOOST_TEST(result.dump() == expected.dump());
}

BOOST_AUTO_TEST_CASE(количество_изображений_должно_соответствовать_количеству_итераций)
{
  using namespace noise_selection_generator;

  nlohmann::json expected = read_json_from_file("tests/generator/iterations_test.json");
  generator_options options = OptionsParser::get_options_without_filesystem_write();
  options.input_selection_path = "../selections/clear";
  options.seed = string_to_seed("test2");
  options.iterations = 5;
  Generator generator(options);

  nlohmann::json result = generator.generate();
  
  BOOST_TEST(result.dump() == expected.dump());
}
