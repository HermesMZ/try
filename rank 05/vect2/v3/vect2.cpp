/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 20:48:24 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/07 21:09:39 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

	vect2::vect2() : x(0), y(0) {}
	vect2::~vect2() {}
	vect2::vect2(const vect2&v) : x(v.x), y(v.y) {}
	vect2& vect2::operator=(const vect2&other) {
		if (*this != other) {
			this->x = other.x;
			this->y = other.y;
		}
		return *this;
	}

	vect2::vect2(int x, int y) : x(x), y(y) {}
	
	int vect2::operator[](int index )const {
		if (index == 0)
			return x;
		return y;
	}
	int& vect2::operator[](int index) {
		if (index == 0)
			return x;
		return y;
	}
	
	vect2& vect2::operator++() {
		this->x++;
		this->y++;
		return *this;
	}
	
	vect2 vect2::operator++(int) {
		vect2 tmp = *this;
		this->x++;
		this->y++;
		return tmp;
	}
	vect2& vect2::operator--() {
		this->x--;
		this->y--;
		return *this;
	}
	vect2 vect2::operator--(int) {
		vect2 tmp = *this;
		this->x--;
		this->y--;
		return tmp;
	}

	vect2& vect2::operator+=(const vect2&v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	vect2 vect2::operator+(const vect2&v)const {
		vect2 tmp = *this;
		tmp += v;
		return tmp;
	}
	
	vect2& vect2::operator-=(const vect2&v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	vect2 vect2::operator-(const vect2&v)const {
		vect2 tmp = *this;
		tmp -= v;
		return tmp;		
	}

	vect2& vect2::operator*=(int v) {
		x *= v;
		y *= v;
		return *this;
	}
	vect2 vect2::operator*(int v)const {
		vect2 tmp = *this;
		tmp *= v;
		return tmp;
	}
	bool vect2::operator==(const vect2&v)const {
		return (x == v.x && y == v.y);
	}
	bool vect2::operator!=(const vect2&v)const {
		return !(x == v.x && y == v.y);
	}
		
	vect2 operator*(int i, const vect2&v) {
		return v * i;
	}
	vect2 operator-(const vect2&v) {
		return v * -1;
	}

std::ostream& operator<<(std::ostream& out, const vect2&v) {
	out << "{" << v[0] << ", " << v[1] << "}";
	return out;
}