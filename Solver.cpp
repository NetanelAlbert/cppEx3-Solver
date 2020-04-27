//
// Created by nati on 26/04/2020.
//


#include "Solver.hpp"
#define TEMPL_TYPE template <typename coe_type, typename class_type>
using namespace solver;
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator+(const class_type& other) const{
    return class_type(_xx + other._xx, _x + other._x , _n + other._n);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator+(const coe_type& n) const{
    return class_type(_xx, _x, _n + n);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator-(const class_type& other) const{
    return class_type(_xx - other._xx, _x - other._x , _n - other._n);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator-(const coe_type& n) const{
    return class_type(_xx, _x, _n - n);
}

TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator*(const class_type& other) const{
    //cout << *this << "*" << other << endl;
    u_int power = 0;
    if(_xx != 0.0 ) power += 2;
    if(_x != 0.0 ) power++;
    if(other._xx != 0.0 ) power += 2;
    if(other._x != 0.0 ) power++;
    if(power > 2)
        throw runtime_error("Can handle only degree 1 or 2");

    Variable<coe_type, class_type> xcopy =  *this;
    xcopy._xx = xcopy._x; xcopy._x = xcopy._n; xcopy._n = 0;

    Variable<coe_type, class_type> xxcopy = *this;
    xxcopy._xx = xxcopy._n; xxcopy._x = 0; xxcopy._n = 0;

    return ((*this)*other._n) + (xcopy*other._x)  + (xxcopy*other._xx);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator*(const coe_type& n) const{
    return class_type(_xx * n, _x * n , _n * n);
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator/(const class_type& other) const{
    if (other._xx == 0.0 && other._x == 0.0)
        return *this/other._n;
    throw runtime_error("Cant divide by variable");
}
TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator/(const coe_type& n) const{
    return class_type(_xx / n, _x / n , _n / n);
}
//// TODO make sure that can't get 1/x, 1/x^2

TEMPL_TYPE
class_type Variable<coe_type, class_type>::operator^(const int& n) const{
    switch (n){
        case 0:
            //cout << "^0" << endl;
            return  class_type(0,0,1);
        case 1:
            cout << "^1" << endl;
            return *this+0;
        case 2:
            //cout << *this << "^2" << endl;
            return (*this+0)*(*this+0);
        default:
            //cout << "^3+" << endl;
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
    return class_type(-_xx,-_x,-_n);
}
TEMPL_TYPE
complex<double> Variable<coe_type, class_type>::solveMe()  const{
    //cout << "solve" << *this << endl;
    complex<double> ans;
    if(_xx == 0.0 && _x == 0.0)
        throw runtime_error("there is no variable");
    else if(_xx == 0.0)
        ans =  (-_n)/_x;
    else {
        complex<double> discriminant = _x * _x - 4.0 * _xx * _n;
        //if (discriminant < 0)
          //  throw runtime_error("the equation has no real solution");

        ans = (sqrt(discriminant) - _x) / (2.0 * _xx);
    }
    return ans;
}

template class solver::Variable<complex<double>, ComplexVariable>;
template class solver::Variable<double, RealVariable>;

