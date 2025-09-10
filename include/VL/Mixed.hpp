/*
    File:       Mixed.hpp

    Function:   Provides 'mixed' operations that allow matrices of one
                type to be used to transform vectors of another. This
                can be useful if you want to keep your data in a lower
                precision format (e.g., float) for space reasons, but
                use a high-precision format for transformations (e.g.,
                double) for accuracy.

                The operations defined here are the various flavours of
                matrix/vector multiplication, and the necessary dot
                products to implement those.

    Copyright:  Andrew Willmott
*/

#ifdef VL_VEC2_H
    // xform
    TVec2   xform(const TMat2& m, const TVec2& v);
    TVec2   xform(const TMat3& m, const TVec2& v);
    TVec3   xform(const TMat3& m, const TVec3& v);
    TVec3   xform(const TMat4& m, const TVec3& v);
    TVec4   xform(const TMat4& m, const TVec4& v);

    // matrix-vector multiplications
    TVec2&  operator *= (TVec2& v, const TMat2& m);
    TVec2   operator *  (const TMat2& m, const TVec2& v);
    TVec2   operator *  (const TVec2& v, const TMat2& m);

    TVec3&  operator *= (TVec3& v, const TMat3& m);
    TVec3   operator *  (const TMat3& m, const TVec3& v);
    TVec3   operator *  (const TVec3& v, const TMat3& m);

    TVec4   operator *  (const TMat4& m, const TVec4& v);
    TVec4   operator *  (const TVec4& v, const TMat4& m);
    TVec4&  operator *= (TVec4& a, const TMat4& m);
#endif

#ifdef VL_VEC_H
    TMElt dot(TMConstRefVec a, TConstRefVec b);  // v . a

    TVec    operator *  (TConstRefMat m, TConstRefVec v);
    TVec    operator *  (TConstRefVec v, TConstRefMat m);
    TRefVec operator *= (TRefVec      v, TConstRefMat m);

    void Multiply     (TConstRefMat  m, TConstRefVec v, TRefVec result);
    void Multiply     (TConstRefVec  v, TConstRefMat m, TRefVec result);
    void MultiplyAccum(TMConstRefVec v, const TElt s, TRefVec result);
    void OuterProduct (TConstRefVec  a, TConstRefVec b, TRefMat result);
#endif


// --- Inlines ----------------------------------------------------------------

#ifdef VL_VEC2_H

inline TVec2 operator * (const TMat2& m, const TVec2& v)
{
    TVec2 result;

    result[0] = TElt(m[0][0] * v[0] + m[0][1] * v[1]);
    result[1] = TElt(m[1][0] * v[0] + m[1][1] * v[1]);

    return result;
}

inline TVec2 operator * (const TVec2& v, const TMat2& m)
{
    TVec2 result;

    result[0] = TElt(v[0] * m[0][0] + v[1] * m[1][0]);
    result[1] = TElt(v[0] * m[0][1] + v[1] * m[1][1]);

    return result;
}

inline TVec2& operator *= (TVec2& v, const TMat2& m)
{
    TElt t;

    t    = TElt(v[0] * m[0][0] + v[1] * m[1][0]);
    v[1] = TElt(v[0] * m[0][1] + v[1] * m[1][1]);
    v[0] = t;

    return v;
}

inline TVec3 operator * (const TMat3& m, const TVec3& v)
{
    TVec3 result;

    result[0] = TElt(v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2]);
    result[1] = TElt(v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2]);
    result[2] = TElt(v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2]);

    return result;
}

inline TVec3 operator * (const TVec3& v, const TMat3& m)
{
    TVec3 result;

    result[0] = TElt(v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0]);
    result[1] = TElt(v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1]);
    result[2] = TElt(v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2]);

    return result;
}

inline TVec3& operator *= (TVec3& v, const TMat3& m)
{
    TElt t0, t1;

    t0   = TElt(v[0] * m[0][0] + v[1] * m[1][0] + v[2] * m[2][0]);
    t1   = TElt(v[0] * m[0][1] + v[1] * m[1][1] + v[2] * m[2][1]);
    v[2] = TElt(v[0] * m[0][2] + v[1] * m[1][2] + v[2] * m[2][2]);
    v[0] = t0;
    v[1] = t1;

    return v;
}

#ifdef VL_ROW_ORIENT
    inline TVec2 xform(const TMat2& m, const TVec2& v)
    { return v * m; }
    inline TVec2 xform(const TMat3& m, const TVec2& v)
    { return proj(TVec3(v, 1.0) * m); }
    inline TVec3 xform(const TMat3& m, const TVec3& v)
    { return v * m; }
    inline TVec3 xform(const TMat4& m, const TVec3& v)
    { return proj(TVec4(v, 1.0) * m); }
    inline TVec4 xform(const TMat4& m, const TVec4& v)
    { return v * m; }
#else
    inline TVec2 xform(const TMat2& m, const TVec2& v)
    { return m * v; }
    inline TVec2 xform(const TMat3& m, const TVec2& v)
    { return proj(m * TVec3(v, 1.0)); }
    inline TVec3 xform(const TMat3& m, const TVec3& v)
    { return m * v; }
    inline TVec3 xform(const TMat4& m, const TVec3& v)
    { return proj(m * TVec4(v, 1.0)); }
    inline TVec4 xform(const TMat4& m, const TVec4& v)
    { return m * v; }
#endif

#endif
