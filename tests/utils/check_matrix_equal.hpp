#ifndef CHECK_MATRIX_EQUAL_HPP
#define CHECK_MATRIX_EQUAL_HPP

#include <boost/test/included/unit_test.hpp>

#include <boost/numeric/ublas/matrix.hpp>

template <typename F>
void check_matrix_equal(boost::numeric::ublas::matrix<F> m1, boost::numeric::ublas::matrix<F> m2)
{
  for (typename boost::numeric::ublas::matrix<F>::iterator1 it1 = m1.begin1(), it2 = m2.begin1(); it1 != m1.end1() || it2 != m2.end1(); it1++, it2++)
  {
    BOOST_CHECK_EQUAL_COLLECTIONS(it1.begin(), it1.end(), it2.begin(), it2.end());
  }
}

#endif
