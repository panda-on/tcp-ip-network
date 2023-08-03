#include <iostream>

int main()
{
    const int var = 5;
    constexpr int k = var;
    std::cout << k;
    return 0;
}