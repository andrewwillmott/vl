/*
    File:       Transform.hpp

    Function:   Provides 2/3/4D transformation matrices.

    Copyright:  Andrew Willmott
*/

#ifndef VL_TRANSFORM_H
#define VL_TRANSFORM_H

TMat2 CRot2   (TElt theta);
TMat2 RRot2   (TElt theta);
TMat2 Scale2  (const TVec2& s);

// Note: all rotations are right-handed.
TMat3 Scale3  (const TVec3& s);                     // Scales vector by 's'
TMat3 CRot3   (const TVec3& axis, TElt theta);      // Rotate col vector around axis by theta in radians.
TMat3 RRot3   (const TVec3& axis, TElt theta);      // Rotate row vector around axis by theta in radians
TMat3 CRot3   (VLAxis       axis, TElt theta);      // Rotate col vector around axis by theta in radians.
TMat3 RRot3   (VLAxis       axis, TElt theta);      // Rotate row vector around axis by theta in radians
TMat3 CRot3   (const TVec4& q);                     // Rotate col vector using given quaternion
TMat3 RRot3   (const TVec4& q);                     // Rotate row vector using given quaternion
TMat3 CRot3   (const TVec3& from, const TVec3& to); // Rotates col vector 'from' to vector 'to'
TMat3 RRot3   (const TVec3& from, const TVec3& to); // Rotates row vector 'from' to vector 'to'

TMat3 HScale3 (const TVec2& s);     // Scale2 as 3x3 homogeneous matrix
TMat3 HCRot3  (TElt theta);         // Rot2 as 3x3 homogeneous matrix on col vectors: see 'proj'.
TMat3 HRRot3  (TElt theta);         // Rot2 as 3x3 homogeneous matrix on row vectors: see 'proj'
TMat3 HCTrans3(const TVec2& t);     // Given 2d translation as 3x3 homogeneous matrix on col vectors
TMat3 HRTrans3(const TVec2& t);     // Given 2d translation as 3x3 homogeneous matrix on row vectors

TMat4 HScale4 (const TVec3& s);     // Scale3 as 4x4 homogeneous matrix
TMat4 HCRot4  (const TVec3& axis, TElt theta);       // CRot3 as 4x4 homogeneous matrix
TMat4 HRRot4  (const TVec3& axis, TElt theta);       // RRot3 as 4x4 homogeneous matrix
TMat4 HCRot4  (VLAxis       axis, TElt theta);       // CRot3 as 4x4 homogeneous matrix
TMat4 HRRot4  (VLAxis       axis, TElt theta);       // RRot3 as 4x4 homogeneous matrix
TMat4 HCRot4  (const TVec4& q);                      // CRot3 as 4x4 homogeneous matrix
TMat4 HRRot4  (const TVec4& q);                      // RRot3 as 4x4 homogeneous matrix
TMat4 HCRot4  (const TVec3& from, const TVec3& to);  // CRot3 as 4x4 homogeneous matrix
TMat4 HRRot4  (const TVec3& from, const TVec3& to);  // RRot3 as 4x4 homogeneous matrix
TMat4 HCTrans4(const TVec3& t);     // Given 3d translation as 4x4 homogeneous matrix on col vectors
TMat4 HRTrans4(const TVec3& t);     // Given 3d translation as 4x4 homogeneous matrix on row vectors

// Legacy, strongly recommended you use explicit RRot/CRot calls.
#ifdef VL_ROW_ORIENT
inline TMat2 Rot2(TElt theta)                            { return RRot2(theta); }

inline TMat3 Rot3(const TVec3& axis, TElt theta)         { return RRot3(axis, theta); }
inline TMat3 Rot3(const TVec4& quaternion)               { return RRot3(quaternion); }
inline TMat3 Rot3(const TVec3& from, const TVec3& to)    { return RRot3(from, to); }

inline TMat3 HRot3  (TElt theta)                         { return HRRot3(theta); }
inline TMat3 HTrans3(const TVec2& t)                     { return HRTrans3(t); }

inline TMat4 HRot4  (const TVec3& axis, TElt theta)      { return HRRot4(axis, theta); }
inline TMat4 HRot4  (const TVec4& q)                     { return HRRot4(q); }
inline TMat4 HRot4  (const TVec3& from, const TVec3& to) { return HRRot4(from, to); }
inline TMat4 HTrans4(const TVec3& t)                     { return HRTrans4(t); }

inline TVec2 xform(const TMat2& m, const TVec2& v)
{ return v * m; }
inline TMat2 xform(const TMat2& m, const TMat2& n)
{ return n * m; }

inline TVec2 xform(const TMat3& m, const TVec2& v)
{ return proj(TVec3(v, 1.0) * m); }
inline TVec3 xform(const TMat3& m, const TVec3& v)
{ return v * m; }
inline TMat3 xform(const TMat3& m, const TMat3& n)
{ return n * m; }

inline TVec3 xform(const TMat4& m, const TVec3& v)
{ return proj(TVec4(v, 1.0) * m); }
inline TVec4 xform(const TMat4& m, const TVec4& v)
{ return v * m; }
inline TMat4 xform(const TMat4& m, const TMat4& n)
{ return n * m; }

#else
inline TMat2 Rot2(TElt theta)                            { return CRot2(theta); }

inline TMat3 Rot3(const TVec3& axis, TElt theta)         { return CRot3(axis, theta); }
inline TMat3 Rot3(const TVec4& quaternion)               { return CRot3(quaternion); }
inline TMat3 Rot3(const TVec3& from, const TVec3& to)    { return CRot3(from, to); }

inline TMat3 HRot3  (TElt theta)                         { return HCRot3(theta); }
inline TMat3 HTrans3(const TVec2& t)                     { return HCTrans3(t); }

inline TMat4 HRot4  (const TVec3& axis, TElt theta)      { return HCRot4(axis, theta); }
inline TMat4 HRot4  (const TVec4& q)                     { return HCRot4(q); }
inline TMat4 HRot4  (const TVec3& from, const TVec3& to) { return HCRot4(from, to); }
inline TMat4 HTrans4(const TVec3& t)                     { return HCTrans4(t); }

inline TVec2 xform(const TMat2& m, const TVec2& v)
{ return m * v; }
inline TMat2 xform(const TMat2& m, const TMat2& n)
{ return m * n; }

inline TVec2 xform(const TMat3& m, const TVec2& v)
{ return proj(m * TVec3(v, 1.0)); }
inline TVec3 xform(const TMat3& m, const TVec3& v)
{ return m * v; }
inline TMat3 xform(const TMat3& m, const TMat3& n)
{ return m * n; }

inline TVec3 xform(const TMat4& m, const TVec3& v)
{ return proj(m * TVec4(v, 1.0)); }
inline TVec4 xform(const TMat4& m, const TVec4& v)
{ return m * v; }
inline TMat4 xform(const TMat4& m, const TMat4& n)
{ return m * n; }
#endif


// --- Inlines ----------------------------------------------------------------

inline TMat3 CRot3(const TQuat& q)
{
    return CRotFromQuat(q);
}

inline TMat3 RRot3(const TQuat& q)
{
    return RRotFromQuat(q);
}

inline TMat4 HCRot4(const TQuat& q)
{
    return TMat4(CRotFromQuat(q));
}

inline TMat4 HRRot4(const TQuat& q)
{
    return TMat4(RRotFromQuat(q));
}

#endif
