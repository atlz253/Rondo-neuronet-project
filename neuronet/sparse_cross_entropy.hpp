#ifndef SPARSE_CROSS_ENTROPY_HPP
#define SPARSE_CROSS_ENTROPY_HPP

#include <cmath>

#include <boost/numeric/ublas/matrix.hpp>

namespace neuronet
{
  template <typename T>
  T sparse_cross_entropy(boost::numeric::ublas::matrix<T> &z, boost::numeric::ublas::matrix<T> &y)
  {
    if (z.size1() > 1 || y.size1() > 1)
    {
      throw std::invalid_argument("Функция sparse_cross_entropy предназначена для работы с векторами");
    }

    if (z.size2() != y.size2())
    {
      throw std::invalid_argument("Функция sparse_cross_entropy работает только с векторами одинакового размера");
    }

    T result = 0;

    for (int i = 0; i < z.size2(); i++)
    {
      result += y(0, i) * log(z(0, i));
    }

    return -result;
  }
}

#endif