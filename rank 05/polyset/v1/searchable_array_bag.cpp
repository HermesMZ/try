/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 14:45:23 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 14:57:39 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

searchable_array_bag::searchable_array_bag() {}
searchable_array_bag::~searchable_array_bag() {}
searchable_array_bag::searchable_array_bag(const searchable_array_bag&sab) : array_bag(sab) {}
searchable_array_bag& searchable_array_bag::operator=(const searchable_array_bag&sab) {
	array_bag::operator=(sab);
	return *this;	
}

bool searchable_array_bag::has(int value)const {
	for (int i = 0; i < this->size; i++) {
		if (this->data[i] == value)
			return true;
	}
	return (false);
}	
