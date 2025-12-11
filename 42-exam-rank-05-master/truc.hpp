/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truc.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:56:11 by mzimeris          #+#    #+#             */
/*   Updated: 2025/12/10 10:06:25 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRUC_HPP
#define TRUC_HPP

class Truc
{
	private:
		int		_foo;
		double	_bar;
	public:
		Truc();
		Truc(const Truc &src);
		~Truc();
		Truc &operator= (const Truc &rhs);

		Truc operator+ (const Truc &rhs);
		Truc &operator+= (const Truc &rhs);
		Truc operator- (const Truc &rhs);
		Truc &operator-= (const Truc &rhs);		
		Truc operator* (const Truc &rhs);
		Truc &operator*= (const Truc &rhs);		
		Truc operator/ (const Truc &rhs);
		Truc &operator/= (const Truc &rhs);
		
		Truc &operator++();
		Truc &operator--();
		Truc operator++(int);
		Truc operator--(int);
};

#endif