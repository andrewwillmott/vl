/*
    File:       Mat2.cpp

    Function:   Implements Mat2.hpp

    Copyright:  Andrew Willmott
*/

#include "VL/Mat2.hpp"


bool TMat2::operator == (const TMat2& m) const
{
    return x == m.x && y == m.y;
}

bool TMat2::operator != (const TMat2& m) const
{
    return x != m.x || y != m.y;
}


TElt det(const TMat2& m)
{
    return m.x.x * m.y.y - m.x.y * m.y.x;
}

#ifndef VL_NO_REAL
TMat2 inv(const TMat2& m)
{
    TElt  det;
    TMat2 result;

    result.x.x =  m.y.y; result.x.y = -m.x.y;
    result.y.x = -m.y.x; result.y.y =  m.x.x;

    det = m.x.x * result.x.x + m.x.y * result.y.x;
    VL_ASSERT_MSG(det != 0.0, "(Mat2::inv) matrix is non-singular");
    result /= det;

    return result;
}
#endif

TMat2 abs(const TMat2& m)
{
    return TMat2(abs(m.x), abs(m.y));
}

TMat2 oprod(const TVec2& a, const TVec2& b)
// returns outerproduct of a and b:  a * trans(b)
{
    TMat2   result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

