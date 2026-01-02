/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:30:58 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/20 20:15:15 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <sstream>

class bigint {
	private:
		std::string value;
	public:
	bigint& operator+=(const bigint& other);
	bigint operator+(int);
	bigint& operator++();
	bigint operator++(int);
	bigint& operator>>=(const bigint& other);
	
	
	bigint operator+(const bigint& other) const;
	bigint& operator<<=(int);
	bigint operator<<(int)const;
	bigint(unsigned int val);
	bigint();
	~bigint();
	bigint(const bigint& other);
	bigint& operator=(const bigint& other);
	bool operator<(const bigint&other);
	bool operator<=(const bigint&other);
	bool operator>(const bigint&other);
	bool operator>=(const bigint&other);
	bool operator==(const bigint&other);
	bool operator!=(const bigint&other);
	std::string getVal()const;
};

std::ostream& operator<<(std::ostream& output, const bigint& other);

#endif /*BIGINT_HPP*/