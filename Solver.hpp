//
// Created by Netanel Albert on 25/04/2020.
//

#ifndef SOLVER_A_SOLVER_H
#define SOLVER_A_SOLVER_H

#include <iostream>
#include <complex>
using namespace std;
namespace solver{
    /**
     * This template class represents a quadratic expression of the form 'a*x^2 + b*x +c'
     * The default initialise creat just '1*x'
     *
     * @tparam coefficient_type - in my implementation - double or complex<double>
     * @tparam class_type - the derived class.
     */
    template <typename coefficient_type, class class_type>
    class Variable{
        coefficient_type _a;
        coefficient_type _b;
        coefficient_type _c;
    protected:
        Variable (coefficient_type a, coefficient_type b, coefficient_type c): _a(a), _b(b), _c(c){};
    public:
        Variable (): _a(0), _b(1), _c(0){};
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
        class_type operator/(const class_type&) const;
        class_type operator/(const coefficient_type&) const;
        friend class_type operator*(const coefficient_type& n,const class_type& other){
            return other * n;
        }
        friend class_type operator/(const coefficient_type& n, const class_type& other){
            if (other._a == 0.0 && other._b == 0.0){
                return class_type(0, 0, n/other._c);
            }
            throw runtime_error("Cant divide by variable");
        }


        class_type operator^(const int&) const;
        class_type operator==(const class_type&) const;
        class_type operator==(const coefficient_type &) const;
        friend class_type operator==(const coefficient_type& n, const class_type& other) {
            return other == n;
        }

        class_type operator -() const;
        complex<double> compareToZero() const;
    };

    class ComplexVariable: public Variable<complex<double>, ComplexVariable>{
    public:
        ComplexVariable() : Variable<complex<double>, ComplexVariable>() {};
        ComplexVariable (complex<double> a, complex<double> b, complex<double> c): Variable<complex<double>, ComplexVariable>(a,b,c) {};
    };

    class RealVariable: public Variable<double, RealVariable>{
    public:
        RealVariable (): Variable<double, RealVariable>() {};
        RealVariable (double a, double b, double c): Variable<double, RealVariable>(a,b,c) {};
    };

    inline double solve(const RealVariable& var){
        complex<double>  ans = var.compareToZero();
        if(ans.imag() != 0)
            throw runtime_error("the equation has no real solution");

        return ans.real();
    };
    inline complex<double> solve(const ComplexVariable& var){
        return var.compareToZero();
    };

}

#endif //SOLVER_A_SOLVER_H