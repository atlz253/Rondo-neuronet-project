#ifndef NEURONET_HPP
#define NEURONET_HPP

#include <cassert>

#include <boost/numeric/ublas/matrix.hpp>

#include "../../external/json.hpp"

#include "matrix.hpp"
#include "softmax.hpp"
#include "linear_algebra.hpp"
#include "activation_functions.hpp"

#define NEURONET_INPUTS 64 // Количество пикселей в изображении 8x8
#define NEURONET_OUTPUTS 88

namespace neuronet
{
  typedef struct neuronet_options
  {
    double learning_rate = 0.001;
    unsigned int first_layer_neurons_count = 128;
  } neuronet_options;

  class Neuronet
  {
  private:
    neuronet_options options;

  public:
    boost::numeric::ublas::matrix<double> W1;
    boost::numeric::ublas::matrix<double> b1;

    boost::numeric::ublas::matrix<double> W2;
    boost::numeric::ublas::matrix<double> b2;

    boost::numeric::ublas::matrix<double> last_question;

    boost::numeric::ublas::matrix<double> t1;
    boost::numeric::ublas::matrix<double> h1;

    boost::numeric::ublas::matrix<double> t2;
    boost::numeric::ublas::matrix<double> last_result;

    boost::numeric::ublas::matrix<double> dE_dt2;
    boost::numeric::ublas::matrix<double> dE_dW2;
    boost::numeric::ublas::matrix<double> dE_db2;

    boost::numeric::ublas::matrix<double> dE_dh1;
    boost::numeric::ublas::matrix<double> dE_dt1;
    boost::numeric::ublas::matrix<double> dE_dW1;
    boost::numeric::ublas::matrix<double> dE_db1;

    Neuronet(neuronet_options &options)
    {
      this->options = options;

      W1 = get_random_values_matrix_with_sizes(NEURONET_INPUTS, options.first_layer_neurons_count);
      b1 = get_random_values_matrix_with_sizes(1, options.first_layer_neurons_count);

      W2 = get_random_values_matrix_with_sizes(options.first_layer_neurons_count, NEURONET_OUTPUTS);
      b2 = get_random_values_matrix_with_sizes(1, NEURONET_OUTPUTS);
    }

    Neuronet(nlohmann::json &j)
    {
      options.first_layer_neurons_count = j["first_layer_neurons_count"];
      options.learning_rate = j["learning_rate"];
      W1 = parse_matrix_from_json<double>(j["W1"]);
      b1 = parse_matrix_from_json<double>(j["b1"]);
      W2 = parse_matrix_from_json<double>(j["W2"]);
      b2 = parse_matrix_from_json<double>(j["b2"]);
    }

    boost::numeric::ublas::matrix<double> forward(boost::numeric::ublas::matrix<double> question)
    {
      using namespace boost::numeric::ublas;

      last_question = question;

      matrix<double> W1xQuestion = multiply_matrix_by_matrix(question, W1);
      t1 = W1xQuestion + b1;
      h1 = ReLU(t1);
      matrix<double> W2xQuestion = multiply_matrix_by_matrix(h1, W2);
      t2 = W2xQuestion + b2;
      last_result = softmax(t2);

      assert(last_result(0, 0) == last_result(0, 0));

      return last_result;
    }

    void backward(boost::numeric::ublas::matrix<double> &answer)
    {
      using namespace boost::numeric::ublas;

      dE_dt2 = last_result - answer;
      matrix<double> h1_transposed = trans(h1);
      dE_dW2 = multiply_matrix_by_matrix(h1_transposed, dE_dt2);
      dE_db2 = dE_dt2;
      matrix<double> W2_transoposed = trans(W2);
      dE_dh1 = multiply_matrix_by_matrix(dE_dt2, W2_transoposed);
      matrix<double> t1_ReLU_d = ReLU_deriv(t1);
      dE_dt1 = hadamard_multiply_matrix_by_matrix(dE_dh1, t1_ReLU_d);
      matrix<double> question_transposed = trans(last_question);
      dE_dW1 = multiply_matrix_by_matrix(question_transposed, dE_dt1);
      dE_db1 = dE_dt1;

      // Обновление весов
      W1 = W1 - options.learning_rate * dE_dW1;
      b1 = b1 - options.learning_rate * dE_db1;
      W2 = W2 - options.learning_rate * dE_dW2;
      b2 = b2 - options.learning_rate * dE_db2;
    }

    nlohmann::json to_json()
    {
      nlohmann::json j;

      j["first_layer_neurons_count"] = options.first_layer_neurons_count;
      j["learning_rate"] = options.learning_rate;
      j["W1"] = convert_matrix_to_json(W1);
      j["b1"] = convert_matrix_to_json(b1);
      j["W2"] = convert_matrix_to_json(W2);
      j["b2"] = convert_matrix_to_json(b2);

      return j;
    }
  };
}

#endif