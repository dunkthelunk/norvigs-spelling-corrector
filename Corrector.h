#ifndef CORRECTOR_H
#define CORRECTOR_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Strings.h"

class Corrector {
private:
  std::unordered_map<std::string, unsigned int> WordFreqMap;
  Strings known(Strings);
  Strings oneEditAway(std::string);
  Strings twoEditsAway(std::string);
  Strings candidates(std::string);

public:
  void loadWords(std::string FilePath);
  std::string correct(std::string);
};
#endif
