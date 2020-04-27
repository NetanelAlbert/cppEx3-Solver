//
// Created by nati on 25/04/2020.
//

#ifndef SOLVER_A_SOLVER_H
#define SOLVER_A_SOLVER_H

#include <iostream>
#include <complex>
using namespace std;
namespace solver{
    template <typename coefficient_type, typename class_type>
    class Variable{

        coefficient_type _xx;
        coefficient_type _x;
        coefficient_type _n;
    protected:
        Variable (coefficient_type a, coefficient_type b, coefficient_type c):_xx(a), _x(b), _n(c){};
    public:
        Variable ():_xx(0), _x(1), _n(0){};
        class_type operator+(const class_type&) const;
        class_type operator+(const coefficient_type&) const;
        class_type operator-(const class_type&) const;
        class_type operator-(const coefficient_type&) const;
        friend class_type operator+(const coefficient_type& n,const class_type& other){
            return other + n;
        }
        friend class_type operator-(const coefficient_type& n,const class_type& other){
            return other - n;
        }

        class_type operator*(const class_type&) const;
        class_type operator*(const coefficient_type&) const;
        class_type operator/(const class_type&) const; // TODO
        class_type operator/(const coefficient_type&) const;
        friend class_type operator*(const coefficient_type& n,const class_type& other){
            return other * n;
        }
        friend class_type operator/(const coefficient_type& n, const class_type& other){
            // TODO return class_type<coe_type>(n)/other.; (cant return local class_type, cant divide certain cases.
            //throw  runtime_error("not yet implemented");
            if (other._xx == 0.0 && other._x == 0.0){
                return class_type(0, 0, n/other._n);
            }
            throw runtime_error("Cant divide by class_type");
        }
    // TODO make sure that can't get 1/x, 1/x^2


        class_type operator^(const int&) const;
        class_type operator==(const class_type&) const;
        class_type operator==(const coefficient_type &) const;
        friend class_type operator==(const coefficient_type& n, const class_type& other) {
            return other == n;
        }

        class_type operator -() const;
        complex<double> solveMe() const;
    };

    class ComplexVariable: public Variable<complex<double>, ComplexVariable>{
    public:
        ComplexVariable() : Variable<complex<double>, ComplexVariable>() {};
        ComplexVariable (complex<double> a, complex<double> b, complex<double> c): Variable<complex<double>, ComplexVariable>(a,b,c) {};
//        ComplexVariable& operator=(const Variable<complex<double>, ComplexVariable> var){
//            //_xx = var._xx;
//            return *this;
//        }
    };

    class RealVariable: public Variable<double, RealVariable>{
    public:
        RealVariable (): Variable<double, RealVariable>() {};
        RealVariable (double a, double b, double c): Variable<double, RealVariable>(a,b,c) {};
//        RealVariable& operator=(const Variable<double, RealVariable> var){
//            //_xx = var._xx;
//            return *this;
//        }
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

}

#endif //SOLVER_A_SOLVER_H

//#include "SolverCode.hpp"
