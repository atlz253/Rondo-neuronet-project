#include <iostream>

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "neuronet.hpp"
#include "sparse_cross_entropy.hpp"

int main()
{
  // srand(time(NULL));
  neuronet::Neuronet n;

  boost::numeric::ublas::matrix<double> question(1, 64);          // FIXME: Заглушка
  boost::numeric::ublas::matrix<double> answer(1, NEURONET_OUTPUTS); // FIXME: Заглушка

  boost::numeric::ublas::matrix<double> z = n.forward(question);
  std::cout << z << std::endl;
  double E = neuronet::sparse_cross_entropy(z, answer); 
  std::cout << E << std::endl;

  n.backward(answer);

  return 0;
}