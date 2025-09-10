/*
    File:       Mixed.cpp

    Function:   Implements Mixed.hpp

    Copyright:  Andrew Willmott
*/

#include "VL/Mixed.hpp"


// --- Vector dot products ----------------------------------------------------


#ifdef VL_VEC_H
TMElt dot(TMConstRefVec a, TConstRefVec b)
{
    VL_ASSERT_MSG(a.elts == b.elts, "(Vec::dot) Vector sizes don't match");

    TMElt  sum = vl_zero;

    for (int i = 0; i < a.elts; i++)
        sum += a.data[i] * b.data[i];

    return sum;
}
#endif


// --- Matrix-vector multiply -------------------------------------------------

#ifdef VL_VEC2_H

TVec4 operator * (const TMat4& m, const TVec4& v)           // m * v
{
    TVec4 result;

    result[0] = TElt(v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2] + v[3] * m[0][3]);
    result[1] = TElt(v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2] + v[3] * m[1][3]);
    result[2] = TElt(v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] + v[3] * m[2][3]);
    result[3] = TElt(v[0] * m[3][0] + v[1] * m[3][1] + v[2] * m[3][2] + v[3] * m[3][3]);

    return result;
}

TVec4 operator * (const TVec4& v, const TMat4& m)           // v * m
{
    TVec4 result;

    result[0] = TElt(v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + v[3] * m[3][0]);
    result[1] = TElt(v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + v[3] * m[3][1]);
    result[2] = TElt(v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + v[3] * m[3][2]);
    result[3] = TElt(v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + v[3] * m[3][3]);

    return result;
}

TVec4& operator *= (TVec4& v, const TMat4& m)               // v *= m
{
    TElt  t0, t1, t2;

    t0   = TElt(v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0] + v[3] * m[3][0]);
    t1   = TElt(v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1] + v[3] * m[3][1]);
    t2   = TElt(v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2] + v[3] * m[3][2]);
    v[3] = TElt(v[0] * m[0][3] + v[1] * m[1][3] + v[2] * m[2][3] + v[3] * m[3][3]);
    v[0] = t0;
    v[1] = t1;
    v[2] = t2;

    return v;
}

#endif

#ifdef VL_VEC_H
TVec operator * (TConstRefMat m, TConstRefVec v)
{
    VL_ASSERT_MSG(m.cols == v.elts, "(Mat::*v) Matrix/vector sizes don't match");

    TVec result(m.rows);

    for (int i = 0; i < m.rows; i++)
        result.data[i] = TElt(dot(m[i], v));

    return result;
}

TVec operator * (TConstRefVec v, TConstRefMat m)          // v * m
{
    VL_ASSERT_MSG(v.elts == m.rows, "(Mat::v*m) Vector/matrix sizes don't match");
    // XXX too many allocs, MultiplyAccum
    TMVec temp(m.cols, vl_zero);    // accumulate in high precision

    for (int i = 0; i < m.rows; i++)
        temp += m[i] * v.data[i];

    TVec result(m.cols);            // return low precision.

    for (int i = 0; i < temp.elts; i++)
        result.data[i] = TElt(temp.data[i]);

    return result;
}

TRefVec operator *= (TRefVec v, TConstRefMat m)              // v *= m
{
    v = v * m;      // Can't optimise much here...

    return v;
}

void Multiply(TConstRefMat m, TConstRefVec v, TRefVec r)
{
    VL_ASSERT_MSG(m.cols == v.elts, "(Mat::*v) Matrix/vector sizes don't match");
    VL_ASSERT_MSG(m.rows == r.elts, "(Mat::*v) Matrix/vector sizes don't match");

    for (int i = 0; i < m.rows; i++)
        r.data[i] = TElt(dot(m[i], v));
}

void Multiply(TConstRefVec v, TConstRefMat m, TRefVec r)
{
    VL_ASSERT_MSG(v.elts == m.rows, "(Mat::v*m) Vector/matrix sizes don't match");
    VL_ASSERT_MSG(r.elts == m.cols, "(Mat::v*m) Vector/matrix sizes don't match");

    r.MakeZero();

    for (int i = 0; i < m.rows; i++)
        MultiplyAccum(m[i], v.data[i], r);
}

void MultiplyAccum(TMConstRefVec v, const TElt s, TRefVec result)
{
    VL_ASSERT_MSG(v.elts == result.elts, "(SparseVec::MultiplyAccum) Vector sizes don't match");

    for (int i = 0; i < v.elts; i++)
        result.data[i] += TElt(s * v.data[i]);
}

void OuterProduct(TConstRefVec a, TConstRefVec b, TRefMat r)
{
    VL_ASSERT_MSG(a.elts == r.rows, "(Mat::OuterProduct) Vector/matrix sizes don't match");
    VL_ASSERT_MSG(b.elts == r.cols, "(Mat::OuterProduct) Vector/matrix sizes don't match");

    for (int i = 0; i < a.elts; i++)
        for (int j = 0; j < b.elts; j++)
            r(i, j) = a.data[i] * b.data[j];
}
#endif
