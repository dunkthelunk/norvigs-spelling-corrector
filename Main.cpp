#include "Corrector.h"
#include <chrono>
#include <iostream>
#include <string>

int main() {
  std::string File = "big.txt";

  Corrector SpellingCorrector;
  SpellingCorrector.loadWords(File);

  std::string InputWord;
  std::cout << "Enter word to correct (Ctrl+D to exit) : ";
  while (std::cin >> InputWord) {
    auto start = std::chrono::system_clock::now();
    std::cout << SpellingCorrector.correct(InputWord) << '\n';
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    std::cout << "Enter word to correct (Ctrl+D to exit) : ";
  }
  std::cout << '\n';
  return 0;
}
