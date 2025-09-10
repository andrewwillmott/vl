/*
    File:       Mat3.hpp

    Function:   Defines a 3 x 3 matrix.

    Copyright:  Andrew Willmott
*/

#ifndef VL_MAT3_H
#define VL_MAT3_H

#include "Vec3.hpp"


// --- Mat3 Class -------------------------------------------------------------

class TVec4;

class TMat3 : public VLMatType
{
public:
    typedef TVec3 Vec;

    // Constructors
    TMat3();
    TMat3(TElt a, TElt b, TElt c,
          TElt d, TElt e, TElt f,
          TElt g, TElt h, TElt i);
    TMat3(TVec3 v0, TVec3 v1, TVec3 v2);
    TMat3(const TMat3& m);

    TMat3(TVec3 diagonal);
    TMat3(VLDiag k);
    TMat3(VLBlock k);

    explicit TMat3(const TMat2& m, TElt scale = TElt(vl_1));
    explicit TMat3(const TElt m[9]);

    template<class T, class U = typename T::IsMat> explicit TMat3(const T& v);

    // Accessor functions
    int          Elts() const { return 9; };
    int          Rows() const { return 3; };
    int          Cols() const { return 3; };

    TVec3&       operator [] (int i);
    const TVec3& operator [] (int i) const;

    TElt&        operator () (int i, int j);
    TElt         operator () (int i, int j) const;

    TElt*        Ref();
    const TElt*  Ref() const;

    // Assignment operators
    TMat3&       operator =  (const TMat3& m);
    TMat3&       operator =  (VLDiag k);
    TMat3&       operator =  (VLBlock k);

    template<class T, class U = typename T::IsMat> TMat3& operator = (const T& m);

    TMat3&       operator += (const TMat3& m);
    TMat3&       operator -= (const TMat3& m);
    TMat3&       operator *= (const TMat3& m);
    TMat3&       operator *= (TElt s);
    TMat3&       operator /= (TElt s);

    // Comparison operators
    bool         operator == (const TMat3& m) const; // M == N?
    bool         operator != (const TMat3& m) const; // M != N?

    // Arithmetic operators
    TMat3        operator + (const TMat3& m) const;  // M + N
    TMat3        operator - (const TMat3& m) const;  // M - N
    const TMat3& operator + () const;                // +M
    TMat3        operator - () const;                // -M
    TMat3        operator * (const TMat3& m) const;  // M * N
    TMat3        operator * (TElt s) const;          // M * s
    TMat3        operator / (TElt s) const;          // M / s

    // Initialisers
    void         MakeZero();                         // Zero matrix
    void         MakeIdentity();                     // Identity matrix
    void         MakeDiag (TVec3 d);                 // Diagonal = d, 0 otherwise
    void         MakeDiag (TElt k = vl_one);         // Diagonal = k, 0 otherwise
    void         MakeBlock(TElt k = vl_one);         // all elts = k

    // Conversion
    TMat2        AsMat2() const;

    // Data
    TVec3 x;
    TVec3 y;
    TVec3 z;
};


// --- Matrix operators -------------------------------------------------------

TVec3& operator *= (TVec3& v, const TMat3& m);        // v *= m
TVec3  operator *  (const TMat3& m, const TVec3& v);  // m * v
TVec3  operator *  (const TVec3& v, const TMat3& m);  // v * m
TMat3  operator *  (const TElt   s, const TMat3& m);  // s * m

TVec3  row(const TMat3& m, int i);             // Return row i of 'm' (same as m[i])
TVec3  col(const TMat3& m, int j);             // Return column i of 'm'

TMat3  trans(const TMat3& m);                  // Transpose
TElt   trace(const TMat3& m);                  // Trace
TMat3  adj  (const TMat3& m);                  // Adjoint
TElt   det  (const TMat3& m);                  // Determinant
TMat3  inv  (const TMat3& m);                  // Inverse
TMat3  abs  (const TMat3& m);                  // abs(m_ij)
TMat3  oprod(const TVec3& a, const TVec3& b);  // Outer product

// The xform functions help avoid dependence on whether row or column
// vectors are used to represent points and vectors.
TVec3  xform(const TMat3& m, const TVec3& v);  // Transform of v by m
TVec2  xform(const TMat3& m, const TVec2& v);  // Hom. xform of v by m
TMat3  xform(const TMat3& m, const TMat3& n);  // Xform v -> m(n(v))


// --- Inlines ----------------------------------------------------------------

inline TMat3::TMat3()
{
}

inline TMat3::TMat3
(
    TElt a, TElt b, TElt c,
    TElt d, TElt e, TElt f,
    TElt g, TElt h, TElt i
) :
    x(a, b, c),
    y(d, e, f),
    z(g, h, i)
{
}

inline TMat3::TMat3(TVec3 v0, TVec3 v1, TVec3 v2) :
    x(v0),
    y(v1),
    z(v2)
{
}

inline TMat3::TMat3(const TMat3& m) :
    x(m.x),
    y(m.y),
    z(m.z)
{
}

inline TMat3::TMat3(TVec3 d)
{
    MakeDiag(d);
}

inline TMat3::TMat3(VLDiag k)
{
    MakeDiag(TElt(k));
}

inline TMat3::TMat3(VLBlock k)
{
    MakeBlock(TElt(k));
}

inline TMat3::TMat3(const TElt m[9])
{
    TElt* elts = (TElt*) this;
    for (int i = 0; i < 9; i++)
        *elts++ = *m++;
}

template<class T, class U> inline TMat3::TMat3(const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat3) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];
}

inline TVec3& TMat3::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 3, "(Mat3::[i]) index out of range");
    return (&x)[i];
}

inline const TVec3& TMat3::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 3, "(Mat3::[i]) index out of range");
    return (&x)[i];
}

inline TElt& TMat3::operator () (int i, int j)
{
    VL_RANGE_MSG(i, 0, 3, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 3, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline TElt TMat3::operator () (int i, int j) const
{
    VL_RANGE_MSG(i, 0, 3, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 3, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline TElt* TMat3::Ref()
{
    return &x.x;
}

inline const TElt* TMat3::Ref() const
{
    return &x.x;
}

inline void TMat3::MakeZero()
{
    x.x = vl_zero; x.y = vl_zero; x.z = vl_zero;
    y.x = vl_zero; y.y = vl_zero; y.z = vl_zero;
    z.x = vl_zero; z.y = vl_zero; z.z = vl_zero;
}

inline void TMat3::MakeIdentity()
{
    x.x = vl_one;     x.y = vl_zero;    x.z = vl_zero;
    y.x = vl_zero;    y.y = vl_one;     y.z = vl_zero;
    z.x = vl_zero;    z.y = vl_zero;    z.z = vl_one;
}

inline void TMat3::MakeDiag(TVec3 d)
{
    x.x = d.x;        x.y = vl_zero;    x.z = vl_zero;
    y.x = vl_zero;    y.y = d.y;        y.z = vl_zero;
    z.x = vl_zero;    z.y = vl_zero;    z.z = d.z;
}

inline void TMat3::MakeDiag(TElt k)
{
    x.x = k;          x.y = vl_zero;    x.z = vl_zero;
    y.x = vl_zero;    y.y = k;          y.z = vl_zero;
    z.x = vl_zero;    z.y = vl_zero;    z.z = k;
}

inline void TMat3::MakeBlock(TElt k)
{
    x.x = k; x.y = k; x.z = k;
    y.x = k; y.y = k; y.z = k;
    z.x = k; z.y = k; z.z = k;
}

inline TMat2 TMat3::AsMat2() const
{
    return TMat2(x.AsVec2(), y.AsVec2());
}

inline TMat3& TMat3::operator = (VLDiag k)
{
    MakeDiag(TElt(k));
    return *this;
}

inline TMat3& TMat3::operator = (VLBlock k)
{
    MakeBlock(TElt(k));
    return *this;
}

template<class T, class U> inline TMat3& TMat3::operator = (const T& m)
{
   VL_ASSERT_MSG(m.Rows() == Rows()|| m.Rows() == VL_REPEAT, "(Mat3::=) Matrix rows don't match");

   for (int i = 0; i < Rows(); i++)
       (*this)[i] = m[i];

   return *this;
}

inline const TMat3& TMat3::operator + () const
{
    return *this;
}

inline TMat3 operator *  (const TElt s, const TMat3& m)
{
    return m * s;
}

inline TVec3 operator * (const TMat3& m, const TVec3& v)
{
    TVec3 result;

    result.x = v.x * m.x.x + v.y * m.x.y + v.z * m.x.z;
    result.y = v.x * m.y.x + v.y * m.y.y + v.z * m.y.z;
    result.z = v.x * m.z.x + v.y * m.z.y + v.z * m.z.z;

    return result;
}

inline TVec3 operator * (const TVec3& v, const TMat3& m)
{
    TVec3 result;

    result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
    result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
    result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;

    return result;
}

inline TVec3& operator *= (TVec3& v, const TMat3& m)
{
    TElt t0, t1;

    t0  = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
    t1  = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
    v.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
    v.x = t0;
    v.y = t1;

    return v;
}

inline TVec3 row(const TMat3& m, int i)
{
    VL_INDEX(i, 3);
    return TVec3(*(&m.x + i));
}

inline TVec3 col(const TMat3& m, int j)
{
    VL_INDEX(j, 3);
    return TVec3(m.x[j], m.y[j], m.z[j]);
}

#endif

