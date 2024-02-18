#include <stacklst/stacklst.h>

StackLst::StackLst()
{

}

void StackLst::push(const Complex& a)
{
	Node* n = new Node {a,head};
	head = n;
}

void StackLst::print()
{
	while (head != nullptr) {
		std::cout << head->c.re << " " << head->c.im << "\n";
		head = head->next;
	}
}

