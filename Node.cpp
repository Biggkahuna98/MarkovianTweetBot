#include "Node.hpp"

void Node::setWord(std::string* word) {
    this->word = *word;
}

void Node::increment() {
    this->count++;
}

std::string Node::getWord() {
    return this->word;
}

int Node::getCount() {
    return this->count;
}