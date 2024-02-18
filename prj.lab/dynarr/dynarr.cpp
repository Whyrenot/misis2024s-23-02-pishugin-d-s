#include <dynarr/dynarr.hpp>


[[nodiscard]] DynArr::DynArr(const DynArr& a) {
	this->size_ = a.size_;
	delete[] data_;
	data_ = new float[size_];
	std::copy(a.data_, a.data_ + a.size_, this->data_);
}

DynArr::~DynArr() {
	delete[] data_;
}

[[nodiscard]] DynArr& DynArr::operator=(const DynArr& a) {
	this->size_ = a.size_;
	delete[] data_;
	data_ = new float[size_];
	std::copy(a.data_, a.data_ + a.size_, this->data_);

	return *this;
}