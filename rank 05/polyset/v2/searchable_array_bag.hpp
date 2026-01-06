/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:49:32 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 17:13:59 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchable_array_bag : public array_bag, public searchable_bag {
	public:
		searchable_array_bag();
		~searchable_array_bag();
		searchable_array_bag(const searchable_array_bag&);
		searchable_array_bag& operator=(const searchable_array_bag&);
		virtual bool has(int) const;
};