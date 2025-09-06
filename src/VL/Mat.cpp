/*
    File:       Mat.cpp

    Function:   Implements Mat.h

    Copyright:  Andrew Willmott
*/

#include "VL/Mat.h"


// --- RefMat Assignment Operators --------------------------------------------

const TRefMat& TRefMat::operator = (const TRefMat& m) const
{
    VL_ASSERT_MSG(same_size(*this, m), "(Mat::=) Matrix dimensions don't match");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = m.data[i];

    return *this;
}

const TRefMat& TRefMat::operator = (TConstRefMat m) const
{
    VL_ASSERT_MSG(same_size(*this, m), "(Mat::=) Matrix dimensions don't match");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = m.data[i];

    return *this;
}

const TRefMat& TRefMat::operator = (TConstSliceMat m) const
{
    VL_ASSERT_MSG(same_size(gen(*this), m), "(Mat::=) Matrix dimensions don't match");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = m.data[i];

    return *this;
}

// --- RefMat In-Place Operators ----------------------------------------------

const TRefMat& TRefMat::operator += (TConstRefMat m) const
{
    Add(*this, m, *this);
    return *this;
}

const TRefMat& TRefMat::operator -= (TConstRefMat m) const
{
    Subtract(*this, m, *this);
    return *this;
}

const TRefMat& TRefMat::operator *= (TConstRefMat m) const
{
    Multiply(*this, m, *this);
    return *this;
}

const TRefMat& TRefMat::operator /= (TConstRefMat m) const
{
    Divide(*this, m, *this);
    return *this;
}

const TRefMat& TRefMat::operator *= (TElt s) const
{
    Multiply(*this, s, *this);
    return *this;
}

const TRefMat& TRefMat::operator /= (TElt s) const
{
    Divide(*this, s, *this);
    return *this;
}

// --- RefMat Matrix initialisers ---------------------------------------------

void TRefMat::MakeZero() const
{
    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = vl_zero;
}

void TRefMat::MakeIdentity() const
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            (*this)(i, j) = (i == j) ? TElt(vl_one) : TElt(vl_zero);
}

void TRefMat::MakeDiag(TConstRefVec d) const
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            (*this)(i, j) = (i == j) ? d[i] : vl_zero;
}

void TRefMat::MakeDiag(TElt k) const
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            (*this)(i, j) = (i == j) ? k : vl_zero;
}

void TRefMat::MakeBlock(TElt k) const
{
    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = k;
}


// --- Mat Constructors & Destructors -----------------------------------------

TMat::TMat(const TMat& m) : TRefMat(m.rows, m.cols, VL_NEW TElt[m.rows * m.cols])
{
    VL_ASSERT_MSG(data != 0, "(Mat) Out of memory");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = m.data[i];
}

TMat::TMat(TMat&& m) : TRefMat(m)
{
    m.data = 0;
}

TMat::TMat(int r, int c, double elt0, ...) : TRefMat(r, c, VL_NEW TElt[r * c])
// The double is hardwired here because it is the only type that will work
// with var args and C++ real numbers.
{
    VL_ASSERT_MSG(data != 0, "(Mat) Out of memory");
    VL_ASSERT_MSG(rows > 0 && cols > 0, "(Mat) illegal matrix size");

    va_list ap;
    va_start(ap, elt0);

    data[0] = TElt(elt0);

    for (int i = 1; i < cols; i++)
        (*this)[0].data[i] = TElt(va_arg(ap, double));

    for (int i = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            (*this)(i, j) = TElt(va_arg(ap, double));

    va_end(ap);
}

TMat::TMat(std::initializer_list<TVec> l) : TRefMat(int(l.size()), 0, nullptr)
{
    for (const TVec& v : l)
        if (cols < v.Elts())
            cols = v.Elts();

    data = new TElt[rows * cols];

    std::initializer_list<TVec>::const_iterator it = l.begin();

    for (int i = 0; i < rows; i++, ++it)
    {
        first((*this)[i], it->Elts()) = *it;

        // Zero out to the right if necessary
        last ((*this)[i], cols - it->Elts()) = vl_0;
    }
}

TMat::TMat(TConstRefMat m) : TRefMat(m.rows, m.cols, VL_NEW TElt[m.rows * m.cols])
{
    VL_ASSERT_MSG(data != 0, "(Mat) Out of memory");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = m.data[i];
}

TMat::TMat(TConstSliceMat m) : TRefMat(m.rows, m.cols, VL_NEW TElt[m.rows * m.cols])
{
    VL_ASSERT_MSG(data != 0, "(Mat) Out of memory");

    for (int i = 0; i < rows; i++)
        (*this)[i] = m[i];
}

// --- Mat Assignment Operators -----------------------------------------------


TMat& TMat::operator = (const TMat& m)
{
    SetSize(m);

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = m.data[i];

    return *this;
}

TMat& TMat::operator = (TMat&& m)
{
    if (this != &m)
    {
        VL_DELETE[] data;
        data = m.data;
        cols = m.cols;
        rows = m.rows;
        m.data = 0;
    }

    return *this;
}


// --- Mat Sizing -------------------------------------------------------------

void TMat::SetSize(int r, int c)
{
    VL_ASSERT_MSG(r > 0 && c > 0, "(Mat::SetSize) Illegal size.");

    int oldElts = Elts();
    int newElts = r * c;

    cols = c;
    rows = r;

    // Don't reallocate if we already have enough storage
    if (newElts <= oldElts)
        return;

    // Otherwise, delete old storage and reallocate
    VL_DELETE[] data;
    data = VL_NEW TElt[newElts];
}


// --- ConstMat Constructors & Destructors ------------------------------------

TConstMat::TConstMat(const TConstMat& m) : TConstRefMat(m.rows, m.cols, VL_NEW TElt[m.rows * m.cols])
{
    VL_ASSERT_MSG(data != 0, "(ConstMat) Out of memory");

    TRefMat& self = (TRefMat&) *this;

    for (int i = 0, n = Elts(); i < n; i++)
        self.data[i] = m.data[i];
}

TConstMat::TConstMat(TConstMat&& m) : TConstRefMat(m)
{
    m.data = 0;
}

TConstMat::TConstMat(int r, int c, double elt0, ...) : TConstRefMat(r, c, VL_NEW TElt[r * c])
// The double is hardwired here because it is the only type that will work
// with var args and C++ real numbers.
{
    VL_ASSERT_MSG(data != 0, "(ConstMat) Out of memory");
    VL_ASSERT_MSG(rows > 0 && cols > 0, "(ConstMat) illegal matrix size");

    va_list ap;
    va_start(ap, elt0);

    TRefMat& self = (TRefMat&) *this;
    self.data[0] = TElt(elt0);

    for (int i = 1; i < cols; i++)
        self[0].data[i] = TElt(va_arg(ap, double));

    for (int i = 1; i < rows; i++)
        for (int j = 0; j < cols; j++)
            self(i, j) = TElt(va_arg(ap, double));

    va_end(ap);
}

TConstMat::TConstMat(std::initializer_list<TConstVec> l) : TConstRefMat(int(l.size()), 0, nullptr)
{
    TRefMat& self = (TRefMat&) *this;

    for (const TConstVec& v : l)
        if (cols < v.Elts())
            cols = v.Elts();

    self.data = new TElt[rows * cols];

    std::initializer_list<TConstVec>::const_iterator it = l.begin();

    for (int i = 0; i < rows; i++, ++it)
    {
        first(self[i], it->Elts()) = *it;

        // Zero out to the right if necessary
        last (self[i], cols - it->Elts()) = vl_0;
    }
}

TConstMat::TConstMat(TConstRefMat m) : TConstRefMat(m.rows, m.cols, VL_NEW TElt[m.rows * m.cols])
{
    VL_ASSERT_MSG(data != 0, "(ConstMat) Out of memory");

    TRefMat& self = (TRefMat&) *this;

    for (int i = 0, n = Elts(); i < n; i++)
        self.data[i] = m.data[i];
}

TConstMat::TConstMat(TConstSliceMat m) : TConstRefMat(m.rows, m.cols, VL_NEW TElt[m.rows * m.cols])
{
    VL_ASSERT_MSG(data != 0, "(ConstMat) Out of memory");

    TRefMat& self = (TRefMat&) *this;

    for (int i = 0; i < rows; i++)
        self[i] = m[i];
}

// --- Mat Arithmetic Operators -----------------------------------------------

TMat operator + (TConstRefMat m, TConstRefMat n)
{
    TMat result(m.rows, m.cols);
    Add(m, n, result);
    return result;
}

TMat operator - (TConstRefMat m, TConstRefMat n)
{
    TMat result(m.rows, m.cols);
    Subtract(m, n, result);
    return result;
}

TMat operator * (TConstRefMat m, TConstRefMat n)
{
    TMat result(m.rows, n.cols);
    Multiply(m, n, result);
    return result;
}

TMat operator / (TConstRefMat m, TConstRefMat n)
{
    TMat result(m.rows, n.cols);
    Divide(m, n, result);
    return result;
}

TMat operator - (TConstRefMat m)
{
    TMat result(m.rows, m.cols);
    Negate(m, result);
    return result;
}

TMat operator * (TConstRefMat m, TElt s)
{
    TMat result(m.rows, m.cols);
    Multiply(m, s, result);
    return result;
}

TMat operator * (TElt s, TConstRefMat m)
{
    TMat result(m.rows, m.cols);
    Multiply(m, s, result);
    return result;
}

TMat operator / (TConstRefMat m, TElt s)
{
    TMat result(m.rows, m.cols);
    Divide(m, s, result);
    return result;
}

TVec operator * (TConstRefMat m, TConstRefVec v)
{
    TVec result(m.rows);
    Multiply(m, v, result);
    return result;
}

TVec operator * (TConstRefVec v, TConstRefMat m)
{
    TVec result(m.cols);
    Multiply(v, m, result);
    return result;
}

TMat trans(TConstRefMat m)
{
    TMat result(m.cols, m.rows);
    Transpose(m, result);
    return result;
}

#ifndef VL_NO_REAL
TMat inv(TConstRefMat m, TElt* determinant, TElt epsilon)
{
    TMat result(m.rows, m.cols);
    VL_EXPECT_MSG(Invert(m, result, determinant, epsilon), "(inv) Matrix not invertible");

    return result;
}
#endif

TMat abs(TConstRefMat m)
{
    TMat result(m.rows, m.cols);
    Absolute(m, result);
    return result;
}

TMat clamped(TConstRefMat m, TElt fuzz)
{
    TMat result(m);
    Clamp(result, fuzz);
    return result;
}

TMat hprod(TConstRefMat a, TConstRefMat b)
{
    TMat result(a.rows, a.cols);
    HadamardProduct(a, b, result);
    return result;
}

TMat oprod(TConstRefVec a, TConstRefVec b)
{
    TMat result(a.elts, b.elts);
    OuterProduct(a, b, result);
    return result;
}


// --- Mat Functions ----------------------------------------------------------

void Add(TConstRefMat a, TConstRefMat b, TRefMat r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Mat::+) Matrix dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Mat::+) Matrix dimensions don't match");
    Add(a.AsVec(), b.AsVec(), r.AsVec());
}

void Subtract(TConstRefMat a, TConstRefMat b, TRefMat r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Mat::-) Matrix dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Mat::-) Matrix dimensions don't match");
    Subtract(a.AsVec(), b.AsVec(), r.AsVec());
}

void Multiply(TConstRefMat a, TConstRefMat b, TRefMat r)
{
    VL_ASSERT_MSG(a.cols == b.rows, "(Mat::*m) Matrix dimensions don't match");
    VL_ASSERT_MSG(r.cols == b.cols, "(Mat::*m) Matrix dimensions don't match");
    VL_ASSERT_MSG(r.rows == a.rows, "(Mat::*m) Matrix dimensions don't match");    

    for (int i = 0; i < a.rows; i++)
        Multiply(a[i], b, r[i]);
}

void Divide(TConstRefMat a, TConstRefMat b, TRefMat r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Mat::/) Matrix dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Mat::/) Matrix dimensions don't match");
    Divide(a.AsVec(), b.AsVec(), r.AsVec());
}

void Negate(TConstRefMat m, TRefMat r)
{
    VL_ASSERT_MSG(same_size(m, r), "(Mat::-) Matrix dimensions don't match");
    Negate(m.AsVec(), r.AsVec());
}

void Multiply(TConstRefMat m, TElt s, TRefMat r)
{
    VL_ASSERT_MSG(same_size(m, r), "(Mat::*s) Matrix dimensions don't match");
    Multiply(m.AsVec(), s, r.AsVec());
}

void MultiplyAccum(TConstRefMat m, TElt s, TRefMat r)
{
    VL_ASSERT_MSG(same_size(m, r), "(Mat::*s) Matrix dimensions don't match");
    MultiplyAccum(m.AsVec(), s, r.AsVec());
}

void Divide(TConstRefMat m, TElt s, TRefMat r)
{
    VL_ASSERT_MSG(same_size(m, r), "(Mat::/s) Matrix dimensions don't match");
    Divide(m.AsVec(), s, r.AsVec());
}

void Multiply(TConstRefMat m, TConstRefVec v, TRefVec r)
{
    VL_ASSERT_MSG(v.elts == m.cols, "(Mat::*v) Matrix/Vector dimensions don't match");
    VL_ASSERT_MSG(r.elts == m.rows, "(Mat::*v) Matrix/Vector dimensions don't match");

    for (int i = 0; i < m.rows; i++)
        r.data[i] = dot(v, m[i]);
}

void Multiply(TConstRefVec v, TConstRefMat m, TRefVec r)
{
    VL_ASSERT_MSG(v.elts == m.rows, "(Mat::v*) Vector/Matrix dimensions don't match");
    VL_ASSERT_MSG(r.elts == m.cols, "(Mat::v*) Vector/Matrix dimensions don't match");

    if (m.rows == 0)
        return;

    Multiply(m[0], v.data[0], r);

    for (int i = 1; i < m.rows; i++)
        MultiplyAccum(m[i], v.data[i], r);
}

void Transpose(TConstRefMat m, TRefMat r)
{
    VL_ASSERT_MSG(r.cols == m.rows, "(Mat::trans) Matrix dimensions don't match");
    VL_ASSERT_MSG(r.rows == m.cols, "(Mat::trans) Matrix dimensions don't match");

    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.cols; j++)
            r(j, i) = m(i, j);
}

void Absolute(TConstRefMat m, TRefMat r)
{
    VL_ASSERT_MSG(same_size(m, r), "(Mat::abs) Matrix dimensions don't match");
    Absolute(m.AsVec(), r.AsVec());
}

void Clamp(TRefMat m, TElt fuzz)
{
    Clamp(m.AsVec(), fuzz);
}

TElt InnerProduct(TConstRefMat a, TConstRefMat b)
{
    VL_ASSERT_MSG(same_size(a, b), "(Mat::iprod) Matrix dimensions don't match");
    return dot(a.AsVec(), b.AsVec());
}

void OuterProduct(TConstRefVec a, TConstRefVec b, TRefMat r)
{
    VL_ASSERT_MSG(r.rows == a.elts, "(Mat::oprod) Matrix dimensions don't match");
    VL_ASSERT_MSG(r.cols == b.elts, "(Mat::oprod) Matrix dimensions don't match");

    for (int i = 0; i < a.elts; i++)
        Multiply(b, a.data[i], r[i]);
}

void HadamardProduct(TConstRefMat a, TConstRefMat b, TRefMat r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Mat::-) Matrix dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Mat::-) Matrix dimensions don't match");
    Multiply(a.AsVec(), b.AsVec(), r.AsVec());
}

#ifndef VL_NO_REAL
bool Invert(TConstRefMat m, TRefMat B, TElt* determinant, TElt epsilon)
{
    VL_ASSERT(m.data != B.data);
    VL_ASSERT_MSG(is_square(m), "(inv) input matrix not square");
    VL_ASSERT_MSG(same_size(m, B), "(inv) Matrix dimensions don't match");

    int  n = m.rows;
    TMat A(m);
    B.MakeIdentity();

    if (determinant)
        *determinant = TElt(vl_0);

    // ---------- Forward elimination -----------------------------------------

    TElt det = TElt(vl_1);

    for (int i = 0; i < n; i++)             // Eliminate in column i, below diag
    {
        TElt max = TElt(-1);

        int j = 0;
        for (int k = i; k < n; k++)         // Find a pivot for column i
            if (len(A(k, i)) > max)
            {
                max = len(A(k, i));
                j = k;
            }

        if (max < epsilon)
            return false;

        if (j != i)                     // Swap rows i and j
        {
            for (int k = i; k < n; k++)
            {
                TElt aik = A(i, k);
                TElt ajk = A(j, k);

                 A(i, k) = ajk;
                 A(j, k) = aik;
            }
            for (int k = 0; k < n; k++)
            {
                TElt bik = B(i, k);
                TElt bjk = B(j, k);

                 B(i, k) = bjk;
                 B(j, k) = bik;
            }

            det = -det;
        }

        TElt pivot = A(i, i);
        if (len(pivot) < epsilon)
            return false;

        det *= pivot;

        for (int k = i + 1; k < n; k++)     // Only do elements to the right of the pivot
            A(i, k) /= pivot;

        for (int k = 0; k < n; k++)
            B(i, k) /= pivot;

        // We know that A(i, i) will be set to 1, so don't bother to do it

        for (int j = i + 1; j < n; j++)
        {                               // Eliminate in rows below i
            TElt t = A(j, i);           // We're gonna zero this guy
            for (int k = i + 1; k < n; k++) // Subtract scaled row i from row j
                A(j, k) -= A(i, k) * t; // (Ignore k <= i, we know they're 0)
            for (int k = 0; k < n; k++)
                B(j, k) -= B(i, k) * t;
        }
    }

    // ---------- Backward elimination ----------------------------------------

    for (int i = n - 1; i > 0; i--)         // Eliminate in column i, above diag
    {
        for (int j = 0; j < i; j++)         // Eliminate in rows above i
        {
            TElt t = A(j, i);               // We're gonna zero this guy
            for (int k = 0; k < n; k++)     // Subtract scaled row i from row j
                B(j, k) -= B(i, k) * t;
        }
    }

    if (determinant)
        *determinant = det;

    return true;
}
#endif

