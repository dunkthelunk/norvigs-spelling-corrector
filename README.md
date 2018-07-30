# norvigs-spelling-corrector
An implementation of Norvig's Spelling Corrector in C++

Here is how it works:
1. Tokenize a large text and store all words along with their frequencies. Let's call this known-word list.
2. If input is in above list, return it
3. Else compute all words which are one edit away from the input and check if any of them are in known-words list. If multiple one-edit-away words are known, return the one with highest frequency.
4. If none of one-edit-away words are proper words, then repeat above with two-edits-away words.

### Result:
    

![alt text](img/spell-correct.png?raw=true)
