/*
    File:       Quat.hpp

    Function:   Quaternion utilities

    Copyright:  Andrew Willmott
 */

#ifndef VL_QUAT_H
#define VL_QUAT_H

#include "Swizzle.hpp"


// --- Quat Utilities ---------------------------------------------------------


typedef TVec4 TQuat;

// Quat construction
TQuat MakeQuat(const TVec3& a, const TVec3& b);  // Returns a quaternion representing the rotation from 'a' to 'b'
TQuat MakeQuat(const TVec3& axis, TElt theta);   // Returns a quaternion rotation about 'axis' by 'theta'

TQuat MakeQuat(const TQuat& a, const TQuat& b);  // Returns relative rotation from 'a' to 'b'

TQuat MakeQuatX(TElt theta);                     // Returns a rotation about the x axis by theta (in radians)
TQuat MakeQuatY(TElt theta);                     // Returns a rotation about the y axis by theta (in radians)
TQuat MakeQuatZ(TElt theta);                     // Returns a rotation about the z axis by theta (in radians)

TQuat MakeQuat(const TVec3& v);                  // Makes a quaternion from a vector, e.g., for use in rotation. Prefer to use QuatApply however.
TQuat MakeQuat(TElt s);                          // Makes a quaternion from a scalar -- this will scale another quat or position by 's' when applied/multiplied.

TQuat MakeQuatFromCRot(const TMat3& rot3);       // Make quaternion from column-vector rotation matrix.
TQuat MakeQuatFromRRot(const TMat3& rot3);       // Make quaternion from row-vector rotation matrix.

TMat3 CRotFromQuat(const TQuat& q);              // Return the equivalent column-vector rotation matrix for q
TMat3 RRotFromQuat(const TQuat& q);              // Return the equivalent row-vector rotation matrix for q

TVec3 XFromQuat(const TQuat& q);                 // Return x axis rotated by q. (The x axis in the rotated frame.)
TVec3 YFromQuat(const TQuat& q);                 // Return y axis rotated by q. (The y axis in the rotated frame.)
TVec3 ZFromQuat(const TQuat& q);                 // Return z axis rotated by q. (The z axis in the rotated frame.)

TVec4 AxisAngleFromQuat(const TQuat& q);         // Returns [axis, angle] representation of quaternion

// Quat ops
TVec3 QuatApply(const TVec3& p, const TQuat& q); // Transform point p by applying quaternion q
TQuat QuatMult (const TQuat& a, const TQuat& b); // Concatenate quaternions: the result represents applying 'a' then 'b'.
TQuat QuatConj (const TQuat& q);                 // Quaternion conjugate. if len(q) = 1, this is also the inverse.
TQuat QuatInv  (const TQuat& q);                 // Quaternion inverse.

TQuat NLerp(const TQuat& q1, const TQuat& q2, TElt s); // Return linear + renormalize interpolation between q1 and q2. Fast, accurate for smaller angles
TQuat SLerp(const TQuat& q1, const TQuat& q2, TElt s); // Return spherical interpolation between q1 and q2

TQuat FastRenormalize(const TQuat& q);                 // Renormalizes a mostly-already-normalized quaternion.
TQuat QuatConstrain(const TQuat& q1, const TQuat& q2); // Return q2 adjusted so lerp between q1 & q2 takes shortest path.

TElt  CosAngle(const TQuat& a, const TQuat& b);     // Returns cosine of the angle of the rotation from 'a' to 'b', e.g., that between (a x p) and (b x p)
TElt  Angle   (const TQuat& a, const TQuat& b);     // Returns the angle of the rotation from 'a' to 'b', e.g., that between (a x p) and (b x p)

TElt  CosArcLength(const TQuat& a, const TQuat& b); // Returns cos of "geodesic distance" -- length of shortest arc between a and b in S3 (on the 4D sphere). This is half the angle of rotation due to the double-cover property of quaternions.
TElt  ArcLength   (const TQuat& a, const TQuat& b); // Returns "geodesic distance" -- length of shortest arc/angle between a and b in S3 (on the 4D sphere).

void  DecomposeTwist(const TQuat& q, const TVec3& axis, TQuat* noTwist, TQuat* twist); // Decomposes q into a 'noTwist' rotation around 'axis', and a residual 'twist' rotation.

TQuat ClosestAxialRotTo(VLAxis a, const TQuat& q);  // Find closest rotation around axis 'a' to q
TQuat ClosestRotXYTo(const TQuat& q);               // Find closest rotation around x and y to q.

TQuat QuatPower(const TQuat& q, TElt t); // Returns q^t
TQuat QuatSqrt(TQuat q);                 // Returns q^1/2, faster than QuatPower/Log/etc.
TQuat QuatSqr (TQuat q);                 // Returns q^2, faster than QuatMult/QuatPower.

TQuat Log(const TQuat& q);       // Quaternion log: analogue of [sin(theta), cos(theta)] -> theta. For unit quaternions, result.w = 0
TQuat Exp(const TQuat& q);       // Quaternion exponentiation: analogue of theta -> [sin(theta), cos(theta)]

TQuat LogUnit(const TQuat& q);   // Faster log for unit quaternion input
TQuat ExpUnit(const TQuat& q);   // Faster exp for unit quaternion input

TVec3 LogUnit3(const TQuat& q);  // LogUnit variant that omits the last (zero) component
TQuat ExpUnit3(const TVec3& lq); // ExpUnit variant that omits the last (zero) component

TVec3 QuatDiff3(const TQuat& a, const TQuat& b); // Returns LogUnit3(MakeQuat(a, b)) -- useful for rotational velocity, and other log/tangent-space deltas

TQuat SLerp(TQuat q, TVec3 wd, TElt t);  // SLerp that takes wd=QuatDiff3(q, qb)). Avoids acos, allows multiple rotations by scaling wd
TQuat SLerp(TQuat q, TVec3 n, TElt w, TElt t);  // Alternate version with separate (normalised) axis and angle


// --- Inlines ----------------------------------------------------------------

#ifdef VL_DEBUG
namespace
{
    inline bool vl_is_unit(const TQuat& v, TElt eps = TElt(1e-3))
    {
        TElt s = 1 - sqrlen(v);
        return s > -eps && s < eps;
    }
}
#endif

inline TQuat MakeQuatX(TElt theta)
{
    theta *= TElt(0.5);
    TElt s, c; vl_sincos(theta, &s, &c);
    return TQuat(s, TElt(0), TElt(0), c);
}

inline TQuat MakeQuatY(TElt theta)
{
    theta *= TElt(0.5);
    TElt s, c; vl_sincos(theta, &s, &c);
    return TQuat(TElt(0), s, TElt(0), c);
}

inline TQuat MakeQuatZ(TElt theta)
{
    theta *= TElt(0.5);
    TElt s, c; vl_sincos(theta, &s, &c);
    return TQuat(TElt(0), TElt(0), s, c);
}

inline TQuat MakeQuat(const TVec3& point)
{
    return TQuat(point, TElt(1));
}

inline TQuat MakeQuat(TElt s)
{
    return TQuat(TElt(0), TElt(0), TElt(0), s);
}

inline TQuat MakeQuat(const TQuat& a, const TQuat& b)
{
    // return QuatMult(QuatInv(a), b);
    TQuat result;
    result.x = + a.w * b.x - a.z * b.y + a.y * b.z - a.x * b.w;
    result.y = + a.z * b.x + a.w * b.y - a.x * b.z - a.y * b.w;
    result.z = - a.y * b.x + a.x * b.y + a.w * b.z - a.z * b.w;
    result.w = + a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    return result / sqrlen(a);  // worth having a MakeQuatUnit?
}

inline TVec3 XFromQuat(const TQuat& q)
{
    return TVec3(1 - 2 * (q.y * q.y + q.z * q.z), 2 * (q.x * q.y + q.w * q.z), 2 * (q.x * q.z - q.w * q.y));
}

inline TVec3 YFromQuat(const TQuat& q)
{
    return TVec3(2 * (q.x * q.y - q.w * q.z), 1 - 2 * (q.x * q.x + q.z * q.z), 2 * (q.y * q.z + q.w * q.x));
}

inline TVec3 ZFromQuat(const TQuat& q)
{
    return TVec3(2 * (q.x * q.z + q.w * q.y), 2 * (q.y * q.z - q.w * q.x), 1 - 2 * (q.x * q.x + q.y * q.y));
}

inline TVec3 QuatApply(const TVec3& p, const TQuat& q)
{
    // total = 18*, 12+
    TVec3 b0 = cross(xyz(q), p);
    TVec3 b1 = cross(xyz(q), b0);
    return p + 2 * (b0 * q.w + b1);
}

inline TQuat QuatMult(const TQuat& a, const TQuat& b)
{
    // total = 16*, 12+
    TQuat result;
    result.x = + a.w * b.x + a.z * b.y - a.y * b.z + a.x * b.w;  // a.w b.v + b.w a.v + a.v x b.v
    result.y = - a.z * b.x + a.w * b.y + a.x * b.z + a.y * b.w;
    result.z = + a.y * b.x - a.x * b.y + a.w * b.z + a.z * b.w;
    result.w = - a.x * b.x - a.y * b.y - a.z * b.z + a.w * b.w;  // a.w * b.w - dot(a, b)

    return result;
}

inline TQuat QuatConj(const TQuat& q)
{
    return TQuat(-q.x, -q.y, -q.z, q.w);
}

inline TQuat QuatInv(const TQuat& q)
{
    return QuatConj(q) / sqrlen(q);
}

inline TQuat NLerp(const TQuat& q1, const TQuat& q2, TElt s)
{
    return FastRenormalize(lerp(q1, q2, s));
}

inline TQuat QuatConstrain(const TQuat& q1, const TQuat& q2)
{
    return dot(q1, q2) < 0 ? -q2 : q2;
}

inline TQuat FastRenormalize(const TQuat& q)
{
    TElt approxOneOverLen = (TElt(3) - sqrlen(q)) * TElt(0.5);
    return q * approxOneOverLen;
}

inline TElt CosAngle(const TQuat& a, const TQuat& b)
{
    VL_ASSERT(vl_is_unit(a));
    VL_ASSERT(vl_is_unit(b));
    return 2 * sqr(dot(a, b)) - 1;
}

inline TElt Angle(const TQuat& a, const TQuat& b)
{
    VL_ASSERT(vl_is_unit(a));
    VL_ASSERT(vl_is_unit(b));
    return 2 * std::acos(vl_clamp<TElt>(dot(a, b), -1, 1));  // Equivalent to LogUnit(QuatMult(inv(a), b)) = LogUnit(MakeQuat(a, b)), namely angle of the rotation from a to b.
}

inline TElt CosArcLength(const TQuat& a, const TQuat& b)
{
    VL_ASSERT(vl_is_unit(a));
    VL_ASSERT(vl_is_unit(b));
    return dot(a, b);
}

inline TElt ArcLength(const TQuat& a, const TQuat& b)
{
    VL_ASSERT(vl_is_unit(a));
    VL_ASSERT(vl_is_unit(b));
    return std::acos(vl_clamp<TElt>(dot(a, b), -1, 1));  // Equivalent to LogUnit(QuatMult(inv(a), b)) = LogUnit(MakeQuat(a, b)), namely angle of the rotation from a to b.
}

inline TQuat QuatPower(const TQuat& q, TElt t)
{
    TVec3 lq = LogUnit3(q);

    TElt theta = len(lq);
    TElt ttheta = t * theta;

    return TQuat(lq * (std::sin(ttheta) / (theta + TElt(1e-8))), std::cos(ttheta));
}

inline TQuat QuatSqrt(TQuat q)
{
    q.w += 1;
    return norm_safe(q);  // https://maxime-tournier.github.io/notes/quaternions.html#fast-square-root
}

inline TQuat QuatSqr(TQuat q)
{
    return { 2 * xyz(q) * q.w, sqr(q.w) - sqrlen(xyz(q)) };  // cross term drops out.
}

inline TQuat Log(const TQuat& q)
{
    TElt qLen = len(q);
    TElt s = len(xyz(q));
    TElt c = q.w;
    return TQuat((std::atan2(s, c) / (s + TElt(1e-8))) * xyz(q), std::log(qLen));
}

inline TQuat Exp(const TQuat& q)
{
    TElt theta = len(xyz(q));
    return std::exp(q.w) * TQuat(xyz(q) * (std::sin(theta) / (theta + vlf_eps)), std::cos(theta));
}

inline TQuat LogUnit(const TQuat& q)
{
    VL_ASSERT(vl_is_unit(q));
    TElt s = len(xyz(q));
    TElt c = q.w;
    return TQuat((std::atan2(s, c) / (s + TElt(1e-8))) * xyz(q), 0);
}

inline TQuat ExpUnit(const TQuat& q)
{
    VL_ASSERT(abs(q.w) < TElt(1e-8));

    TElt theta = len(xyz(q));
    return TQuat(xyz(q) * (std::sin(theta) / (theta + TElt(1e-8))), std::cos(theta));
}

inline TVec3 LogUnit3(const TQuat& q)
{
    VL_ASSERT(vl_is_unit(q));
    TElt s = len(xyz(q));
    TElt c = q.w;
    return (std::atan2(s, c) / (s + TElt(1e-8))) * xyz(q);
}

inline TQuat ExpUnit3(const TVec3& lq)
{
    TElt theta = len(lq);
    return TQuat(lq * (std::sin(theta) / (theta + TElt(1e-8))), std::cos(theta));
}

#endif
