/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:22:50 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/07 21:03:32 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class vect2 {
	private:
		int x;
		int y;
	public:
		vect2();
		~vect2();
		vect2(const vect2&);
		vect2& operator=(const vect2&);	

		vect2(int, int);
		
		int operator[](int)const;
		int& operator[](int);
		
		vect2& operator++();
		vect2 operator++(int);
		vect2& operator--();
		vect2 operator--(int);

		vect2& operator+=(const vect2&);
		vect2 operator+(const vect2&)const;
		vect2& operator-=(const vect2&);
		vect2 operator-(const vect2&)const;
		vect2 operator*(int)const;
		vect2& operator*=(int);

		bool operator==(const vect2&)const;
		bool operator!=(const vect2&)const;
		
	};
	vect2 operator*(int, const vect2&);
	vect2 operator-(const vect2&);

std::ostream& operator<<(std::ostream&, const vect2&);