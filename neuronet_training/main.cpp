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

#include "progress.hpp"
#include "help_message.hpp"
#include "option_parser.hpp"

int main(int argc, char *argv[])
{
  Arguments arguments(argc, argv);

  if (arguments.contains("--help") || arguments.count() == 0)
  {
    std::cout << HELP_MESSAGE << std::endl;

    return 0;
  }

  // TODO: выбрасывать ошибку если не передан аргумент --input

  srand(time(NULL));
  neuronet::OptionParser option_parser;
  neuronet::trainer_options options = option_parser.parse_from_arguments(arguments);
  neuronet::Neuronet n(options.neuronet_params);

  nlohmann::json report;
  report["learning_rate"] = options.neuronet_params.learning_rate;

  nlohmann::json dataset = read_json_from_file(options.input_selection_path);

  std::cout << "Обучение нейросети" << std::endl;
  for (int i = 0; i < options.epochs_count; i++)
  {
    show_progress_bar((float)(i * dataset.size()) / (options.epochs_count * dataset.size()));
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
      boost::numeric::ublas::matrix<double> answer = neuronet::json_to_matrix<double>(dataset[j]["answer"]);
      backward_report["answer"] = neuronet::convert_matrix_to_json(answer);

      double E = neuronet::sparse_cross_entropy(z, answer);
      backward_report["E"] = E;

      n.backward(answer);

      backward_report["dE_dt2"] = neuronet::convert_matrix_to_json(n.dE_dt2);
      backward_report["dE_dW2"] = neuronet::convert_matrix_to_json(n.dE_dW2);
      backward_report["dE_db2"] = neuronet::convert_matrix_to_json(n.dE_db2);
      backward_report["dE_dh1"] = neuronet::convert_matrix_to_json(n.dE_dh1);
      backward_report["dE_dt1"] = neuronet::convert_matrix_to_json(n.dE_dt1);
      backward_report["dE_dW1"] = neuronet::convert_matrix_to_json(n.dE_dW1);
      backward_report["dE_db1"] = neuronet::convert_matrix_to_json(n.dE_db1);

      backward_report["W1"] = neuronet::convert_matrix_to_json(n.W1);
      backward_report["b1"] = neuronet::convert_matrix_to_json(n.b1);
      backward_report["W2"] = neuronet::convert_matrix_to_json(n.W2);
      backward_report["b2"] = neuronet::convert_matrix_to_json(n.b2);

      report["report"].push_back(backward_report);
    }
  }
  show_progress_bar(1);

  std::cout << std::endl
            << "Подсчет точности распознавания изображений из входной выборки" << std::endl;

  int correct = 0;
  for (int j = 0; j < dataset.size(); j++)
  {
    boost::numeric::ublas::matrix<double> question = neuronet::json_to_matrix<double>(dataset[j]["values"]);
    boost::numeric::ublas::matrix<double> answer = neuronet::json_to_matrix<double>(dataset[j]["answer"]);
    boost::numeric::ublas::matrix<double> z = n.forward(question);
    unsigned int z_index = neuronet::get_maximum_vector_index(z);

    if (answer(0, z_index) == 1)
    {
      correct++;
    }
  }
  report["accuracy"] = (float)correct / dataset.size();
  std::cout << "Точность распознавания входной выборки: " << report["accuracy"] << std::endl;

  std::cout << "Запись полученных данных в хранилище" << std::endl;

  show_progress_bar(0);
  std::ofstream out("report.bson");
  std::vector<uint8_t> report_bson = nlohmann::json::to_bson(report);
  for (int i = 0; i < report_bson.size(); i++)
  {
    out << report_bson[i];
  }
  out.close();
  show_progress_bar(0.5);

  std::ofstream weights_out("weights.json");
  weights_out << n.to_json();
  weights_out.close();
  show_progress_bar(1);

  return 0;
}