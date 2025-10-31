//
// VL234i.cpp
//
// Andrew Willmott
//


#include "VL234i.hpp"
#include <ctype.h>
#include <iomanip>
#include <vector>









Vec4i& Vec4i::MakeUnit(int n, int k)
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

bool Vec4i::operator == (const Vec4i& a) const
{
    return x == a.x && y == a.y && z == a.z && w == a.w;
}

bool Vec4i::operator != (const Vec4i& a) const
{
    return x != a.x || y != a.y || z != a.z || w != a.w;
}

bool Vec4i::operator < (const Vec4i& a) const
{
    return x < a.x && y < a.y && z < a.z && w < a.w;
}

bool Vec4i::operator >= (const Vec4i& a) const
{
    return x >= a.x && y >= a.y && z >= a.z && w >= a.w;
}

Vec4i cross(const Vec4i& a, const Vec4i& b, const Vec4i& c)
{
    Vec4i result;

    result.x =  dot(Vec3i(a.y, b.y, c.y), cross(Vec3i(a.z, b.z, c.z), Vec3i(a.w, b.w, c.w)));
    result.y = -dot(Vec3i(a.x, b.x, c.x), cross(Vec3i(a.z, b.z, c.z), Vec3i(a.w, b.w, c.w)));
    result.z =  dot(Vec3i(a.x, b.x, c.x), cross(Vec3i(a.y, b.y, c.y), Vec3i(a.w, b.w, c.w)));
    result.w = -dot(Vec3i(a.x, b.x, c.x), cross(Vec3i(a.y, b.y, c.y), Vec3i(a.z, b.z, c.z)));

    return result;
}

Vec3i proj(const Vec4i& v)
{
    Vec3i result;

    VL_ASSERT_MSG(v.w != 0, "(Vec4/proj) last elt. is zero");

    result.x = v.x / v.w;
    result.y = v.y / v.w;
    result.z = v.z / v.w;

    return result;
}
