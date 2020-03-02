#include "markov.hpp"

MarkovGenerator::MarkovGenerator() {
    mPrevWord = "";
}

void MarkovGenerator::InsertWord(std::string* word) {
    // If the word is not already in the chain, add it
    if (mMarkovChain.find(*word) == mMarkovChain.end()) {
        mMarkovChain.emplace(*word);
        // Check for the first word being added to the chain
        //mMarkovChain.at(*word) = new std::vector<Node>();
        if (this->mPrevWord != "") { // Not the first word
            for (auto itr = mMarkovChain[*word].begin(); itr != mMarkovChain[*word].end(); itr++) {
                if (itr->getWord())
            }
            Node node;
            node.setWord(&mPrevWord);
            node.increment();
            mMarkovChain[*word].push_back(node);
        }
    }
}