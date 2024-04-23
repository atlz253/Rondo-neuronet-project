#include <iostream>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "neuronet.hpp"

int main()
{
  srand(time(NULL));
  neuronet::Neuronet n;

  boost::numeric::ublas::matrix<double> question(1, 64);          // FIXME: Заглушка
  boost::numeric::ublas::matrix<int> answer(1, NEURONET_OUTPUTS); // FIXME: Заглушка

  std::cout << n.forward(question) << std::endl;

  return 0;
}