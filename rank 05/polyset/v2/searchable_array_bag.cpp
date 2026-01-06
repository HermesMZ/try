/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:51:21 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 17:13:34 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() {}

searchable_array_bag::~searchable_array_bag() {}

searchable_array_bag::searchable_array_bag(const searchable_array_bag&bag) : array_bag(bag) {}

searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag&bag) {
	array_bag::operator=(bag);
	return *this;
}

bool searchable_array_bag::has(int value) const {
	for (int i = 0; i < size; i++) {
		if (data[i] == value)
			return true;
	}
	return false;
}