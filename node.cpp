#include "node.hpp"
#include <iostream>

namespace eda {


Node::Node(): ptrNext(nullptr) {
}

Node::Node(int r, int c, Node* next) : row(r), col(c), ptrNext(next) {}


void Node::setNext(Node* next){
	ptrNext = next;
}

Node* Node::getNext(){
	return ptrNext;
}

void Node::setRow(int _row) {
    row = _row;
}

void Node::setCol(int _col) {
    col = _col;
}

int Node::getRow() {
    return row;
}

int Node::getCol() {
    return col;
}

void Node::print(){ 
    std::cout << "(" << row << "," << col << ")" << std::endl;
}

Node::~Node() {

}

} /* namespace eda */
