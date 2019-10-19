#pragma once
#include <vector>
#include <string>

class InputParser
{
  public:
    InputParser(int &argc, char **argv);
    const std::string &getCmdOption(const std::string &option) const;
    bool cmdOptionExists(const std::string &option) const;
    std::string getLast() const;

  private:
    std::vector<std::string> tokens;
};