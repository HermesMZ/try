/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:49:17 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 18:15:57 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"
#include "searchable_bag.hpp"

set::set() {}
set::~set() {}
set::set(const set&other) : bag(other.bag) {}
set& set::operator=(const set&other) {
	if (this != &other)
		bag = other.bag;
	return *this;
}

set::set(searchable_bag&bag) : bag(&bag) {}

searchable_bag& set::get_bag() const {
	return *bag;
}

void set::insert(int value) {
	if (bag && !bag->has(value)) bag->insert(value);
}

void set::insert(int* values, int size) {
	for (int i = 0; i < size; i++) {
		if (bag) insert(values[i]);
	}
}

bool set::has(int value) {
	return bag && bag->has(value);
}

void set::print() {
	if (bag) bag->print();
}

void set::clear() {
	if (bag) bag->clear();
}

