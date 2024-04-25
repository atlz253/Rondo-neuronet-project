#ifndef NEURONET_HPP
#define NEURONET_HPP

#include <boost/numeric/ublas/matrix.hpp>

#include "softmax.hpp"
#include "linear_algebra.hpp"
#include "activation_functions.hpp"

#include <iostream>
#include <boost/numeric/ublas/io.hpp>

#define NEURONET_INPUTS 64 // Количество пикселей в изображении 8x8
#define NEURONET_OUTPUTS 5 // Возможные варианты ответа: C, D, O, Q, Неизвестно

#define NEURONET_FIRST_LAYER_NEURONS_COUNT 64

#define LEARNING_RATE 0.001
#define EPOCHS_COUNT 100

namespace neuronet
{

  class Neuronet
  {
  private:
    boost::numeric::ublas::matrix<double> W1 = get_random_values_matrix_with_sizes(NEURONET_INPUTS, NEURONET_FIRST_LAYER_NEURONS_COUNT);
    boost::numeric::ublas::matrix<double> b1 = get_random_values_matrix_with_sizes(1, NEURONET_FIRST_LAYER_NEURONS_COUNT);

    boost::numeric::ublas::matrix<double> W2 = get_random_values_matrix_with_sizes(NEURONET_FIRST_LAYER_NEURONS_COUNT, NEURONET_OUTPUTS);
    boost::numeric::ublas::matrix<double> b2 = get_random_values_matrix_with_sizes(1, NEURONET_OUTPUTS);

    boost::numeric::ublas::matrix<double> last_question;
    boost::numeric::ublas::matrix<double> last_result;

    boost::numeric::ublas::matrix<double> t1;
    boost::numeric::ublas::matrix<double> h1;

  public:
    boost::numeric::ublas::matrix<double> forward(boost::numeric::ublas::matrix<double> question)
    {
      using namespace boost::numeric::ublas;

      last_question = question;

      matrix<double> W1xQuestion = multiply_matrix_by_matrix(question, W1);
      t1 = W1xQuestion + b1;
      h1 = ReLU(t1);
      matrix<double> W2xQuestion = multiply_matrix_by_matrix(h1, W2);
      matrix<double> t2 = W2xQuestion + b2;
      last_result = softmax(t2);

      return last_result;
    }

    void backward(boost::numeric::ublas::matrix<double> &answer)
    {
      using namespace boost::numeric::ublas;

      matrix<double> dE_dt2 = last_result - answer;
      matrix<double> h1_transposed = trans(h1);
      matrix<double> dE_dW2 = multiply_matrix_by_matrix(h1_transposed, dE_dt2);
      matrix<double> dE_db2 = dE_dt2;
      matrix<double> W2_transoposed = trans(W2);
      matrix<double> dE_dh1 = multiply_matrix_by_matrix(dE_dt2, W2_transoposed);
      matrix<double> t1_ReLU_d = ReLU_deriv(t1);
      matrix<double> dE_dt1 = hadamard_multiply_matrix_by_matrix(dE_dh1, t1_ReLU_d);
      matrix<double> question_transposed = trans(last_question);
      matrix<double> dE_dW1 = multiply_matrix_by_matrix(question_transposed, dE_dt1);
      matrix<double> dE_db1 = dE_dt1;

      // Обновление весов
      W1 = W1 - LEARNING_RATE * dE_dW1;
      b1 = b1 - LEARNING_RATE * dE_db1;
      W2 = W2 - LEARNING_RATE * dE_dW2;
      b2 = b2 - LEARNING_RATE * dE_db2;
    }
  };
}

#endif