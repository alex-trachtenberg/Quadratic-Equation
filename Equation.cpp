#include <iomanip>    // for std::setprecision
#include <cmath>      // for std::sqrt function
#include <stdexcept>  // for std::invalid_argument exception throwing

#include "Equation.hpp"

/*  Private method that updates the m_solutions & m_solutions_size fields
    according to m_a, m_b, m_c values. If the new calculated discriminant
    changes the current m_solutions_size field, then the method deletes its
    dynamically alocated array in m_solutions field and creates a new one
    with the correct size, according to the updated m_solutions_size field.  */
void Equation::update_solutions() {
    double discriminant = m_b * m_b - 4 * m_a * m_c;
    if (discriminant > 0) {
        if (m_solutions_size < 2) {
            if (m_solutions != nullptr) {      // current m_solutions_size == 1 & m_solutions points to an array of length one.
                delete[] m_solutions;
            }
            m_solutions = new double[2];
            m_solutions_size = 2;
        }     
        m_solutions[0] = (-m_b + sqrt(discriminant)) / (2 * m_a);
        m_solutions[1] = (-m_b - sqrt(discriminant)) / (2 * m_a);
    }
    else if (discriminant == 0) {
        if (m_solutions_size != 1) {
            if (m_solutions != nullptr) {      // current m_solutions_size == 2 & m_solutions points to an array of length two.
                delete[] m_solutions;
            }
            m_solutions = new double[1];
            m_solutions_size = 1;
        }
        m_solutions[0] = -(m_b) / (2 * m_a);
    }
    else {  // case when discriminant < 0
        if (m_solutions_size > 0) {
            delete[] m_solutions;
            m_solutions = nullptr;
            m_solutions_size = 0;
        }
    }
}

Equation::Equation(double a, double b, double c)
    : m_a{a}, m_b{b}, m_c{c}
    , m_solutions{nullptr}
    , m_solutions_size{0}
{
    if (m_a == 0)
        throw std::invalid_argument{"Invalid \"a\" argument of Equation, can't be equal to zero"};
    else
        this->update_solutions();
}

Equation::Equation(const Equation &other_eq)
    : m_a{other_eq.m_a}, m_b{other_eq.m_b}, m_c{other_eq.m_c}
    , m_solutions{nullptr}
    , m_solutions_size{other_eq.m_solutions_size}
{
    if (m_solutions_size > 0) {
        m_solutions = new double[m_solutions_size];
        m_solutions[0] = other_eq.m_solutions[0];
        if (m_solutions_size == 2) {
            m_solutions[1] = other_eq.m_solutions[1];
        }
    }
}

Equation& Equation::operator =(const Equation &other_eq) & {
    if (this != &other_eq) {
        m_a = other_eq.m_a;
        m_b = other_eq.m_b;
        m_c = other_eq.m_c;
        delete[] m_solutions;
        m_solutions = nullptr;
        m_solutions_size = other_eq.m_solutions_size;
        if (m_solutions_size > 0) {
            m_solutions = new double[m_solutions_size];
            m_solutions[0] = other_eq.m_solutions[0];
            if (m_solutions_size == 2) {
                m_solutions[1] = other_eq.m_solutions[1];
            }
        }
    }
    return *this;
}

Equation::Equation(Equation &&other_eq) noexcept
    : m_a{other_eq.m_a}, m_b{other_eq.m_b}, m_c{other_eq.m_c}
    , m_solutions{other_eq.m_solutions}
    , m_solutions_size{other_eq.m_solutions_size}
{
    other_eq.m_solutions = nullptr;
}

Equation& Equation::operator =(Equation &&other_eq) noexcept {
    if (this != &other_eq) {
        m_a = other_eq.m_a;
        m_b = other_eq.m_b;
        m_c = other_eq.m_c;
        m_solutions_size = other_eq.m_solutions_size;
        m_solutions = other_eq.m_solutions;
        other_eq.m_solutions = nullptr;
    }
    return *this;
}

Equation::~Equation() {
    delete[] m_solutions;
    m_solutions = nullptr;
}

double Equation::get_a() const {
    return m_a;
}

void Equation::set_a(double a) {
    if (a == 0)
        throw std::invalid_argument{"Invalid \"a\" argument of Equation, can't be equal to zero"};
    else
        this->update_solutions();
}

double Equation::get_b() const {
    return m_b;
}

void Equation::set_b(double b) {
    m_b = b;
    this->update_solutions();
}

double Equation::get_c() const {
    return m_c;
}

void Equation::set_c(double c) {
    m_c = c;
    this->update_solutions();
}

double const * Equation::get_solutions() const {
    return m_solutions;
}

std::size_t Equation::get_solutions_size() const {
    return m_solutions_size;
}

/*  This friend funcion overloads the << operator, it allows "pushing" an Equation
    object to an output stream with the same as though you called the following
    printf format "%.1f X^2 + %.1f X + %.1f = 0". If b or c arguments are missing in
    the Equation object, they are not printed. If b or c arguments are negative, the
    plus signs in the format are changed to minus.*/
std::ostream& operator <<(std::ostream &out, const Equation &eq) {
    double abs_b = 0;
    double abs_c = 0;
    std::string b_str, c_str, b_sign, c_sign;
    std::string plus_sign("+ ");
    std::string minus_sign("- ");
    std::stringstream b_stream, c_stream;
    b_stream.precision(1);
    if (eq.m_b != 0) {
        if (eq.m_b < 0) {
            b_sign = minus_sign;
            abs_b = -eq.m_b;
        }
        else {
            b_sign = plus_sign;
            abs_b = eq.m_b;
        }
        b_stream << std::fixed << abs_b;
        b_str = b_stream.str() + " X ";
    }
    c_stream.precision(1);
    if (eq.m_c != 0) {
        if (eq.m_c < 0) {
            c_sign = minus_sign;
            abs_c = -eq.m_c;
        }
        else {
            c_sign = plus_sign;
            abs_c = eq.m_c;
        }
        c_stream << std::fixed << abs_c;
        c_str = c_stream.str() + " ";
    }
    return out << std::fixed << std::setprecision(1) << eq.m_a << " X^2 " << b_sign << b_str << c_sign << c_str << "= 0";
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
