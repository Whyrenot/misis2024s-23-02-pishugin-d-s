#include <stacklst/stacklst.h>

StackLst::StackLst()
{

}

StackLst::~StackLst() {
	while (head != nullptr) {
		Node temp = *head;
		delete head;
		head = temp.next;
	}
}

Complex& StackLst::Top() {
	return head->c;
}

void StackLst::push(const Complex& a) {
	Node* n = new Node {a,head};
	head = n;
}

void StackLst::pop() {
	Node temp = *head;
	delete head;
	head = temp.next;
}

void StackLst::print() {
	while (head != nullptr) {
		std::cout << head->c.re << " " << head->c.im << "\n";
		head = head->next;
	}
}

bool StackLst::IsEmpty() {
	return head == nullptr;
}

