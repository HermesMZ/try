/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:08:28 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 17:20:52 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag() {}

searchable_tree_bag::~searchable_tree_bag() {}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag&bag) : tree_bag(bag) {}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag&bag) {
	tree_bag::operator=(bag);
	return *this;
}

bool searchable_tree_bag::has(int value) const {
	node *current = tree;

	while (current != nullptr) {
		if (value == current->value)
			return (true);
		else if (value < current->value)
			current = current->l;
		else
			current = current->r;
	}
	return (false);
}