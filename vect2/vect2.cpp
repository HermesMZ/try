/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 20:00:48 by zoum              #+#    #+#             */
/*   Updated: 2025/12/21 20:32:00 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"
#include <iostream>

vect2::vect2() : x(0), y(0) {}

vect2::~vect2() {}

vect2::vect2(const vect2&other) : x(other.x), y(other.y) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2& vect2::operator=(const vect2&other) {
	if (*this != other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return (*this);
}

vect2& vect2::operator+=(const vect2&other) {
	this->x += other.x;
	this->y += other.y;
	return (*this);
}

vect2& vect2::operator-=(const vect2&other) {
	this->x -= other.x;
	this->y -= other.y;
	return (*this);
}

vect2& vect2::operator*=(int num) {
	this->x *= num;
	this->y *= num;
	return (*this);
}

vect2 vect2::operator+(const vect2&other) const {
	vect2 tmp = *this;
	tmp.x += other.x;
	tmp.y += other.y;
	return (tmp);
}

vect2 vect2::operator-(const vect2&other) const {
	vect2 tmp = *this;
	tmp.x -= other.x;
	tmp.y -= other.y;
	return (tmp);
}

vect2 vect2::operator*(int num) const {
	vect2 tmp = *this;
	tmp.x *= num;
	tmp.y *= num;
	return (tmp);
}

vect2 vect2::operator++(int) {
	vect2 tmp = *this;
	++(*this);
	return (tmp);
}

vect2& vect2::operator++() {
	this->x += 1;
	this->y += 1;
	return (*this);
}

vect2 vect2::operator--(int) {
	vect2 tmp = *this;
	--(*this);
	return (tmp);
}

vect2& vect2::operator--() {
	this->x -= 1;
	this->y -= 1;
	return (*this);
}


int vect2::operator[](int index) const {
	if (index == 0)
		return (this->x);
	else
		return (this->y);
}

int& vect2::operator[](int index) {
	if (index == 0)
		return (this->x);
	else
		return (this->y);
}

bool vect2::operator==(const vect2&other) {
	return (this->x == other.x && this->y == other.y);
}

bool vect2::operator!=(const vect2&other) {
	return (this->x != other.x || this->y != other.y);
}

vect2 operator-(const vect2&other) {
	vect2 tmp = other;
	tmp[0] *= -1;
	tmp[1] *= -1;
	return (tmp);
}

vect2 operator*(const int num, const vect2&other) {
	vect2 tmp = other;
	tmp[0] *= num;
	tmp[1] *= num;
	return (tmp);
}

std::ostream& operator<<(std::ostream& output, const vect2&other) {
	output << "{" << other[0] << ", " << other[1] << "}";
	return (output);
}