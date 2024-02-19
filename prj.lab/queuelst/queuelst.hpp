#pragma once
#include <complex/complex.hpp>

class QueueLst {
private:
	struct Node {
		Complex c;
		Node* next;
	};
	Node* head = nullptr;
	Node* tail = nullptr;
public:
	QueueLst();
	~QueueLst();

	Complex& Top();
	void Push(const Complex& a);
	void Print();
	void Pop();
	bool IsEmpty();
};