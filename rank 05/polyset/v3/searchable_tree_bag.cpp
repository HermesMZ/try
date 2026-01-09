#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {};

searchable_tree_bag::~searchable_tree_bag() {};

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag&stb) : tree_bag(stb) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag&stb) {
	tree_bag::operator=(stb);
	return *this;
}

bool searchable_tree_bag::has(int value) const {
	node *current = tree;
	while (current) {
		if (current->value == value)
			return true;
		else if (current->value > value)
			current = current->l;
		else if (current->value < value)
			current = current->r;
	}
	return false;
}