/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:41:25 by zoum              #+#    #+#             */
/*   Updated: 2025/12/21 19:36:43 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

bigint::bigint() : num("0") {}

bigint::bigint(unsigned int num) {
	std::stringstream ss;
	ss << num;
	this->num = ss.str();
}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint&other) {
	if (*this != other)
		this->num = other.num;
	return (*this);
}

bigint::bigint(const bigint&other) : num(other.num) {}

std::string bigint::getNum() const {
	return (this->num);
} 

std::string addition(const bigint&obj1, const bigint&obj2) {
	std::string result;
	std::string str1 = obj1.getNum();
	std::string str2 = obj2.getNum();

	int retenue = 0;
	int i = str1.length() - 1;
	int j = str2.length() - 1;
	while (i >= 0 || j >= 0 || retenue)
	{
		int sum = retenue;
		if (i >= 0)
			sum += str1[i--] - '0';
		if (j >= 0)
			sum += str2[j--] - '0';
		result = static_cast<char>((sum % 10) + '0') + result;
		retenue = sum / 10;
	}
	return (result);
}

bigint bigint::operator+(const bigint&other) const {
	bigint result = *this;
	result += other;
	return (result);
}

bigint& bigint::operator+=(const bigint&other) {
	this->num = addition(*this, other);
	return (*this);
}

bigint bigint::operator++(int) {
	bigint tmp = *this;
	*this += bigint(1);
	return (tmp);
}

bigint& bigint::operator++() {
	*this += bigint(1);
	return (*this);
}

bigint bigint::operator<<(int precision) const {
	bigint tmp = *this;
	tmp <<= precision;
	return (tmp);
}

bigint& bigint::operator<<=(int precision) {
	for (int i = 0; i < precision; i++)
		this->num = this->num + "0";
	return (*this);
}

bigint& bigint::operator>>=(const bigint&precision) {
	bigint len(this->num.length());
	
	if (len <= precision)
		return (*this = bigint(0));
	for (bigint i; i < precision; i++)
		this->num.erase(this->num.length() - 1);
	return (*this);	
}

int compare(const bigint&obj1, const bigint&obj2)
{
	if (obj1.getNum().length() > obj2.getNum().length())
		return (1);
	if (obj1.getNum().length() < obj2.getNum().length())
		return (-1);
	for (size_t i = 0; i < obj1.getNum().length(); i++) {
		if (obj1.getNum()[i] > obj2.getNum()[i])
			return (1);
		if (obj1.getNum()[i] < obj2.getNum()[i])
			return (-1);
	}
	return (0);
}

bool bigint::operator>(const bigint&other) const {
    return compare(*this, other) == 1;
}

bool bigint::operator<(const bigint&other) const {
    return compare(*this, other) == -1;
}

bool bigint::operator>=(const bigint&other) const {
    return compare(*this, other) >= 0;
}

bool bigint::operator<=(const bigint&other) const {
    return compare(*this, other) <= 0;
}

bool bigint::operator!=(const bigint&other) const {
    return compare(*this, other) != 0;
}

bool bigint::operator==(const bigint&other) const {
    return compare(*this, other) == 0;
}

std::ostream& operator<<(std::ostream& output, const bigint&other)
{
	output << other.getNum();
	return (output);
}