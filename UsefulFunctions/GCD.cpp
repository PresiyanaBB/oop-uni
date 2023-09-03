#include <iostream>
using std::swap;

size_t GetGcd(size_t a, size_t b) {
    if (a < 0)
        a *= -1;

    if (b < 0)
        b *= -1;

    if (a < b)
        std::swap(a, b);

    while (b != 0) {
        size_t temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}