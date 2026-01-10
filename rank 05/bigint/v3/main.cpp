#include "bigint.hpp"
#include <iostream>

int main()
{
    std::cout << "=== TEST SUJET OFFICIEL ===" << std::endl;
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    std::cout << "a =" << a << std::endl;
    std::cout << "d =" << d << std::endl;

    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;

    std::cout << "\n=== TESTS SUPPLEMENTAIRES ===" << std::endl;
    
    // Test nombres très grands
    bigint big1(999999999);
    bigint big2(1);
    std::cout << "999999999 + 1 = " << big1 + big2 << std::endl;
    
    // Test shift avec grands nombres
    bigint shift1(42);
    std::cout << "42 << 5 = " << (shift1 << 5) << " (expected: 4200000)" << std::endl;
    
    bigint shift2(123456789);
    std::cout << "123456789 >> 3 = " << (shift2 >>= bigint(3)) << " (expected: 123456)" << std::endl;
    
    // Test comparaisons edge cases
    bigint x(100);
    bigint y(99);
    bigint z(100);
    std::cout << "100 > 99 = " << (x > y) << " (expected: 1)" << std::endl;
    std::cout << "100 == 100 = " << (x == z) << " (expected: 1)" << std::endl;
    std::cout << "100 <= 100 = " << (x <= z) << " (expected: 1)" << std::endl;
    
    // Test shift vers zéro
    bigint small(5);
    std::cout << "5 >> 10 = " << (small >>= bigint(10)) << " (expected: 0)" << std::endl;
    
    // Test constructeur par défaut
    bigint zero;
    std::cout << "bigint() = " << zero << " (should be empty or 0)" << std::endl;
    std::cout << "bigint() + 42 = " << (zero + bigint(42)) << std::endl;
    
    return 0;
}
