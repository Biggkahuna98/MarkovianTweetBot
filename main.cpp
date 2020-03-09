#include "markov.hpp"

int main(int argc, char **argv) {
    string path = "const.txt";
    if (argc > 1) {
        path = argv[1];
    }
    MarkovGenerator mg;
    mg.ReadInFile(path);
    mg.Print();
    cout << "-------------" << endl;
    cout << mg.GenerateChain() << endl;
    return 0;
}