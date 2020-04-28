//
// Created by Netanel Albert on 28/04/2020.
//

#include <iostream>
#include <random>
#include "doctest.h"
#include "solver.hpp"

#define EPS 0.0001

using namespace solver;
using namespace std;

double myRandom(){
    static uniform_real_distribution<double> unif(-10,10);
    static default_random_engine re;
    return unif(re);
}
double myRandomMoreThan(double min){
    uniform_real_distribution<double> unif(min+1,min+10);
    default_random_engine re;
    return unif(re);
}
double myRandomLessThan(double max){
    uniform_real_distribution<double> unif(max-10,max-1);
    default_random_engine re;
    return unif(re);
}
complex<double> myCmpRandom(){
    static uniform_real_distribution<double> unif(-10,10);
    static default_random_engine re;
    return complex<double>{unif(re), unif(re)};
}

double solveLiner(double b, double c){ // b*x == c
    return c/b;
}
double solveQuadratic(double a, double b, double c) {
    return (-b+sqrt(b*b-4*a*c))/(2*a);
}
double solveQuadraticMinus(double a, double b, double c) {
    return (-b-sqrt(b*b-4*a*c))/(2*a);
}

complex<double> solveLinerCmp(complex<double> b, complex<double> c){ // b*x == c
    return c/b;
}
complex<double> solveQuadratic(complex<double> a, complex<double> b, complex<double> c) {
    return (-b+sqrt(b*b-4.0*a*c))/(2.0*a);
}
complex<double> solveQuadraticMinus(complex<double> a, complex<double> b, complex<double> c) {
    return (-b-sqrt(b*b-4.0*a*c))/(2.0*a);
}
TEST_CASE("Real variable Linear"){
    RealVariable x;
    double b1,b2,c1,c2;
    // b1*x - c1 == -c2 + x*b2
    for (u_int i = 0; i < 20; ++i) {
        b1 = myRandom(); b2 = myRandom(); c1 = myRandom(); c2 = myRandom();
        RealVariable equ = (-b1*x - c1 == -c2 + x*b2);
        double actual = solve(equ);
        double expect = solveLiner(-b1-b2, c1-c2);
        double diff = abs(actual - expect);
        CHECK(diff < EPS);
    }

    // -x*b1 + 0.5*b2*x == -c2 - c1
    for (u_int i = 0; i < 20; ++i) {
        b1 = myRandom(); b2 = myRandom(); c1 = myRandom(); c2 = myRandom();
        RealVariable equ = (-x*b1 + 0.5*b2*x == -c2 - c1);
        double actual = solve(equ);
        double expect = solveLiner(-b1+0.5*b2, -c1-c2);
        double diff = abs(actual - expect);
        CHECK(diff < EPS);
    }

    // c2-c1 == 2*x*b1 - x*b2
    for (u_int i = 0; i < 20; ++i) {
        b1 = myRandom(); b2 = myRandom(); c1 = myRandom(); c2 = myRandom();
        RealVariable equ = (c2-c1 == 2*x*b1 - x*b2);
        double actual = solve(equ);
        double expect = solveLiner(2*b1-b2, c2-c1);
        double diff = abs(actual - expect);
        CHECK(diff < EPS);
    }
}

TEST_CASE("Real variable quadratic"){
    RealVariable x;
    double a, b, c;
    // a*(x^2) + b*x + c == 0
    for (u_int i = 0; i < 20; ++i) {
        b = myRandom();
        c = myRandom();
        do{  a = myRandom();
        } while (abs(a)<EPS || b*b - 4*a*c < 0);
        RealVariable equ = (a*(x^2) + b*x + c == 0);
        double actual = solve(equ);
        double expect1 = solveQuadratic(a, b, c);
        double expect2 = solveQuadraticMinus(a, b, c);
        double diff1 = abs(actual - expect1);
        double diff2 = abs(actual - expect2);
        CHECK((diff1 < EPS || diff2 < EPS));
    }

    // x*a*x + b*x + c == 0
    for (u_int i = 0; i < 20; ++i) {
        b = myRandom();
        c = myRandom();
        do{  a = myRandom();
        } while (abs(a)<EPS || b*b - 4*a*c < 0);
        RealVariable equ = (x*a*x + b*x + c == 0);
        double actual = solve(equ);
        double expect1 = solveQuadratic(a, b, c);
        double expect2 = solveQuadraticMinus(a, b, c);
        double diff1 = abs(actual - expect1);
        double diff2 = abs(actual - expect2);
        CHECK((diff1 < EPS || diff2 < EPS));
    }


}

TEST_CASE("Real variable quadratic with no real solution"){
    RealVariable x;
    double a, b, c;
    // a*(x^2) + b*x + c == 0
    for (u_int i = 0; i < 20; ++i) {  //    b^2-4ac < 0 // b^2 < 4ac // b^2/4c < a
        c = myRandom();
        b = myRandom();
        if(c > 0)
            a = myRandomMoreThan((b*b)/(4*c));
        else
            a = myRandomLessThan((b*b)/(4*c));

        RealVariable equ = (a*(x^2) + b*x + c == 0);
        CHECK_THROWS(solve(equ));
    }
}

TEST_CASE("Complex variable Linear") {
    ComplexVariable x;
    double b1, c1;
    complex<double> b2, c2;

    // b1*x - c1 == -c2 + x*b2
    for (u_int i = 0; i < 20; ++i) {
        b1 = myRandom();
        b2 = myCmpRandom();
        c1 = myRandom();
        c2 = myCmpRandom();
        ComplexVariable equ = (-b1 * x - c1 == -c2 + x * b2);
        complex<double> actual = solve(equ);
        complex<double> expect = solveLinerCmp(-b1 - b2, c1 - c2);
        double diff = abs(actual - expect);
        CHECK(diff < EPS);
    }
}

TEST_CASE("Complex variable quadratic") {
    ComplexVariable x;
    complex<double> a, b, c;

    // a*(x^2) + b*x + c == 0
    for (u_int i = 0; i < 20; ++i) {
        b = myCmpRandom();
        c = myCmpRandom();
        do {
            a = myCmpRandom();
        } while (abs(a) < EPS);
        ComplexVariable equ = (a * (x ^ 2) + b * x + c == 0);
        complex<double> actual = solve(equ);
        complex<double> expect1 = solveQuadratic(a, b, c);
        complex<double> expect2 = solveQuadraticMinus(a, b, c);
        double diff1 = abs(actual - expect1);
        double diff2 = abs(actual - expect2);
        CHECK((diff1 < EPS || diff2 < EPS));
    }
}