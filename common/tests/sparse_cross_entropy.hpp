#include <boost/test/included/unit_test.hpp>

#include <boost/numeric/ublas/matrix.hpp>

#include "../neuronet/matrix.hpp"
#include "../neuronet/sparse_cross_entropy.hpp"

bool is_sparse_cross_entropy_argument_not_vector_message(const std::logic_error &ex);
bool is_sparse_cross_entropy_vector_different_sizes_message(const std::logic_error &ex);

BOOST_AUTO_TEST_CASE(выбрасывается_исключение_если_передан_не_вектор)
{
  boost::numeric::ublas::matrix<double> m1(2, 2), m2(1, 1);

  BOOST_CHECK_EXCEPTION(neuronet::sparse_cross_entropy(m1, m2), std::invalid_argument, is_sparse_cross_entropy_argument_not_vector_message);
  BOOST_CHECK_EXCEPTION(neuronet::sparse_cross_entropy(m2, m1), std::invalid_argument, is_sparse_cross_entropy_argument_not_vector_message);
}

bool is_sparse_cross_entropy_argument_not_vector_message(const std::logic_error &ex)
{
  BOOST_CHECK_EQUAL(ex.what(), std::string("Функция sparse_cross_entropy предназначена для работы с векторами"));
  return true;
}

BOOST_AUTO_TEST_CASE(выбрасывается_исключение_если_переданы_векторы_разного_размера)
{
  boost::numeric::ublas::matrix<double> m1(1, 1), m2(1, 2);

  BOOST_CHECK_EXCEPTION(neuronet::sparse_cross_entropy(m1, m2), std::invalid_argument, is_sparse_cross_entropy_vector_different_sizes_message);
}

bool is_sparse_cross_entropy_vector_different_sizes_message(const std::logic_error &ex)
{
  BOOST_CHECK_EQUAL(ex.what(), std::string("Функция sparse_cross_entropy работает только с векторами одинакового размера"));
  return true;
}

BOOST_AUTO_TEST_CASE(sparse_cross_entropy_работает_корректно)
{
  double expect = 0.22314355131420971;
  double m1_data[1][3] = {{0.1, 0.8, 0.1}};
  boost::numeric::ublas::matrix<double> m1 = neuronet::get_filled_matrix_by_array_with_sizes((double *)m1_data, 1, 3);
  double m2_data[1][3] = {{0, 1, 0}};
  boost::numeric::ublas::matrix<double> m2 = neuronet::get_filled_matrix_by_array_with_sizes((double *)m2_data, 1, 3);

  double result = neuronet::sparse_cross_entropy(m1, m2);

  BOOST_TEST(result == expect);
}