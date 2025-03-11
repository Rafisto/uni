#include <iostream>

int main(void) {
    auto f = [](int x) -> int { return 1 + x * (x + 1); };
    auto g = [](int x, int y) -> int { return x + y * y; };
    auto h = [](int y, int x) -> int { return x + y * y; };

    std::cout << "f(2): " << f(2) << std::endl;
    std::cout << "g(2, 3): " << g(2, 3) << std::endl;
    std::cout << "h(3, 2): " << h(3, 2) << std::endl;
}