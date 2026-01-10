/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:24:13 by zoum              #+#    #+#             */
/*   Updated: 2025/12/14 18:44:59 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

bigint::bigint() : num("0") {}

bigint::~bigint() {}

bigint::bigint(unsigned int num) {
	std::stringstream ss;
	ss << num;
	this->num = ss.str();
}

bigint::bigint(const bigint& other) : num(other.num) {}

bigint& bigint::operator=(const bigint& other)
{
	if (*this != other) {
		this->num = other.num;
	}
	return *this;
}

bigint bigint::operator<<(unsigned int precision)const {
	bigint tmp = *this;
	for (unsigned int i = 0; i < precision; i++)
		tmp.num = tmp.num + "0";
	return (tmp);
}

bigint& bigint::operator<<=(unsigned int precision) {
	for (unsigned int i = 0; i < precision; i++)
		this->num = this->num + "0";
	return (*this);
}

bigint& bigint::operator>>=(const bigint& precision) {
	bigint i(0);
	int j = 0;
	bigint len = bigint(this->num.length());
	bigint tmp;
	tmp.num = "";

	while ((precision + i) < len)
	{
		tmp.num = tmp.num + this->num[j];
		i++;
		j++;
	}
	
	if (tmp.num.empty())
		tmp.num = "0";
	
	this->num = tmp.num;
	return (*this);
}

std::string addition(const bigint& obj1, const bigint& obj2) {
	std::string result;
	std::string num1 = obj1.getNum();
	std::string num2 = obj2.getNum();

	int retenue = 0;
	int	i = num1.length() - 1;
	int j = num2.length() - 1;

	while (i >= 0 || j >= 0 || retenue)
	{
		int sum = retenue;
		if (i >= 0) {
			sum += (num1[i] - '0');
			i--;
		}
		if (j >= 0) {
			sum += (num2[j] - '0');
			j--;
		}
		result = static_cast<char>(sum % 10 + '0') + result;
		retenue = sum / 10;
	}
	return (result);
}

bigint bigint::operator+(const bigint& other) const {
	bigint result;
	result.num = addition(*this, other);
	return (result);
}

bigint& bigint::operator+=(const bigint& other) {
	this->num = addition(*this, other);
	return (*this);
}

bigint& bigint::operator++() {
	*this = *this + bigint(1);
	return (*this);
}

bigint bigint::operator++(int) {
	bigint tmp = *this;
	this->num = addition(*this, bigint(1));
	return (tmp);
}

std::string bigint::getNum()const {
	return (this->num);
}

std::ostream& operator<<(std::ostream& output, const bigint& input) {
	output << input.getNum();
	return (output);
}

bool bigint::operator!=(const bigint& other)const {
	return (this->num != other.num);
}

bool bigint::operator==(const bigint& other)const {
	return (this->num == other.num);
}

bool bigint::operator<(const bigint& other) const {
    if (this->num.length() != other.num.length())
        return (this->num.length() < other.num.length());
    return (this->num < other.num);
}

bool bigint::operator>(const bigint& other) const {
    if (this->num.length() != other.num.length())
        return (this->num.length() > other.num.length());
    return (this->num > other.num);
}

bool bigint::operator<=(const bigint& other) const {
    return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const {
    return !(*this < other);
}