#include <iostream>

#include "Equation.hpp"

int main() {
    Equation eq1(1, 3, -4);

    std::cout << eq1 << std::endl;
    std::cout << eq1.get_solutions_size() << std::endl;
    if (eq1.get_solutions_size() > 0) {
        std::cout << "eq1: X1 = " << eq1.get_solutions()[0] << std::endl;
        if (eq1.get_solutions_size() == 2)
            std::cout << "eq1: X2 = " << eq1.get_solutions()[1] << std::endl;
    }
    std::cout << std::endl;

    Equation eq2{eq1};
    
    std::cout << eq2 << std::endl;
    std::cout << eq2.get_solutions_size() << std::endl;
    if (eq2.get_solutions_size() > 0) {
        std::cout << "eq2: X1 = " << eq2.get_solutions()[0] << std::endl;
        if (eq2.get_solutions_size() == 2)
            std::cout << "eq2: X2 = " << eq2.get_solutions()[1] << std::endl;
    }
    std::cout << std::endl;

    eq2.set_a(10);
    eq2.set_b(20);
    eq2.set_c(10);

    std::cout << eq2 << std::endl;
    std::cout << eq2.get_solutions_size() << std::endl;
    if (eq2.get_solutions_size() > 0) {
        std::cout << "eq2: X1 = " << eq2.get_solutions()[0] << std::endl;
        if (eq2.get_solutions_size() == 2)
            std::cout << "eq2: X2 = " << eq2.get_solutions()[1] << std::endl;
    }
    std::cout << std::endl;

    eq1 = eq2;
    eq1.set_c(30);

    std::cout << eq1 << std::endl;
    std::cout << eq1.get_solutions_size() << std::endl;
    if (eq1.get_solutions_size() > 0) {
        std::cout << "eq1: X1 = " << eq1.get_solutions()[0] << std::endl;
        if (eq1.get_solutions_size() == 2)
            std::cout << "eq1: X2 = " << eq1.get_solutions()[1] << std::endl;
    }

    return 0;
}