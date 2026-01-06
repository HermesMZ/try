/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:46:29 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 16:19:23 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set {
	private:
		searchable_bag* bag;
	public:
		set();
		~set();
		set(const set&);
		set& operator=(const set&);

		set(searchable_bag&);
		searchable_bag& get_bag();

		void insert(int);
		void insert(int*, int);
		bool has(int)const;
		void print()const;
		void clear();
};