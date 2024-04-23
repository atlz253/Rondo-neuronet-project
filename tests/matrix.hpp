#include <boost/test/included/unit_test.hpp>

#include "utils/check_matrix_equal.hpp"

#include "../matrix.hpp"

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