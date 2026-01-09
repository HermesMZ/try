#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() {};

searchable_array_bag::~searchable_array_bag() {};

searchable_array_bag::searchable_array_bag(const searchable_array_bag& sab) : array_bag(sab) {}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag&sab) {
	array_bag::operator=(sab);
	return *this;
}

bool searchable_array_bag::has(int value) const {
	for (int i = 0; i < size; i++) {
		if (value == data[i]) return true;
	}
	return false;
}