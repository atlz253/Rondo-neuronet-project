#include <string>
#include <iomanip>
#include <iostream>

#include <boost/container/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "../external/json.hpp"

#include "../common/arguments.hpp"
#include "../common/image/image.hpp"
#include "../common/neuronet/matrix.hpp"
#include "../common/neuronet/neuronet.hpp"

#include "weights.hpp"
#include "help_message.hpp"

int main(int argc, char *argv[])
{
  Arguments arguments(argc, argv);

  if (argc == 1 || arguments.contains("--help"))
  {
    std::cout << HELP_MESSAGE << std::endl;
    return 0;
  }
  
  neuronet::Neuronet n(weights);

  boost::container::vector<std::string> classes{"буква C", "буква D", "буква O", "буква Q", "ни на что не похоже"};
  image::Image img = image::read_png_image(argv[1]);

  nlohmann::json mask_json = img.get_mask().to_json();
  boost::numeric::ublas::matrix<double> m = neuronet::json_vector_to_matrix<double>(mask_json["values"]); // TODO: json_to_vector

  boost::numeric::ublas::matrix<double> answer = n.forward(m);
  unsigned int answer_index = neuronet::get_maximum_vector_index(answer);

  if (answer_index == 4)
  {
    std::cout << "Мне не удалось распознать образ :(" << std::endl;
  }
  else
  {
    std::cout << "Я думаю, что на изображении " << classes[answer_index] << std::endl;
  }

  if (arguments.contains("--show-precentage"))
  {
    std::cout << "Если подробнее, то вот что я думаю об этом изображении:" << std::endl;
    for (int i = 0; i < answer.size2(); i++)
    {
      std::cout << "Вероятность, что это " << classes[i] << ": " << std::fixed << std::setprecision(2) << answer(0, i) * 100 << "%" << std::endl;
    }
  }

  return 0;
}