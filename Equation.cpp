// #include <ostream>
#include <iomanip>    // for std::setprecision
#include <cmath>      // for std::sqrt function
#include <stdexcept>  // for std::invalid_argument exception throwing

#include "Equation.hpp"

void Equation::update_solutions() {
    int discriminant = this->b * this->b - 4 * this->a * this->c;
    if (discriminant > 0) {
        if (this->solutions_size < 2) {
            if (this->solutions != nullptr) {      // solutions_size == 1 & solutions points to an array of length one.
                delete[] this->solutions;
            }
            this->solutions = new double[2];
            this->solutions_size = 2;
        }     
        this->solutions[0] = (-this->b + sqrt(discriminant)) / (2 * this->a);
        this->solutions[1] = (-this->b - sqrt(discriminant)) / (2 * this->a);
    }
    else if (discriminant == 0) {
        if (this->solutions_size != 1) {
            if (this->solutions != nullptr) {      // solutions_size == 2 & solutions points to an array of length two.
                delete[] this->solutions;
            }
            this->solutions = new double[1];
            this->solutions_size = 1;
        }
        this->solutions[0] = -(this->b) / (2 * this->a);
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

Equation::Equation(const Equation &other_eq)
    : a{other_eq.a}, b{other_eq.b}, c{other_eq.c}
    , solutions{nullptr}
    , solutions_size{other_eq.solutions_size}
{
    if (this->solutions_size > 0) {
        this->solutions = new double[this->solutions_size];
        this->solutions[0] = other_eq.solutions[0];
        if (this->solutions_size == 2) {
            this->solutions[1] = other_eq.solutions[1];
        }
    }
}

Equation& Equation::operator =(const Equation &other_eq) & {
    if (this != &other_eq) {
        this->a = other_eq.a;
        this->b = other_eq.b;
        this->c = other_eq.c;
        delete[] this->solutions;
        this->solutions = nullptr;
        this->solutions_size = other_eq.solutions_size;
        if (this->solutions_size > 0) {
            this->solutions = new double[this->solutions_size];
            this->solutions[0] = other_eq.solutions[0];
            if (this->solutions_size == 2) {
                this->solutions[1] = other_eq.solutions[1];
            }
        }
    }
    return *this;
}

Equation::Equation(Equation &&other_eq)
    : a{other_eq.a}, b{other_eq.b}, c{other_eq.c}
    , solutions{other_eq.solutions}
    , solutions_size{other_eq.solutions_size}
{
    other_eq.solutions = nullptr;
}

Equation& Equation::operator =(Equation &&other_eq) {
    if (this != &other_eq) {
        this->a = other_eq.a;
        this->b = other_eq.b;
        this->c = other_eq.c;
        this->solutions_size = other_eq.solutions_size;
        this->solutions = other_eq.solutions;
        other_eq.solutions = nullptr;
    }
    return *this;
}

Equation::~Equation() {
    delete[] this->solutions;
    this->solutions = nullptr;
}

double Equation::get_a() const {
    return this->a;
}

void Equation::set_a(double a) {
    // TODO: Throw exception std::invalid_argument (from the <stdexcept> library) in case a = 0
    this->a = a;
    this->update_solutions();
}

double Equation::get_b() const {
    return this->b;
}

void Equation::set_b(double b) {
    this->b = b;
    this->update_solutions();
}

double Equation::get_c() const {
    return this->c;
}

void Equation::set_c(double c) {
    this->c = c;
    this->update_solutions();
}

double const * Equation::get_solutions() const {
    return this->solutions;
}

std::size_t Equation::get_solutions_size() const {
    return this->solutions_size;
}

std::ostream& operator <<(std::ostream &out, const Equation &eq) {
    double abs_b, abs_c;
    std::string b_str, c_str, b_sign, c_sign;
    std::string plus_sign("+ ");
    std::string minus_sign("- ");
    std::stringstream b_stream, c_stream;
    b_stream.precision(1);
    if (eq.b != 0) {
        if (eq.b < 0) {
            b_sign = minus_sign;
            abs_b = -eq.b;
        }
        else {
            b_sign = plus_sign;
            abs_b = eq.b;
        }
        b_stream << std::fixed << abs_b;
        b_str = b_stream.str() + " X ";
    }
    c_stream.precision(1);
    if (eq.c != 0) {
        if (eq.c < 0) {
            c_sign = minus_sign;
            abs_c = -eq.c;
        }
        else {
            c_sign = plus_sign;
            abs_c = eq.c;
        }
        c_stream << std::fixed << abs_c;
        c_str = c_stream.str() + " ";
    }
    return out << std::fixed << std::setprecision(1) << eq.a << " X^2 " << b_sign << b_str << c_sign << c_str << "= 0";
//    return out << std::fixed << std::setprecision(1) << eq.a << " X^2 + " << eq.b << " X + " << eq.c << " = 0";
}

Equation operator +(const Equation &eq1, const Equation &eq2) {
    Equation addition_result = Equation{eq1.get_a() + eq2.get_a(),
                                        eq1.get_b() + eq2.get_b(),
                                        eq1.get_c() + eq2.get_c()};
    return addition_result;
}

Equation operator +(const Equation &eq, double add_to_c) {
    Equation eq_result{eq};
    eq_result.set_c(eq_result.get_c() + add_to_c);
    return eq_result;
}

Equation operator +(double add_to_c, const Equation &eq) {
    Equation eq_result{eq};
    eq_result.set_c(eq_result.get_c() + add_to_c);
    return eq_result;
}
