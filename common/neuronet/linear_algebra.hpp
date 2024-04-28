#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

#include <cmath>
#include <limits>

#include <boost/numeric/ublas/matrix.hpp>

#include "matrix.hpp"

namespace neuronet
{
  template <typename T>
  T sum_vector_values(boost::numeric::ublas::matrix<T> &v)
  {
    if (v.size1() > 1)
    {
      throw std::invalid_argument("Вместо вектора была передана матрица");
    }

    T sum = 0;
    for (int i = 0; i < v.size2(); i++)
    {
      sum += v(0, i);
    }

    return sum;
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> multiply_matrix_by_matrix(boost::numeric::ublas::matrix<T> &m1, boost::numeric::ublas::matrix<T> &m2)
  {
    using namespace boost::numeric::ublas;

    if (m1.size2() != m2.size1())
    {
      throw std::invalid_argument("Количество столбцов матрицы A не равно количеству строк матрицы B");
    }

    matrix<T> result = get_zero_values_matrix_with_sizes<T>(m1.size1(), m2.size2());

    for (int k = 0; k < m2.size2(); k++)
    {
      for (int j = 0; j < m1.size1(); j++)
      {
        for (int i = 0; i < m1.size2(); i++)
        {
          result(j, k) += m1(j, i) * m2(i, k);
        }
      }
    }

    return result;
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> hadamard_multiply_matrix_by_matrix(boost::numeric::ublas::matrix<T> &m1, boost::numeric::ublas::matrix<T> &m2)
  {
    if (m1.size1() != m2.size1() || m1.size2() != m2.size2())
    {
      throw std::invalid_argument("Произведение адамара работает для матриц одинаковой размерности");
    }

    boost::numeric::ublas::matrix<T> result(m1.size1(), m1.size2());

    for (int i = 0; i < m1.size1(); i++)
    {
      for (int j = 0; j < m1.size2(); j++)
      {
        result(i, j) = m1(i, j) * m2(i, j);
      }
    }

    return result;
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> exp_matrix(boost::numeric::ublas::matrix<T> &m)
  {
    boost::numeric::ublas::matrix<T> result(m.size1(), m.size2());

    for (int i = 0; i < m.size1(); i++)
    {
      for (int j = 0; j < m.size2(); j++)
      {
        if (m(i, j) >= 709.8)
        {
          result(i, j) = exp(709.8);
        }
        else if (m(i, j) <= -708.4)
        {
          result(i, j) = exp(-708.4);
        }
        else
        {
          result(i, j) = exp(m(i, j));
        }
      }
    }

    return result;
  }
}

#endif
