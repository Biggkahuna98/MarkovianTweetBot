#include "markov.hpp"

MarkovGenerator::MarkovGenerator() {
}

void MarkovGenerator::InsertWords(std::string* word1, std::string* word2) {
    // If the word is in the chain, update the value map with the
    // successive word and count
    if (mMarkovChain.count(*word1) > 0) {
        auto word1Iter = mMarkovChain.at(*word1);
        // See if the successive word is already in the first words submap
        // If it is, update the count, otherwise add it
        if (word1Iter.count(*word2) > 0) {
            word1Iter.at(*word2)++; // might flop
        } else {
            word1Iter.insert(std::pair<std::string, int>(*word2, 1));
        }
    } else {
        std::map<std::string, int> innerMap;
        innerMap.insert(std::pair<std::string, int>(*word2, 1));
        mMarkovChain.emplace(*word1, innerMap);
    }
}