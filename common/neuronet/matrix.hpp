#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <boost/numeric/ublas/matrix.hpp>

#include "../../external/json.hpp"

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

  template <typename T>
  unsigned int get_maximum_vector_index(boost::numeric::ublas::matrix<T> &v)
  {
    if (v.size1() > 1)
    {
      throw std::invalid_argument("Вместо вектора была передана матрица");
    }

    unsigned int max_index = 0;
    for (int i = 0; i < v.size2(); i++)
    {
      if (v(0, max_index) < v(0, i))
      {
        max_index = i;
      }
    }

    return max_index;
  }

  template <typename T>
  nlohmann::json convert_matrix_to_json(boost::numeric::ublas::matrix<T> &m)
  {
    nlohmann::json result;
    result["height"] = (int)m.size1();
    result["width"] = (int)m.size2();

    for (int i = 0; i < m.size1(); i++)
    {
      for (int j = 0; j < m.size2(); j++)
      {
        result["values"].push_back(m(i, j));
      }
    }

    return result;
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> parse_matrix_from_json(nlohmann::json &data)
  {
    boost::numeric::ublas::matrix<T> result(data["height"], data["width"]);

    for (int i = 0; i < result.size1(); i++)
    {
      for (int j = 0; j < result.size2(); j++)
      {
        result(i, j) = data["values"][i * result.size2() + j];
      }
    }

    return result;
  }

  template <typename T>
  boost::numeric::ublas::matrix<T> json_vector_to_matrix(nlohmann::json &v)
  {
    boost::numeric::ublas::matrix<T> result(1, v.size());

    for (int i = 0; i < v.size(); i++)
    {
      result(0, i) = v[i];
    }

    return result;
  }
}

#endif