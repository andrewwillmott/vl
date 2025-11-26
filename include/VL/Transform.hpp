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

TVec2 HApply(TVec2 v, const TMat3& m);  // Apply given affine row-vector transform 'm' to 'v'
TVec3 HApply(TVec3 v, const TMat4& m);  // Apply given affine row-vector transform 'm' to 'v'
TVec2 HApply(const TMat3& m, TVec2 v);  // Apply given affine col-vector transform 'm' to 'v'
TVec3 HApply(const TMat4& m, TVec3 v);  // Apply given affine col-vector transform 'm' to 'v'

TVec2 HProj(TVec2 v, const TMat3& m);   // Apply given affine row-vector projection 'm' to 'v'
TVec3 HProj(TVec3 v, const TMat4& m);   // Apply given affine row-vector projection 'm' to 'v'
TVec2 HProj(const TMat3& m, TVec2 v);   // Apply given affine col-vector projection 'm' to 'v'
TVec3 HProj(const TMat4& m, TVec3 v);   // Apply given affine col-vector projection 'm' to 'v'

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
{ return proj(TVec3(v, TElt(1)) * m); }
inline TVec3 xform(const TMat3& m, const TVec3& v)
{ return v * m; }
inline TMat3 xform(const TMat3& m, const TMat3& n)
{ return n * m; }

inline TVec3 xform(const TMat4& m, const TVec3& v)
{ return proj(TVec4(v, TElt(1)) * m); }
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
{ return proj(m * TVec3(v, TElt(1))); }
inline TVec3 xform(const TMat3& m, const TVec3& v)
{ return m * v; }
inline TMat3 xform(const TMat3& m, const TMat3& n)
{ return m * n; }

inline TVec3 xform(const TMat4& m, const TVec3& v)
{ return proj(m * TVec4(v, TElt(1))); }
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

inline TVec2 HApply(TVec2 v, const TMat3& m)
{
    return v.x * m.x.AsVec2() + v.y * m.y.AsVec2() + m.z.AsVec2();
}

inline TVec3 HApply(TVec3 v, const TMat4& m)
{
    return v.x * m.x.AsVec3() + v.y * m.y.AsVec3() + v.z * m.z.AsVec3() + m.w.AsVec3();
}

inline TVec2 HApply(const TMat3& m, TVec2 v)
{
    return TVec2(dot(m.x.AsVec2(), v) + m.x.z, dot(m.y.AsVec2(), v) + m.y.z);
}

inline TVec3 HApply(const TMat4& m, TVec3 v)
{
    return TVec3(dot(m.x.AsVec3(), v) + m.x.w, dot(m.y.AsVec3(), v) + m.y.w, dot(m.z.AsVec3(), v) + m.z.w);
}

inline TVec2 HProj(TVec2 v, const TMat3& m)
{
    TVec3 hv = v.x * m.x + v.y * m.y + m.z;
    return proj(hv);
}

inline TVec3 HProj(TVec3 v, const TMat4& m)
{
    TVec4 hv = v.x * m.x + v.y * m.y + v.z * m.z + m.w;
    return proj(hv);
}

inline TVec2 HProj(const TMat3& m, TVec2 v)
{
    TVec3 hv(dot(m.x.AsVec2(), v) + m.x.z, dot(m.y.AsVec2(), v) + m.y.z, dot(m.z.AsVec2(), v) + m.z.z);
    return proj(hv);
}

inline TVec3 HProj(const TMat4& m, TVec3 v)
{
    TVec4 hv(dot(m.x.AsVec3(), v) + m.x.w, dot(m.y.AsVec3(), v) + m.y.w, dot(m.z.AsVec3(), v) + m.z.w, dot(m.w.AsVec3(), v) + m.w.w);
    return proj(hv);
}

#endif
