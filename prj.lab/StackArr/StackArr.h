#pragma once
#include <complex/complex.hpp>
#include <iostream>
#include <algorithm>
#include <sstream>


class StackArr
{
private:
	Complex* data = nullptr;
	int size = 1;
	int i_head = 0;
public:
	StackArr();
	StackArr(const StackArr& a);
	~StackArr();
	//StackArr& operator = (const StackArr& a);

	Complex& Top();
	void push(const Complex& c);
	void pop(); // noexcept
	bool IsEmpty(); // noexcept

};

