#include "StackArr.h"

StackArr::StackArr()
{
	size = 1;
	i_head = 0;
	data = new TempComplex[size];
}

StackArr::StackArr(const StackArr& a)
{
	this->size = a.size;
	this->i_head = a.i_head;
	this->data = new TempComplex[size];
	std::copy(a.data,a.data + a.size,data);
}

StackArr::StackArr(const int size)
{
	if (size > 0) {
		this->size = size;
		i_head = size;
		data = new TempComplex[size];
		std::fill(data, data + size, 0);
	}
	else if (size < 0) {
		throw::std::invalid_argument("Negative stack size");
	}
}

StackArr::~StackArr()
{
	delete[] data;
}

//StackArr& StackArr::operator=(const StackArr& a)
//{
//	//this->data = a.data;
//	//this->size = a.size;
//	return *this;
//}

const TempComplex& StackArr::Top()
{
	return data[i_head];
}

void StackArr::push(const TempComplex& c)
{
	if (!(i_head < size)) {
		this->size *= 2;
		data = new TempComplex[size];
	}
	data[i_head] = c;
}

void StackArr::pop()
{

}

bool StackArr::IsEmpty()
{
	return false;
}
