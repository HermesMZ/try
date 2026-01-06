/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:44:41 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 18:15:54 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "searchable_bag.hpp"

class set {
	private:
		searchable_bag *bag;
	public:
		set();
		~set();
		set(const set&);
		set& operator=(const set&);
		
		set(searchable_bag&);
		searchable_bag& get_bag() const;
		void insert(int);
		void insert(int* ,int);
		bool has(int);
		void print();
		void clear();
};