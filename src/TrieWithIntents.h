#ifndef EMBEDDEDINTENTRECOGNIZER_TRIEWITHINTENTS_H
#define EMBEDDEDINTENTRECOGNIZER_TRIEWITHINTENTS_H

#include <string>

// Define the trie size = Number of letters in English alphabet
#define ALPHABET_SIZE 26

// A class to store a Trie node with listIntentID at end
class TrieWithIntents {
public:
    TrieWithIntents();

    void insert(std::string, int);

    int search(std::string);

private:
    bool isLeaf, end;

    int intentID;

    TrieWithIntents *letter[ALPHABET_SIZE];
};

#endif //EMBEDDEDINTENTRECOGNIZER_TRIEWITHINTENTS_H
