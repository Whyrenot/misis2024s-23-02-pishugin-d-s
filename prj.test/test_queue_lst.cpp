#include <queuelst/queuelst.hpp>

int main() {
	QueueLst q;
	q.Push(Complex(4, 3));
	q.Push(Complex(8, 3));
	q.Push(Complex(4, 9));
	q.Push(Complex(8, 8));

	return 0;
}