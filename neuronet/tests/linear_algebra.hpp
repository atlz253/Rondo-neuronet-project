#include <boost/test/included/unit_test.hpp>

#include <boost/numeric/ublas/matrix.hpp>

#include "utils/check_matrix_equal.hpp"

#include "../linear_algebra.hpp"

bool is_not_vector_message(const std::logic_error &ex);
bool is_wrong_matrix_sizes_message(const std::logic_error &ex);
bool is_hadamard_multiply_matrix_different_message(const std::logic_error &ex);

BOOST_AUTO_TEST_CASE(сложение_значений_вектора_выбрасывает_исключение_если_была_передана_матрица)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  matrix<int> m1(3, 1);

  BOOST_CHECK_EXCEPTION(sum_vector_values(m1), std::invalid_argument, is_not_vector_message);
}

bool is_not_vector_message(const std::logic_error &ex)
{
  BOOST_CHECK_EQUAL(ex.what(), std::string("Вместо вектора была передана матрица"));
  return true;
}

BOOST_AUTO_TEST_CASE(сложение_значений_вектора_работает)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  int input_vector_data[1][5] = {{1, 2, 3, 4, 5}};
  matrix<int> input = get_filled_matrix_by_array_with_sizes((int *)input_vector_data, 1, 5);

  int result = sum_vector_values(input);

  BOOST_TEST(result == 15);
}

BOOST_AUTO_TEST_CASE(умножение_матриц_выбрасывает_исключение_если_количество_строк_матрицы_A_не_совпадает_с_количеством_столбцов_матрицы_B)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  matrix<int> m1(3, 3), m2(1, 3);

  BOOST_CHECK_EXCEPTION(multiply_matrix_by_matrix(m1, m2), std::invalid_argument, is_wrong_matrix_sizes_message);
}

bool is_wrong_matrix_sizes_message(const std::logic_error &ex)
{
  BOOST_CHECK_EQUAL(ex.what(), std::string("Количество столбцов матрицы A не равно количеству строк матрицы B"));
  return true;
}

BOOST_AUTO_TEST_CASE(умножение_матрицы_на_матрицу_должно_работать)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  int expected_matrix_values[3][3] = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
  matrix<int> expected = get_filled_matrix_by_array_with_sizes((int *)expected_matrix_values, 3, 3);
  int matrix_values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  matrix<int> m1 = get_filled_matrix_by_array_with_sizes((int *)matrix_values, 3, 3);
  matrix<int> m2(m1);

  matrix<int> result = multiply_matrix_by_matrix(m1, m2);

  check_matrix_equal(result, expected);
}

BOOST_AUTO_TEST_CASE(произведение_Адамара_должно_выбрасывать_исключение_если_матрицы_разной_размерности)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  matrix<int> m1(2, 2), m2(1, 1);

  BOOST_CHECK_EXCEPTION(hadamard_multiply_matrix_by_matrix(m1, m2), std::invalid_argument, is_hadamard_multiply_matrix_different_message);
}

bool is_hadamard_multiply_matrix_different_message(const std::logic_error &ex)
{
  BOOST_CHECK_EQUAL(ex.what(), std::string("Произведение адамара работает для матриц одинаковой размерности"));
  return true;
}

BOOST_AUTO_TEST_CASE(произведение_Адамара_должно_работать_корректно)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  int expected_matrix_values[3][3] = {{1, 4, 9}, {16, 25, 36}, {49, 64, 81}};
  matrix<int> expected = get_filled_matrix_by_array_with_sizes((int *)expected_matrix_values, 3, 3);
  int matrix_values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  matrix<int> m1 = get_filled_matrix_by_array_with_sizes((int *)matrix_values, 3, 3);
  matrix<int> m2(m1);

  matrix<int> result = hadamard_multiply_matrix_by_matrix(m1, m2);

  check_matrix_equal(result, expected);
}

BOOST_AUTO_TEST_CASE(exp_matrix_работает_корректно)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  double expect_values[3][3] = {{2.7182818284590451, 7.3890560989306504, 20.085536923187668}, {54.598150033144236, 148.4131591025766, 403.42879349273511}, {1096.6331584284585, 2980.9579870417283, 8103.0839275753842}};
  matrix<double> expect = get_filled_matrix_by_array_with_sizes((double *)expect_values, 3, 3);
  double matrix_values[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  matrix<double> m = get_filled_matrix_by_array_with_sizes((double *)matrix_values, 3, 3);

  matrix<double> result = exp_matrix(m);

  check_matrix_equal(result, expect);
}