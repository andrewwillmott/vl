/*
    File:       Mat4.hpp

    Function:   Defines a 4 x 4 matrix.

    Copyright:  Andrew Willmott
 */

#ifndef VL_MAT4_H
#define VL_MAT4_H

#include "Vec4.hpp"


// --- Mat4 Class -------------------------------------------------------------

class TVec3;

class TMat4 : public VLMatType
{
public:
    typedef TVec4 Vec;

    // Constructors
    TMat4();
    TMat4(TElt a, TElt b, TElt c, TElt d,
          TElt e, TElt f, TElt g, TElt h,
          TElt i, TElt j, TElt k, TElt l,
          TElt m, TElt n, TElt o, TElt p);
    TMat4(TVec4 v0, TVec4 v1, TVec4 v2, TVec4 v3);
    TMat4(const TMat4& m);

    TMat4(TVec4 diagonal);
    TMat4(VLDiag k);
    TMat4(VLBlock k);

    explicit TMat4(const TMat3& m, TElt scale = TElt(vl_1));
    explicit TMat4(const TElt data[16]);

    template<class T, class U = typename T::IsMat> explicit TMat4(const T& v);

    // Accessor functions
    int          Elts() const { return 16; };
    int          Rows() const { return  4; };
    int          Cols() const { return  4; };

    TVec4&       operator [] (int i);
    const TVec4& operator [] (int i) const;

    TElt&        operator () (int i, int j);
    TElt         operator () (int i, int j) const;

    TElt*        Ref();
    const TElt*  Ref() const;

    // Assignment operators
    TMat4&       operator =  (const TMat4& m);
    TMat4&       operator =  (VLDiag k);
    TMat4&       operator =  (VLBlock k);

    template<class T, class U = typename T::IsMat> TMat4& operator = (const T& m);

    TMat4&       operator += (const TMat4& m);
    TMat4&       operator -= (const TMat4& m);
    TMat4&       operator *= (const TMat4& m);
    TMat4&       operator *= (TElt s);
    TMat4&       operator /= (TElt s);

    // Comparison operators
    bool         operator == (const TMat4& m) const; // M == N?
    bool         operator != (const TMat4& m) const; // M != N?

    // Arithmetic operators
    TMat4        operator + (const TMat4& m) const;  // M + N
    TMat4        operator - (const TMat4& m) const;  // M - N
    const TMat4& operator + () const;                // +M
    TMat4        operator - () const;                // -M
    TMat4        operator * (const TMat4& m) const;  // M * N
    TMat4        operator * (TElt s) const;          // M * s
    TMat4        operator / (TElt s) const;          // M / s

    // Initialisers
    void         MakeZero();                         // Zero matrix
    void         MakeIdentity();                     // Identity matrix
    void         MakeDiag (TVec4 d);                 // Diagonal = d, 0 otherwise
    void         MakeDiag (TElt k = vl_one);         // Diagonal = k, 0 otherwise
    void         MakeBlock(TElt k = vl_one);         // All elts = k

    // Conversion
    TMat3        AsMat3() const;

    // Data
    TVec4 x;
    TVec4 y;
    TVec4 z;
    TVec4 w;
};


// --- Matrix operators -------------------------------------------------------

TVec4& operator *= (TVec4& a, const TMat4& m);        // v *= m
TVec4  operator *  (const TMat4& m, const TVec4& v);  // m * v
TVec4  operator *  (const TVec4& v, const TMat4& m);  // v * m
TMat4  operator *  (const TElt   s, const TMat4& m);  // s * m

TVec4  row(const TMat4& m, int i);             // Return row i of 'm' (same as m[i])
TVec4  col(const TMat4& m, int j);             // Return column i of 'm'

TMat4  trans(const TMat4& m);                  // Transpose
TElt   trace(const TMat4& m);                  // Trace
TMat4  adj  (const TMat4& m);                  // Adjoint
TElt   det  (const TMat4& m);                  // Determinant
TMat4  inv  (const TMat4& m);                  // Inverse
TMat4  abs  (const TMat4& m);                  // abs(m_ij)
TMat4  oprod(const TVec4& a, const TVec4& b);  // Outer product

// The xform functions help avoid dependence on whether row or column
// vectors are used to represent points and vectors.
TVec4  xform(const TMat4& m, const TVec4& v);  // Transform of v by m
TVec3  xform(const TMat4& m, const TVec3& v);  // Hom. xform of v by m
TMat4  xform(const TMat4& m, const TMat4& n);  // Xform v -> m(n(v))


// --- Inlines ----------------------------------------------------------------

inline TMat4::TMat4()
{
}

inline TMat4::TMat4(TVec4 v0, TVec4 v1, TVec4 v2, TVec4 v3) :
    x(v0),
    y(v1),
    z(v2),
    w(v3)
{
}

inline TMat4::TMat4(const TMat4& m) :
    x(m.x),
    y(m.y),
    z(m.z),
    w(m.w)
{
}

inline TMat4::TMat4(TVec4 d)
{
    MakeDiag(d);
}

inline TMat4::TMat4(VLDiag k)
{
    MakeDiag(TElt(k));
}

inline TMat4::TMat4(VLBlock k)
{
    MakeBlock(TElt(k));
}

inline TMat4::TMat4(const TElt m[16])
{
    TElt* elts = (TElt*) this;
    for (int i = 0; i < 16; i++)
        *elts++ = *m++;
}

template<class T, class U> inline TMat4::TMat4(const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat4) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];
}

inline TVec4& TMat4::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 4, "(Mat4::[i]) index out of range");
    return (&x)[i];
}

inline const TVec4& TMat4::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 4, "(Mat4::[i]) index out of range");
    return (&x)[i];
}

inline TElt& TMat4::operator () (int i, int j)
{
    VL_RANGE_MSG(i, 0, 4, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 4, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline TElt TMat4::operator () (int i, int j) const
{
    VL_RANGE_MSG(i, 0, 4, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 4, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline TElt* TMat4::Ref()
{
    return &x.x;
}

inline const TElt* TMat4::Ref() const
{
    return &x.x;
}

inline TMat4& TMat4::operator = (VLDiag k)
{
    MakeDiag(TElt(k));
    return *this;
}

inline TMat4& TMat4::operator = (VLBlock k)
{
    MakeBlock(TElt(k));
    return *this;
}

template<class T, class U> inline TMat4& TMat4::operator = (const T& m)
{
    VL_ASSERT_MSG(Rows() == m.Rows() || m.Rows() == VL_REPEAT, "(Mat4::=) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];

    return *this;
}

inline const TMat4& TMat4::operator + () const
{
    return *this;
}

inline TMat4 operator * (TElt s, const TMat4& m)
{
    return m * s;
}

inline TVec4 row(const TMat4& m, int i)
{
    VL_INDEX(i, 4);
    return TVec4(*(&m.x + i));
}

inline TVec4 col(const TMat4& m, int j)
{
    VL_INDEX(j, 4);
    return TVec4(m.x[j], m.y[j], m.z[j], m.w[j]);
}

#endif
