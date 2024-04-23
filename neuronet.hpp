#ifndef NEURONET_HPP
#define NEURONET_HPP

#include <boost/numeric/ublas/matrix.hpp>

#include "softmax.hpp"
#include "linear_algebra.hpp"
#include "activation_functions.hpp"

#define NEURONET_INPUTS 64 // Количество пикселей в изображении 8x8
#define NEURONET_OUTPUTS 5 // Возможные варианты ответа: C, D, O, Q, Неизвестно

#define NEURONET_FIRST_LAYER_NEURONS_COUNT 64

namespace neuronet
{

  class Neuronet
  {
  private:
    boost::numeric::ublas::matrix<double> W1 = get_random_values_matrix_with_sizes(NEURONET_INPUTS, NEURONET_FIRST_LAYER_NEURONS_COUNT);
    boost::numeric::ublas::matrix<double> b1 = get_random_values_matrix_with_sizes(1, NEURONET_FIRST_LAYER_NEURONS_COUNT);

    boost::numeric::ublas::matrix<double> W2 = get_random_values_matrix_with_sizes(NEURONET_FIRST_LAYER_NEURONS_COUNT, NEURONET_OUTPUTS);
    boost::numeric::ublas::matrix<double> b2 = get_random_values_matrix_with_sizes(1, NEURONET_OUTPUTS);

  public:
    boost::numeric::ublas::matrix<double> forward(boost::numeric::ublas::matrix<double> question)
    {
      using namespace boost::numeric::ublas;
      matrix<double> W1xQuestion = multiply_matrix_by_matrix(question, W1);
      matrix<double> t1 = sum_matrix_by_matrix(W1xQuestion, b1);
      matrix<double> h1 = ReLU(t1);
      matrix<double> W2xQuestion = multiply_matrix_by_matrix(h1, W2);
      matrix<double> t2 = sum_matrix_by_matrix(W2xQuestion, b2);
      matrix<double> z = softmax(t2);
      return z;
    }
  };
}

#endif