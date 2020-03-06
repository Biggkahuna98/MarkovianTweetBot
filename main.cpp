#include "markov.hpp"

int main() {
    MarkovGenerator mg;
    mg.ReadInFile("const.txt");
    mg.Print();
    cout << "-------------" << endl;
    cout << mg.GenerateTweet() << endl;
    return 0;
}