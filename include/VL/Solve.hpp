/*
    File:       Solve.hpp

    Function:   Contains routines for solving a system of linear equations.
                Includes the overrelaxation (a more general version of
                Gauss Seidel) and conjugate gradient methods, for both
                normal and sparse matrices.

    Copyright:  Andrew Willmott
 */

#ifndef VL_SOLVE_H
#define VL_SOLVE_H

TMElt SolveOverRelax
(
    TConstRefMat A,
    TRefVec      x,
    TConstRefVec b,
    TMElt        epsilon,
    TMElt        omega = TMElt(1),
    int*         steps = 0
);
// Solves A x = b, if specified, *steps contains max iterations, and actual #
// of iterations is returned. omega controls overrelaxation.

TMElt SolveConjGrad    (TConstRefMat A, TRefVec x, TConstRefVec b, TElt epsilon, int* steps = 0);
// Solves A x = b. If specified, *steps contains max iterations, and actual #
// of iterations is returned.
TMElt SolveConjGrad_AtA(TConstRefMat A, TRefVec x, TConstRefVec b, TElt epsilon, int* steps = 0);
// Solves AtA x = At b, without having to form AtA

#endif
