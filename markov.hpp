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
        void InsertWords(std::string* word1, std::string* word2);
};