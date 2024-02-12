#include <complex/complex.hpp>

class StackLst {
private:
	struct Node {
		Complex c;
		Node* next;
	};
	Node* head = nullptr;
public:
	StackLst();
	
	void push(const Complex &a);
	void print();
	void pop();
	void IsEmpty();
};