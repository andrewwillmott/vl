/*
    File:       Quat.cpp

    Function:   Implements Quat.h

    Copyright:  Andrew Willmott
*/


#include "VL/Quat.h"


TQuat MakeQuat(const TVec3& v1, const TVec3& v2)
{
   TVec3 half = norm_safe(v1 + v2);

   TElt w = dot(half, v1);

   if (w != TElt(0))
       return TQuat(cross(v1, half), w);

   TVec3 altDir(v2.z, v2.x, v2.y);

   return TQuat(norm(cross(v1, altDir)), w);
}

TQuat MakeQuat(const TVec3& axis, TElt theta)
{
    theta *= TElt(0.5);

    TElt s, c;
    vl_sincos(theta, &s, &c);

    return TQuat(s * axis.x, s * axis.y, s * axis.z, c);
}

#ifdef REFERENCE
TQuat QuatMult(const TQuat& a, const TQuat& b)
{
    TQuat  result;
    const TVec3& va = a.AsVec3();
    const TVec3& vb = b.AsVec3();

    result = TQuat(a.w * vb + b.w * va + cross(va, vb), a.w * b.w - dot(va, vb));

    return result;
}
#endif

TQuat QuatMult(const TQuat& a, const TQuat& b)
{
    TQuat result;

    // 16/12
    result.x = + a.x * b.w + a.y * b.z - a.z * b.y + a.w * b.x;
    result.y = - a.x * b.z + a.y * b.w + a.z * b.x + a.w * b.y;
    result.z = + a.x * b.y - a.y * b.x + a.z * b.w + a.w * b.z;
    result.w = - a.x * b.x - a.y * b.y - a.z * b.z + a.w * b.w;

    return result;
}

TQuat MakeQuatFromCRot(const TMat3& R)
{
#ifdef REFERENCE
    // Classic algorithm
    TQuat q;
    TElt s;

    if (R.z.z <= TElt(0))   // x^2 + y^2 >= z^2 + w^2
    {
        TElt yx = R.y.y - R.x.x;
        TElt zz = TElt(1) - R.z.z;

        if (yx <= TElt(0))   // x^2 >= y^2
        {
            s = zz - yx;
            q = TQuat(s, R.x.y + R.y.x, R.x.z + R.z.x, R.z.y - R.y.z);
        }
        else     // y^2 >= x^2
        {
            s = zz + yx;
            q = TQuat(R.x.y + R.y.x, s, R.y.z + R.z.y, R.x.z - R.z.x);
        }
    }
    else     // z^2 + w^2 >= x^2 + y^2
    {
        TElt yx = R.y.y + R.x.x;
        TElt zz = TElt(1) + R.z.z;

        if (yx <= TElt(0))   // z^2 >= w^2
        {
            s = zz - yx;
            q = TQuat(R.x.z + R.z.x, R.y.z + R.z.y, s, R.y.x - R.x.y);
        }
        else     // w^2 >= z^2
        {
            s = zz + yx;
            q = TQuat(R.z.y - R.y.z, R.x.z - R.z.x, R.y.x - R.x.y, s);
        }
    }

    q *= TElt(0.5) / sqrt(s);
    VL_ASSERT(!HasNAN(q));

    return q;
#else
    // Branchless version
    int qc = R.z.z < TElt(0) ? (R.x.x > R.y.y ? 0 : 1) : (R.x.x < -R.y.y ? 2 : 3);

    TElt qs1 = ( qc      & 2) > 0 ? TElt(-1) : TElt(1);
    TElt qs2 = ( qc      & 1) > 0 ? TElt(-1) : TElt(1);
    TElt qs3 = ((qc - 1) & 2) > 0 ? TElt(-1) : TElt(1);

    TElt qt = TElt(1) - qs3 * R.x.x - qs2 * R.y.y - qs1 * R.z.z;
    TElt qs = TElt(0.5) / sqrt(qt);

    TQuat result;
    result[qc ^ 0] = qs * qt;
    result[qc ^ 1] = qs * (R.y.x + qs1 * R.x.y);
    result[qc ^ 2] = qs * (R.x.z + qs2 * R.z.x);
    result[qc ^ 3] = qs * (R.z.y + qs3 * R.y.z);

    return result;
#endif
}

TQuat MakeQuatFromRRot(const TMat3& R)
{
#ifdef REFERENCE
    // Classic algorithm
    TQuat q;
    TElt s;

    if (R.z.z <= TElt(0))   // x^2 + y^2 >= z^2 + w^2
    {
        TElt yx = R.y.y - R.x.x;
        TElt zz = TElt(1) - R.z.z;

        if (yx <= TElt(0))   // x^2 >= y^2
        {
            s = zz - yx;
            q = TQuat(s, R.x.y + R.y.x, R.x.z + R.z.x, R.y.z - R.z.y);
        }
        else     // y^2 >= x^2
        {
            s = zz + yx;
            q = TQuat(R.x.y + R.y.x, q.y = s, q.z = R.y.z + R.z.y, q.w = R.z.x - R.x.z);
        }
    }
    else     // z^2 + w^2 >= x^2 + y^2
    {
        TElt yx = R.y.y + R.x.x;
        TElt zz = TElt(1) + R.z.z;

        if (yx <= TElt(0))   // z^2 >= w^2
        {
            s = zz - yx;
            q = TQuat(R.x.z + R.z.x, q.y = R.y.z + R.z.y, q.z = s, q.w = R.x.y - R.y.x);
        }
        else     // w^2 >= z^2
        {
            s = zz + yx;
            q = TQuat(R.y.z - R.z.y, R.z.x - R.x.z, R.x.y - R.y.x, s);
        }
    }

    q *= TElt(0.5) / sqrt(s);
    VL_ASSERT(!HasNAN(q));

    return q;
#else
    // Branchless version
    int qc = R.z.z < TElt(0) ? (R.x.x > R.y.y ? 0 : 1) : (R.x.x < -R.y.y ? 2 : 3);

    TElt qs1 = ( qc      & 2) > 0 ? TElt(-1) : TElt(1);
    TElt qs2 = ( qc      & 1) > 0 ? TElt(-1) : TElt(1);
    TElt qs3 = ((qc - 1) & 2) > 0 ? TElt(-1) : TElt(1);

    TElt qt = TElt(1) - qs3 * R.x.x - qs2 * R.y.y - qs1 * R.z.z;
    TElt qs = TElt(0.5) / sqrt(qt);

    TQuat result;
    result[qc ^ 0] = qs * qt;
    result[qc ^ 1] = qs * (R.x.y + qs1 * R.y.x);
    result[qc ^ 2] = qs * (R.z.x + qs2 * R.x.z);
    result[qc ^ 3] = qs * (R.y.z + qs3 * R.z.y);
    return result;
#endif
}

TMat3 CRotFromQuat(const TQuat& q)
{
    TElt i2 =  2 * q.x,
         j2 =  2 * q.y,
         k2 =  2 * q.z,
         ij = i2 * q.y,
         ik = i2 * q.z,
         jk = j2 * q.z,
         ri = i2 * q.w,
         rj = j2 * q.w,
         rk = k2 * q.w;

    i2 *= q.x;
    j2 *= q.y;
    k2 *= q.z;

    TMat3 m;

    m.x.x = 1 - j2 - k2;  m.x.y = ij - rk    ;  m.x.z = ik + rj;
    m.y.x = ij + rk    ;  m.y.y = 1 - i2 - k2;  m.y.z = jk - ri;
    m.z.x = ik - rj    ;  m.z.y = jk + ri    ;  m.z.z = 1 - i2 - j2;

    return m;
}

TMat3 RRotFromQuat(const TQuat& q)
{
    TElt i2 =  2 * q.x,
         j2 =  2 * q.y,
         k2 =  2 * q.z,
         ij = i2 * q.y,
         ik = i2 * q.z,
         jk = j2 * q.z,
         ri = i2 * q.w,
         rj = j2 * q.w,
         rk = k2 * q.w;

    i2 *= q.x;
    j2 *= q.y;
    k2 *= q.z;

    TMat3 m;

    m.x.x = 1 - j2 - k2;  m.x.y = ij + rk    ;  m.x.z = ik - rj;
    m.y.x = ij - rk    ;  m.y.y = 1 - i2 - k2;  m.y.z = jk + ri;
    m.z.x = ik + rj    ;  m.z.y = jk - ri    ;  m.z.z = 1 - i2 - j2;

    return m;
}

TVec4 AxisAngleFromQuat(const TQuat& q)
{
    TVec4 aa = norm(q);
    TElt ct = aa.w;
    TElt st = sqrt(TElt(1) - sqr(ct));

    aa.AsVec3() /= st + TElt(1e-6);
    aa.w = TElt(2) * acos(ct);

    return aa;
}

TQuat SLerp(const TQuat& q1, const TQuat& q2, TElt s)
{
//    VL_ASSERT(IsNormalised(q1));
//    VL_ASSERT(IsNormalised(q2));
    VL_ASSERT(s >= TElt(0) && s <= TElt(1));

    // Calculate angle between them.
    TElt cosHalfTheta = dot(q1, q2);

    // If q1 = q2 or q1 = -q2 then theta = 0 and we can return q1
    if (abs(cosHalfTheta) >= TElt(0.999))
        return q1;

    TElt sinHalfTheta = sqrt(TElt(1) - cosHalfTheta * cosHalfTheta);

    // If theta = pi then result is not fully defined, we could rotate around
    // any axis normal to q1 or q2.
    if (sinHalfTheta < TElt(1e-3))
        return TElt(0.5) * (q1 + q2);

    TElt halfTheta = std::cos(cosHalfTheta);

    TElt t = TElt(1) - s;
    TElt ratio1 = std::sin(t * halfTheta) / sinHalfTheta;
    TElt ratio2 = std::sin(s * halfTheta) / sinHalfTheta;

    return ratio1 * q1 + ratio2 * q2;
}

void DecomposeTwist
(
    const TQuat& q,
    const TVec3& axis,
    TQuat*       twist,
    TQuat*       noTwist
)
{
    TVec3 rotAxis = QuatApply(q, axis);

    *noTwist = MakeQuat(axis, rotAxis);
    *twist = QuatMult(QuatInv(*noTwist), q);
}

// See Eberly's "Constrained Quaternions"
// Returns closest rotation about X to qd

TQuat ClosestAxialRotTo(VLAxis a, const TQuat& qd)
{
    TQuat q(vl_w);

    TElt sqrLength = qd[a] * qd[a] + qd.w * qd.w;

    if (sqrLength > TElt(0))
    {
        TElt invLength = TElt(1) / sqrt(sqrLength);

        q[a] = qd[a] * invLength;
        q.w = qd.w * invLength;
    }

    return q;
}

TQuat ClosestRotXYTo(const TQuat& qd)
{
    TElt det = abs(qd.w * qd.z - qd.x * qd.y);

    if (det < TElt(0.5))
    {
        TElt disc = sqrt(TElt(1) - TElt(4) * det * det);
        TElt a = qd.w * qd.x + qd.y * qd.z;
        TElt b = qd.w * qd.w - qd.x * qd.x + qd.y * qd.y - qd.z * qd.z;

        TElt s0;
        TElt c0;

        if (b >= TElt(0))
        {
            s0 = a;
            c0 = TElt(0.5) * (disc + b);
        }
        else
        {
            s0 = TElt(0.5) * (disc - b);
            c0 = a;
        }

        TElt invLength0 = TElt(1) / sqrt(sqr(s0) + sqr(c0));
        s0 *= invLength0;
        c0 *= invLength0;

        TElt s1 = qd.y * c0 + qd.z * s0;
        TElt c1 = qd.w * c0 + qd.x * s0;

        TElt invLength1 = TElt(1) / sqrt(sqr(s1) + sqr(c1));
        s1 *= invLength1;
        c1 *= invLength1;

        return TQuat(s0 * c1, c0 * s1, s0 * s1, c0 * c1);
    }

    TElt invLength = TElt(1) / sqrt(det);

    return TQuat(qd.x * invLength, TElt(0), TElt(0), qd.w * invLength);
}
