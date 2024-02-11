#pragma once
#include <iostream>
#include <algorithm>
#include <sstream>

class TempComplex
{
private:
	double im, re;
public:
	TempComplex() {

	}
	TempComplex(double im, double re) {
		this->im = im;
		this->re = re;
	}
	/*TempComplex& operator= (const TempComplex& a) {
		this->im = a.im;
		this->re = a.re;
		return *this;
	}*/
	void print() {
		std::cout << im << " " << re << "\n";
	}
	bool operator==(const TempComplex& b) {
		return (this->im == b.im && this->re == b.re);
	}
};

class StackArr
{
private:
	TempComplex* data = nullptr;
	int size = 1;
	int i_head = 0;
public:
	StackArr();
	StackArr(const StackArr& a);
	~StackArr();
	//StackArr& operator = (const StackArr& a);

	TempComplex& Top();
	void push(const TempComplex& c);
	void pop(); // noexcept
	bool IsEmpty(); // noexcept

};

