#ifndef SOFTMAX_HPP
#define SOFTMAX_HPP

#include <cmath>

#include <boost/numeric/ublas/matrix.hpp>

#include "linear_algebra.hpp"

namespace neuronet
{
  template <typename T>
  boost::numeric::ublas::matrix<T> softmax(boost::numeric::ublas::matrix<T> &m)
  {
    if (m.size1() > 1)
    {
      throw std::invalid_argument("Функция softmax предназначена для работы с векторами");
    }

    boost::numeric::ublas::matrix<T> result(1, m.size2());
    result = exp_matrix(m);
    result /= sum_vector_values(result);
    return result;
  }
}

#endif
