#include <fstream>
#include <iostream>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "../external/json.hpp"

#include "../common/json.hpp"
#include "../common/arguments.hpp"

#include "../common/neuronet/matrix.hpp"
#include "../common/neuronet/neuronet.hpp"
#include "../common/neuronet/sparse_cross_entropy.hpp"

#include "option_parser.hpp"
#include "help_message.hpp"

int main(int argc, char *argv[])
{
  Arguments arguments(argc, argv);

  if (arguments.contains("--help") || arguments.count() == 0)
  {
    std::cout << HELP_MESSAGE << std::endl;

    return 0;
  }

  // TODO: выбрасывать ошибку если не передан аргумент --input

  // srand(time(NULL));
  neuronet::OptionParser option_parser;
  neuronet::trainer_options options = option_parser.parse_from_arguments(arguments);
  neuronet::Neuronet n(options.neuronet_params);
  nlohmann::json report;

  nlohmann::json dataset = read_json_from_file(options.input_selection_path);

  for (int i = 0; i < options.epochs_count; i++)
  {
    for (int j = 0; j < dataset.size(); j++)
    {
      nlohmann::json forward_report;
      forward_report["type"] = "forward";
      boost::numeric::ublas::matrix<double> question = neuronet::json_to_matrix<double>(dataset[j]["values"]);
      forward_report["question"] = neuronet::convert_matrix_to_json(question);

      boost::numeric::ublas::matrix<double> z = n.forward(question);
      forward_report["t1"] = neuronet::convert_matrix_to_json(n.t1);
      forward_report["h1"] = neuronet::convert_matrix_to_json(n.h1);
      forward_report["t2"] = neuronet::convert_matrix_to_json(n.t2);
      forward_report["result"] = neuronet::convert_matrix_to_json(n.last_result);
      report["report"].push_back(forward_report);

      nlohmann::json backward_report;
      backward_report["type"] = "backward";
      backward_report["result"] = neuronet::convert_matrix_to_json(n.last_result);
      backward_report["learning_rate"] = options.neuronet_params.learning_rate;
      boost::numeric::ublas::matrix<double> answer = neuronet::json_to_matrix<double>(dataset[j]["answer"]);
      backward_report["answer"] = neuronet::convert_matrix_to_json(answer);

      std::cout << z << std::endl;
      double E = neuronet::sparse_cross_entropy(z, answer);
      backward_report["E"] = E;
      std::cout << E << std::endl;

      backward_report["W1_before"] = neuronet::convert_matrix_to_json(n.W1);
      backward_report["b1_before"] = neuronet::convert_matrix_to_json(n.b1);
      backward_report["W2_before"] = neuronet::convert_matrix_to_json(n.W2);
      backward_report["b2_before"] = neuronet::convert_matrix_to_json(n.b2);

      n.backward(answer);

      backward_report["dE_dt2"] = neuronet::convert_matrix_to_json(n.dE_dt2);
      backward_report["dE_dW2"] = neuronet::convert_matrix_to_json(n.dE_dW2);
      backward_report["dE_db2"] = neuronet::convert_matrix_to_json(n.dE_db2);
      backward_report["dE_dh1"] = neuronet::convert_matrix_to_json(n.dE_dh1);
      backward_report["dE_dt1"] = neuronet::convert_matrix_to_json(n.dE_dt1);
      backward_report["dE_dW1"] = neuronet::convert_matrix_to_json(n.dE_dW1);
      backward_report["dE_db1"] = neuronet::convert_matrix_to_json(n.dE_db1);

      backward_report["W1_after"] = neuronet::convert_matrix_to_json(n.W1);
      backward_report["b1_after"] = neuronet::convert_matrix_to_json(n.b1);
      backward_report["W2_after"] = neuronet::convert_matrix_to_json(n.W2);
      backward_report["b2_after"] = neuronet::convert_matrix_to_json(n.b2);

      report["report"].push_back(backward_report);
    }
  }

  std::ofstream out("report.bson");
  std::vector<uint8_t> report_bson = nlohmann::json::to_bson(report);
  for (int i = 0; i < report_bson.size(); i++)
  {
    out << report_bson[i];
  }
  out.close();

  std::ofstream weights_out("weights.json");
  weights_out << n.to_json();
  weights_out.close();

  return 0;
}