/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:10:09 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/02 14:23:35 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"
#include <iostream>
#include <sstream>
#include <string>

bigint::bigint() : num("0") {};

bigint::~bigint() {}

bigint::bigint(const bigint&other) : num(other.num) {}

bigint& bigint::operator=(const bigint&other) {
	if (this != &other)
		this->num = other.num;
	return (*this);
}

bigint::bigint(int val) {
	std::stringstream ss;
	ss << val;
	num = ss.str();
}

std::string addition(const bigint&num1, const bigint&num2) {
	std::string result;
	std::string str1 = num1.getNum();
	std::string str2 = num2.getNum();

	int i = str1.length() - 1;
	int j = str2.length() - 1;
	int retenue = 0;
	
	while (i >= 0 || j >= 0 || retenue) {
		int sum = retenue;
		if (i >= 0) {
			sum += str1[i] - '0';
			i--;
		}
		if (j >= 0) {
			sum += str2[j] - '0';
			j--;
		}
		result = static_cast<char>((sum % 10) + '0') + result;
		retenue = sum / 10;	
	}
	return (result);
}

bigint& bigint::operator+=(const bigint&other) {
	this->num = addition(*this, other);
	return (*this);
}

bigint bigint::operator+(const bigint&other)const {
	bigint result;
	result.num = addition(*this, other);
	return (result);
}

bigint& bigint::operator++() {
	return (*this += bigint(1));
}

bigint bigint::operator++(int) {
	bigint tmp = *this;
	*this += bigint(1);
	return (tmp);
}

bigint& bigint::operator<<=(int pre) {
	for (int i = 0; i < pre ; i++) {
		this->num += '0';
	}
	return (*this);
}

bigint bigint::operator<<(int pre)const {
	bigint result(*this);
	for (int i = 0; i < pre ; i++) {
		result.num += '0';
	}
	return (result);
}

bigint& bigint::operator>>=(const bigint&other) {
	
	if (bigint(this->num.length()) <= other)
		this->num = "0";
	else {
		for (bigint i; i < other; ++i) {
			this->num.erase(this->num.length() - 1);
		}
	}
	return (*this);
}

bool bigint::operator==(const bigint&other)const {
	if (this->num.length() != other.num.length())
		return (false);
	for (int i = other.num.length() - 1; i >= 0; i--) {
		if (this->num[i] != other.num[i])
			return (false);
	}
	return (true);
}

bool bigint::operator!=(const bigint&other)const {
	return (!(*this == other));
}

bool bigint::operator>(const bigint&other)const {
	if (this->num.length() < other.num.length())
		return (false);
	for (size_t i = 0; i < this->num.length(); i++) {
		if (this->num[i] > other.num[i])
			return (true);
		if (this->num[i] < other.num[i])
			return (false);
	}
	return (false);
}

bool bigint::operator>=(const bigint&other)const {
	if (*this == other)
		return (true);
	return (*this > other);
}

bool bigint::operator<(const bigint&other)const {
	return (!(*this >= other));
}

bool bigint::operator<=(const bigint&other)const {
	return(!(*this > other));
}

std::string bigint::getNum()const {
	return (this->num);
}

std::ostream& operator<<(std::ostream&output, const bigint&other) {
	output << other.getNum();
	return (output);
}