#pragma once
#include <iostream>

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
	TempComplex& operator = (const TempComplex& a) {
		this->im = a.im;
		this->re = a.re;
		return *this;
	}
	void print() {
		std::cout << im << "\n" << re << "\n\n";
	}
};

class StackArr
{
private:
	TempComplex* data = nullptr;
	int size = 1;
	int i_head = 1;
public:
	StackArr();
	StackArr(const StackArr& a);
	~StackArr();
	StackArr& operator = (const StackArr& a);

	const TempComplex& Top();
	void push(const TempComplex& c);
	void pop(); // noexcept
	bool IsEmpty(); // noexcept

};

