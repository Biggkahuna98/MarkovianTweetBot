#include <map>
#include <string>
#include <vector>
#include "Node.hpp"

#define MarkovDictionary std::map<std::string, std::vector<Node>>

class MarkovGenerator {
    public:
        MarkovGenerator();
    private:
        MarkovDictionary mMarkovChain;
        std::string mPrevWord;
        void InsertWord(std::string* word);
};