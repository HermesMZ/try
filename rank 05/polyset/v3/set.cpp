#include "set.hpp"

set::set() {}

set::~set() {}

set::set(const set&other) : bag(other.bag) {}

set& set::operator=(const set&other) {
	if (this != &other)
		bag = other.bag;
	return *this;
}

set::set(searchable_bag&other) : bag(&other) {}

void set::insert(int value) {
	if (bag && !bag->has(value)) bag->insert(value);
}

void set::insert(int* values, int size) {
	for (int i = 0; i < size; i++) {
		if (bag && !bag->has(values[i])) bag->insert(values[i]);
	}
}

bool set::has(int value) const {
	return bag && bag->has(value);
}

void set::print() const {
	if (bag) bag->print();
}

void set::clear() {
	if (bag) bag->clear();
}

searchable_bag& set::get_bag()  {
	return *bag;
}