#ifndef PROGRESS_HPP
#define PROGRESS_HPP

#include <iostream>

#define BAR_WIDTH 70

void show_progress_bar(float progress)
{
  std::cout << "\r[";
  int pos = BAR_WIDTH * progress;
  for (int i = 0; i < BAR_WIDTH; ++i)
  {
    if (i < pos)
      std::cout << "=";
    else if (i == pos)
      std::cout << ">";
    else
      std::cout << " ";
  }
  std::cout << "] " << int(progress * 100.0) << " %";
  std::cout.flush();
}

#endif