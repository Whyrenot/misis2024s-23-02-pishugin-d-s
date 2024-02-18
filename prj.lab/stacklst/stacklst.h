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
	~StackLst();
	
	Complex& Top();
	void push(const Complex &a);
	void print();
	void pop();
	bool IsEmpty();
};