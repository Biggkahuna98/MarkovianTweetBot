#include "markov.hpp"

MarkovGenerator::MarkovGenerator() {
    mPrevWord = "";
    // Seed random number generator
    srand(time(NULL));
}

void MarkovGenerator::InsertWord(const std::string* word) {
    // Check to see if there is a previous word
    if (mPrevWord == "") {
        mMarkovChain.insert(make_pair(*word, vector<Node>()));
    } else {
        // If there is a previous word, add the new word to the previous word's vector (or update the count if it already is in it)
        bool found = false;
        // Go through the vector associated with the previous input and see if the inputted word exists as a node
        for (vector<Node>::iterator itr = mMarkovChain[mPrevWord].begin(); itr != mMarkovChain[mPrevWord].end(); itr++) {
            if (itr->getWord() == *word) {
                itr->increment();
                found = true;
            }
        }
        // If the node doesn't exist, found is still false
        if (!found) {
            Node n;
            n.setWord(word);
            mMarkovChain[mPrevWord].push_back(n);
        }
    }
    mPrevWord = *word;
}

void MarkovGenerator::Print() {
    // Go through the map and print out the inner vector
    for (MarkovDictionary::iterator mapItr = mMarkovChain.begin(); mapItr != mMarkovChain.end(); mapItr++) {
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
    for (MarkovDictionary::iterator mapItr = mMarkovChain.begin(); mapItr != mMarkovChain.end(); mapItr++) {
        if (i == idx)
            return mapItr->first;
        i++;
    }
}

string MarkovGenerator::GetWordFromVector(vector<Node>* vec) {
    int vecSize = vec->size();
    int idx = rand() % vecSize;
    return vec->at(idx).getWord();
}

string MarkovGenerator::GenerateTweet() {
    int wordCount = 50;
    string tweet, word;
    tweet = "";

    int mapSize = mMarkovChain.size();
    int startingIndex = rand() % mapSize;
    word = GetKeyFromIndex(startingIndex);
    tweet += word + " ";

    for (int i = 0; i < wordCount; i++) {
        word = GetWordFromVector(&mMarkovChain[word]);
        tweet += word + " ";
    }

    return tweet;
}