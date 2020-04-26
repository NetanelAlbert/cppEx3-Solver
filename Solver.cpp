//
// Created by nati on 26/04/2020.
//

#include "Solver.hpp"
using namespace solver;

RealVariable RealVariable::operator+(const RealVariable& other) const{
    return RealVariable(_xx + other._xx, _x + other._x , _n + other._n);
}
RealVariable RealVariable::operator+(const double& n) const{
    return RealVariable(_xx, _x, _n + n);
}
RealVariable RealVariable::operator-(const RealVariable& other) const{
    return RealVariable(_xx - other._xx, _x - other._x , _n - other._n);
}
RealVariable RealVariable::operator-(const double& n) const{
    return RealVariable(_xx, _x, _n - n);
}
RealVariable solver::operator+(const double& n, const RealVariable& other){
    return  other + n;
}
RealVariable solver::operator-(const double& n, const RealVariable& other){
    return  other - n;
}

RealVariable RealVariable::operator*(const RealVariable& other) const{
    //cout << *this << "*" << other << endl;
    u_int power = 0;
    if(_xx != 0 ) power += 2;
    if(_x != 0 ) power++;
    if(other._xx != 0 ) power += 2;
    if(other._x != 0 ) power++;
    if(power > 2)
        throw runtime_error("Can handle only degree 1 or 2");

    RealVariable xcopy = *this;
    xcopy._xx = xcopy._x; xcopy._x = xcopy._n; xcopy._n = 0;

    RealVariable xxcopy = *this;
    xxcopy._xx = xxcopy._n; xxcopy._x = 0; xxcopy._n = 0;

    return ((*this)*other._n) + (xcopy*other._x)  + (xxcopy*other._xx);
}
RealVariable RealVariable::operator*(const double& n) const{
    return RealVariable(_xx * n, _x * n , _n * n);
}
RealVariable RealVariable::operator/(const RealVariable& other) const{
    if (other._xx == 0 && other._x == 0)
        return *this/other._n;
    throw runtime_error("Cant divide by variable");
}
RealVariable RealVariable::operator/(const double& n) const{
    return RealVariable(_xx / n, _x / n , _n / n);
}
RealVariable solver::operator*(const double& n, const RealVariable& other){
    return other * n;
}
RealVariable solver::operator/(const double& n, const RealVariable& other){
    // TODO return RealVariable(n)/other.; (cant return local variable, cant divide certain cases.
    //throw  runtime_error("not yet implemented");
    if (other._xx == 0 && other._x == 0){
        RealVariable(0, 0, n/other._n);
    }
    throw runtime_error("Cant divide by variable");
}
// TODO make sure that can't get 1/x, 1/x^2


RealVariable RealVariable::operator^(const int& n) const{
    switch (n){
        case 0:
            //cout << "^0" << endl;
            return  RealVariable(0,0,1);
        case 1:
            cout << "^1" << endl;
            return *this;
        case 2:
            //cout << *this << "^2" << endl;
            return (*this)*(*this);
        default:
            //cout << "^3+" << endl;
            throw runtime_error("can only handle power of 0,1 or 2");
    }
}

RealVariable RealVariable::operator==(const RealVariable& other) const{
    return *this - other;
}
RealVariable RealVariable::operator==(const double& n) const{
    return *this - n;
}
RealVariable solver::operator==(const double& n, const RealVariable& other){
    return other == n;
}

RealVariable RealVariable::operator -() const{
    return RealVariable(-_xx,-_x,-_n);
}

double RealVariable::solveMe()  const{
    //cout << "solve" << *this << endl;
    double ans;
    if(_xx == 0 && _x == 0)
        throw runtime_error("there is no variable");
    else if(_xx == 0)
        ans =  (-_n)/_x;
    else {
        double discriminant = _x * _x - 4 * _xx * _n;
        if (discriminant < 0)
            throw runtime_error("the equation has no real solution");

        ans = (-_x + sqrt(discriminant)) / (2 * _xx);
    }
    return ans;
}

ostream& solver::operator << (ostream& s, const RealVariable &var){
    s << "(";
    if(var._xx == 0 && var._x ==0 && var._n == 0) {
        s << 0;
    } else {
        if(var._xx != 0)
            s << var._xx << "x^2";
        if(var._x != 0){
            if(var._x > 0)
                s << "+";
            s << var._x << "x";
        }

        if(var._n != 0){
            if(var._n > 0)
                s << "+";
            s << var._n;
        }
    }
    s << ")";
    return s;
};
