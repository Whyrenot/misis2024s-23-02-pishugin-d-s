#include <stacklst/stacklst.h>

int main() {
	StackLst a;

	a.push(Complex(2,3));
	a.push(Complex(4,4));
	a.push(Complex(33, 4));
	a.push(Complex(4, 69));

	
	std::cout << a.Top().re << " " << a.Top().im << std::endl;

	return 0;
}