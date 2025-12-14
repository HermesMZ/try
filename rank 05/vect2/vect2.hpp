/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:08:58 by zoum              #+#    #+#             */
/*   Updated: 2025/12/14 20:16:58 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2 {
	private:
		int x;
		int y;
	public:
		vect2();
		vect2(const vect2& other);
		vect2(int x, int y);
		vect2& operator=(const vect2& other);
		~vect2();

		vect2& operator++();
		vect2 operator++(int);
		vect2& operator--();
		vect2 operator--(int);
		vect2 operator+(const vect2& other)const;
		vect2& operator+=(const vect2& other);
		vect2 operator-(const vect2& other)const;
		vect2& operator-=(const vect2& other);
		vect2 operator*(int num)const;
		vect2& operator*=(int num);

		
		bool operator!=(const vect2& other)const;
		bool operator==(const vect2& other)const;
		int& operator[](int index);
		int operator[](int index)const;
};
vect2 operator*(int num, const vect2& other);
vect2 operator-(const vect2& other);

std::ostream& operator<<(std::ostream& output, const vect2& other);

#endif