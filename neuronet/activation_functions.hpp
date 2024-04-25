#ifndef ACTIVATION_FUNCTION_HPP
#define ACTIVATION_FUNCTION_HPP

#include <boost/numeric/ublas/matrix.hpp>

namespace neuronet
{
  template <typename T>
  T ReLU(T x)
  {
    if (x <= 0)
    {
      return 0;
    }
    else
    {
      return x;
    }
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> ReLU(boost::numeric::ublas::matrix<T> &m)
  {
    boost::numeric::ublas::matrix<T> result(m.size1(), m.size2());

    for (int i = 0; i < m.size1(); i++)
    {
      for (int j = 0; j < m.size2(); j++)
      {
        result(i, j) = ReLU(m(i, j));
      }
    }

    return result;
  }

  template <typename T>
  T ReLU_deriv(T x)
  {
    return (x >= 0) ? 1 : 0;
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> ReLU_deriv(boost::numeric::ublas::matrix<T> &m)
  {
    if (m.size1() > 1)
    {
      throw std::invalid_argument("ReLU_deriv работает только с векторами");
    }

    boost::numeric::ublas::matrix<T> result(1, m.size2());

    for (int i = 0; i < m.size2(); i++)
    {
      result(0, i) = ReLU_deriv(m(0, i));
    }

    return result;
  }
}

#endif