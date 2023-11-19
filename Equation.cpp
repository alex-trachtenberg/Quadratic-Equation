#include <ostream>
#include <cmath>      // for sqrt function
#include <stdexcept>  // for std::invalid_argument exception throwing

#include "Equation.hpp"

void Equation::update_solutions()
{
    int discriminant = this->b * this->b - 4 * this->a * this->c;
    if (discriminant > 0) {
        if (this->solutions_size < 2) {
            if (this->solutions != nullptr) {      // solutions_size == 1 & solutions points to an array of length one.
                delete[] this->solutions;
            }
            this->solutions = new double[2];
            this->solutions_size = 2;
        }     
        this->solutions[0] = (-this->b + sqrt(discriminant)) / 2 * this->a;
        this->solutions[1] = (-this->b - sqrt(discriminant)) / 2 * this->a;
    }
    else if (discriminant == 0) {
        if (this->solutions_size != 1) {
            if (this->solutions != nullptr) {      // solutions_size == 2 & solutions points to an array of length two.
                delete[] this->solutions;
            }
            this->solutions = new double[1];
            this->solutions_size = 1;
        }
        this->solutions[0] = (-this->b) / 2 * this->a;
    }
    else {  // case when discriminant < 0
        if (this->solutions_size > 0) {
            delete[] this->solutions;
            this->solutions = nullptr;
            this->solutions_size = 0;
        }
    }
}

Equation::Equation(double a, double b, double c)
    : a{a}, b{b}, c{c}
    , solutions{nullptr}
    , solutions_size{0}
{
    // TODO: Throw exception std::invalid_argument (from the <stdexcept> library) in case a = 0
    this->update_solutions();
}

Equation::~Equation()
{
    if (this->solutions != nullptr) {
        delete[] this->solutions;
        this->solutions = nullptr;
    }
}

double Equation::get_a() const
{
    return this->a;
}

void Equation::set_a(double a)
{
    // TODO: Throw exception std::invalid_argument (from the <stdexcept> library) in case a = 0
    this->a = a;
    this->update_solutions();
}

double Equation::get_b() const
{
    return this->b;
}

void Equation::set_b(double b)
{
    this->b = b;
    this->update_solutions();
}

double Equation::get_c() const
{
    return this->c;
}

void Equation::set_c(double c)
{
    this->c = c;
    this->update_solutions();
}

double const * Equation::get_solutions()
{
    return this->solutions;
}

std::size_t Equation::get_solutions_size()
{
    return this->solutions_size;
}

std::ostream& operator <<(std::ostream &out, const Equation &eq)
{
    return out << eq.a << "X^2 + " << eq.b << "X + " << eq.c << " = 0";
}
