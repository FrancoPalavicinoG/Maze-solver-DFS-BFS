#include "linkedList.hpp"
#include <iostream>

namespace eda {

LinkedList::LinkedList(): head(nullptr) {

}

void LinkedList::insertFirst(int row, int col){
	Node* node = new Node(row, col);
	if (head == nullptr) {
		head = node;
	}
	else{
		node->setNext(head);
		head = node;
	}
}

void LinkedList::insertLast(int row, int col){
	Node* node = new Node(row, col);
	if (head == nullptr) {
		head = node;
	}
	else{
		Node* ptr = head;
		while(ptr->getNext() != nullptr){
			ptr = ptr->getNext();
		}
		ptr->setNext(node);
	}
}

void LinkedList::removeFirst(){
	Node* ptr = head;
	if (head != nullptr){
		head = head->getNext();
		delete ptr;
	}
}

void LinkedList::remove(int row, int col){
	Node* ptr = head;
	Node* ptr_prev = nullptr;
	while (ptr != nullptr){
		if (ptr->getRow() == row && ptr->getCol() == col){
			//erase node
			if (ptr_prev == nullptr) {
				head = ptr->getNext();
				delete ptr;
				ptr = head;
			}
			else{
				ptr_prev->setNext(ptr->getNext());
				delete ptr;
				ptr = ptr_prev->getNext();
			}
		}
		else{
			ptr_prev = ptr;
			ptr = ptr->getNext();
		}
	}
}

void LinkedList::removeAll(){

	while (head != nullptr){
		removeFirst();
	}
}

Node* LinkedList::find(int row, int col){
	Node* ptr = head;
	while ((ptr != nullptr) && (ptr->getRow() != row ) && (ptr->getCol() != col)){
		ptr = ptr->getNext();
	}
	return ptr;
}

void LinkedList::print(){
	Node* ptr = head;
	while (ptr != nullptr) {
		ptr->print();
		//std::cout << " -> " ;
		ptr = ptr->getNext();
	}
	std::cout << std::endl;
}

void LinkedList::removeAfter(int row, int col) {
    Node* ptr = head;
    Node* ptr_prev = nullptr;

    while (ptr != nullptr) {
        if (ptr->getRow() == row && ptr->getCol() == col) {
            break;
        }
        ptr_prev = ptr;
        ptr = ptr->getNext();
    }

    if (ptr == nullptr) {
        return;
    }

    while (ptr != nullptr) {
        Node* aux = ptr;
        ptr = ptr->getNext();
        delete aux;
    }

    if (ptr_prev != nullptr) {
        ptr_prev->setNext(nullptr);
    } else {
        head = nullptr;
    }
}

LinkedList::~LinkedList() {
	removeAll();
}

} /* namespace eda */
