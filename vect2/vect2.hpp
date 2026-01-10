/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:45:46 by zoum              #+#    #+#             */
/*   Updated: 2025/12/21 20:18:14 by zoum             ###   ########.fr       */
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
		~vect2();
		vect2(const vect2&);
		vect2& operator=(const vect2&);

		vect2(int, int);

		int operator[](int)const;
		int& operator[](int);

		vect2& operator+=(const vect2&);
		vect2& operator-=(const vect2&);
		vect2& operator*=(int);
		vect2 operator+(const vect2&)const;
		vect2 operator-(const vect2&)const;
		vect2 operator*(int)const;
		
		
		vect2 operator++(int);
		vect2& operator++();
		vect2 operator--(int);
		vect2& operator--();

		bool operator==(const vect2&);
		bool operator!=(const vect2&);
};
vect2 operator-(const vect2&);
vect2 operator*(const int, const vect2&);

std::ostream& operator<<(std::ostream&, const vect2&);

#endif /*VECT2_HPP*/