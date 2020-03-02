#include <string>

class Node {
    public:
        void setWord(std::string* word);
        void increment();
        std::string getWord();
        int getCount();
    private:
        std::string word;
        int count;
}