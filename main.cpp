#include "markov.hpp"

int main() {
    MarkovGenerator mg;
    mg.ReadInFile("const.txt");
    mg.Print();
    cout << "-------------" << endl;
    cout << mg.GenerateChain() << endl;
    return 0;
}