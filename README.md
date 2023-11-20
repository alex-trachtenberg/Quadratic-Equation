# Quadratic-Equation

Create a class/struct called Equation. It will represent a Quadratic Equation of the form:
A * X2 + B * X + C = 0

It will have the following private fields:
a - double representing the A part.
A should never be zero! If there's an attempt to construct an Equation with a=0 or set
its value later to zero, the code should throw std::invalid_argument (from the <stdexcept
> library). (be careful of constructor memory leaking if the exception is caught)
b - double representing the B part.
c - double representing the C part.
solutions - double pointer - points to an array of two doubles (dynamically allocated).
solutions_size - std::size_t - represents the size of solutions (0,1,2).

It will have the following public methods:
accessors get_* and set_* for a,b & c (i.e. get_a() which returns the value of a,
set_a(double) which sets the value of a etc..)
when setting a,b or c, the values of solutions and soultions_size needs to be updated
accordingly (more details below. hint: you can make a private update_solutions method and call it when required).
std::size_t get_solutions_size(); - returns solutions_size.
double const * get_solutions(); - returns solutions.

It will have the following constructor:
Equation(double a, double b, double c);
It will follow the rule of Three & the rule of Five.
(You may employ the idioms teached in class to simplify the process)
It will support the following operations (need to be const-correct!):
Allow "pushing" an equation object to an output stream with the << operator. the format will be the same as though you called the following printf format:
"%.1f X^2 + %.1f X + %.1f = 0"
the first "%.1f" specifier will show the value of a.
the second "%.1f" specifier will show the value of b.
the third "%.1f" specifier will show the value of c.
Do not actually use printf functions to write to a stream. You can utilize the std::fixed and std::setprecision(1) manipulators instead. Restoring the old stream state post-printing is not required (Note: no need to worry about changing addition-sign with subtraction-sign for negative B and C).
(Note: no need to remove " + BX" if B is zero nor will you need to remove "+ C" if C is zero).

addition of two equations:
Equation(1,2,3) + Equation(40,50,60)
//result: temporary Equation object with a=41, b=52,c=63
addition of an Equation and a double. the operation will modify the c part of the result:
Equation(1,2,3) + 40.0
//result: temporary Equation object with a=1,b=2,c=43
Addition of a double and an Equation (double is the left operand):
40.0 + Equation(1,2,3)
//result: temporary Equation object with a=1,b=2,c=43

(NOTE: if an addition will cause an equation to have a with a value of zero it should throw std::invalid_argument as was explained above, it will be up to the user-code to avoid adding two equations that will cause this or to catch the exception).