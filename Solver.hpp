//
// Created by nati on 25/04/2020.
//

#ifndef SOLVER_A_SOLVER_H
#define SOLVER_A_SOLVER_H

#include <iostream>
#include <complex>
using namespace std;
namespace solver{
    class RealVariable{
        double _xx;
        double _x;
        double _n;
        void restart();
        RealVariable (double a, double b, double c):_xx(a), _x(b), _n(c){};
    public:
        RealVariable ():_xx(0), _x(1), _n(0){};
        RealVariable operator+(const RealVariable&) const;
        RealVariable operator+(const double&) const;
        RealVariable operator-(const RealVariable&) const;
        RealVariable operator-(const double&) const;
        friend RealVariable operator+(const double&,const RealVariable&);
        friend RealVariable operator-(const double&,const RealVariable&);
        // friend RealVariable& operator-(RealVariable&); TODO -x

        RealVariable operator*(const RealVariable&) const;
        RealVariable operator*(const double&) const;
        RealVariable operator/(const RealVariable&) const; // TODO
        RealVariable operator/(const double&) const;
        friend RealVariable operator*(const double&, const RealVariable&);
        friend RealVariable operator/(const double&, const RealVariable&);
        // TODO make sure that can't get 1/x, 1/x^2

        RealVariable operator^(const int&) const;
        RealVariable operator==(const RealVariable&) const;
        RealVariable operator==(const double &) const;
        friend RealVariable operator==(const double&, const RealVariable&);

        RealVariable operator -() const;
        double solveMe() const;
        friend ostream& operator << (ostream& s, const RealVariable &var);
    };
    class ComplexVariable{

    };
//    class solve{
//        friend double operator ()(const RealVariable& var){
//            return var.solveMe();
//        };
//    };
    inline double solve(const RealVariable& var){
        return var.solveMe();
    };

    //complex<double> solve(ComplexVariable);
}
#endif //SOLVER_A_SOLVER_H
