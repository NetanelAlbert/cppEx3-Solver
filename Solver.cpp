//
// Created by Netanel Albert on 26/04/2020.
//


#include "Solver.hpp"
#define TEMPL_TYPE template <typename coe_type, typename class_type>
using namespace solver;
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator+(const class_type& other) const{
    return class_type(_a + other._a, _b + other._b , _c + other._c);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator+(const coe_type& n) const{
    return class_type(_a, _b, _c + n);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator-(const class_type& other) const{
    return class_type(_a - other._a, _b - other._b , _c - other._c);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator-(const coe_type& n) const{
    return class_type(_a, _b, _c - n);
}

TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator*(const class_type& other) const{
    u_int power = 0;
    if(_a != 0.0 ) power += 2;
    if(_b != 0.0 ) power++;
    if(other._a != 0.0 ) power += 2;
    if(other._b != 0.0 ) power++;
    if(power > 2)
        throw runtime_error("Can handle only degree 1 or 2");

    Variable<coe_type, class_type> xcopy =  *this;
    xcopy._a = xcopy._b; xcopy._b = xcopy._c; xcopy._c = 0;

    Variable<coe_type, class_type> xxcopy = *this;
    xxcopy._a = xxcopy._c; xxcopy._b = 0; xxcopy._c = 0;

    return ((*this)*other._c) + (xcopy*other._b)  + (xxcopy*other._a);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator*(const coe_type& n) const{
    return class_type(_a * n, _b * n , _c * n);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator/(const class_type& other) const{
    if (other._a == 0.0 && other._b == 0.0)
        return *this/other._c;
    throw runtime_error("Cant divide by variable");
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator/(const coe_type& n) const{
    return class_type(_a / n, _b / n , _c / n);
}
//// TODO make sure that can't get 1/x, 1/x^2

TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator^(const int& n) const{
    switch (n){
        case 0:
            return  class_type(0,0,1);
        case 1:
            cout << "^1" << endl;
            return *this+0;
        case 2:
            return (*this+0)*(*this+0);
        default:
            throw runtime_error("can only handle power of 0,1 or 2");
    }
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator==(const class_type& other) const{
    return *this - other;
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator==(const coe_type& n) const{
    return *this - n;
}

TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator -() const{
    return class_type(-_a, -_b, -_c);
}
TEMPL_TYPE
complex<double> Variable<coe_type, class_type>::compareToZero()  const{
    //cout << "solve" << *this << endl;
    complex<double> ans;
    if(_a == 0.0 && _b == 0.0)
        throw runtime_error("there is no variable");
    else if(_a == 0.0)
        ans = (-_c) / _b;
    else {
        complex<double> discriminant = _b * _b - 4.0 * _a * _c;
        ans = (-_b + sqrt(discriminant)) / (2.0 * _a);
    }
    return ans;
}

template class solver::Variable<complex<double>, ComplexVariable>;
template class solver::Variable<double, RealVariable>;

