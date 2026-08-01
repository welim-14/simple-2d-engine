#include <iostream>
#include "Physics/Vec2.h"

void printVec(const char* name, const Vec2& v)
{
    std::cout << name << " = (" << v.m_x << ", " << v.m_y << ")\n";
}

int main()
{
    Vec2 a(3.f, 4.f);
    Vec2 b(2.f, 1.f);

    std::cout << "===== Initial Vectors =====\n";
    printVec("a", a);
    printVec("b", b);

    std::cout << "\n===== Basic Operations =====\n";

    printVec("a + b", a + b);
    printVec("a - b", a - b);
    printVec("a * 2", a * 2.f);
    printVec("a / 2", a / 2.f);

    std::cout << "\n===== Compound Operators =====\n";

    Vec2 c = a;

    c += b;
    printVec("c += b", c);

    c = a;
    c -= b;
    printVec("c -= b", c);

    c = a;
    c *= 2.f;
    printVec("c *= 2", c);

    c = a;
    c /= 2.f;
    printVec("c /= 2", c);

    std::cout << "\n===== Vector Math =====\n";

    std::cout << "Length of a: " << a.length() << '\n';
    std::cout << "Length squared of a: " << a.lengthSquared() << '\n';
    std::cout << "Dot(a, b): " << a.dot(b) << '\n';

    printVec("Normalized a", a.normalized());

    std::cout << "\n===== Zero Vector =====\n";

    printVec("Zero", Vec2::Zero);
    printVec("Normalized Zero", Vec2::Zero.normalized());

    return 0;
}
