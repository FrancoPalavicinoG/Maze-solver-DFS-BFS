#ifndef NODE_HPP_
#define NODE_HPP_

namespace eda {

class Node {
private:
	int row;
	int col;
	Node* ptrNext;
public:
	Node();
	Node(int _row, int _col, Node* next = nullptr);
	void setNext(Node* _next);
	void setRow(int _row);
	void setCol(int _col);
	int getRow();
	int getCol();
	void print();
	Node* getNext();
	virtual ~Node();
};

} /* namespace eda */

#endif /* NODE_HPP_ */
