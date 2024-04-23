#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <boost/numeric/ublas/matrix.hpp>

namespace neuronet
{
  template <typename T>
  boost::numeric::ublas::matrix<T> get_zero_values_matrix_with_sizes(int rows, int columns)
  {
    boost::numeric::ublas::matrix<T> result(rows, columns);

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns; j++)
      {
        result(i, j) = 0;
      }
    }

    return result;
  }

  boost::numeric::ublas::matrix<double> get_random_values_matrix_with_sizes(int rows, int columns)
  {
    boost::numeric::ublas::matrix<double> result(rows, columns);

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns; j++)
      {
        result(i, j) = (double)rand() / RAND_MAX;
      }
    }

    return result;
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> get_filled_matrix_by_array_with_sizes(T *values, int rows, int columns)
  {
    using namespace boost::numeric::ublas;

    matrix<T> result(rows, columns);

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < columns; j++)
      {
        result(i, j) = values[i * columns + j];
      }
    }

    return result;
  }
}

#endif