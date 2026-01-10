/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:23:28 by zoum              #+#    #+#             */
/*   Updated: 2025/12/21 17:20:16 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>

class	bigint
{
	private :
		static const unsigned int	base = 1000;
		unsigned int				num[300];
		unsigned int				size;
	public :
		bigint();
		bigint(unsigned int num);
		bigint(const bigint &other);
		bigint& operator=(const bigint& other);
		~bigint();

		bigint operator+(const bigint& other) const;
		bigint& operator+=(const bigint& other);

		bigint& operator++();
		bigint operator++(int);

		bigint operator<<(unsigned int precision)const;
		bigint& operator<<=(unsigned int precision);
		bigint operator>>(const bigint& other) const;
		bigint& operator>>=(const bigint& other);		bool operator<(const bigint& other)const;
		
		bool operator<=(const bigint& other)const;
		bool operator>(const bigint& other)const;
		bool operator>=(const bigint& other)const;
		bool operator!=(const bigint& other)const;
		bool operator==(const bigint& other)const;
		
		unsigned int operator[](unsigned int index)const;
		unsigned int getNum(unsigned int index)const;
		unsigned int getSize()const;
		std::string toStr() const;
		bigint toBigint(const std::string&str);
};

std::ostream& operator<<(std::ostream& output, const bigint& input);

#endif