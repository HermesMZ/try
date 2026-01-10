/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:41:46 by zoum              #+#    #+#             */
/*   Updated: 2025/12/21 18:36:35 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>
#include <sstream>


class bigint {
	private:
		std::string num;
	public:
		bigint();
		bigint(unsigned int num);
		bigint(const bigint&other);
		~bigint();
		bigint& operator=(const bigint&other);

		bigint operator+(const bigint&other)const;
		bigint& operator+=(const bigint&other);

		bigint operator++(int);
		bigint& operator++();

		bigint operator<<(int precision)const;
		bigint& operator<<=(int precision);
		bigint& operator>>=(const bigint&precision);

		bool operator>(const bigint&other)const;
		bool operator>=(const bigint&other)const;
		bool operator<(const bigint&other)const;
		bool operator<=(const bigint&other)const;
		bool operator==(const bigint&other)const;
		bool operator!=(const bigint&other)const;
		
		std::string getNum() const;
};

std::ostream& operator<<(std::ostream& output, const bigint&other);

#endif /*BIGINT_HPP*/