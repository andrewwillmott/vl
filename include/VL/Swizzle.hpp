/*
    File:       VLSwizzle.hpp

    Function:   Swizzling operators and helpers for vectors

    Copyright:  Andrew Willmott
 */

#ifndef VL_SWIZZLE_H
#define VL_SWIZZLE_H

// Vec3->Vec2
const TVec2 xy(const TVec3& v);
const TVec2 yz(const TVec3& v);
const TVec2 xz(const TVec3& v);

// Vec4->Vec2
const TVec2 xy(const TVec4& v);
const TVec2 yz(const TVec4& v);
const TVec2 zw(const TVec4& v);

const TVec2 xw(const TVec4& v);
const TVec2 yw(const TVec4& v);
const TVec2 zw(const TVec4& v);

// Vec4->Vec3
const TVec3 xyz(const TVec4& v);
const TVec3 xyw(const TVec4& v);
const TVec3 yzw(const TVec4& v);
const TVec3 xzw(const TVec4& v);

// Reversal
const TVec2 reverse(const TVec2& v);
const TVec3 reverse(const TVec3& v);
const TVec4 reverse(const TVec4& v);


// --- Inlines ----------------------------------------------------------------

inline const TVec2 xy(const TVec3& v)
{
    return TVec2(v.x, v.y);
}
inline const TVec2 yz(const TVec3& v)
{
    return TVec2(v.y, v.z);
}
inline const TVec2 xz(const TVec3& v)
{
    return TVec2(v.x, v.z);
}


inline const TVec2 xy(const TVec4& v)
{
    return TVec2(v.x, v.y);
}
inline const TVec2 yz(const TVec4& v)
{
    return TVec2(v.y, v.z);
}
inline const TVec2 xw(const TVec4& v)
{
    return TVec2(v.x, v.w);
}
inline const TVec2 yw(const TVec4& v)
{
    return TVec2(v.y, v.w);
}
inline const TVec2 zw(const TVec4& v)
{
    return TVec2(v.z, v.w);
}


inline const TVec3 xyz(const TVec4& v)
{
    return TVec3(v.x, v.y, v.z);
}
inline const TVec3 xyw(const TVec4& v)
{
    return TVec3(v.x, v.y, v.w);
}
inline const TVec3 yzw(const TVec4& v)
{
    return TVec3(v.y, v.z, v.w);
}
inline const TVec3 xzw(const TVec4& v)
{
    return TVec3(v.x, v.z, v.w);
}


inline const TVec2 reverse(const TVec2& v)
{
    return TVec2(v.y, v.x);
}
inline const TVec3 reverse(const TVec3& v)
{
    return TVec3(v.z, v.y, v.x);
}
inline const TVec4 reverse(const TVec4& v)
{
    return TVec4(v.w, v.z, v.y, v.x);
}

#endif
