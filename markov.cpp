#include "markov.hpp"

MarkovGenerator::MarkovGenerator() {
    mPrevWord = "";
    // Seed random number generator
    srand(time(NULL));
}

void MarkovGenerator::InsertWord(const std::string* word) {
    // Check to see if there is a previous word
    if (mPrevWord == "") {
        mMarkovMap.insert(make_pair(*word, vector<Node>()));
    } else {
        // If there is a previous word, add the new word to the previous word's vector (or update the count if it already is in it)
        bool found = false;
        // Go through the vector associated with the previous input and see if the inputted word exists as a node
        for (vector<Node>::iterator itr = mMarkovMap[mPrevWord].begin(); itr != mMarkovMap[mPrevWord].end(); itr++) {
            if (itr->getWord() == *word) {
                itr->increment();
                found = true;
            }
        }
        // If the node doesn't exist, found is still false
        if (!found) {
            Node n;
            n.setWord(word);
            mMarkovMap[mPrevWord].push_back(n);
        }
    }
    mPrevWord = *word;
}

void MarkovGenerator::Print() {
    // Go through the map and print out the inner vector
    for (MarkovMap::iterator mapItr = mMarkovMap.begin(); mapItr != mMarkovMap.end(); mapItr++) {
        cout << mapItr->first << ": ";
        for (vector<Node>::iterator vecItr = mapItr->second.begin(); vecItr != mapItr->second.end(); vecItr++) {
            cout << vecItr->getWord() << "(" << vecItr->getCount() << "), ";
        }
        cout << endl;
    }
}

void MarkovGenerator::ReadInFile(const std::string path) {
    fstream file;
    // Ideally scrub file path for security before this call
    file.open(path.c_str());

    string word;
    while (file >> word) {
        InsertWord(&word);
    }
}

// This function assumes the index is a valid one
string MarkovGenerator::GetKeyFromIndex(int idx) {
    int i = 0;
    for (MarkovMap::iterator mapItr = mMarkovMap.begin(); mapItr != mMarkovMap.end(); mapItr++) {
        if (i == idx)
            return mapItr->first;
        i++;
    }
}

// This function chooses a word from the vector of following words (the words that directly follow the first word)
string MarkovGenerator::GetWordFromVector(vector<Node>* vec) {
    int vecSize = vec->size();
    int sumOfWeights = 0;
    // Sum the weights
    for (auto itr = vec->begin(); itr != vec->end(); itr++)
        sumOfWeights += itr->getCount();
    // Random number from the weights
    int randomNum = rand() % sumOfWeights;
    int idx;
    // Figure out which node is the chosen one by the randomNum
    // Thank you stack overflower https://stackoverflow.com/questions/1761626/weighted-random-numbers
    for (auto itr = vec->begin(); itr != vec->end(); itr++) {
        if (randomNum < itr->getCount())
            return itr->getWord();
        else
            randomNum -= itr->getCount();
    }
    assert("If you're here, you fucked up hard bro");
}

void MarkovGenerator::PrettifyChain(string* chain) {
    // Takes in the generated chain and attempts to make it look better
    // This included correct(ish) capitalization and punctuation, kinda
    // It's not going to be remotely perfect but it should look at least a little better; could be iterated upon but idk if i gaf
    // itr is set to each character in the chain
    for (auto itr = chain->begin(); itr != chain->end(); itr++) {
        // Enjoy the gross if tree to check various things
        // Make sure the first letter of the first word is capitalized
        if (*itr == chain->at(0) && islower(*itr)) {
            *itr = toupper(*itr);
        }
        // Make sure the first letter of the word after a "." is capitalized
        // The second part is to account for a space after punctuation
        if (*prev(itr) == '.' || *prev(itr, 2) == '.') {
            if (islower(*itr)) {
                *itr = toupper(*itr);
            }
        }
    }
    // Complete flop so idgaf right now
    // cout << "CHAIN->BACK: " << chain->back() << endl;
    // cout << "CHAIN->END: " << *chain->end() << endl;
    // cout << "PREV(CHAIN->END()): " << *prev(chain->end()) << endl;
    // // Make sure the last character is punctuation
    // if (chain->back() != '.' || chain->back() != '?') {
    //     *chain->end() = '.';
    // }
}

string MarkovGenerator::GenerateChain() {
    int charCount = 280;
    string chain, word;
    chain = "";

    int mapSize = mMarkovMap.size();
    int startingIndex = rand() % mapSize;
    word = GetKeyFromIndex(startingIndex);
    chain += word + " ";

    while (chain.size() < charCount) {
        word = GetWordFromVector(&mMarkovMap[word]);
        chain += word + " ";
    }

    // Make sure the chain looks ok
    PrettifyChain(&chain);
    return chain;
}