/*
    File:       Mat3.cpp

    Function:   Implements Mat3.hpp

    Copyright:  Andrew Willmott
*/


#include "VL/Mat3.hpp"
#include "VL/Vec4.hpp"


TMat3::TMat3(const TMat2& m, TElt s) :
    x(m.x,  vl_0),
    y(m.y,  vl_0),
    z(vl_0, s)
{
}

TMat3& TMat3::operator = (const TMat3& m)
{
    x = m.x;
    y = m.y;
    z = m.z;

    return *this;
}

TMat3& TMat3::operator += (const TMat3& m)
{
    x += m.x;
    y += m.y;
    z += m.z;

    return *this;
}

TMat3& TMat3::operator -= (const TMat3& m)
{
    x -= m.x;
    y -= m.y;
    z -= m.z;

    return *this;
}

TMat3& TMat3::operator *= (const TMat3& m)
{
    TVec3 t0, t1;

    t0 = x.x * m.x + x.y * m.y + x.z * m.z;
    t1 = y.x * m.x + y.y * m.y + y.z * m.z;
    z  = z.x * m.x + z.y * m.y + z.z * m.z;
    x  = t0;
    y  = t1;

    return *this;
}

TMat3& TMat3::operator *= (TElt s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

TMat3& TMat3::operator /= (TElt s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}


bool TMat3::operator == (const TMat3& m) const
{
    return x == m.x && y == m.y && z == m.z;
}

bool TMat3::operator != (const TMat3& m) const
{
    return x != m.x || y != m.y || z != m.z;
}


TMat3 TMat3::operator + (const TMat3& m) const
{
    TMat3 result;

    result.x = x + m.x;
    result.y = y + m.y;
    result.z = z + m.z;

    return result;
}

TMat3 TMat3::operator - (const TMat3& m) const
{
    TMat3 result;

    result.x = x - m.x;
    result.y = y - m.y;
    result.z = z - m.z;

    return result;
}

TMat3 TMat3::operator - () const
{
    TMat3 result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

TMat3 TMat3::operator * (const TMat3& m) const
{
    TMat3 result;

    result.x.x = x.x * m.x.x + x.y * m.y.x + x.z * m.z.x;
    result.x.y = x.x * m.x.y + x.y * m.y.y + x.z * m.z.y;
    result.x.z = x.x * m.x.z + x.y * m.y.z + x.z * m.z.z;

    result.y.x = y.x * m.x.x + y.y * m.y.x + y.z * m.z.x;
    result.y.y = y.x * m.x.y + y.y * m.y.y + y.z * m.z.y;
    result.y.z = y.x * m.x.z + y.y * m.y.z + y.z * m.z.z;

    result.z.x = z.x * m.x.x + z.y * m.y.x + z.z * m.z.x;
    result.z.y = z.x * m.x.y + z.y * m.y.y + z.z * m.z.y;
    result.z.z = z.x * m.x.z + z.y * m.y.z + z.z * m.z.z;

    return result;
}

TMat3 TMat3::operator * (TElt s) const
{
    TMat3 result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

TMat3 TMat3::operator / (TElt s) const
{
    TMat3 result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;

    return result;
}

TMat3 trans(const TMat3& m)
{
    TMat3 t;

    t.x.x = m.x.x; t.x.y = m.y.x; t.x.z = m.z.x;
    t.y.x = m.x.y; t.y.y = m.y.y; t.y.z = m.z.y;
    t.z.x = m.x.z; t.z.y = m.y.z; t.z.z = m.z.z;

    return t;
}

TMat3 adj(const TMat3& m)
{
    TMat3 result;

    result.x = cross(m.y, m.z);
    result.y = cross(m.z, m.x);
    result.z = cross(m.x, m.y);

    return result;
}


TElt trace(const TMat3& m)
{
    return m.x.x + m.y.y + m.z.z;
}

TElt det(const TMat3& m)
{
    return dot(m.x, cross(m.y, m.z));
}

TMat3 inv(const TMat3& m)
{
    TElt  det;
    TMat3 adjoint;
    TMat3 result;

    adjoint = adj(m);
    det = dot(adjoint.x, m.x);

    VL_ASSERT_MSG(det != 0, "(Mat3::inv) matrix is non-singular");

    result = trans(adjoint);
    result /= det;

    return result;
}

TMat3 abs(const TMat3& m)
{
    return TMat3(abs(m.x), abs(m.y), abs(m.z));
}

TMat3 oprod(const TVec3& a, const TVec3& b)
// returns outerproduct of a and b:  a * trans(b)
{
    TMat3 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}
