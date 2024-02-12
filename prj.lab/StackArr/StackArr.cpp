#include "StackArr.h"

StackArr::StackArr()
{
	data = new Complex[size];
}

StackArr::StackArr(const StackArr& a)
{
	this->size = a.size;
	this->i_head = a.i_head;
	this->data = new Complex[size];
	std::copy(a.data, a.data + a.size, this->data);
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

Complex& StackArr::Top()
{
	return data[i_head-1];
}

void StackArr::push(const Complex& c)
{
	if (i_head >= size) {
		this->size *= 2;
		Complex* old_data = new Complex[size];
		std::copy(data, data + size/2, old_data);
		this->data = old_data;
		//should we delete old_data
	}
	data[i_head] = c;
	i_head++;
}

void StackArr::pop()
{
	this->size--;
	this->i_head--;
	std::copy(data, data + size, data);
}

bool StackArr::IsEmpty()
{
	return this->i_head <= 0;
}