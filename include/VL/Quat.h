/*
    File:       Quat.h

    Function:   Quaternion utilities

    Copyright:  Andrew Willmott
 */

#ifndef VL_QUAT_H
#define VL_QUAT_H


// --- Quat Class -------------------------------------------------------------


typedef TVec4 TQuat;

// Quat construction
TQuat MakeQuat(const TVec3& a, const TVec3& b);  // Returns a quaternion representing the rotation from a to b
TQuat MakeQuat(const TVec3& axis, TElt theta);   // Returns a quaternion rotation about 'axis' by 'theta'

TQuat MakeQuatX(TElt theta);                      // Returns a rotation about the x axis by theta (in radians)
TQuat MakeQuatY(TElt theta);                      // Returns a rotation about the y axis by theta (in radians)
TQuat MakeQuatZ(TElt theta);                      // Returns a rotation about the z axis by theta (in radians)

TQuat MakeQuat(const TVec3& point);               // Makes a quaternion from a point (e.g., for use in rotation)
TQuat MakeQuat(TElt s);                           // Makes a quaternion from a scalar

TQuat MakeQuatFromCRot(const TMat3& rot3);        // Make quaternion from column-based rotation matrix.
TQuat MakeQuatFromRRot(const TMat3& rot3);        // Make quaternion from row-based rotation matrix.

TMat3 CRotFromQuat(const TQuat& q);               // Return the equivalent column-based rotation matrix for q
TMat3 RRotFromQuat(const TQuat& q);               // Return the equivalent row-based rotation matrix for q

TVec4 AxisAngleFromQuat(const TQuat& q);          // Returns [axis, angle] representation of quaternion

// Quat ops
TVec3 QuatApply(const TQuat& q, const TVec3& p);  // Transform point p by quaternion q
TQuat QuatMult (const TQuat& a, const TQuat& b);  // Concatenate quaternions, the result represents applying qb then qa.
TQuat QuatConj (const TQuat& q);                  // Quaternion conjugate. if len(q) = 1, this is also the inverse.
TQuat QuatInv  (const TQuat& q);                  // Quaternion inverse.

TQuat NLerp(const TQuat& q1, const TQuat& q2, TElt s);   // Return linear + renormalise interpolation between q1 and q2. Fast, accurate for smaller angles
TQuat SLerp(const TQuat& q1, const TQuat& q2, TElt s);   // Return spherical interpolation between q1 and q2

TQuat FastRenormalize(const TQuat& q);                    // Renormalizes a mostly-already-normalized quaternion.
void  ConstrainNeighbourhood(const TQuat& q1, TQuat* q2); // Adjust q2 so lerp between q1 & q2 takes shortest path.

TElt CosAngleBetween(TQuat q0, TQuat q1);          // Returns cosine of the angle between q0 . a vs q1 . a

void DecomposeTwist(const TQuat& q, const TVec3& axis, TQuat* twist, TQuat* noTwist);
// Decomposes q into a 'twist' rotation around 'axis', and a residual 'noTwist' rotation.

TQuat ClosestAxialRotTo(VLAxis a, const TQuat& q); // Find closest rotation around axis 'a' to q
TQuat ClosestRotXYTo(const TQuat& q);              // Find closest rotation around x and y to q.


// --- Inlines ----------------------------------------------------------------

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

inline TVec3 QuatApply(const TQuat& q, const TVec3& p)
{
    // total = 18*, 12+
    TVec3 b0 = cross(q.AsVec3(), p);
    TVec3 b1 = cross(q.AsVec3(), b0);
    return p + 2 * (b0 * q.w + b1);
}

inline TQuat QuatConj(const TQuat& q)
{
    return TQuat(-q[0], -q[1], -q[2], q[3]);
}

inline TQuat QuatInv(const TQuat& q)
{
    return QuatConj(q) / sqrlen(q);
}

inline TQuat NLerp(const TQuat& q1, const TQuat& q2, TElt s)
{
    return FastRenormalize(lerp(q1, q2, s));
}

inline void ConstrainNeighbourhood(const TQuat& q1, TQuat* q2)
{
    if (dot(q1, *q2) < 0)
        *q2 = -*q2;
}

inline TQuat FastRenormalize(const TQuat& q)
{
    TElt approxOneOverLen = (TElt(3) - sqrlen(q)) * TElt(0.5);
    return q * approxOneOverLen;
}

inline TElt CosAngleBetween(TQuat q0, TQuat q1)
{
    return dot(q0, q1);
}

#endif
