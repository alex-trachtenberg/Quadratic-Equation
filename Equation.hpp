#include <cstddef>
#include <iosfwd>

class Equation 
{
private:
    double m_a;
    double m_b;
    double m_c;
    double *m_solutions;
    std::size_t m_solutions_size;

    void update_solutions();

public:
    Equation(double, double, double);
    Equation(const Equation&);
    Equation& operator =(const Equation&) &;
    Equation(Equation&&) noexcept;
    Equation& operator =(Equation&&) noexcept;
    ~Equation ();
    double get_a() const;
    void set_a(double);
    double get_b() const;
    void set_b(double);
    double get_c() const;
    void set_c(double);
    double const * get_solutions() const;
    std::size_t get_solutions_size() const;
    friend std::ostream& operator <<(std::ostream&, const Equation&);
};

Equation operator +(const Equation&, const Equation&);
Equation operator +(const Equation&, double);
Equation operator +(double, const Equation&);
