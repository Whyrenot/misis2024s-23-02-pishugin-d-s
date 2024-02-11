#include "StackArr.h"
//test
StackArr::StackArr()
{

}

StackArr::StackArr(const StackArr& a)
{
	this->data = a.data;
	this->size = a.size;
}

StackArr::~StackArr()
{
	delete[] data;
}

StackArr& StackArr::operator=(const StackArr& a)
{
	this->data = a.data;
	this->size = a.size;
	return *this;
}

const TempComplex& StackArr::Top()
{
	return data[i_head];
}

void StackArr::push(const TempComplex& c)
{
	if (!(i_head < size)) {
		data = new(TempComplex[size*2]);
	}
	*(data + i_head) = c;
}

void StackArr::pop()
{

}

bool StackArr::IsEmpty()
{
	return false;
}
