/*
    File:       Factor.cpp

    Function:   Implements some matrix factorizations: SVD, QR

    Copyright:  Andrew Willmott
*/

#include "VL/Factor.h"

// We must #ifndef all calls that don't mix TMat + TVec with VL_MIXED

#ifndef VL_MIXED
TMElt QRFactorization(TRefMat A, TMat& Q, TMat& R)
// Factor A into an orthogonal matrix Q and an upper-triangular matrix R.
// Destroys A.
{
    VL_ASSERT_MSG(A.Rows() >= A.Cols(), "matrix must have rows >= cols");

    Q.SetSize(A.Rows(), A.Cols());
    R.SetSize(A.Cols(), A.Cols());

    return QRFactorization(A, (TRefMat) Q, (TRefMat) R);
}

TMElt QRFactorization(TRefMat A, TRefMat Q, TRefMat R)
// Factor A into an orthogonal matrix Q and an upper-triangular matrix R.
// Destroys A.
{
    VL_ASSERT_MSG(A.Rows() >= A.Cols(), "matrix must have rows >= cols");
    VL_ASSERT_MSG(Q.Rows() == A.Rows() && Q.Cols() == A.Cols(), "Q size mismatch");
    VL_ASSERT_MSG(R.Rows() == A.Cols() && R.Cols() == A.Cols(), "R size mismatch");

    TMat Qs(A.Rows(), A.Rows(), vl_I);

    R = vl_0;

    TMElt normAcc = vl_0;

    // for each column
    for (int i = 0; i < A.Cols(); i++)
    {
        // apply householder
        TMElt diagElt = LeftHouseholder(A, Qs, i);

        // copy over row i of A to R
        R(i, i) = diagElt;

        int j = A.Cols() - i - 1;

        if (j != 0)
            last(R[i], j) = last(A[i], j);

        normAcc = vl_max(normAcc, abs(diagElt));
    }

    Q = sub(Qs, 0, 0, A.Rows(), A.Cols());

    return normAcc;
}

void SVDFactorization(TRefMat A, TMat& U, TMat& V, TMVec& diagonal)
{
    diagonal.SetSize(A.Cols());

    U.SetSize(A.Rows(), A.Cols());
    V.SetSize(A.Cols(), A.Cols());

    SVDFactorization(A, TRefMat(U), TRefMat(V), TRefVec(diagonal));
}

void SVDFactorization(TRefMat A, TRefMat U, TRefMat V, TMRefVec diagonal)
{
    TVec superDiag(A.Cols() - 1);

    VL_ASSERT(diagonal.Elts() == A.Cols());
    VL_ASSERT(same_size(U, A));
    VL_ASSERT(is_square(V) && V.Cols() == A.Cols());

    // Find the bidiagonal matrix, and then eliminate the
    // elements above the diagonal to get the final
    // result.
    Bidiagonalize(A, U, V, diagonal, superDiag);
    Diagonalize  (         diagonal, superDiag, U, V);
}
#endif

#ifndef VL_MIXED
bool Cholesky(TConstRefMat A, TRefMat L)
// Factors symmetric positive definite matrix 'A' into L Lt, where
// L is lower triangular.
{
    for (int i = 0, n = A.Elts(); i < n; i++)
        for (int j = i; j < n; j++)
        {
            TMElt sum = A(i, j);

            for (int k = i - 1; k >= 0; k--)
                sum -= L(i, k) * L(j, k);

            if (i == j)
            {
                if (sum <= 0)
                    return false;

                L(i, i) = sqrt(sum);
            }
            else
            {
                L(j, i) = sum / L(i, i);
                L(i, j) = 0;
            }
        }

    return true;
}
#endif

void BacksolveLLt(TConstRefMat L, TRefVec x, TConstRefVec b)
// Given 'L' from a Cholesky decomposition, solve L Lt x = b.
{
    VL_ASSERT(is_square(L));
    VL_ASSERT(b.Elts() == L.Rows());
    VL_ASSERT(x.Elts() == L.Rows());

    const int n = L.Rows();

    // Solve L x' = b
    for (int i = 0; i < n; i++)
    {
        TMElt sum = 0;

        for (int j = 0; j < i; j++)
            sum += L(i, j) * x[j];

        x[i] = TElt((b[i] - sum) / L(i, i));
    }

    // Solve Lt x = x'
    for (int i = n - 1; i >= 0; i--)
    {
        TMElt sum = 0;

        for (int j = i + 1; j < n; j++)
            sum += L(j, i) * x[j];

        x[i] = TElt((x[i] - sum) / L(i, i));
    }
}

#ifndef VL_MIXED
TMat GramSchmidt(TConstRefMat M)
{
   TMat V;
   V.SetSize(M);

    for (int j = 0, nr = V.Rows(); j < nr; j++)
    {
        V[j] = M[j];

        for (int k = 0; k < j; k++)
            V[j] -= (dot(V[k], M[j]) / dot(V[k], V[k])) * V[k];
    }

    return V;
}

TMat ModifiedGramSchmidt(TConstRefMat M)
{
    TMat V(M);
    TMat Q;
    Q.SetSize(M);

    for (int j = 0, nr = V.Rows(); j < nr; j++)
    {
        Q[j] = V[j] / sqrlen(V[j]);

        for (int k = j; k < V.Rows(); k++)
            V[k] -= dot(V[k], Q[j]) * Q[j];
    }

    return Q;
}

bool GaussianEliminate(TRefMat A, TMElt epsilon)
{
    int nr = A.Rows();
    int nc = A.Cols();

    for (int ir = 0, ic = 0; ic < nc && ir < nr; ic++)
    {
        // Eliminate in column ic, below diag
        TMElt max = TMElt(-1);

        int jr = ir;
        for (int kr = ir; kr < nr; kr++)  // Find pivot
        {
            TMElt a = len(A(kr, ic));

            if (a > max)
            {
                max = a;
                jr = kr;
            }
        }

        if (max < epsilon)
            continue;

        if (jr != ir)
        {
            // Swap rows ir and jr
            for (int kc = ic; kc < nc; kc++)
            {
                TMElt aik = A(ir, kc);
                TMElt ajk = A(jr, kc);

                A(ir, kc) = ajk;
                A(jr, kc) = aik;
            }
        }

        TMElt pivot = A(ir, ic);

        if (len(pivot) < epsilon)
            return false;

        for (int jr = ir + 1; jr < nr; jr++)
        {
            TMElt t = A(jr, ic) / pivot;

            A(jr, ic) = 0;

            for (int kc = ic + 1; kc < nc; kc++) // Subtract scaled row ir from row jr
                A(jr, kc) -= A(ir, kc) * t;
        }

        ir++;
    }

    return true;
}

void BackSubstitute(TRefMat A, TMElt epsilon)
{
    int nc = A.Cols();
    int nr = A.Rows();

    for (int ir = nr - 1; ir >= 0; ir--)
    {
        // Eliminate in column ic, above diag

        // find pivot (leading non-zero) if it exists
        for (int ic = 0; ic < nc; ic++)
        {
            TMElt pivot = A(ir, ic);

            if (len(pivot) < epsilon)
                continue;

            // First normalise this row so pivot = 1
            A(ir, ic) = 1;
            for (int kc = ic + 1; kc < nc; kc++)     // Only do elements to the right of the pivot
                A(ir, kc) /= pivot;

            // Now use to zero column above it
            for (int jr = 0; jr < ir; jr++)
            {
                TMElt t = A(jr, ic);           // We're gonna zero this guy
                A(jr, ic) = 0;

                for (int kc = ic + 1; kc < nc; kc++)     // Subtract scaled row i from row j
                    A(jr, kc) -= A(ir, kc) * t;
            }

            break;
        }
    }
}

void RowEchelonForm(TRefMat A, TMElt epsilon)
{
    GaussianEliminate(A, epsilon);
}

void ReducedRowEchelonForm(TRefMat A, TMElt epsilon)
{
    GaussianEliminate(A, epsilon);
    BackSubstitute   (A, epsilon);
}

/*
    NOTE

    Householder transformations zero all elements of a vector v apart
    from the first element.

        H = I - 2uut
            where ||u||^2 = 1
            HtH = HHt = HH = I
            - it's a reflection, so we would expect HH = I

        Hv = [c 0 0 0 0]
            where c = +/- ||v||
            and u = f(v - [c 0 0..])
            where f = 1/sqrt(2c(c - v[0]))

        For convenience, we can write
            Hv = v - 2u(u.v)
        or
            Hv = v - 2w(w.v)/g
            where g = c(c - v[0])
            w = v - [c 0 0..]
*/

TMElt LeftHouseholder(TRefMat A, TRefMat U, const int i)
// Zeroes out those elements below the diagonal in column i by use of a
// Householder transformation matrix H: A' = HA. U is replaced with UH,
// so that U'A' = UH HA = UA
{
    VL_ASSERT_MSG(i < A.Rows(), "bad i");

    // scale factor is the sum of abs of elements below and including
    // the diagonal in column i
    TMElt scale = 0;
    for (int k = i; k < A.Rows(); k++)
        scale += abs(A[k][i]);

    // return if nothing to eliminate...
    if (scale == 0)
        return scale;

    // scale the column, find sum of squares
    TMElt vSqrLen = 0;

    for (int k = i; k < A.Rows(); k++)
    {
        A[k][i] /= scale;
        vSqrLen += sqr(A[k][i]);
    }

    TMElt oldDiag = A[i][i];          // v[0]
    TMElt newDiag = sqrt(vSqrLen);    // c
    if (oldDiag > 0)
        newDiag = -newDiag;

    TMElt g = vSqrLen - oldDiag * newDiag;  // c(c - v0)

    // replace column i of A with w
    A[i][i] = oldDiag - newDiag;

    // Apply H to A by transforming remaining columns of A
    for (int j = i + 1; j < A.Cols(); j++)
    {
        // find dot product of the columns [i:i..m] (w) and [j:i..m]
        TMElt dotProd = 0;
        for (int k = i; k < A.Rows(); k++)
            dotProd += A[k][j] * A[k][i];

        dotProd /= g;

        // calculate A's new column j
        for (int k = i; k < A.Rows(); k++)
            A[k][j] -= A[k][i] * dotProd;
    }

    // Apply H to rows of U
    for (int j = 0; j < A.Rows(); j++)
    {
        // vH = v - (v.w)w / g

        TMElt dotProd = 0;
        for (int k = i; k < A.Rows(); k++)
            dotProd += A[k][i] * U[j][k];

        dotProd /= g;

        for (int k = i; k < A.Rows(); k++)
            U[j][k] -=  A[k][i] * dotProd;
    }

    return newDiag * scale;
}

TMElt RightHouseholder(TRefMat A, TRefMat V, const int i)
// Zeroes out those elements to the right of the super-diagonal in row i
// by use of a Householder transformation matrix H: A' = AH. V is
// replaced with VH, so that A'V't = AH (HV)t = AVt
{
    VL_ASSERT_MSG(i < A.Cols() - 1, "bad i");

    // scale factor is the sum of abs of elements to the right of the
    // diagonal in row i
    TMElt scale = 0;
    for (int k = i + 1; k < A.Cols(); k++)
        scale += abs(A[i][k]);

    // return if nothing to eliminate...
    if (scale == 0)
        return scale;

    TMElt vSqrLen = 0;
    for (int k = i + 1; k < A.Cols(); k++)
    {
        A[i][k] /= scale;
        vSqrLen += sqr(A[i][k]);
    }

    TMElt oldSuperDiag = A[i][i + 1];
    TMElt newSuperDiag = sqrt(vSqrLen);
    if (oldSuperDiag > 0)
        newSuperDiag = -newSuperDiag;

    TMElt g = oldSuperDiag * newSuperDiag - vSqrLen;
    A[i][i + 1] = oldSuperDiag - newSuperDiag;

    // transform the remaining rows below i
    for (int j = i + 1; j < A.Rows(); j++)
    {
        TMElt dotProd = 0;
        for (int k = i + 1; k < A.Cols(); k++)
            dotProd += A[i][k] * A[j][k];

        dotProd /= g;

        for (int k = i + 1; k < A.Cols(); k++)
            A[j][k] += A[i][k] * dotProd;
    }

    // Accumulate the transform in V
    for (int j = 1; j < A.Cols(); j++)
    {
        TMElt dotProd = 0;
        for (int k = i + 1; k < A.Cols(); k++)
            dotProd += A[i][k] * V[j][k];

        dotProd /= g;

        for (int k = i + 1; k < A.Cols(); k++)
            V[j][k] += A[i][k] * dotProd;
    }

    // return new super-diagonal element A[i][i+1]
    return newSuperDiag * scale;
}
#endif

void Bidiagonalize(TRefMat A, TRefMat U, TRefMat V, TRefVec diagonal, TRefVec superDiag)
// bidiagonalize matrix A by using householder transformations to eliminate
// columns below the diagonal and rows to the right of the super-diagonal.
// A is modified, and the diagonal and superDiag set.
{
    VL_ASSERT_MSG(A.Rows() >= A.Cols(), "A must have rows >= cols");
    VL_ASSERT_MSG(diagonal .Elts() == A.Cols()    , "diagonal size mismatch");
    VL_ASSERT_MSG(superDiag.Elts() == A.Cols() - 1, "super diagonal size mismatch");
    VL_ASSERT_MSG(U.Rows() == A.Rows() && U.Cols() == A.Cols(), "U size mismatch");
    VL_ASSERT_MSG(V.Rows() == A.Cols() && V.Cols() == A.Cols(), "V size mismatch");

    V = vl_I;

    TMat Us(A.Rows(), A.Rows(), vl_I);

    for (int i = 0; i < A.Cols(); i++)
    {
        diagonal[i] = TElt(LeftHouseholder(A, Us, i));

        if (i < A.Cols() - 1)
            superDiag[i] = TElt(RightHouseholder(A, V, i));
    }

    U = sub(Us, 0, 0, A.Rows(), A.Cols());
}


/*
    NOTE

    Givens rotations perform a rotation in a 2D plane. Can be
    used to zero an entry of a matrix.

    We pick axes i and j, then form G such that it is basically
    I with entries:

        i    j
    i:  c   -s
         ...
    j:  s    c


    s^2 + c^2 = 1
    inv(G) = Gt

    A' = GA
        modifies rows i and j only:
            row'[i] = c * row[i] - s * row[j]
            row'[j] = c * row[j] + s * row[i]
        can force:
        A'[i][j] = 0
            if c * A[i][j] - s * A[j][j] = 0
            if c = A[j][j], s = A[i][j]
            must normalize to retain identity:
                norm = sqrt(c^2 + s^2), c /= norm, s /= norm
            A'[j][j] = c * (norm * c) + s * (norm * s) = norm
        A'[i][i] = 0
            if c * A[i][i] - s * A[j][i] = 0
            if c = A[j][i], s = A[i][i]

    A' = AGt


*/

namespace
{
    void RotateRight(TRefMat U, const int i, const int j, const TMElt c, const TMElt s)
    // rotate U by the given Givens rotation: U' = UGt
    // where G is defined as above
    {
        TMVec temp(col(U, i));

        col(U, i) =  c * col(U, i) - s * col(U, j);
        col(U, j) =  c * col(U, j) + s * temp;
    }

    void ClearSuperEntry
    (
        TRefVec diagonal,
        TRefVec superDiag,
        TRefMat U,
        const int k,
        const int l,
        const TMElt precision
    )
    // We have a zero diagonal element at diag[l]. This means we can zero
    // out the super-diagonal entry to its right with a series of rotations.
    // Each rotation clears an entry (starting with the original
    // super-diagonal entry) but creates another entry immediately to its
    // right which must in turn be zeroed. Eventually we run off the end of
    // the matrix, and the process terminates.
    {
        // We zero the superdiagonal element l by using the row immediately
        // below it in a Givens rotation. Unfortunately, the superdiagonal
        // in this row in turn creates another entry A[l][l+2]. We must keep
        // applying rotations in the plane of the axes l and l + n to keep
        // zeroing each new entry created until we reach the right hand side
        // of the matrix.

        // initialise: start with f being the original super diagonal entry
        // we're eliminating
        TMElt f = superDiag[l];
        superDiag[l] = TElt(0);

        // at each stage, f = A[l][i], rotate in the l/i plane
        for (int i = l + 1; true; i++)
        {
            if (abs(f) + precision == precision)  // if f is zero, we don't have to eliminate further
                break;

            // to eliminate f at each stage we pick s = -f, c = di
            TMElt s = -f;
            TMElt c = diagonal[i];

            // normalize
            TMElt norm = sqrt(sqr(c) + sqr(s));
            c /= norm;
            s /= norm;

            // apply inverse rotation to U
            RotateRight(U, i, l, c, s);

            // do the rotation, zeroing f and creating f' immediately to its right
            diagonal[i] = TElt(norm); // di' = c * di - s * f = norm

            if (i == k)               // done?
                break;

            f = s * superDiag[i];   // f'  = c * 0  + s * superdiag[i]
            superDiag[i] = TElt(superDiag[i] * c);      // ei' = c * ei - s * 0
        }
    }

    int FindSplit(TRefVec diagonal, TRefVec superDiag, TRefMat U, const int k, const TMElt prec)
    // Check for a zero entry along the superdiagonal; if we find one, we can
    // QR iterate on two separate matrices above and below it.
    // If there is a zero on the *diagonal*, we can call ClearSuperEntry to
    // zero out the corresponding superdiagonal entry to its right.
    {
        for (int l = k - 1; l >= 0; l--)
            if (superDiag[l] + prec == prec)
                // can split here
                return l + 1;
            else if (diagonal[l] + prec == prec)
            {
                // can create a split here
                ClearSuperEntry(diagonal, superDiag, U, k, l, prec);
                return l + 1;
            }

        return 0;
    }
}

void Diagonalize(TRefVec diagonal, TRefVec superDiag, TRefMat U, TRefMat V)
// Diagonalise the bidiagonal matrix A = (diagonal, superDiag), accumulating
// transforms into U on the left and Vt on the right.
//
// diag(A) = diagonal and diag(A, 1) = superDiag, that is to say, diagonal[0]
// is A[0][0], and superDiag[0] is A[0][1].
{
    // work out a good precision value
    TMElt prec = abs(diagonal[0]);

    for (int i = 1; i < diagonal.Elts(); i++)
        prec = vl_max(prec, TMElt(abs(diagonal[i]) + abs(superDiag[i - 1])));

    // work our way up from the bottom of the matrix
    for (int k = diagonal.Elts() - 1; k >= 0; k--)
    {
        while (1)
        {
            // if there's a split, start from there rather than A[0][0]
            int l = FindSplit(diagonal, superDiag, U, k, prec);

            // are we done?
            if (l == k)     // last super-diag entry must be zero -- what we wanted.
                break;

            // QR iterate over the sub-matrix of A, A[l..k][l..k], until
            // we've nuked super diagonal entry A[k - 1][k]

            // For extra stability, we shift the QR computation.  We
            // want the shift to be as close as possible to the largest
            // eigenvalue, which of course we don't know yet... so we
            // take the eigenvalues of the 2x2 matrix at the bottom of
            // our window of A, and use those.

            TMElt  e0 = (k > 1) ? superDiag[k - 2] : 0;
            TMElt  e1 =           superDiag[k - 1];

            TMElt  d1 = diagonal[k - 1];
            TMElt  d2 = diagonal[k];
            TMElt  dl = diagonal[l];

            //      d0  e0
            //          d1  e1
            //   k:         d2

            TMElt shift = (d1 - d2) * (d1 + d2) + (e0 - e1) * (e0 + e1);

            shift /= TMElt(2 * e1 * d1);
            shift += TMElt(sign(shift) * sqrt(sqr(shift) + 1));
            shift = ((dl - d2) * (dl + d2) + e1 * (d1 / shift - e1)) / dl;

            d1 = dl;    // d1 == A[i - 1][i - 1]: initialise it to that
            e1 = superDiag[l];
            // the first rotation is the QR-shifted one. After that, we
            // are continually eliminating below-diagonal and
            // above-super diagonal elements created by the previous
            // rotation, until we hit the bottom-right of the matrix and
            // we have a bidiagonal matrix again. The QR-shift will
            // ensure that the new matrix has smaller super-diagonal
            // elements, however.
            TMElt g0 = e1;
            e0 = shift;

            for (int i = l + 1; true; i++)
            {
                // rotate in plane of axes i - 1, i:
                //    d0  e0  g0      d0  e0'  0
                //        d1  e1   ->     d1'  e1'
                //  i:        d2          f1   d2'
                // we are rotating on the right, and so affecting columns
                d2 = diagonal[i];

                // eliminate g0 using e0 (except for the first iteration,
                // where e0 and g0 would be off the top of the matrix, and
                // we're performing the QR-shift.)
                TMElt sin_th = g0;
                TMElt cos_th = e0;

                TMElt norm = sqrt(sqr(cos_th) + sqr(sin_th));
                cos_th /= norm;
                sin_th /= norm;

                // perform the rotation
                if (i > 1)
                    superDiag[i - 2] = TElt(norm);  // e0' = cos_th * e0 + sin_th * g0

                TMElt d1n =  cos_th * d1 + sin_th * e1;
                TMElt e1n = -sin_th * d1 + cos_th * e1;

                TMElt f1;
                f1 = sin_th * d2;  // f1  = c *  0 + s * d2
                d2 = cos_th * d2;  // d2' = c * d2 + s * 0

                // Accumulate rotation in V
                RotateRight(V, i, i - 1, cos_th, sin_th);

                // in eliminating g0, we've created f1: eet must be
                // destroyed

                // rotate in plane of axes i - 1, i:
                //      d0  e0             d0   e0
                //      d1  e1      ->     d1'  e1'  g1'
                //  i:  f1  d2  e2         0    d2'  e2'
                // we are rotating on the left, and so affecting rows

                // standard rotation to eliminate the f1 we've just created
                TMElt cos_ph = d1n;
                TMElt sin_ph = f1;

                norm = sqrt(sqr(cos_ph) + sqr(sin_ph));

                if (norm == 0)
                {
                    // rotation angle is arbitrary
                    cos_ph = cos_th;
                    sin_ph = sin_th;
                }
                else
                {
                    cos_ph /= norm;
                    sin_ph /= norm;
                }

                // as usual, for the elimination pair, f1 = 0, d1 = norm
                diagonal[i - 1] = TElt(norm);  // d1'

                // rotate e1 and d2
                e1 =  cos_ph * e1n + sin_ph * d2;
                d2 = -sin_ph * e1n + cos_ph * d2;

                // Accumulate rotation into U
                RotateRight(U, i, i - 1, cos_ph, sin_ph);

                if (i == k)
                    break;

                // rotate g1 and e2
                TMElt e2 = cos_ph * superDiag[i];
                TMElt g1 = sin_ph * superDiag[i];

                d1 = d2;  // the new d1 will be the old d2
                e0 = e1;
                e1 = e2;
                g0 = g1;
            }

            if (l > 0)
                superDiag[l - 1] = TElt(0);  // Supposed to be eliminated by now

            superDiag[k - 1] = TElt(e1);  // write in the last superdiagonal
            diagonal [k    ] = TElt(d2);  // and diagonal
        }

        // Force singular value to be +ve if needs be
        if (diagonal[k] < 0)
        {
            diagonal[k] = -diagonal[k];
            // flip the corresponding row of Vt to balance out
            col(V, k) = -col(V, k);
        }
    }
}
