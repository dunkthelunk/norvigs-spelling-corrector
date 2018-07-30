#include "Corrector.h"
#include <algorithm>

void Corrector::loadWords(std::string Filepath) {
  // TODO READ Words FROM FILE in lowercase
  Strings WordsFromFile;
  WordsFromFile.push_back("eat");
  WordsFromFile.push_back("book");
  WordsFromFile.push_back("read");
  WordsFromFile.push_back("bus");
  WordsFromFile.push_back("bus");
  WordsFromFile.push_back("bus");
  WordsFromFile.push_back("busy");
  WordsFromFile.push_back("city");
  WordsFromFile.push_back("buffalo");
  for (auto Word : WordsFromFile) {
    auto WIt = WordFreqMap.find(Word);
    auto PrevFreq = 0;
    if (WIt != WordFreqMap.end()) {
      PrevFreq = WIt->second;
    }
    WordFreqMap.insert_or_assign(Word, ++PrevFreq);
  }
}

std::string Corrector::correct(std::string Input) {
  std::transform(Input.begin(), Input.end(), Input.begin(), ::tolower);
  auto Candidates = this->candidates(Input);
  if (Candidates.size() == 1 & Candidates[0] == Input) {
    return Input;
  }
  auto CompareFrequency = [&](const std::string &F,
                              const std::string &S) -> bool {
    return WordFreqMap.at(F) > WordFreqMap.at(S);
  };
  auto MaxIt =
      std::max_element(Candidates.begin(), Candidates.end(), CompareFrequency);
  return *MaxIt;
}

Strings Corrector::known(Strings WordSet) {
  Strings KnownWords;
  for (auto W : WordSet) {
    if (std::any_of(this->WordFreqMap.begin(), this->WordFreqMap.end(),
                    [&](auto S) -> bool { return S.first == W; })) {
      KnownWords.push_back(W);
    }
  }
  return KnownWords;
}
Strings Corrector::oneEditAway(std::string Word) {
  Strings WordsOneEditAway;
  std::string Alphabet = "abcdefghijklmnopqrstuvwxyz";
  for (auto j = 0; j <= Word.size(); j++) {
    if (j != Word.size()) {
      WordsOneEditAway.push_back(Word.substr(0, j) +
                                 Word.substr(j + 1, Word.size()));
    }
    if (j < Word.size() - 1) {
      WordsOneEditAway.push_back(Word.substr(0, j) + Word[j + 1] + Word[j] +
                                 Word.substr(j + 2, Word.size()));
    }
    for (auto i = 0; i < 26; i++) {
      WordsOneEditAway.push_back(Word.substr(0, j) + Alphabet[i] +
                                 Word.substr(j, Word.size()));
      if (j != Word.size()) {
        WordsOneEditAway.push_back(Word.substr(0, j) + Alphabet[i] +
                                   Word.substr(j + 1, Word.size()));
      }
    }
  }
  return WordsOneEditAway;
}
Strings Corrector::twoEditsAway(std::string Word) {
  Strings Result;
  for (auto WordOneEditAway : oneEditAway(Word)) {
    auto TwoEditsAway = oneEditAway(WordOneEditAway);
    Result.insert(Result.end(), TwoEditsAway.begin(), TwoEditsAway.end());
  }
  return Result;
}

Strings Corrector::candidates(std::string Word) {
  auto Result = this->known({Word});
  if (Result.size() != 0) {
    return Result;
  }
  Result = this->known(this->oneEditAway(Word));
  if (Result.size() != 0) {
    return Result;
  }
  Result = this->known(this->twoEditsAway(Word));
  if (Result.size() != 0) {
    return Result;
  }
  return {Word};
}
