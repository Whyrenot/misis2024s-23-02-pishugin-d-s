#include <stacklst/stacklst.h>

int main() {
	StackLst a;
	Complex b(3, 3);
	a.push(b);
	a.print();

	return 0;
}