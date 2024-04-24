#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <string>

#include <boost/container/map.hpp>
#include <boost/container/list.hpp>

class Arguments
{
private:
  int argc;
  char **argv;
  boost::container::map<std::string, boost::container::list<std::string>> args_map;

  virtual void parse_argument(char *arg, int position)
  {
    args_map[arg] = boost::container::list<std::string>();

    for (int i = position + 1; i < argc && !is_argument(argv[i]); i++)
    {
      args_map[arg].push_back(argv[i]);
    }
  }

  bool is_argument(char *input)
  {
    return input[0] == '-';
  }

public:
  Arguments(int argc, char *argv[])
  {
    this->argc = argc;
    this->argv = argv;

    for (int i = 1; i < argc; i++)
    {
      if (is_argument(argv[i]))
      {
        parse_argument(argv[i], i);
      }
    }
  }

  int count()
  {
    return args_map.size();
  }

  bool contains(std::string key)
  {
    return args_map.contains(key);
  }

  boost::container::map<std::string, boost::container::list<std::string>>::iterator begin()
  {
    return args_map.begin();
  }

  boost::container::map<std::string, boost::container::list<std::string>>::iterator end()
  {
    return args_map.end();
  }

  const boost::container::list<std::string> &operator[](std::string key)
  {
    return args_map[key];
  }
};

#endif