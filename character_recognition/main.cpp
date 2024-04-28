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

  boost::container::vector<std::string> classes{"_", "-", ",", ";", "!", "'", "(", ")", "[", "]", "@", "&", "#", "%", "^", "+", "=", "$", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "A", "b", "B", "/", "c", "C", ":", "d", "D", ".", "e", "E", "f", "F", "g", "G", "h", "H", "i", "I", "j", "J", "k", "K", "l", "L", "|", "m", "M", "n", "N", "o", "O", "p", "P", "q", "Q", "\"", "r", "R", "s", "S", "\\", "*", "t", "T", "u", "U", "v", "V", "w", "W", "x", "X", "y", "Y", "z", "Z", "ни на что не похоже"};
  image::Image img = image::read_png_image(argv[1]);

  nlohmann::json mask_json = img.get_mask().to_json();
  boost::numeric::ublas::matrix<double> m = neuronet::json_vector_to_matrix<double>(mask_json["values"]);

  boost::numeric::ublas::matrix<double> answer = n.forward(m);
  unsigned int answer_index = neuronet::get_maximum_vector_index(answer);

  if (answer_index == 87)
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