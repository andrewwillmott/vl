/*
    File:       Solve.cpp

    Function:   Implements linear system solvers

    Copyright:  Andrew Willmott
*/


#include "VL/Solve.hpp"

namespace
{
    const int kMaxSolveSteps = 10000;
}


/** Solves Ax = b via gaussian elimination.

    Each iteration modifies the current approximate solution x.
    Omega controls overrelaxation: omega = 1 gives Gauss-Seidel,
    omega somewhere beteen 1 and 2 gives the fastest convergence.

    x is the initial guess on input, and solution vector on output.

    If steps is zero, the routine iterates until the residual is
    less than epsilon. Otherwise, it performs at most *steps
    iterations, and returns the actual number of iterations performed
    in *steps.

    Returns approximate squared length of residual vector: |Ax-b|^2.

    [Strang, "Introduction to Applied Mathematics", 1986, p. 407]
*/

TMElt SolveOverRelax
(
    TConstRefMat A,
    TRefVec      x,
    TConstRefVec b,
    TMElt        epsilon,
    TMElt        omega,
    int*         steps
)
{
    VL_ASSERT_MSG(is_square(A), "(SolveOverRelax) Matrix not square");
    int jMax;

    if (steps)
        jMax = *steps;
    else
        jMax = kMaxSolveSteps;

    int j = 0;
    TMElt error;

    do
    {
        error = 0.0;

        for (int i = 0; i < A.Rows(); i++)
        {
            TMElt sum = b[i] - dot(A[i], x);
            TMElt diagonal = A(i, i);
            sum += diagonal * x[i];
            // I.e., sum = b[i] - (A[i] * x - A[i,i])
            TMElt xOld = x[i];

            if (diagonal == TMElt(0))
                VL_WARNING("(SolveOverRelax) diagonal element = 0");
            else if (omega == TMElt(1.0))  // Gauss-Seidel
                x[i] = TElt(sum / diagonal);
            else                    // Overrelax
                x[i] = TElt(lerp(xOld, sum / diagonal, omega));

            sum -= diagonal * xOld;
            error += sqr(sum);
        }
        j++;
    }
    while (error > epsilon && j < jMax);

    if (steps)
        *steps = j;

    return error;
}


/**
    Solve Ax = b by conjugate gradient method, for symmetric, positive
    definite A.

    x is the initial guess on input, and solution vector on output.

    Returns squared length of residual vector.

    If A is not symmetric, this will solve the system (A + At)x/2 = b

    [Strang, "Introduction to Applied Mathematics", 1986, p. 422]
*/

TMElt SolveConjGrad
(
    TConstRefMat A,         // Solve Ax = b.
    TRefVec      x,
    TConstRefVec b,
    TElt         epsilon,   // how low should we go?
    int*         steps      // iterations to converge.
)
{
    VL_ASSERT_MSG(is_square(A), "(SolveConjGrad) Matrix not square");

    TVec r(A.Rows());       // Residual vector, b - Ax
    TVec t(A.Rows());       // temp!

    // r = b - A * x;
    Multiply(A, x, t);
    Subtract(b, t, r);

    TElt rSqrLen = sqrlen(r);
    int i = 0;

    if (rSqrLen > epsilon)
    {
        TVec d(r);

        int iMax;
        if (steps)
            iMax = *steps;
        else
            iMax = kMaxSolveSteps;

        while (i < iMax)
        {
            i++;
            // t = A * d;
            Multiply(A, d, t);
            TElt u = dot(d, t);

            if (len(u) < TElt(1e-12))
            {
                VL_WARNING("(SolveConjGrad) d'Ad = 0");
                break;
            }

            TElt alpha = rSqrLen / u;  // How far should we go?
            // x += alpha * d;         // Take a step along direction d
            MultiplyAccum(d,  alpha, x);

            if (i & 0x3F)
                // r -= alpha * t;
                MultiplyAccum(t, -alpha, r);
            else
            {
                // For stability, correct r every 64th iteration
                // r = b - A * x;
                Multiply(A, x, t);
                Subtract(b, t, r);
            }

            TElt rSqrLenOld = rSqrLen;
            rSqrLen = sqrlen(r);

            if (rSqrLen <= epsilon)
                break;                  // Converged! Let's get out of here

            TElt beta = rSqrLen / rSqrLenOld;
            // d = r + beta * d;        //  Change direction
            d *= beta;
            d += r;
        }
    }

    if (steps)
        *steps = i;

    return rSqrLen;
}

TMElt SolveConjGrad_AtA
(
    TConstRefMat A,         // Solve AtA x = At b.
    TRefVec      x,
    TConstRefVec b,
    TElt         epsilon,   // how low should we go?
    int*         steps      // iterations to converge.
)
{
    TVec r (A.Cols());      // Residual vector, Atb - AtAx
    TVec t (A.Cols());      // temp
    TVec t2(A.Rows());      // temp

    // r = Atb;
    Multiply(b, A, r);
    // r -= At A * x;
    Multiply(A, x, t2);
    Multiply(t2, A, t);     // tmp_t A = trans(A_t tmp)
    Subtract(r, t, r);

    TElt rSqrLen = sqrlen(r);

    int i = 0;

    if (rSqrLen > epsilon)  // If we haven't already converged...
    {
        TVec d(r);

        int iMax;
        if (steps)
            iMax = *steps;
        else
            iMax = kMaxSolveSteps;

        while (i < iMax)
        {
            i++;
            // t = AtA * d;
            Multiply(A, d, t2);
            Multiply(t2, A, t);
            TElt u = dot(d, t);

            if (u == 0.0)
            {
                VL_WARNING("(SolveConjGrad) d'Ad = 0");
                break;
            }

            TElt alpha = rSqrLen / u;  // How far should we go?
            // x += alpha * d;         // Take a step along direction d
            // r -= alpha * t;
            MultiplyAccum(d,  alpha, x);
            MultiplyAccum(t, -alpha, r);

            TElt rSqrLenOld = rSqrLen;
            rSqrLen = sqrlen(r);

            if (rSqrLen <= epsilon)
                break;                  // Converged! Let's get out of here

            TElt beta = rSqrLen / rSqrLenOld;
            // d = r + beta * d;        //  Change direction
            Multiply(d, beta, d);
            Add(d, r, d);
        }
    }

    if (steps)
        *steps = i;

    return rSqrLen;
}
