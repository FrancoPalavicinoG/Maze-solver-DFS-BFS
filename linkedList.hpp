#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include "node.hpp"

namespace eda {

class LinkedList {
public:
	Node* head;
	LinkedList();
	void insertLast(int row, int col);
	void insertFirst(int row, int col);
	void removeFirst();
	void remove(int row, int col);
	void removeAll();
	Node* find(int row, int col);
	void print();
	void removeAfter(int row, int col);
	virtual ~LinkedList();
};

} /* namespace eda */

#endif
