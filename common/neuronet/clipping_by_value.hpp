#ifndef CLIPPING_BY_VALUE_HPP
#define CLIPPING_BY_VALUE_HPP

#include <cmath>

#include <boost/numeric/ublas/matrix.hpp>

#include "linear_algebra.hpp"

namespace neuronet
{
  template <typename T>
  boost::numeric::ublas::matrix<T> clipping_by_value(boost::numeric::ublas::matrix<T> &m, double max_threshold, double min_threshold)
  {
    boost::numeric::ublas::matrix<T> result(m);

    for (int i = 0; i < result.size1(); i++)
    {
      for (int j = 0; j < result.size2(); j++)
      {
        if (result(i, j) > max_threshold)
        {
          result(i, j) = max_threshold;
        }
        else if (result(i, j) < min_threshold)
        {
          result(i, j) = min_threshold;
        }
      }
    }

    return result;
  }
}

#endif
