/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:45:29 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/07 16:40:40 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"
#include <iostream>

bigint::bigint() : value("0") {}

bigint::~bigint() {}

bigint::bigint(unsigned int val) {
	std::stringstream ss;
	ss << val;
	this->value = ss.str();
}

bigint::bigint(const bigint&other) : value(other.value) {}

bigint& bigint::operator=(const bigint& other) {
	if (*this != other) {
		this->value = other.value;
	}
	return *this;
}

bigint bigint::operator+(const bigint&other)const {
	bigint tmp;
	std::string obj1 = this->getVal();
	std::string obj2 = other.getVal();

	int	i;
	int	j;
	i = obj1.length() - 1;
	j = obj2.length() - 1;
	int retenue = 0;
	
	while (i >= 0 || j >= 0 || retenue)
	{
		int sum = retenue;
		if (i >= 0)
			sum += obj1[i];
		if (j >= 0)
			sum += obj2[j];
		if (retenue)
			sum++;
	}
	
}

bigint bigint::operator<<(int val)const {
	bigint tmp;
	tmp.value = this->value;
	for (int i = 0; i < val; i++)
		tmp.value = tmp.value + "0";
	return (tmp);
}

bigint& bigint::operator<<=(int val) {
	for (int i = 0; i < val; i++)
		this->value = this->value + "0";
	return (*this);
}

bool bigint::operator<(const bigint& other) {
	return (this->value < other.value);
}
bool bigint::operator<=(const bigint& other) {
	return (this->value <= other.value);
}
bool bigint::operator>(const bigint& other) {
	return (this->value > other.value);
}
bool bigint::operator>=(const bigint& other) {
	return (this->value >= other.value);
}
bool bigint::operator==(const bigint& other) {
	return (this->value == other.value);
}
bool bigint::operator!=(const bigint& other) {
	return (this->value != other.value);
}

std::string bigint::getVal()const {
	return (this->value);
}

std::ostream& operator<<(std::ostream& output, const bigint& other) {
	output << other.getVal();
	return (output);
}