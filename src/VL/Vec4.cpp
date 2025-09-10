/*
    File:       Vec4.cpp

    Function:   Implements Vec4.hpp

    Copyright:  Andrew Willmott
*/


#include "VL/Vec4.hpp"


TVec4& TVec4::MakeUnit(int n, TElt k)
{
    if (n == 0)
    { x = k; y = vl_zero; z = vl_zero; w = vl_zero; }
    else if (n == 1)
    { x = vl_zero; y = k; z = vl_zero; w = vl_zero; }
    else if (n == 2)
    { x = vl_zero; y = vl_zero; z = k; w = vl_zero; }
    else if (n == 3)
    { x = vl_zero; y = vl_zero; z = vl_zero; w = k; }
    else
        VL_ERROR("(Vec4::MakeUnit) illegal unit vector");

    return *this;
}

bool TVec4::operator == (const TVec4& a) const
{
    return x == a.x && y == a.y && z == a.z && w == a.w;
}

bool TVec4::operator != (const TVec4& a) const
{
    return x != a.x || y != a.y || z != a.z || w != a.w;
}

bool TVec4::operator < (const TVec4& a) const
{
    return x < a.x && y < a.y && z < a.z && w < a.w;
}

bool TVec4::operator >= (const TVec4& a) const
{
    return x >= a.x && y >= a.y && z >= a.z && w >= a.w;
}

TVec4 cross(const TVec4& a, const TVec4& b, const TVec4& c)
{
    TVec4 result;

    result.x =  dot(TVec3(a.y, b.y, c.y), cross(TVec3(a.z, b.z, c.z), TVec3(a.w, b.w, c.w)));
    result.y = -dot(TVec3(a.x, b.x, c.x), cross(TVec3(a.z, b.z, c.z), TVec3(a.w, b.w, c.w)));
    result.z =  dot(TVec3(a.x, b.x, c.x), cross(TVec3(a.y, b.y, c.y), TVec3(a.w, b.w, c.w)));
    result.w = -dot(TVec3(a.x, b.x, c.x), cross(TVec3(a.y, b.y, c.y), TVec3(a.z, b.z, c.z)));

    return result;
}

TVec3 proj(const TVec4& v)
{
    TVec3 result;

    VL_ASSERT_MSG(v.w != 0, "(Vec4/proj) last elt. is zero");

    result.x = v.x / v.w;
    result.y = v.y / v.w;
    result.z = v.z / v.w;

    return result;
}
