#ifndef VECTOR_OPERATIONS_HPP
#define VECTOR_OPERATIONS_HPP

#include <boost/container/vector.hpp>

namespace vector_operations
{
  template <typename M, typename V>
  V multiply_matrix_by_vector(M &m, V &v)
  {
    V result(v.size());

    for (int i = 0; i < m.size(); i++)
    {
      for (int j = 0; j < v.size(); j++)
      {
        result[i] += m[i][j] * v[j];
      }
    }

    return result;
  }
}

#endif