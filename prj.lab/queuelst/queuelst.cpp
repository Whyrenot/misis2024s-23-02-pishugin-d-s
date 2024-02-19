#pragma once
#include <queuelst/queuelst.hpp>

QueueLst::QueueLst()
{

}

QueueLst::~QueueLst() {
	while (head != nullptr) {
		Node temp = *head;
		delete head;
		head = temp.next;
	}
}

Complex& QueueLst::Top() {
	return head->c;
}

void QueueLst::Push(const Complex& a) {
	Node* n = new Node{ a,head };
	head = n;
	if (tail == nullptr) {
		tail = head;
	}
	else if (tail->next == head->next) {
		tail->next = tail;
	}
}

void QueueLst::Pop() {
	Node temp = *tail;
	delete tail;
	tail = temp.next;
}

void QueueLst::Print() {
	while (head != nullptr) {
		std::cout << head->c.re << " " << head->c.im << "\n";
		head = head->next;
	}
}

bool QueueLst::IsEmpty() {
	return head == nullptr;
}

