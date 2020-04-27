//
// Created by nati on 25/04/2020.
//

#ifndef SOLVER_A_SOLVER_H
#define SOLVER_A_SOLVER_H

#include <iostream>
#include <complex>
using namespace std;
namespace solver{

    class ComplexVariable{
        complex<double> _xx;
        complex<double> _x;
        complex<double> _n;
        //void restart();
        ComplexVariable (complex<double> a, complex<double> b, complex<double> c):_xx(a), _x(b), _n(c){};
    public:
        ComplexVariable ():_xx(0), _x(1), _n(0){};
        ComplexVariable operator+(const ComplexVariable&) const;
        ComplexVariable operator+(const complex<double>&) const;
        ComplexVariable operator-(const ComplexVariable&) const;
        ComplexVariable operator-(const complex<double>&) const;
        friend ComplexVariable operator+(const complex<double>&,const ComplexVariable&);
        friend ComplexVariable operator-(const complex<double>&,const ComplexVariable&);

        ComplexVariable operator*(const ComplexVariable&) const;
        ComplexVariable operator*(const complex<double>&) const;
        ComplexVariable operator/(const ComplexVariable&) const; // TODO
        ComplexVariable operator/(const complex<double>&) const;
        friend ComplexVariable operator*(const complex<double>&, const ComplexVariable&);
        friend ComplexVariable operator/(const complex<double>&, const ComplexVariable&);
        // TODO make sure that can't get 1/x, 1/x^2

        ComplexVariable operator^(const int&) const;
        ComplexVariable operator==(const ComplexVariable&) const;
        ComplexVariable operator==(const complex<double> &) const;
        friend ComplexVariable operator==(const complex<double>&, const ComplexVariable&);

        ComplexVariable operator -() const;
        complex<double> solveMe() const;
        friend ostream& operator << (ostream& s, const ComplexVariable &var);
    };

    class RealVariable: public ComplexVariable{

    };

    inline double solve(const RealVariable& var){
        complex<double>  ans = var.solveMe();
        if(ans.imag() != 0)
            throw runtime_error("the equation has no real solution");

        return ans.real();
    };
    inline complex<double> solve(const ComplexVariable& var){
        return var.solveMe();
    };

    //complex<double> solve(ComplexVariable);
}
#endif //SOLVER_A_SOLVER_H
