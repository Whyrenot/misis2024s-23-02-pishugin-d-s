#include <iostream>

int main() {
	int k, n, w;
	std::cin >> k >> n >> w;
	
	int s = 0;
	for (int i = 1; i <= w; i++)
		s += i;
	
	int r = n - k * s;
	if (r >= 0)
		std::cout << "0";
	else
		std::cout << -r;

	return 0;
}
