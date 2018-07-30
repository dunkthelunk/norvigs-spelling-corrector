#include "Corrector.h"
#include <iostream>
#include <string>

int main() {
  std::string File = "big.txt";

  Corrector SpellingCorrector;
  SpellingCorrector.loadWords(File);

  std::string InputWord;
  std::cout << "Enter word to correct (Ctrl+D to exit) : ";
  while (std::cin >> InputWord) {
    std::cout << SpellingCorrector.correct(InputWord) << '\n';
    std::cout << "Enter word to correct (Ctrl+D to exit) : ";
  }
  std::cout << '\n';
  return 0;
}
