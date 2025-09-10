/*
    File:       Transform.cpp

    Function:   Implements various Mat234 transforms

    Copyright:  Andrew Willmott
*/


#include "VL/Transform.hpp"


TMat2 CRot2(TElt theta)
{
    TElt s, c;
    vl_sincos(theta, &s, &c);

    TMat2 m;

    m.x.x = c; m.x.y = -s;
    m.y.x = s; m.y.y =  c;

    return m;
}

TMat2 RRot2(TElt theta)
{
    TElt s, c;
    vl_sincos(theta, &s, &c);

    TMat2 m;

    m.x.x =  c; m.x.y = s;
    m.y.x = -s; m.y.y = c;

    return m;
}

TMat2 Scale2(const TVec2& s)
{
    TMat2 m;

    m.x.x = s.x ; m.x.y = vl_0;
    m.y.x = vl_0; m.y.y = s.y ;

    return m;
}


// Mat3

TMat3 CRot3(const TVec3& axis, TElt theta)
{
    theta /= TElt(2);

    TElt s, c;
    vl_sincos(theta, &s, &c);

    TQuat q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return CRot3(q);
}

TMat3 RRot3(const TVec3& axis, TElt theta)
{
    theta /= TElt(2);

    TElt s, c;
    vl_sincos(theta, &s, &c);

    TQuat q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return RRot3(q);
}

TMat3 CRot3(VLAxis axis, TElt angle)
{
    int a0 = axis;
    int a1 = (axis + 1) % 3;
    int a2 = (axis + 2) % 3;

    TElt s, c;
    vl_sincos(angle, &s, &c);

    TMat3 rot = vl_0;
    rot(a0, a0) =  1;
    rot(a1, a1) =  c;
    rot(a1, a2) = -s;
    rot(a2, a2) =  c;
    rot(a2, a1) = +s;

    return rot;
}

TMat3 RRot3(VLAxis axis, TElt angle)
{
    int a0 = axis;
    int a1 = (axis + 1) % 3;
    int a2 = (axis + 2) % 3;

    TElt s, c;
    vl_sincos(angle, &s, &c);

    TMat3 rot = vl_0;
    rot(a0, a0) =  1;
    rot(a1, a1) =  c;
    rot(a1, a2) =  s;
    rot(a2, a2) =  c;
    rot(a2, a1) = -s;

    return rot;
}

namespace
{
    inline TVec3 FindOrthoVector(const TVec3& v)
    {
        TVec3 u;

        // we choose the axis that is most orthogonal to v,
        // and return the cross product of it and v.

        if (abs(v.x) < abs(v.y))
            if (abs(v.x) < abs(v.z))
            {   u.x =     0; u.y =  v.z; u.z = -v.y; }
            else
            {   u.x =  v.y; u.y = -v.x; u.z =     0; }
        else
            if (abs(v.y) < abs(v.z))
            {   u.x = -v.z; u.y =     0; u.z =  v.x; }
            else
            {   u.x =  v.y; u.y = -v.x; u.z =     0; }

        return u;
    }
}

TMat3 CRot3(const TVec3& from, const TVec3& to)
{
    TVec3 axis(cross(from, to));

    TElt s = len(axis);        // sin(theta) between from & to
    TElt c = dot(from, to);    // cos(theta)

    if (s < 1e-6f) // identical or opposing directions; substitute arbitrary orthogonal vector
        axis = norm(FindOrthoVector(from));
    else
        axis /= s;

    // Rodrigues' rotation formula for rotating about unit-length axis by theta.
    TVec3 ta = axis * (1 - c);
    TVec3 sa = axis * s;

    // oprod(t, axis) + c/s mix
    TMat3 result
    (
        ta[0] * axis[0] + c    ,  ta[1] * axis[0] - sa[2],  ta[2] * axis[0] + sa[1],
        ta[0] * axis[1] + sa[2],  ta[1] * axis[1] + c   ,   ta[2] * axis[1] - sa[0],
        ta[0] * axis[2] - sa[1],  ta[1] * axis[2] + sa[0],  ta[2] * axis[2] + c
    );

    return result;
}

TMat3 RRot3(const TVec3& from, const TVec3& to)
{
    TVec3 axis(cross(from, to));

    TElt s = len(axis);        // sin(theta) between from & to
    TElt c = dot(from, to);    // cos(theta)

    if (s < 1e-6f) // identical or opposing directions; substitute arbitrary orthogonal vector
        axis = norm(FindOrthoVector(from));
    else
        axis /= s;

    // Rodrigues' rotation formula for rotating about unit-length axis by theta.
    TVec3 ta = axis * (1 - c);
    TVec3 sa = axis * s;

    // oprod(t, axis) + c/s mix
    TMat3 result
    (
        ta[0] * axis[0] + c    ,  ta[0] * axis[1] + sa[2],  ta[0] * axis[2] - sa[1],
        ta[1] * axis[0] - sa[2],  ta[1] * axis[1] + c   ,   ta[1] * axis[2] + sa[0],
        ta[2] * axis[0] + sa[1],  ta[2] * axis[1] - sa[0],  ta[2] * axis[2] + c
    );

    return result;
}


TMat3 Scale3(const TVec3& s)
{
    TMat3 m(vl_0);

    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = s.z;

    return m;
}

TMat3 HCRot3(TElt theta)
{
    TElt s, c;
    vl_sincos(theta, &s, &c);

    TMat3 m;

    m.x.x =  c; m.x.y = -s; m.x.z =  vl_0;
    m.y.x =  s; m.y.y =  c; m.y.z =  vl_0;
    m.z = vl_z;

    return m;
}

TMat3 HRRot3(TElt theta)
{
    TElt s, c;
    vl_sincos(theta, &s, &c);

    TMat3 m;

    m.x.x =  c; m.x.y =  s; m.x.z =  vl_0;
    m.y.x = -s; m.y.y =  c; m.y.z =  vl_0;
    m.z = vl_z;

    return m;
}

TMat3 HScale3(const TVec2& s)
{
    TMat3 m(vl_0);

    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = vl_1;

    return m;
}

TMat3 HCTrans3(const TVec2& t)
{
    TMat3 m(vl_I);

    m.x.z = t.x;
    m.y.z = t.y;

    return m;
}

TMat3 HRTrans3(const TVec2& t)
{
    TMat3 m(vl_I);

    m.z.x = t.x;
    m.z.y = t.y;

    return m;
}


// Mat4

TMat4 HCRot4(const TVec3& axis, TElt theta)
{
    theta /= TElt(2);

    TElt s, c;
    vl_sincos(theta, &s, &c);

    TVec4 q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return HCRot4(q);
}

TMat4 HRRot4(const TVec3& axis, TElt theta)
{
    theta /= TElt(2);

    TElt s, c;
    vl_sincos(theta, &s, &c);

    TVec4 q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return HRRot4(q);
}

TMat4 HCRot4(VLAxis axis, TElt theta)
{
    TMat3 m3 = CRot3(axis, theta);
    return TMat4(m3, vl_1);
}

TMat4 HRRot4(VLAxis axis, TElt theta)
{
    TMat3 m3 = RRot3(axis, theta);
    return TMat4(m3, vl_1);
}

TMat4 HCRot4(const TVec3& from, const TVec3& to)
{
    TMat3 m3 = CRot3(from, to);
    return TMat4(m3, vl_1);
}

TMat4 HRRot4(const TVec3& from, const TVec3& to)
{
    TMat3 m3 = RRot3(from, to);
    return TMat4(m3, vl_1);
}

TMat4 HScale4(const TVec3& s)
{
    TMat4 m(vl_0);

    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = s.z;
    m.w.w = vl_1;

    return m;
}

TMat4 HCTrans4(const TVec3& t)
{
    TMat4 m(vl_I);

    m.x.w = t.x;
    m.y.w = t.y;
    m.z.w = t.z;

    return m;
}

TMat4 HRTrans4(const TVec3& t)
{
    TMat4 m(vl_I);

    m.w.x = t.x;
    m.w.y = t.y;
    m.w.z = t.z;

    return m;
}
