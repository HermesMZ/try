/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 19:09:57 by zoum              #+#    #+#             */
/*   Updated: 2025/12/14 20:34:07 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"
#include <iostream>

int main()
{
    std::cout << "=== TEST CONSTRUCTEURS ===" << std::endl;
    vect2 v1;
    vect2 v2(3, 4);
    const vect2 v3(v2);
    vect2 v4 = v2;
    
    std::cout << "v1 (default): " << v1 << " (attendu: {0, 0})" << std::endl;
    std::cout << "v2 (3, 4): " << v2 << " (attendu: {3, 4})" << std::endl;
    std::cout << "v3 (copie de v2): " << v3 << " (attendu: {3, 4})" << std::endl;
    std::cout << "v4 (= v2): " << v4 << " (attendu: {3, 4})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR [] ===" << std::endl;
    std::cout << "v2[0]: " << v2[0] << " (attendu: 3)" << std::endl;
    std::cout << "v2[1]: " << v2[1] << " (attendu: 4)" << std::endl;
    std::cout << "v3[0] (const): " << v3[0] << " (attendu: 3)" << std::endl;
    v2[0] = 10;
    std::cout << "Après v2[0] = 10: " << v2 << " (attendu: {10, 4})" << std::endl;
    v2[0] = 3;

    std::cout << "\n=== TEST OPERATEUR = ===" << std::endl;
    v1 = v2;
    std::cout << "v1 = v2: " << v1 << " (attendu: {3, 4})" << std::endl;
    v1 = v1;
    std::cout << "v1 = v1: " << v1 << " (attendu: {3, 4})" << std::endl;

    std::cout << "\n=== TEST ++ (pré et post) ===" << std::endl;
    vect2 v5(1, 2);
    std::cout << "v5 initial: " << v5 << " (attendu: {1, 2})" << std::endl;
    std::cout << "v5++: " << v5++ << " (attendu: {1, 2})" << std::endl;
    std::cout << "v5 après: " << v5 << " (attendu: {2, 3})" << std::endl;
    std::cout << "++v5: " << ++v5 << " (attendu: {3, 4})" << std::endl;
    std::cout << "v5 après: " << v5 << " (attendu: {3, 4})" << std::endl;

    std::cout << "\n=== TEST -- (pré et post) ===" << std::endl;
    std::cout << "v5--: " << v5-- << " (attendu: {3, 4})" << std::endl;
    std::cout << "v5 après: " << v5 << " (attendu: {2, 3})" << std::endl;
    std::cout << "--v5: " << --v5 << " (attendu: {1, 2})" << std::endl;
    std::cout << "v5 après: " << v5 << " (attendu: {1, 2})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR + ===" << std::endl;
    vect2 v6(1, 2);
    vect2 v7(3, 4);
    vect2 v8 = v6 + v7;
    std::cout << v6 << " + " << v7 << " = " << v8 << " (attendu: {4, 6})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR += ===" << std::endl;
    v6 += v7;
    std::cout << "Après v6 += v7: " << v6 << " (attendu: {4, 6})" << std::endl;
    v6 += v6;
    std::cout << "Après v6 += v6: " << v6 << " (attendu: {8, 12})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR - ===" << std::endl;
    vect2 v9(5, 8);
    vect2 v10(2, 3);
    vect2 v11 = v9 - v10;
    std::cout << v9 << " - " << v10 << " = " << v11 << " (attendu: {3, 5})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR -= ===" << std::endl;
    v9 -= v10;
    std::cout << "Après v9 -= v10: " << v9 << " (attendu: {3, 5})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR - UNAIRE ===" << std::endl;
    vect2 v12(3, -4);
    std::cout << "-" << v12 << " = " << -v12 << " (attendu: {-3, 4})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR * (vect2 * int) ===" << std::endl;
    vect2 v13(2, 3);
    vect2 v14 = v13 * 4;
    std::cout << v13 << " * 4 = " << v14 << " (attendu: {8, 12})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR * (int * vect2) ===" << std::endl;
    vect2 v15 = 3 * v13;
    std::cout << "3 * " << v13 << " = " << v15 << " (attendu: {6, 9})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR *= ===" << std::endl;
    v13 *= 2;
    std::cout << "Après v13 *= 2: " << v13 << " (attendu: {4, 6})" << std::endl;

    std::cout << "\n=== TEST OPERATEUR == ===" << std::endl;
    vect2 v16(5, 7);
    vect2 v17(5, 7);
    vect2 v18(5, 8);
    std::cout << v16 << " == " << v17 << ": " << (v16 == v17) << " (attendu: 1)" << std::endl;
    std::cout << v16 << " == " << v18 << ": " << (v16 == v18) << " (attendu: 0)" << std::endl;

    std::cout << "\n=== TEST OPERATEUR != ===" << std::endl;
    std::cout << v16 << " != " << v17 << ": " << (v16 != v17) << " (attendu: 0)" << std::endl;
    std::cout << v16 << " != " << v18 << ": " << (v16 != v18) << " (attendu: 1)" << std::endl;

    std::cout << "\n=== TEST EXPRESSIONS COMPLEXES ===" << std::endl;
    vect2 v19(1, 2);
    vect2 v20 = v19 + v19 * 2;
    std::cout << "v19 + v19 * 2 = " << v20 << " (attendu: {3, 6})" << std::endl;
    
    vect2 v21(2, 3);
    v21 += v21 += vect2(1, 1);
    std::cout << "v21 après v21 += v21 += {1,1}: " << v21 << " (attendu: {6, 8})" << std::endl;

    std::cout << "\n=== TOUS LES TESTS TERMINES ===" << std::endl;
    return 0;
}
