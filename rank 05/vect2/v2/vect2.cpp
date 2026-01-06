/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 13:17:32 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/06 13:47:24 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"
#include "iostream"

vect2::vect2() : x(0), y(0) {}

vect2::~vect2() {}

vect2::vect2(const vect2&other) : x(other.x), y(other.y) {}

vect2& vect2::operator=(const vect2&other) {
	if (*this != other) {
		this->x = other.x;
		this->y = other.y;
	}
	return *this;
};

vect2::vect2(int x, int y) : x(x), y(y) {}

int vect2::operator[](int index)const {
	if (index == 0)
		return this->x;
	else
		return this->y;
}

int& vect2::operator[](int index) {
	if (index == 0)
		return this->x;
	else
		return this->y;
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

vect2& vect2::operator+=(const vect2&other) {
	this->x += other.x;
	this->y += other.y;
	return *this;
}

vect2& vect2::operator-=(const vect2&other) {
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

vect2& vect2::operator*=(int val) {
	this->x *= val;
	this->y *= val;
	return *this;
}

vect2 vect2::operator+(const vect2&other)const {
	vect2 tmp = *this;
	return tmp += other;
}

vect2 vect2::operator-(const vect2&other)const {
	vect2 tmp = *this;
	return tmp -= other;
}

vect2 vect2::operator*(int val)const {
	vect2 tmp = *this;
	return tmp *= val;
}

bool vect2::operator==(const vect2&other)const {
	if (this->x == other.x && this->y == other.y)
		return true;
	return false;
}

bool vect2::operator!=(const vect2&other)const {
	return (!(*this == other));
}

vect2 operator*(int val, const vect2&other) {
	return other * val;
}

vect2 operator-(const vect2&other) {
	return other * -1;
}

std::ostream& operator<<(std::ostream&out, const vect2&other) {
	out << "{" << other[0] << ", " << other[1] << "}";
	return out;
}
