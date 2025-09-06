/*
    File:       Factor.h

    Function:   Provides routines for factoring a matrix:

                + SVD decomposes A into three matrices, A = U D Vt, where:

                    U is m x n, and orthogonal

                    D is n x n, and is diagonal; its elements are the
                    square roots of the eigenvalues of AtA.

                    V is n x n, and orthogonal.

                + QR factors A into A = Q R, where R is upper-triangular,
                and Q is orthogonal.

    Copyright:  Andrew Willmott
*/

#ifndef VL_FACTOR_H
#define VL_FACTOR_H

// --- Factorization routines--------------------------------------------------

TMElt QRFactorization(TRefMat A, TMat&   Q, TMat&   R);
TMElt QRFactorization(TRefMat A, TRefMat Q, TRefMat R);
// Factor A into an orthogonal matrix Q and an upper-triangular matrix R.
// Destroys A.

void  SVDFactorization(TRefMat A, TMat&   U, TMat&   V, TMVec&   diagonal);
void  SVDFactorization(TRefMat A, TRefMat U, TRefMat V, TMRefVec diagonal);
// Factor A into U D V^t. Destroys A.

bool  Cholesky(TConstRefMat A, TRefMat L);
// Factors symmetric positive definite matrix 'A' into L Lt, where
// L is lower triangular.
void  BacksolveLLt(TConstRefMat L, TRefVec x, TConstRefVec b);
// Given 'L' from a Cholesky decomposition, solve L Lt x = b.

// --- Utility routines--------------------------------------------------------

TMat  GramSchmidt        (TConstRefMat M);  // Orthogonalises rows of 'M' by applying the Gram-Schmidt process
TMat  ModifiedGramSchmidt(TConstRefMat M);  // Modified Gram-Schmidt -- more numerically stable, uses more memory.

bool  GaussianEliminate(TRefMat A, TMElt epsilon);
// Perform Gaussian elimination on A.
void  BackSubstitute   (TRefMat A, TMElt epsilon);
// Perform back substitution on a matrix in row echelon form, transforming it into reduced row echelon form.

void  RowEchelonForm       (TRefMat A, TMElt epsilon);
// Synonym for GaussianEliminate
void  ReducedRowEchelonForm(TRefMat A, TMElt epsilon);
// Transforms A into reduced row echelon form (often abbreviated rref).
// The number of non-zero rows is the rank of the matrix.
// The non-zero rows form the row space of the matrix.
// The pivot columns (those containing a leading one) form the column space.

TMElt LeftHouseholder (TRefMat A, TRefMat U, int i); // Apply Householder xform for column i on left of A
TMElt RightHouseholder(TRefMat A, TRefMat V, int i); // Apply Householder xform for row i on right of A

void  Bidiagonalize(TRefMat A, TRefMat U, TRefMat V, TRefVec diagonal, TRefVec superDiag);  // bidiagonalize 'A' using Householder transforms
void  Diagonalize  (                                 TRefVec diagonal, TRefVec superDiag, TRefMat U, TRefMat V);  // Diagonalise diagonal/superDiagonal 

#endif
