//
// Created by nati on 25/04/2020.
//

#ifndef SOLVER_A_SOLVER_H
#define SOLVER_A_SOLVER_H
namespace solver{
//    Class solve{
//
//    public:
//        operator()()
//    };
    solve(RealVariable);
    solve(ComplexVariable);
    Class RealVariable{
        double _x;
        double _xx;
        double _n;
        RealVariable(double n):_x(0), _xx(0), _n(n){};
    public:
        RealVariable ():_x(0), _xx(0), _n(0){};
        operator+(RealVariable);
        operator+(double);
        operator-(RealVariable);
        operator-(double);
    };
    Class ComplexVariable{

    };
}
#endif //SOLVER_A_SOLVER_H
