#include <boost/test/included/unit_test.hpp>

#include "../utils/check_matrix_equal.hpp"

#include "../../../external/json.hpp"

#include "../../../common/json.hpp"

#include "../../neuronet/matrix.hpp"

BOOST_AUTO_TEST_CASE(получение_матрицы_со_значениями_из_массива_должно_быть_корректным)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  int values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  matrix<int> expect(3, 3);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      expect(i, j) = values[i][j];
    }
  }

  matrix<int> result = get_filled_matrix_by_array_with_sizes((int *)values, 3, 3);

  check_matrix_equal(result, expect);
}

BOOST_AUTO_TEST_CASE(Конвертирование_матрицы_в_json_должно_работать_корректно)
{
  nlohmann::json expect = read_json_from_file("tests/matrix/matrix_to_json.json");
  int values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  boost::numeric::ublas::matrix<int> m = neuronet::get_filled_matrix_by_array_with_sizes((int *)values, 3, 3);

  nlohmann::json result = neuronet::convert_matrix_to_json(m);

  BOOST_TEST(result.dump() == expect.dump());
}

BOOST_AUTO_TEST_CASE(Преобразование_json_в_матрицу_работает_корректно)
{
  int values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  boost::numeric::ublas::matrix<int> expect = neuronet::get_filled_matrix_by_array_with_sizes((int *)values, 3, 3);
  nlohmann::json matrix_json = read_json_from_file("tests/matrix/matrix_to_json.json");

  boost::numeric::ublas::matrix<int> result = neuronet::parse_matrix_from_json<int>(matrix_json);

  check_matrix_equal(result, expect);
}