#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "node.hpp"

using namespace std;

#define MarkovDictionary std::map<std::string, std::vector<Node>>

class MarkovGenerator {
    public:
        MarkovGenerator();
        void Print();
        void ReadInFile(const std::string path);
        string GenerateTweet();
    private:
        MarkovDictionary mMarkovChain;
        //map<string, vector<Node*>> mMarkovChain;
        std::string mPrevWord;

        void InsertWord(const std::string* word);
        string GetKeyFromIndex(int idx);
        string GetWordFromVector(vector<Node>* vec);
};