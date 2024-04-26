#include <random>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <boost/format.hpp>
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

  if (!arguments.contains("--input-selection"))
  {
    throw std::invalid_argument("Отсутствует обязательный аргумент --input-selection");
  }

  srand(time(NULL));
  neuronet::OptionParser option_parser;
  neuronet::trainer_options options = option_parser.parse_from_arguments(arguments);
  neuronet::Neuronet n(options.neuronet_params);

  nlohmann::json report;
  report["learning_rate"] = options.neuronet_params.learning_rate;

  nlohmann::json dataset = read_json_from_file(options.input_selection_path);

  auto rd = std::random_device{};
  auto rng = std::default_random_engine{rd()};

  std::cout << "Обучение нейросети" << std::endl;
  for (int i = 0; i < options.epochs_count; i++)
  {
    show_progress_bar((float)(i * dataset.size()) / (options.epochs_count * dataset.size()));

    if (options.dataset_shuffle)
    {
      std::shuffle(std::begin(dataset), std::end(dataset), rng);
    }

    for (int j = 0; j < dataset.size(); j++)
    {
      boost::numeric::ublas::matrix<double> question = neuronet::json_vector_to_matrix<double>(dataset[j]["values"]);

      boost::numeric::ublas::matrix<double> z = n.forward(question);

      if (options.generate_report)
      {
        nlohmann::json forward_report;
        forward_report["type"] = "forward";
        forward_report["question"] = neuronet::convert_matrix_to_json(question);
        forward_report["t1"] = neuronet::convert_matrix_to_json(n.t1);
        forward_report["h1"] = neuronet::convert_matrix_to_json(n.h1);
        forward_report["t2"] = neuronet::convert_matrix_to_json(n.t2);
        forward_report["result"] = neuronet::convert_matrix_to_json(n.last_result);
        report["report"].push_back(forward_report);
      }

      boost::numeric::ublas::matrix<double> answer = neuronet::json_vector_to_matrix<double>(dataset[j]["answer"]);

      double E = neuronet::sparse_cross_entropy(z, answer);

      n.backward(answer);

      if (options.generate_report)
      {
        nlohmann::json backward_report;
        backward_report["type"] = "backward";
        backward_report["result"] = neuronet::convert_matrix_to_json(n.last_result);
        backward_report["answer"] = neuronet::convert_matrix_to_json(answer);
        backward_report["E"] = E;
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
  }
  show_progress_bar(1);

  std::cout << std::endl
            << "Подсчет точности распознавания изображений из входной выборки" << std::endl;

  int correct = 0;
  for (int j = 0; j < dataset.size(); j++)
  {
    boost::numeric::ublas::matrix<double> question = neuronet::json_vector_to_matrix<double>(dataset[j]["values"]);
    boost::numeric::ublas::matrix<double> answer = neuronet::json_vector_to_matrix<double>(dataset[j]["answer"]);
    boost::numeric::ublas::matrix<double> z = n.forward(question);
    unsigned int z_index = neuronet::get_maximum_vector_index(z);

    if (answer(0, z_index) == 1)
    {
      correct++;
    }
  }
  report["accuracy"] = (float)correct / dataset.size();
  std::cout << "Точность распознавания входной выборки: " << report["accuracy"] << std::endl;

  if (options.test_selection_path.size() > 0)
  {
    std::cout << std::endl
              << "Подсчет точности распознавания изображений из тестовой выборки" << std::endl;

    nlohmann::json test_selection = read_json_from_file(options.test_selection_path);

    correct = 0;
    for (int j = 0; j < test_selection.size(); j++)
    {
      boost::numeric::ublas::matrix<double> question = neuronet::json_vector_to_matrix<double>(test_selection[j]["values"]);
      boost::numeric::ublas::matrix<double> answer = neuronet::json_vector_to_matrix<double>(test_selection[j]["answer"]);
      boost::numeric::ublas::matrix<double> z = n.forward(question);
      unsigned int z_index = neuronet::get_maximum_vector_index(z);

      if (answer(0, z_index) == 1)
      {
        correct++;
      }
    }
    float test_selection_recognition_accuracy = (float)correct / test_selection.size();

    std::cout << "Точность распознавания тестовой выборки: " << test_selection_recognition_accuracy << std::endl;
  }

  if (options.generate_report)
  {
    std::cout << "Запись отчета в хранилище" << std::endl;
    show_progress_bar(0);
    std::ofstream out("report.bson");
    std::vector<uint8_t> report_bson = nlohmann::json::to_bson(report);
    for (int i = 0; i < report_bson.size(); i++)
    {
      out << report_bson[i];
    }
    out.close();
    show_progress_bar(1);
    std::cout << std::endl;
  }

  if (options.save_weights)
  {
    std::cout << "Запись полученных весов в хранилище" << std::endl;
    show_progress_bar(0);
    std::ofstream weights_out("weights.json");
    weights_out << n.to_json();
    weights_out.close();
    show_progress_bar(0.5);
    std::ofstream weights_cpp_out("weights.cpp");
    weights_cpp_out << (boost::format("#include \"weights.hpp\"\nnlohmann::json weights = nlohmann::json::parse(R\"(%1%)\");") % n.to_json()).str();
    weights_cpp_out.close();
    show_progress_bar(1);
  }

  return 0;
}