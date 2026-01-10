/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:24:13 by zoum              #+#    #+#             */
/*   Updated: 2025/12/21 17:19:46 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"
#include <iomanip>
#include <string>
#include <sstream>

bigint::bigint() : size(1) {
	for (unsigned int i = 0; i < 300; i++)
		num[i] = 0;
}

bigint::~bigint() {}

bigint::bigint(unsigned int num) {
	this->size = 0;
	for (unsigned int i = 0; i < 300; i++)
		this->num[i] = 0;
	while (num > 0) {
		this->num[this->size] = num % base;
		num /= base;
		this->size++;
	}
	if (this->size == 0)
		this->size = 1;
}

bigint bigint::operator+(const bigint& other)const {
	bigint result;
    unsigned int maxSize = (this->size > other.size) ? this->size : other.size;
	int	retenue = 0;
	int sum = 0;

	result.size = 0;
	for (unsigned int i = 0; i < maxSize || retenue; i++) {
		sum = retenue;
		if (i < this->size)
			sum += (*this)[i];
		if (i < other.size)
			sum += other[i];
		result.num[result.size++] = sum % base;
		retenue = sum / base;
	}
	return (result);
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

bigint& bigint::operator+=(const bigint&other) {
	*this = *this + other;
	return (*this);
}


bigint::bigint(const bigint& other) : size(other.size) {
	for (unsigned int i = 0; i < 300; i++)
		this->num[i] = other.num[i];
}

bigint& bigint::operator=(const bigint& other) {
	if (this != &other) {
		this->size = other.size;
		for (unsigned int i = 0; i < other.size; i++)
			this->num[i] = other.num[i];
	}
	return *this;
}

unsigned int bigint::getSize()const {
	return (this->size);
}

unsigned int bigint::getNum(unsigned int index)const {
	return (this->num[index]);
}

bool bigint::operator>(const bigint&other)const {
	if (this->size > other.size)
		return (true);
	if (this->size < other.size)
		return (false);
	for (int i = this->size - 1; i >= 0; i--)
	{
		if ((*this)[i] > other[i])
			return (true);
		if ((*this)[i] < other[i])
			return (false);
	}
	return (false);
}

bool bigint::operator==(const bigint&other)const {
	if (this->size != other.size)
		return (false);
	for (int i = this->size - 1; i >= 0; i--)
	{
		if ((*this)[i] != other[i])
			return (false);
	}
	return (true);
}

bool bigint::operator>=(const bigint&other)const {
    return !(*this < other);
}

bool bigint::operator<(const bigint&other)const {
    return (other > *this);
}

bool bigint::operator<=(const bigint&other)const {
    return !(*this > other);
}

bool bigint::operator!=(const bigint&other)const {
	return (!(*this == other));
}

unsigned int bigint::operator[](unsigned int index)const {
	return (this->getNum(index));
}

std::ostream& operator<<(std::ostream&output, const bigint&other) {
	for (int i = other.getSize() - 1; i >= 0; i--)
		if (i == (int)other.getSize() - 1)
			output << other.getNum(i);
		else
			output << std::setw(3) << std::setfill('0') << other.getNum(i);
	return (output);
}

std::string bigint::toStr() const {
    std::stringstream ss;
    for (int i = this->getSize() - 1; i >= 0; i--)
        if (i == (int)this->getSize() - 1)
            ss << this->getNum(i);
        else
            ss << std::setw(3) << std::setfill('0') << this->getNum(i);
    return (ss.str());
}

bigint bigint::toBigint(const std::string& str) {
    bigint result;
    int pos = str.length();
	int debut;
	unsigned int val;
    
    result.size = 0;
    while (pos > 0) {
        debut = (pos > 3) ? pos - 3 : 0;
        
        val = 0;
        for (int i = debut; i < pos; i++)
            val = val * 10 + (str[i] - '0');
        
        result.num[result.size++] = val;
        pos = debut;
    }
    if (result.size == 0) {
        result.size = 1;
        result.num[0] = 0;
    }
    return result;
}

bigint& bigint::operator<<=(unsigned int precision) {
	if (precision == 0)
		return (*this);
	std::string str = this->toStr();
	for (unsigned int i = 0; i < precision; i++)
		str += '0';
	*this = this->toBigint(str);
	return (*this);
}

bigint bigint::operator<<(unsigned int precision)const {
	bigint result = *this;
	result <<= precision;
	return (result);
}

bigint& bigint::operator>>=(const bigint&precision) {
	std::string str = this->toStr();
	
	if (precision >= bigint(str.length())) {
		*this = bigint(0);
		return (*this);		
	}
	bigint counter;
	while (counter != precision) {
		if (str.empty()) {
			*this = bigint(0);
			return (*this);
		}
		str.erase(str.length() - 1);
		counter++;
	}
	*this = this->toBigint(str);
	return (*this);
}