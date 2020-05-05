//
// Created by Netanel Albert on 25/04/2020.
//

#ifndef SOLVER_A_SOLVER_H
#define SOLVER_A_SOLVER_H

#include <iostream>
#include <complex>
#define VAR Variable<coefficient_type>

using namespace std;

namespace solver{
    /**
     * This template class represents a quadratic expression of the form 'a*x^2 + b*x +c'
     * The default initialise creat just '1*x'
     *
     * @tparam coefficient_type - in my implementation - double or complex<double>
     */
    template <typename coefficient_type>
    class Variable{
        coefficient_type _a;
        coefficient_type _b;
        coefficient_type _c;
    protected:
        Variable<coefficient_type>(coefficient_type a, coefficient_type b, coefficient_type c): _a(a), _b(b), _c(c){};
    public:
        Variable<coefficient_type> (): _a(0), _b(1), _c(0){};
        Variable<coefficient_type> (const coefficient_type& c): _a(0), _b(0), _c(c){};
        Variable<coefficient_type> (const int& c): _a(0), _b(0), _c(1.0*c){};

        friend VAR operator+(const VAR& n,const VAR& other);
        friend VAR operator-(const VAR& n,const VAR& other);
        VAR operator -() const;

        friend VAR operator*(const VAR& n,const VAR& other);
        friend VAR operator/(const VAR& n, const VAR& other);

        VAR operator^(const int&) const;
        friend VAR operator==(const VAR&, const VAR&);
        complex<double> compareToZero() const;
    };

    using RealVariable = Variable<double>;
    using ComplexVariable = Variable<complex<double>>;

    inline double solve(const RealVariable& var){
        complex<double>  ans = var.compareToZero();
        if(ans.imag() != 0)
            throw runtime_error("the equation has no real solution");

        return ans.real();
    }
    inline complex<double> solve(const ComplexVariable& var){
        return var.compareToZero();
    }

}

#endif //SOLVER_A_SOLVER_H

#include "solver.cpp"