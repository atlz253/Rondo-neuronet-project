#include <boost/test/included/unit_test.hpp>

#include <boost/numeric/ublas/matrix.hpp>

#include "utils/check_matrix_equal.hpp"

#include "../neuronet/matrix.hpp"
#include "../neuronet/softmax.hpp"

bool is_argument_not_vector_message(const std::logic_error &ex);

BOOST_AUTO_TEST_CASE(softmax_выбрасывает_исключение_если_передан_не_вектор)
{
  boost::numeric::ublas::matrix<int> m(3, 3);

  BOOST_CHECK_EXCEPTION(neuronet::softmax(m), std::invalid_argument, is_argument_not_vector_message);
}

bool is_argument_not_vector_message(const std::logic_error &ex)
{
  BOOST_CHECK_EQUAL(ex.what(), std::string("Функция softmax предназначена для работы с векторами"));
  return true;
}

BOOST_AUTO_TEST_CASE(softmax_работает_корректно)
{
  using namespace neuronet;
  using namespace boost::numeric::ublas;

  double expect_matrix_data[1][3] = {{0.090030573170380462, 0.24472847105479767, 0.6652409557748219}};
  matrix<double> expect = get_filled_matrix_by_array_with_sizes((double*)expect_matrix_data, 1, 3);
  double input_matrix_data[1][3] = {{1, 2, 3}};
  matrix<double> input = get_filled_matrix_by_array_with_sizes((double*)input_matrix_data, 1, 3);

  matrix<double> result = softmax(input);

  check_matrix_equal(result, expect);
}