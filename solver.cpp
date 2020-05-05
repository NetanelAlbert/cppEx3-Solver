//
// Created by Netanel Albert on 26/04/2020.
//

#ifndef SOLVER_A_SOLVER_CPP
#define SOLVER_A_SOLVER_CPP

#include "solver.hpp"

#define TEMPL_TYPE template <typename coefficient_type>
using namespace solver;
using namespace std;

TEMPL_TYPE
solver::VAR operator+(const VAR& v1,const VAR& v2){
    return VAR(v1._a + v2._a, v1._b + v2._b , v1._c + v2._c);
}

TEMPL_TYPE
solver::VAR operator/(const VAR& v1, const VAR& other){
    if (other._a == 0.0 && other._b == 0.0){
        return VAR(v1._a / other._c, v1._b / other._c, v1._c / other._c);
    }
    throw runtime_error("Cant divide by variable");
}
TEMPL_TYPE
VAR operator-(const VAR& v1,const VAR& v2){
    return VAR(v1._a - v2._a, v1._b - v2._b , v1._c - v2._c);
}
TEMPL_TYPE
VAR operator*(const VAR& v1,const VAR& v2){
    u_int power = 0;
    if(v1._a != 0.0 ) power += 2;
    if(v1._b != 0.0 ) power++;
    if(v2._a != 0.0 ) power += 2;
    if(v2._b != 0.0 ) power++;
    if(power > 2)
        throw runtime_error("Can handle only degree 1 or 2");

    VAR xcopy(v1._b, v1._c, 0);
    VAR xxcopy(v1._c, 0, 0);
    return (v1*v2._c) + (xcopy*v2._b)  + (xxcopy*v2._a);
}
TEMPL_TYPE
VAR operator==(const VAR& v1,const VAR& v2){
    return v1-v2;
}
TEMPL_TYPE
VAR VAR::operator^(const int& n) const{
    switch (n){
        case 0:
            return  VAR(0,0,1);
        case 1:
            cout << "^1" << endl;
            return *this;
        case 2:
            return (*this)*(*this);
        default:
            throw runtime_error("can only handle power of 0,1 or 2");
    }
}
TEMPL_TYPE
VAR VAR::operator -() const{
    return VAR(-_a, -_b, -_c);
}
TEMPL_TYPE
complex<double> VAR::compareToZero()  const{
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

//template class solver::Variable<complex<double>>;
//template class solver::Variable<double>;

#endif //SOLVER_A_SOLVER_CPP