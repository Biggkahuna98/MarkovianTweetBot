#include <string>
#include <iostream>

using namespace std;

class Node {
    public:
        Node();
        void setWord(const std::string* word);
        void increment();
        std::string getWord();
        int getCount();
    private:
        std::string word;
        int count;
};