/*
    File:       Mat4.cpp

    Function:   Implements Mat4.h

    Copyright:  Andrew Willmott
*/


#include "VL/Mat4.h"


TMat4::TMat4(TElt a, TElt b, TElt c, TElt d,
             TElt e, TElt f, TElt g, TElt h,
             TElt i, TElt j, TElt k, TElt l,
             TElt m, TElt n, TElt o, TElt p)
{
    x.x = a;  x.y = b;  x.z = c;  x.w = d;
    y.x = e;  y.y = f;  y.z = g;  y.w = h;
    z.x = i;  z.y = j;  z.z = k;  z.w = l;
    w.x = m;  w.y = n;  w.z = o;  w.w = p;
}

TMat4::TMat4(const TMat3& m, TElt s)
{
    x.AsVec3() = m.x ; x.w = TElt(vl_0);
    y.AsVec3() = m.y ; y.w = TElt(vl_0);
    z.AsVec3() = m.z ; z.w = TElt(vl_0);
    w.AsVec3() = vl_0; w.w = s;
}

TMat4& TMat4::operator = (const TMat4& m)
{
    x = m.x;
    y = m.y;
    z = m.z;
    w = m.w;

    return *this;
}

TMat4& TMat4::operator += (const TMat4& m)
{
    x += m.x;
    y += m.y;
    z += m.z;
    w += m.w;

    return *this;
}

TMat4& TMat4::operator -= (const TMat4& m)
{
    x -= m.x;
    y -= m.y;
    z -= m.z;
    w -= m.w;

    return *this;
}

TMat4& TMat4::operator *= (const TMat4& m)
{
    TVec4  t0, t1, t2;

    t0   = x.x * m.x + x.y * m.y + x.z * m.z + x.w * m.w;
    t1   = y.x * m.x + y.y * m.y + y.z * m.z + y.w * m.w;
    t2   = z.x * m.x + z.y * m.y + z.z * m.z + z.w * m.w;
    w    = w.x * m.x + w.y * m.y + w.z * m.z + w.w * m.w;
    x = t0;
    y = t1;
    z = t2;

    return *this;
}

TMat4& TMat4::operator *= (TElt s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

TMat4& TMat4::operator /= (TElt s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}


bool TMat4::operator == (const TMat4& m) const
{
    return x == m.x && y == m.y && z == m.z && w == m.w;
}

bool TMat4::operator != (const TMat4& m) const
{
    return x != m.x || y != m.y || z != m.z || w != m.w;
}


TMat4 TMat4::operator + (const TMat4& m) const
{
    TMat4 result;

    result.x = x + m.x;
    result.y = y + m.y;
    result.z = z + m.z;
    result.w = w + m.w;

    return result;
}

TMat4 TMat4::operator - (const TMat4& m) const
{
    TMat4 result;

    result.x = x - m.x;
    result.y = y - m.y;
    result.z = z - m.z;
    result.w = w - m.w;

    return result;
}

TMat4 TMat4::operator - () const
{
    TMat4 result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

TMat4 TMat4::operator * (const TMat4& m) const
{
    TMat4 result;

    result.x.x = x.x * m.x.x + x.y * m.y.x + x.z * m.z.x + x.w * m.w.x;
    result.x.y = x.x * m.x.y + x.y * m.y.y + x.z * m.z.y + x.w * m.w.y;
    result.x.z = x.x * m.x.z + x.y * m.y.z + x.z * m.z.z + x.w * m.w.z;
    result.x.w = x.x * m.x.w + x.y * m.y.w + x.z * m.z.w + x.w * m.w.w;

    result.y.x = y.x * m.x.x + y.y * m.y.x + y.z * m.z.x + y.w * m.w.x;
    result.y.y = y.x * m.x.y + y.y * m.y.y + y.z * m.z.y + y.w * m.w.y;
    result.y.z = y.x * m.x.z + y.y * m.y.z + y.z * m.z.z + y.w * m.w.z;
    result.y.w = y.x * m.x.w + y.y * m.y.w + y.z * m.z.w + y.w * m.w.w;

    result.z.x = z.x * m.x.x + z.y * m.y.x + z.z * m.z.x + z.w * m.w.x;
    result.z.y = z.x * m.x.y + z.y * m.y.y + z.z * m.z.y + z.w * m.w.y;
    result.z.z = z.x * m.x.z + z.y * m.y.z + z.z * m.z.z + z.w * m.w.z;
    result.z.w = z.x * m.x.w + z.y * m.y.w + z.z * m.z.w + z.w * m.w.w;

    result.w.x = w.x * m.x.x + w.y * m.y.x + w.z * m.z.x + w.w * m.w.x;
    result.w.y = w.x * m.x.y + w.y * m.y.y + w.z * m.z.y + w.w * m.w.y;
    result.w.z = w.x * m.x.z + w.y * m.y.z + w.z * m.z.z + w.w * m.w.z;
    result.w.w = w.x * m.x.w + w.y * m.y.w + w.z * m.z.w + w.w * m.w.w;

    return result;
}

TMat4 TMat4::operator * (TElt s) const
{
    TMat4 result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    result.w = w * s;

    return result;
}

TMat4 TMat4::operator / (TElt s) const
{
    TMat4 result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;
    result.w = w / s;

    return result;
}

TVec4 operator * (const TMat4& m, const TVec4& v)         // m * v
{
    TVec4 result;

    result.x = v.x * m.x.x + v.y * m.x.y + v.z * m.x.z + v.w * m.x.w;
    result.y = v.x * m.y.x + v.y * m.y.y + v.z * m.y.z + v.w * m.y.w;
    result.z = v.x * m.z.x + v.y * m.z.y + v.z * m.z.z + v.w * m.z.w;
    result.w = v.x * m.w.x + v.y * m.w.y + v.z * m.w.z + v.w * m.w.w;

    return result;
}

TVec4 operator * (const TVec4& v, const TMat4& m)         // v * m
{
    TVec4 result;

    result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + v.w * m.w.x;
    result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + v.w * m.w.y;
    result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + v.w * m.w.z;
    result.w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + v.w * m.w.w;

    return result;
}

TVec4& operator *= (TVec4& v, const TMat4& m)             // v *= m
{
    TElt  t0, t1, t2;

    t0   = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + v.w * m.w.x;
    t1   = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + v.w * m.w.y;
    t2   = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + v.w * m.w.z;
    v.w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + v.w * m.w.w;
    v.x = t0;
    v.y = t1;
    v.z = t2;

    return v;
}

TMat4 trans(const TMat4& m)
{
    TMat4 t;

    t.x.x = m.x.x; t.x.y = m.y.x; t.x.z = m.z.x; t.x.w = m.w.x;
    t.y.x = m.x.y; t.y.y = m.y.y; t.y.z = m.z.y; t.y.w = m.w.y;
    t.z.x = m.x.z; t.z.y = m.y.z; t.z.z = m.z.z; t.z.w = m.w.z;
    t.w.x = m.x.w; t.w.y = m.y.w; t.w.z = m.z.w; t.w.w = m.w.w;

    return t;
}

TMat4 adj(const TMat4& m)
{
    TMat4   result;

    result.x =  cross(m.y, m.z, m.w);
    result.y = -cross(m.x, m.z, m.w);
    result.z =  cross(m.x, m.y, m.w);
    result.w = -cross(m.x, m.y, m.z);

    return result;
}

TElt trace(const TMat4& m)
{
    return m.x.x + m.y.y + m.z.z + m.w.w;
}

TElt det(const TMat4& m)
{
    return dot(m.x, cross(m.y, m.z, m.w));
}

TMat4 inv(const TMat4& m)
{
    TElt  det;
    TMat4 adjoint;
    TMat4 result;

    adjoint = adj(m);               // Find the adjoint
    det = dot(adjoint.x, m.x);

    VL_ASSERT_MSG(det != 0, "(Mat4::inv) matrix is non-singular");

    result = trans(adjoint);
    result /= det;

    return result;
}

TMat4 abs(const TMat4& m)
{
    return TMat4(abs(m.x), abs(m.y), abs(m.z), abs(m.w));
}

TMat4 oprod(const TVec4& a, const TVec4& b)
// returns outerproduct of a and b:  a * trans(b)
{
    TMat4   result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

void TMat4::MakeZero()
{
    TElt* data = &x.x;

    for (int i = 0; i < 16; i++)
        data[i] = vl_zero;
}

void TMat4::MakeIdentity()
{
    TVec4* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = vl_one;
            else
                row[i][j] = vl_zero;
}

void TMat4::MakeDiag(TVec4 d)
{
    TVec4* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = d[i];
            else
                row[i][j] = vl_zero;
}

void TMat4::MakeDiag(TElt k)
{
    TVec4* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = k;
            else
                row[i][j] = vl_zero;
}

void TMat4::MakeBlock(TElt k)
{
    TElt* data = &x.x;

    for (int i = 0; i < 16; i++)
        data[i] = k;
}

TMat3 TMat4::AsMat3() const
{
    return TMat3(x.AsVec3(), y.AsVec3(), z.AsVec3());
}
