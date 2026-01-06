/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:00:03 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 15:16:11 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_tree_bag.hpp"
#include <cstdlib>

searchable_tree_bag::searchable_tree_bag() {}
searchable_tree_bag::~searchable_tree_bag() {}
searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag&stb) : tree_bag(stb) {}
searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag&stb) {
	tree_bag::operator=(stb);
	return *this;	
}

bool searchable_tree_bag::has(int value) const {
    node *current = tree;
    
    while (current != NULL) {
        if (value == current->value)
            return true;
        else if (value < current->value)
            current = current->l;
        else
            current = current->r;
    }
    return false;
}