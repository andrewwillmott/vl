#include "VLVec234f.h"




Vec4f& Vec4f::MakeUnit(int n, float k)
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

bool Vec4f::operator == (const Vec4f& a) const
{
    return x == a.x && y == a.y && z == a.z && w == a.w;
}

bool Vec4f::operator != (const Vec4f& a) const
{
    return x != a.x || y != a.y || z != a.z || w != a.w;
}

bool Vec4f::operator < (const Vec4f& a) const
{
    return x < a.x && y < a.y && z < a.z && w < a.w;
}

bool Vec4f::operator >= (const Vec4f& a) const
{
    return x >= a.x && y >= a.y && z >= a.z && w >= a.w;
}

Vec4f cross(const Vec4f& a, const Vec4f& b, const Vec4f& c)
{
    Vec4f result;

    result.x =  dot(Vec3f(a.y, b.y, c.y), cross(Vec3f(a.z, b.z, c.z), Vec3f(a.w, b.w, c.w)));
    result.y = -dot(Vec3f(a.x, b.x, c.x), cross(Vec3f(a.z, b.z, c.z), Vec3f(a.w, b.w, c.w)));
    result.z =  dot(Vec3f(a.x, b.x, c.x), cross(Vec3f(a.y, b.y, c.y), Vec3f(a.w, b.w, c.w)));
    result.w = -dot(Vec3f(a.x, b.x, c.x), cross(Vec3f(a.y, b.y, c.y), Vec3f(a.z, b.z, c.z)));

    return result;
}

Vec3f proj(const Vec4f& v)
{
    Vec3f result;

    VL_ASSERT_MSG(v.w != 0, "(Vec4/proj) last elt. is zero");

    result.x = v.x / v.w;
    result.y = v.y / v.w;
    result.z = v.z / v.w;

    return result;
}
