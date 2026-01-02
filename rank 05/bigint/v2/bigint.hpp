/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:58:54 by mzimeris          #+#    #+#             */
/*   Updated: 2026/01/02 14:18:29 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
	private:
		std::string num;
	public:
		bigint();
		~bigint();
		bigint(const bigint&);
		bigint &operator=(const bigint&);

		bigint(int);
		bigint &operator+=(const bigint&);
		bigint operator+(const bigint&)const;

		bigint &operator++();
		bigint operator++(int);

		bigint &operator<<=(int);
		bigint operator<<(int)const;
		bigint &operator>>=(const bigint&);

		std::string getNum()const;

		bool operator>=(const bigint&)const;
		bool operator>(const bigint&)const;
		bool operator<=(const bigint&)const;
		bool operator<(const bigint&)const;
		bool operator==(const bigint&)const;
		bool operator!=(const bigint&)const;
		
};

std::ostream &operator<<(std::ostream&, const bigint&);

#endif