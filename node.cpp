#include "node.hpp"

Node::Node() {
    this->count = 1;
    this->word = "";
}

void Node::setWord(const std::string* word) {
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