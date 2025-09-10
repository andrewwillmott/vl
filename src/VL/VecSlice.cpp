/*
    File:       VecSlice.cpp

    Function:   Implements VecSlice.hpp

    Copyright:  Andrew Willmott
*/

#include "VL/VecSlice.hpp"
#include "VL/Vec.hpp"


// --- SliceVec Constructors & Destructors ------------------------------------


TConstSliceVec::TConstSliceVec(int n, int span, const TElt data[]) :
    data(data),
    elts(n),
    span(span)
{
}

TSliceVec::TSliceVec(int n, int span, TElt data[]) :
    data(data),
    elts(n),
    span(span)
{
}


// --- SliceVec Assignment Operators ------------------------------------------


const TSliceVec& TSliceVec::operator = (const TSliceVec& v) const
{
    return operator=((TConstSliceVec) v);
}

const TSliceVec& TSliceVec::operator = (TConstSliceVec v) const
{
    VL_ASSERT_MSG(elts == v.elts || v.elts == VL_REPEAT, "(SliceVec::=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        (*this)[i] = v[i];

    return *this;
}

const TSliceVec& TSliceVec::operator = (TRefVec v) const
{
    return operator=((TConstRefVec) v);
}

const TSliceVec& TSliceVec::operator = (TConstRefVec v) const
{
    return operator=((TConstSliceVec) v);
}

#ifdef VL_VEC2_H
const TSliceVec& TSliceVec::operator = (const TVec2& v) const 
{
     return *this = TConstRefVec(v); 
}

const TSliceVec& TSliceVec::operator = (const TVec3& v) const 
{
     return *this = TConstRefVec(v); 
}

const TSliceVec& TSliceVec::operator = (const TVec4& v) const 
{
     return *this = TConstRefVec(v); 
}
#endif


// --- SliceVec In-Place operators --------------------------------------------


const TSliceVec& TSliceVec::operator += (TConstSliceVec sv) const
{
    VL_ASSERT_MSG(elts == sv.elts || sv.elts == VL_REPEAT, "(SliceVec::+=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        (*this)[i] += sv[i];

    return *this;
}

const TSliceVec& TSliceVec::operator -= (TConstSliceVec sv) const
{
    VL_ASSERT_MSG(elts == sv.elts || sv.elts == VL_REPEAT, "(SliceVec::-=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        (*this)[i] -= sv[i];

    return *this;
}

const TSliceVec& TSliceVec::operator *= (TConstSliceVec sv) const
{
    VL_ASSERT_MSG(elts == sv.elts || sv.elts == VL_REPEAT, "(SliceVec::*=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        (*this)[i] *= sv[i];

    return *this;
}

const TSliceVec& TSliceVec::operator /= (TConstSliceVec sv) const
{
    VL_ASSERT_MSG(elts == sv.elts || sv.elts == VL_REPEAT, "(SliceVec::/=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        (*this)[i] /= sv[i];

    return *this;
}

const TSliceVec& TSliceVec::operator *= (TElt s) const
{
    for (int i = 0; i < elts; i++)
        (*this)[i] *= s;

    return *this;
}

const TSliceVec& TSliceVec::operator /= (TElt s) const
{
    for (int i = 0; i < elts; i++)
        (*this)[i] /= s;

    return *this;
}

// --- SliceVec Vector initialisers -------------------------------------------

void TSliceVec::MakeZero() const
{
    for (int i = 0; i < elts; i++)
        (*this)[i] = vl_0;
}

void TSliceVec::MakeUnit(int axis, TElt k) const
{
    for (int i = 0; i < elts; i++)
        (*this)[i] = vl_0;
    (*this)[axis] = k;
}

void TSliceVec::MakeBlock(TElt k) const
{
    for (int i = 0; i < elts; i++)
        (*this)[i] = k;
}


// --- SliceVec Comparison Operators ------------------------------------------


bool operator == (TConstSliceVec a, TConstSliceVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts || a.elts == VL_REPEAT || b.elts == VL_REPEAT, "(Vec::==) Vector sizes don't match");

    for (int i = 0; i < a.elts; i++)
        if (a[i] != b[i])
            return false;

    return true;
}


// --- SliceVec Arithmetic Operators ------------------------------------------


TVec operator + (TConstSliceVec a, TConstSliceVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts || b.elts == VL_REPEAT, "(Vec::+) Vector sizes don't match");

    TVec result(a.elts);

    for (int i = 0; i < a.elts; i++)
        result[i] = a[i] + b[i];

    return result;
}

TVec operator - (TConstSliceVec a, TConstSliceVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts || b.elts == VL_REPEAT, "(Vec::-) Vector sizes don't match");

    TVec result(a.elts);

    for (int i = 0; i < a.elts; i++)
        result[i] = a[i] - b[i];

    return result;
}

TVec operator - (TConstSliceVec v)
{
    TVec result(v.elts);

    for (int i = 0; i < v.elts; i++)
        result[i] = - v[i];

    return result;
}

TVec operator * (TConstSliceVec a, TConstSliceVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts || b.elts == VL_REPEAT, "(Vec::*) Vector sizes don't match");

    TVec result(a.elts);

    for (int i = 0; i < a.elts; i++)
        result[i] = a[i] * b[i];

    return result;
}

TVec operator * (TConstSliceVec v, TElt s)
{
    TVec result(v.elts);

    for (int i = 0; i < v.elts; i++)
        result[i] = v[i] * s;

    return result;
}

TVec operator / (TConstSliceVec a, TConstSliceVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts || b.elts == VL_REPEAT, "(Vec::/) Vector sizes don't match");

    TVec result(a.elts);

    for (int i = 0; i < a.elts; i++)
        result[i] = a[i] / b[i];

    return result;
}

TVec operator / (TConstSliceVec v, TElt s)
{
    TVec result(v.elts);

    for (int i = 0; i < v.elts; i++)
        result[i] = v[i] / s;

    return result;
}

TVec operator * (TElt s, TConstSliceVec v)
{
    TVec result(v.elts);

    for (int i = 0; i < v.elts; i++)
        result[i] = v[i] * s;

    return result;
}

TElt dot(TConstSliceVec a, TConstSliceVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts || b.elts == VL_REPEAT, "(Vec::dot) Vector sizes don't match");

    TElt sum = TElt(vl_zero);

    for (int i = 0; i < a.elts; i++)
        sum += a[i] * b[i];

    return sum;
}

#ifndef VL_NO_REAL
TVec norm(TConstSliceVec v)
{
    VL_ASSERT_MSG(TElt(vl_0) < sqrlen(v), "normalising length-zero vector");
    return v / len(v);
}

TVec norm_safe(TConstSliceVec v)
{
    return v / (len(v) + TElt(1e-8));
}
#endif

TElt sum(TConstSliceVec v)
{
    TElt s = TElt(vl_0);

    for (int i = 0; i < v.elts; i++)
        s += v[i];

    return s;
}

TVec abs(TConstSliceVec v)
{
    TVec result(v.elts);
    Absolute(result, result);
    return result;
}

TVec clamped(TConstSliceVec v, TElt fuzz)
{
    TVec result(v);
    Clamp(result, fuzz);
    return result;
}
