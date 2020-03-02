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
            Node node;
            node.setWord(word);
            node.increment();
            mMarkovChain[this->mPrevWord].push_back(node);
            // for (auto itr = mMarkovChain[this->mPrevWord].begin(); itr != mMarkovChain[this->mPrevWord].end(); itr++) {
            //     if (itr->getWord() == *word) {
            //         itr->increment();
            //     } else {
            //         Node node;
            //         node.setWord(word);
            //         node.increment();
            //         mMarkovChain[this->mPrevWord].push_back(node);
            //     }
            // }
        }
    }
}