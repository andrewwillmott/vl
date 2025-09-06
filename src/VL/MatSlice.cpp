/*
    File:       MatSlice.cpp

    Function:   Implements MatSlice.h

    Copyright:  Andrew Willmott
*/


#include "VL/MatSlice.h"

#include "VL/Mat.h"


// --- SliceMat Assignment Operators ------------------------------------------


const TSliceMat& TSliceMat::operator = (const TSliceMat& m) const
{
    return operator=((TConstSliceMat) m);
}

const TSliceMat& TSliceMat::operator = (TConstSliceMat m) const
{
    VL_ASSERT_MSG(rows == m.rows || m.rows == VL_REPEAT, "(SliceMat::=) Matrix rows don't match");
    for (int i = 0; i < rows; i++)
        (*this)[i] = m[i];

    return *this;
}

const TSliceMat& TSliceMat::operator = (TRefMat m) const
{
    return operator=((TConstSliceMat) (TConstRefMat) m);
}

const TSliceMat& TSliceMat::operator = (TConstRefMat m) const
{
    return operator=(TConstSliceMat(m));
}

#ifdef VL_MAT2_H
const TSliceMat& TSliceMat::operator = (const TMat2& m) const 
{ 
    return *this = TConstRefMat(m);
}

const TSliceMat& TSliceMat::operator = (const TMat3& m) const 
{ 
    return *this = TConstRefMat(m);
}

const TSliceMat& TSliceMat::operator = (const TMat4& m) const 
{ 
    return *this = TConstRefMat(m);
}
#endif

const TSliceMat& TSliceMat::operator = (VLDiag k) const
{
    MakeDiag(TElt(k));
    return *this;
}

const TSliceMat& TSliceMat::operator = (VLBlock k) const
{
    MakeBlock(TElt(k));
    return *this;
}

// --- SliceMat In-Place operators --------------------------------------------


const TSliceMat& TSliceMat::operator += (TConstSliceMat m) const
{
    VL_ASSERT_MSG(m.rows == rows || m.rows == VL_REPEAT, "(SliceMat::+=) Matrix rows don't match");

    for (int i = 0; i < rows; i++)
        (*this)[i] += m[i];

    return *this;
}

const TSliceMat& TSliceMat::operator -= (TConstSliceMat m) const
{
    VL_ASSERT_MSG(m.rows == rows || m.rows == VL_REPEAT, "(SliceMat::-=) Matrix rows don't match");

    for (int i = 0; i < rows; i++)
        (*this)[i] -= m[i];

    return *this;
}

const TSliceMat& TSliceMat::operator *= (TConstSliceMat m) const
{
    VL_ASSERT_MSG(cols == m.cols, "(SliceMat::*=) Matrix columns don't match");  // for in-place *=, m must be cols x cols.

    for (int i = 0; i < rows; i++)
        (*this)[i] = (*this)[i] * m;    // XXX have no vs *= ms

    return *this;
}

const TSliceMat& TSliceMat::operator /= (TConstSliceMat m) const
{
    VL_ASSERT_MSG(m.rows == rows || m.rows == VL_REPEAT, "(SliceMat::*=) Matrix rows don't match");

    for (int i = 0; i < rows; i++)
        (*this)[i] /= m[i];

    return *this;
}

const TSliceMat& TSliceMat::operator *= (TElt s) const
{
    for (int i = 0; i < rows; i++)
        (*this)[i] *= s;

    return *this;
}

const TSliceMat& TSliceMat::operator /= (TElt s) const
{
    for (int i = 0; i < rows; i++)
        (*this)[i] /= s;

    return *this;
}

// --- SliceMat Matrix initialisers -------------------------------------------

void TSliceMat::MakeZero() const
{
    for (int i = 0; i < rows; i++)
        (*this)[i].MakeBlock(vl_0);
}

void TSliceMat::MakeIdentity() const
{
    for (int i = 0; i < rows; i++)
        (*this)[i].MakeUnit(i);
}

void TSliceMat::MakeDiag(TElt k) const
{
    for (int i = 0; i < rows; i++)
        (*this)[i].MakeUnit(i, k);
}

void TSliceMat::MakeBlock(TElt k) const
{
    for (int i = 0; i < rows; i++)
        (*this)[i].MakeBlock(k);
}


// --- SliceMat Comparison Operators ------------------------------------------


bool operator == (TConstSliceMat m, TConstSliceMat n)
{
    VL_ASSERT_MSG(m.rows == n.rows || m.rows == VL_REPEAT || n.rows == VL_REPEAT, "(SliceMat::==) Matrix rows don't match");

    for (int i = 0; i < m.rows; i++)
        if (m[i] != n[i])
            return false;

    return true;
}


// --- SliceMat Arithmetic Operators ------------------------------------------


TMat operator + (TConstSliceMat m, TConstSliceMat n)
{
    TMat result(m);
    result += n;

    return result;
}

TMat operator - (TConstSliceMat m, TConstSliceMat n)
{
    TMat result(m);
    result -= n;

    return result;
}

TMat operator * (TConstSliceMat m, TConstSliceMat n)
{
    VL_ASSERT_MSG(m.cols == n.rows, "(SliceMat::*m) Matrix dimensions don't match");

    TMat result(m.rows, n.cols);

    for (int i = 0; i < m.rows; i++)
        result[i] = m[i] * n;

    return result;
}

TMat operator / (TConstSliceMat m, TConstSliceMat n)
{
    VL_ASSERT_MSG(m.cols == n.rows, "(SliceMat::/m) Matrix dimensions don't match");

    TMat result(m.rows, n.cols);
    result /= n;

    return result;
}

TMat operator - (TConstSliceMat m)
{
    TMat result(m);

    for (int i = 0; i < m.rows; i++)
        Negate(result[i], result[i]);

    return result;
}

TMat operator * (TConstSliceMat m, TElt s)
{
    TMat result(m);

    result *= s;

    return result;
}

TMat operator * (TElt s, TConstSliceMat m)
{
    TMat result(m);

    result *= s;

    return result;
}

TMat operator / (TConstSliceMat m, TElt s)
{
    TMat result(m);
    result /= s;

    return result;
}

TVec operator * (TConstSliceMat m, TConstSliceVec v)
{
    VL_ASSERT_MSG(m.cols == v.elts, "(SliceMat::*v) Matrix and vector sizes don't match");

    TVec result(m.rows);

    for (int i = 0; i < m.rows; i++)
        result[i] = dot(v, m[i]);

    return result;
}

TVec operator * (TConstSliceVec v, TConstSliceMat m)
{
    VL_ASSERT_MSG(v.elts == m.rows, "(SliceMat::v*m) Vector and matrix sizes don't match");

    return operator*(transpose(m), v);
}

TElt sum(TConstSliceMat m)
{
    TElt result = vl_0;

    for (int i = 0; i < m.rows; i++)
        result += sum(m[i]);

    return result;
}

TElt sumsqr(TConstSliceMat m)
{
    TElt result = TElt(vl_0);

    for (int i = 0; i < m.rows; i++)
        result += sqrlen(m[i]);

    return result;
}

#ifndef VL_NO_REAL
TElt frob(TConstSliceMat m)
{
    return sqrt(sumsqr(m));
}

TMat inv(TConstSliceMat m, TElt* determinant, TElt epsilon)
{
    TMat M(m);
    TMat M_inv(m.rows, m.cols);

    VL_EXPECT_MSG(Invert(M, M_inv, determinant, epsilon), "(inv) Matrix not invertible");

    return M_inv;
}
#endif

TMat trans(TConstSliceMat m)
{
    TMat result(transpose(m));
    return result;
}

TMat abs(TConstSliceMat m)
{
    TMat result(m);
    Absolute(result, result);
    return result;
}

TMat clamped(TConstSliceMat m, TElt fuzz)
{
    TMat result(m);
    Clamp(result, fuzz);
    return result;
}

TMat hprod(TConstSliceMat m, TConstSliceMat n)
{
    VL_ASSERT_MSG(m.rows == n.rows, "(hprod(SliceMat)) Matrix rows don't match");

    TMat result(m);
    for (int i = 0; i < m.rows; i++)
        result[i] *= n[i];

    return result;
}

TMat oprod(TConstSliceVec a, TConstSliceVec b)
{
    TMat result(a.elts, b.elts);

    for (int i = 0; i < a.elts; i++)
        result[i] = b * a[i];

    return result;
}

TMat transformed(TConstSliceMat m, TElt f(TElt))
{
    TMat result(m);

    for (int i = 0; i < m.rows; i++)
        transform(result[i], f);

    return result;
}

void transform(TSliceMat m, TElt f(TElt))
{
    for (int i = 0; i < m.rows; i++)
        transform(m[i], f);
}

TElt reduced(TConstSliceMat m, TElt f(TElt, TElt))
{
    if (m.rows == 0)
        return TElt(vl_0);
    TElt result = reduced(m[0], f);
    for (int i = 1; i < m.rows; i++)
        result = f(result, reduced(m[i], f));
    return result;
}


// --- Sub functions: SliceMat ------------------------------------------------

// TConstSliceMat

TConstSliceMat sub(TConstSliceMat m, int i, int j, int rows, int cols)
{
    VL_ASSERT_MSG(j >= 0 && cols >= 0 && j + cols <= m.cols, "(sub(SliceMat)) illegal subset of matrix");
    VL_ASSERT_MSG(i >= 0 && rows >= 0 && i + rows <= m.rows, "(sub(SliceMat)) illegal subset of matrix");

    return TConstSliceMat(rows, cols, m.rspan, m.cspan, m.data + i * m.rspan + j * m.cspan);
}

TConstSliceMat first(TConstSliceMat m, int rows, int cols)
{
    VL_ASSERT_MSG(cols >= 0 && rows >= 0 && rows <= m.rows && cols <= m.cols, "(first(SliceMat)) illegal subset of matrix");

    return TConstSliceMat(rows, cols, m.rspan, m.cspan, m.data);
}

TConstSliceMat last(TConstSliceMat m, int rows, int cols)
{
    VL_ASSERT_MSG(cols >= 0 && rows >= 0 && rows <= m.rows && cols <= m.cols, "(last(SliceMat)) illegal subset of matrix");

    return TConstSliceMat(rows, cols, m.rspan, m.cspan, m.data
            + (m.rows - rows) * m.rspan + (m.cols - cols) * m.cspan);
}

TConstSliceVec col(TConstSliceMat m, int j)
{
    VL_RANGE_MSG(j, 0, m.cols, "(col(SliceMat)) illegal column index");

    return TConstSliceVec(m.rows, m.rspan, m.data + j * m.cspan);
}

TConstSliceVec row(TConstSliceMat m, int i)
{
    VL_RANGE_MSG(i, 0, m.rows, "(row(SliceMat)) illegal row index");

    return TConstSliceVec(m.cols, m.cspan, m.data + i * m.rspan);
}

TConstSliceVec diag(TConstSliceMat m, int i)
{
    VL_RANGE_MSG(i, 1 - m.rows, m.cols, "(row(Mat)) illegal row index");

    if (i < 0)
        return TConstSliceVec(vl_min<int>(m.rows + i, m.cols), m.rspan + m.cspan, m.data - i * m.rspan);
    else
        return TConstSliceVec(vl_min<int>(m.cols - i, m.rows), m.rspan + m.cspan, m.data + i * m.cspan);
}

TConstSliceMat transpose(TConstSliceMat m)
{
    return TConstSliceMat(m.cols, m.rows, m.cspan, m.rspan, m.data);
}

TConstSliceMat repeat(const TElt& elt, int rows, int cols)
{
    return TConstSliceMat(rows, cols, 0, 0, &elt);
}

TConstSliceMat repeat(TConstSliceVec v, int rows)
{
    return TConstSliceMat(rows, v.elts, 0, v.span, v.data);
}


// TSliceMat

TSliceMat sub(TSliceMat m, int i, int j, int rows, int cols)
{
    VL_ASSERT_MSG(j >= 0 && cols >= 0 && j + cols <= m.cols, "(sub(SliceMat)) illegal subset of matrix");
    VL_ASSERT_MSG(i >= 0 && rows >= 0 && i + rows <= m.rows, "(sub(SliceMat)) illegal subset of matrix");

    return TSliceMat(rows, cols, m.rspan, m.cspan, m.data + i * m.rspan + j * m.cspan);
}

TSliceMat first(TSliceMat m, int rows, int cols)
{
    VL_ASSERT_MSG(cols >= 0 && rows >= 0 && rows <= m.rows && cols <= m.cols, "(first(SliceMat)) illegal subset of matrix");

    return TSliceMat(rows, cols, m.rspan, m.cspan, m.data);
}

TSliceMat last(TSliceMat m, int rows, int cols)
{
    VL_ASSERT_MSG(cols >= 0 && rows >= 0 && rows <= m.rows && cols <= m.cols, "(last(SliceMat)) illegal subset of matrix");

    return TSliceMat(rows, cols, m.rspan, m.cspan, m.data
            + (m.rows - rows) * m.rspan + (m.cols - cols) * m.cspan);
}

TSliceVec col(TSliceMat m, int j)
{
    VL_RANGE_MSG(j, 0, m.cols, "(col(SliceMat)) illegal column index");

    return TSliceVec(m.rows, m.rspan, m.data + j * m.cspan);
}

TSliceVec row(TSliceMat m, int i)
{
    VL_RANGE_MSG(i, 0, m.rows, "(row(SliceMat)) illegal row index");

    return TSliceVec(m.cols, m.cspan, m.data + i * m.rspan);
}

TSliceVec diag(TSliceMat m, int i)
{
    VL_RANGE_MSG(i, 1 - m.rows, m.cols, "(row(Mat)) illegal row index");

    if (i < 0)
        return TSliceVec(vl_min<int>(m.rows + i, m.cols), m.rspan + m.cspan, m.data - i * m.rspan);
    else
        return TSliceVec(vl_min<int>(m.cols - i, m.rows), m.rspan + m.cspan, m.data + i * m.cspan);
}

TSliceMat transpose(TSliceMat m)
{
    return TSliceMat(m.cols, m.rows, m.cspan, m.rspan, m.data);
}

TConstSliceMat repeat(TSliceVec v, int rows)
{
    return TConstSliceMat(rows, v.elts, 0, v.span, v.data);
}
