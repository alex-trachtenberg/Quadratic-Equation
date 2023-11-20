#include <cstddef>
#include <iosfwd>

class Equation 
{
private:
    double a;
    double b;
    double c;
    double *solutions;
    size_t solutions_size;

    void update_solutions();

public:
    Equation (double a, double b, double c);
    Equation (const Equation &other_eq);
    Equation& operator=(const Equation &other_eq);
    ~Equation ();
    double get_a() const;
    void set_a(double a);
    double get_b() const;
    void set_b(double b);
    double get_c() const;
    void set_c(double c);
    double const * get_solutions();
    std::size_t get_solutions_size();
    friend std::ostream& operator <<(
        std::ostream &out, const Equation &eq);
};
