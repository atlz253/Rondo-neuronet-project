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
}

#endif