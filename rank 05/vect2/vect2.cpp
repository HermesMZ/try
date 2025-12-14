/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:09:29 by zoum              #+#    #+#             */
/*   Updated: 2025/12/14 20:17:31 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(const vect2& other) : x(other.x), y(other.y) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::~vect2() {}

vect2& vect2::operator=(const vect2& other) {
	if (*this != other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return (*this);
}

int& vect2::operator[](int index) {
	if (index == 0)
		return (this->x);
	else if (index == 1)
		return (this->y);
	return(this->x);
}

int vect2::operator[](int index)const {
	if (index == 0)
		return (this->x);
	else if (index == 1)
		return (this->y);
	return(0);
}

vect2& vect2::operator++() {
	(this->x)++;
	(this->y)++;
	return (*this);
}

vect2 vect2::operator++(int) {
	vect2 tmp = *this;
	(this->x)++;
	(this->y)++;
	return (tmp);
}

vect2& vect2::operator--() {
	(this->x)--;
	(this->y)--;
	return (*this);
}

vect2 vect2::operator--(int) {
	vect2 tmp = *this;
	(this->x)--;
	(this->y)--;
	return (tmp);
}

vect2 vect2::operator*(int num)const {
	vect2 tmp = *this;
	tmp.x *= num;
	tmp.y *= num;
	return (tmp);
}




vect2& vect2::operator*=(int num) {
	this->x *= num;
	this->y *= num;
	return (*this);
}

vect2 vect2::operator+(const vect2& other)const {
	vect2 tmp = *this;
	tmp.x += other.x;
	tmp.y += other.y;
	return (tmp);
}


vect2& vect2::operator+=(const vect2& other) {
	(this->x) += other.x;
	(this->y) += other.y;
	return (*this);
}

vect2 vect2::operator-(const vect2& other)const {
	vect2 tmp = *this;
	tmp.x -= other.x;
	tmp.y -= other.y;
	return (tmp);
}

vect2& vect2::operator-=(const vect2& other) {
	(this->x) -= other.x;
	(this->y) -= other.y;
	return (*this);
}

bool vect2::operator!=(const vect2& other)const {
    return (this->x != other.x || this->y != other.y);
}

bool vect2::operator==(const vect2& other)const {
    return (this->x == other.x && this->y == other.y);
}

vect2 operator*(int num, const vect2& other) {
	return (other * num);
}

vect2 operator-(const vect2& other) {
	return (other * -1);
}

std::ostream& operator<<(std::ostream& output, const vect2& other) {
	output << "{" << other[0] << ", " << other[1] << "}";
	return (output);
}
