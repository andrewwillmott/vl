/*
    File:       Vec.cpp

    Function:   Implements Vec.h

    Copyright:  Andrew Willmott
*/


#include "VL/Vec.h"


// --- RefVec Assignment Operators --------------------------------------------

const TRefVec& TRefVec::operator = (const TRefVec& v) const
{
    VL_ASSERT_MSG(elts == v.elts, "(Vec::=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] = v.data[i];

    return *this;
}

const TRefVec& TRefVec::operator = (TConstRefVec v) const
{
    VL_ASSERT_MSG(elts == v.elts, "(Vec::=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] = v.data[i];

    return *this;
}

const TRefVec& TRefVec::operator = (TConstSliceVec v) const
{
    VL_ASSERT_MSG(elts == v.elts, "(Vec::=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] = v.data[i];

    return *this;
}

// --- RefVec In-Place Operators ----------------------------------------------

const TRefVec& TRefVec::operator += (TConstRefVec v) const
{
    VL_ASSERT_MSG(elts == v.elts, "(Vec::+=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] += v.data[i];

    return *this;
}

const TRefVec& TRefVec::operator -= (TConstRefVec v) const
{
    VL_ASSERT_MSG(elts == v.elts, "(Vec::-=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] -= v.data[i];

    return *this;
}

const TRefVec& TRefVec::operator *= (TConstRefVec v) const
{
    VL_ASSERT_MSG(elts == v.elts, "(Vec::*=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] *= v.data[i];

    return *this;
}

const TRefVec& TRefVec::operator /= (TConstRefVec v) const
{
    VL_ASSERT_MSG(elts == v.elts, "(Vec::/=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] /= v.data[i];

    return *this;
}

const TRefVec& TRefVec::operator *= (TElt s) const
{
    for (int i = 0; i < elts; i++)
        data[i] *= s;

    return *this;
}

const TRefVec& TRefVec::operator /= (TElt s) const
{
    for (int i = 0; i < elts; i++)
        data[i] /= s;

    return *this;
}

// --- RefVec Vector initialisers ---------------------------------------------

void TRefVec::MakeZero() const
{
    for (int i = 0; i < elts; i++)
        data[i] = vl_zero;
}

void TRefVec::MakeUnit(int i, TElt k) const
{
    MakeZero();
    data[i] = k;
}

void TRefVec::MakeBlock(TElt k) const
{
    for (int i = 0; i < elts; i++)
        data[i] = k;
}


// --- Vec Constructors & Destructors -----------------------------------------

TVec::TVec(const TVec& v) : TRefVec(v.elts, VL_NEW TElt[v.elts])
{
    VL_ASSERT_MSG(data != 0, "(Vec) Out of memory");

    for (int i = 0; i < elts; i++)
        data[i] = v.data[i];
}

TVec::TVec(TVec&& v) : TRefVec(v.elts, v.data)
{
    v.data = 0;
}

TVec::TVec(int n, double elt0, ...) : TRefVec(n, VL_NEW TElt[n])
// The double is hardwired here because it is the only type that will work
// with var args and C++ real numbers.
{
    VL_ASSERT_MSG(data != 0, "(Vec) Out of memory");
    VL_ASSERT_MSG(n > 0,"(Vec) illegal vector size");

    va_list ap;

    va_start(ap, elt0);

    data[0] = TElt(elt0);

    int i = 1;
    while (--n)
        data[i++] = TElt(va_arg(ap, double));

    va_end(ap);
}

TVec::TVec(std::initializer_list<TElt> l) : TRefVec(int(l.size()), VL_NEW TElt[l.size()])
{
    std::initializer_list<TElt>::const_iterator it = l.begin();

    for (int i = 0; i < elts; i++)
        data[i] = *it++;
}

TVec::TVec(TConstRefVec v) : TRefVec(v.elts, VL_NEW TElt[v.elts])
{
    VL_ASSERT_MSG(data != 0, "(Vec) Out of memory");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = v.data[i];
}

TVec::TVec(TConstSliceVec v) : TRefVec(v.elts, VL_NEW TElt[v.elts])
{
    VL_ASSERT_MSG(data != 0, "(Mat) Out of memory");
    
    for (int i = 0; i < elts; i++)
        (*this)[i] = v[i];
}

// --- Vec Assignment Operators -----------------------------------------------


TVec& TVec::operator = (const TVec& v)
{
    if (this != &v)
    {
        SetSize(v.elts);

        for (int i = 0; i < elts; i++)
            data[i] = v.data[i];
    }
    
    return *this;
}

TVec& TVec::operator = (TVec&& v)
{
    if (this != &v)
    {
        VL_DELETE[] data;
        data = v.data;
        elts = v.elts;
        v.data = 0;
    }

    return *this;
}


// --- Vec Sizing -------------------------------------------------------------

void TVec::SetSize(int n)
{
    VL_ASSERT_MSG(n > 0, "(Vec::SetSize) Illegal size.");

    int oldElts = elts;
    elts = n;

    // Don't reallocate if we already have enough storage
    if (elts <= oldElts)
        return;

    // Otherwise, delete old storage and reallocate
    VL_DELETE[] data;
    data = VL_NEW TElt[elts];
}


// --- ConstVec Constructors & Destructors ------------------------------------

TConstVec::TConstVec(const TConstVec& v) : TConstRefVec(v.elts, VL_NEW TElt[v.elts])
{
    VL_ASSERT_MSG(data != 0, "(Vec) Out of memory");

    TRefVec& self = (TRefVec&) *this;
    for (int i = 0; i < elts; i++)
        self.data[i] = v.data[i];
}

TConstVec::TConstVec(TConstVec&& v) : TConstRefVec(v.elts, v.data)
{
    v.data = 0;
}

TConstVec::TConstVec(int n, double elt0, ...) : TConstRefVec(n, VL_NEW TElt[n])
// The double is hardwired here because it is the only type that will work
// with var args and C++ real numbers.
{
    VL_ASSERT_MSG(data != 0, "(Vec) Out of memory");
    VL_ASSERT_MSG(n > 0,"(Vec) illegal vector size");

    va_list ap;
    va_start(ap, elt0);

    TRefVec& self = (TRefVec&) *this;
    self.data[0] = TElt(elt0);

    int i = 1;
    while (--n)
        self.data[i++] = TElt(va_arg(ap, double));

    va_end(ap);
}

TConstVec::TConstVec(std::initializer_list<TElt> l) : TConstRefVec(int(l.size()), VL_NEW TElt[l.size()])
{
    TRefVec& self = (TRefVec&) *this;

    std::initializer_list<TElt>::const_iterator it = l.begin();

    for (int i = 0; i < elts; i++)
        self.data[i] = *it++;
}

TConstVec::TConstVec(TConstRefVec v) : TConstRefVec(v.elts, VL_NEW TElt[v.elts])
{
    VL_ASSERT_MSG(data != 0, "(Vec) Out of memory");

    TRefVec& self = (TRefVec&) *this;
    for (int i = 0, n = Elts(); i < n; i++)
        self.data[i] = v.data[i];
}

TConstVec::TConstVec(TConstSliceVec v) : TConstRefVec(v.elts, VL_NEW TElt[v.elts])
{
    VL_ASSERT_MSG(data != 0, "(Mat) Out of memory");
    
    TRefVec& self = (TRefVec&) *this;
    for (int i = 0; i < elts; i++)
        self[i] = v[i];
}


// --- Vec Comparison Operators -----------------------------------------------

bool operator == (TConstRefVec a, TConstRefVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts, "(Vec::==) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        if (a.data[i] != b.data[i])
            return false;

    return true;
}

bool operator != (TConstRefVec a, TConstRefVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts, "(Vec::!=) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        if (a.data[i] != b.data[i])
            return true;

    return false;
}

bool operator < (TConstRefVec a, TConstRefVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts, "(Vec::<) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        if (a.data[i] >= b.data[i])
            return false;

    return true;
}

bool operator >= (TConstRefVec a, TConstRefVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts, "(Vec::>=) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        if (a.data[i] < b.data[i])
            return false;

    return true;
}

// --- Vec Arithmetic Operators -----------------------------------------------

TVec operator + (TConstRefVec a, TConstRefVec b)
{
    TVec result(a.elts);
    Add(a, b, result);

    return result;
}

TVec operator - (TConstRefVec a, TConstRefVec b)
{
    TVec result(a.elts);
    Subtract(a, b, result);
    return result;
}

TVec operator - (TConstRefVec v)
{
    TVec result(v.elts);
    Negate(v, result);
    return result;
}

TVec operator * (TConstRefVec a, TConstRefVec b)
{
    TVec result(a.elts);
    Multiply(a, b, result);
    return result;
}

TVec operator * (TConstRefVec v, TElt s)
{
    TVec result(v.elts);
    Multiply(v, s, result);
    return result;
}

TVec operator / (TConstRefVec a, TConstRefVec b)
{
    TVec result(a.elts);
    Divide(a, b, result);
    return result;
}

TVec operator / (TConstRefVec v, TElt s)
{
    TVec result(v.elts);
    Divide(v, s, result);
    return result;
}

TVec operator * (TElt s, TConstRefVec v)
{
    TVec result(v.elts);
    Multiply(v, s, result);
    return result;
}

TElt dot(TConstRefVec a, TConstRefVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts, "(Vec::dot) Vector sizes don't match");

    TElt  sum = TElt(vl_zero);

    for (int i = 0; i < a.elts; i++)
        sum += a.data[i] * b.data[i];

    return sum;
}

TElt sum(TConstRefVec v)
{
    TElt s = TElt(vl_0);

    for (int i = 0; i < v.elts; i++)
        s += v.data[i];

    return s;
}

TVec abs(TConstRefVec v)
{
    TVec result(v.elts);
    Absolute(v, result);
    return result;
}

TVec clamped(TConstRefVec v, TElt fuzz)
{
    TVec result(v);
    Clamp(result, fuzz);
    return result;
}


// --- Vec Functions ----------------------------------------------------------

void Add(TConstRefVec a, TConstRefVec b, TRefVec result)
{
    VL_ASSERT_MSG(a.elts == b     .elts, "(Vec::+) Vector sizes don't match");
    VL_ASSERT_MSG(a.elts == result.elts, "(Vec::+) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        result.data[i] = a.data[i] + b.data[i];
}

void Subtract(TConstRefVec a, TConstRefVec b, TRefVec result)
{
    VL_ASSERT_MSG(a.elts == b     .elts, "(Vec::-) Vector sizes don't match");
    VL_ASSERT_MSG(a.elts == result.elts, "(Vec::-) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        result.data[i] = a.data[i] - b.data[i];
}

void Negate(TConstRefVec v, TRefVec result)
{
    VL_ASSERT_MSG(v.elts == result.elts, "(Vec::-) Vector sizes don't match");

    for (int i = 0; i < v.elts; i++)
        result.data[i] = - v.data[i];
}

void Multiply(TConstRefVec a, TConstRefVec b, TRefVec result)
{
    VL_ASSERT_MSG(a.elts == b     .elts, "(Vec::*) Vector sizes don't match");
    VL_ASSERT_MSG(a.elts == result.elts, "(Vec::*) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        result.data[i] = a.data[i] * b.data[i];
}

void Multiply(TConstRefVec v, TElt s, TRefVec result)
{
    VL_ASSERT_MSG(v.elts == result.elts, "(Vec::*) Vector sizes don't match");

    for (int i = 0; i < v.elts; i++)
        result.data[i] = v.data[i] * s;
}

void MultiplyAccum(TConstRefVec v, const TElt s, TRefVec result)
{
    VL_ASSERT_MSG(v.elts == result.elts, "(Vec::MultiplyAccum) Vector sizes don't match");

    for (int i = 0; i < v.elts; i++)
        result.data[i] += s * v.data[i];
}

void Divide(TConstRefVec a, TConstRefVec b, TRefVec result)
{
    VL_ASSERT_MSG(a.elts == b     .elts, "(Vec::/) Vector sizes don't match");
    VL_ASSERT_MSG(a.elts == result.elts, "(Vec::/) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        result.data[i] = a.data[i] / b.data[i];
}

void Divide(TConstRefVec v, TElt s, TRefVec result)
{
    VL_ASSERT_MSG(v.elts == result.elts, "(Vec::/) Vector sizes don't match");

    TElt t = TElt(vl_1) / s;
    for (int i = 0; i < v.elts; i++)
        result.data[i] = v.data[i] * t;
}

#ifndef VL_NO_REAL
void Normalize(TConstRefVec v, TRefVec result)
{
    Divide(v, len(v), result);
}

void NormalizeSafe(TConstRefVec v, TRefVec result)
{
    Divide(v, len(v) + TElt(1e-8), result);
}
#endif

void Absolute(TConstRefVec v, TRefVec result)
{
    VL_ASSERT_MSG(v.elts == result.elts, "(Vec::abs) Vector sizes don't match");

    for (int i = 0; i < v.elts; i++)
        result.data[i] = abs(v.data[i]);  // AAA
}

void Clamp(TRefVec v, TElt fuzz)
{
    for (int i = 0; i < v.elts; i++)
        if (len(v.data[i]) < fuzz)
            v.data[i] = vl_zero;
}
