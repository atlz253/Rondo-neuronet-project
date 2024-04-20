#include <boost/test/included/unit_test.hpp>

#include <boost/container/vector.hpp>

#include "../vector_operations.hpp"

boost::container::vector<boost::container::vector<double>> get_test_matrix();

BOOST_AUTO_TEST_CASE(умножение_матрицы_из_векторов_на_вектор)
{
  boost::container::vector<double> v{1, 2, 3, 4};
  boost::container::vector<double> expect{20, 60, 100, 140};
  boost::container::vector<boost::container::vector<double>> m = get_test_matrix();
  boost::container::vector<double> result = vector_operations::multiply_matrix_by_vector(m, v);
  BOOST_TEST(result == expect);
}

boost::container::vector<boost::container::vector<double>> get_test_matrix()
{
  boost::container::vector<boost::container::vector<double>> m;
  double count = 0;
  for (int i = 0; i < 4; i++, count += 4)
  {
    m.push_back(boost::container::vector<double>{count, count + 1, count + 2, count + 3});
  }
  return m;
}