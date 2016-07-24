#include <iostream>
#include "Calculator.cpp"

int main() {
    std::string str;
    std::cin >> str;
    Calculator calc(str);
    std::cout << calc.result() << std::endl;
    std::cin >> str;
    calc.setTarget(str);
    std::cout << calc.result() << std::endl;
}
