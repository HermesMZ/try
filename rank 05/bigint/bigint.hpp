/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:23:28 by zoum              #+#    #+#             */
/*   Updated: 2025/12/14 17:57:55 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <sstream>

class	bigint
{
	private :
		// unsigned int	precision;
		std::string		num;
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
		bigint& operator>>=(const bigint& other);

		bool operator<(const bigint& other)const;
		bool operator<=(const bigint& other)const;
		bool operator>(const bigint& other)const;
		bool operator>=(const bigint& other)const;
		bool operator!=(const bigint& other)const;
		bool operator==(const bigint& other)const;
		
		std::string getNum()const;
};

std::ostream& operator<<(std::ostream& output, const bigint& input);

#endif