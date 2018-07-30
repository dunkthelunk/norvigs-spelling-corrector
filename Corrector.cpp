#include "Corrector.h"
#include <algorithm>
#include <fstream>
#include <iostream>

void Corrector::loadWords(std::string FilePath) {
  std::fstream File;
  File.open(FilePath);
  std::string WordIn;
  while (File >> WordIn) {
    std::transform(WordIn.begin(), WordIn.end(), WordIn.begin(), ::tolower);
    auto WIt = WordFreqMap.find(WordIn);
    auto PrevFreq = 0;
    if (WIt != WordFreqMap.end()) {
      PrevFreq = WIt->second;
    }
    WordFreqMap.insert_or_assign(WordIn, ++PrevFreq);
  }
  File.close();
}

std::string Corrector::correct(std::string Input) {
  std::transform(Input.begin(), Input.end(), Input.begin(), ::tolower);
  auto Candidates = this->candidates(Input);
  if (Candidates.size() == 1 & Candidates[0] == Input) {
    return Input;
  }
  auto CompareFrequency = [&](auto F, auto S) -> bool {
    return WordFreqMap.at(F) > WordFreqMap.at(S);
  };
  auto MaxIt =
      std::max_element(Candidates.begin(), Candidates.end(), CompareFrequency);
  return *MaxIt;
}

Strings Corrector::known(Strings WordSet) {
  Strings KnownWords;
  for (auto W : WordSet) {
    if (WordFreqMap.find(W) != WordFreqMap.end()) {
      KnownWords.push_back(W);
    }
  }
  return KnownWords;
}
Strings Corrector::oneEditAway(std::string Word) {
  Strings WordsOneEditAway;
  std::string Alphabet = "abcdefghijklmnopqrstuvwxyz";
  for (auto j = 0; j <= Word.size(); j++) {
    if (j != Word.size()) { // delete letter
      WordsOneEditAway.push_back(Word.substr(0, j) +
                                 Word.substr(j + 1, Word.size()));
    }
    if (j < Word.size() - 1) { // transpose
      WordsOneEditAway.push_back(Word.substr(0, j) + Word[j + 1] + Word[j] +
                                 Word.substr(j + 2, Word.size()));
    }
    for (auto i = 0; i < 26; i++) {
      WordsOneEditAway.push_back(Word.substr(0, j) + Alphabet[i] +
                                 Word.substr(j, Word.size())); // insert
      if (j != Word.size()) {                                  // replace
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
