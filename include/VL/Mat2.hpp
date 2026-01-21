/*
    File:       Mat2.hpp

    Function:   Defines a 2 x 2 matrix.

    Copyright:  Andrew Willmott
 */

#ifndef VL_MAT2_H
#define VL_MAT2_H

#include "Vec2.hpp"


// --- Mat2 Class -------------------------------------------------------------

class TMat2 : public VLMatType
{
public:
    typedef TVec2 Vec;

    // Constructors
    TMat2();
    TMat2(TElt a, TElt b, TElt c, TElt d);
    TMat2(const TVec2 v0, const TVec2 v1);
    TMat2(const TMat2& m);

    TMat2(TVec2 diagonal);
    TMat2(VLDiag k);
    TMat2(VLBlock k);

    explicit TMat2(const TElt m[4]);

    template<class T, class U = typename T::IsMat> explicit TMat2(const T& v);

    // Accessor functions
    int          Elts() const { return 4; };
    int          Rows() const { return 2; };
    int          Cols() const { return 2; };

    TVec2&       operator [] (int i);
    const TVec2& operator [] (int i) const;

    TElt&        operator () (int i, int j);
    TElt         operator () (int i, int j) const;

    TElt*        Ref();
    const TElt*  Ref() const;

    // Assignment operators
    TMat2&       operator =  (const TMat2& m);
    TMat2&       operator =  (VLDiag k);
    TMat2&       operator =  (VLBlock k);

    template<class T, class U = typename T::IsMat> TMat2& operator = (const T& m);

    TMat2&       operator += (const TMat2& m);
    TMat2&       operator -= (const TMat2& m);
    TMat2&       operator *= (const TMat2& m);
    TMat2&       operator *= (TElt s);
    TMat2&       operator /= (TElt s);

    // Comparison operators
    bool         operator == (const TMat2& m) const; // M == N?
    bool         operator != (const TMat2& m) const; // M != N?

    // Arithmetic operators
    TMat2        operator + (const TMat2& m) const;  // M + N
    TMat2        operator - (const TMat2& m) const;  // M - N
    const TMat2& operator + () const;                // +M
    TMat2        operator - () const;                // -M
    TMat2        operator * (const TMat2& m) const;  // M * N
    TMat2        operator * (TElt s) const;          // M * s
    TMat2        operator / (TElt s) const;          // M / s

    // Initialisers
    void         MakeZero();                         // Zero matrix
    void         MakeIdentity();                     // Identity matrix
    void         MakeDiag (TVec2 d);                 // Diagonal = d, 0 otherwise
    void         MakeDiag (TElt k = vl_one);         // Diagonal = k, 0 otherwise
    void         MakeBlock(TElt k = vl_one);         // all elts = k

    // Data
    TVec2 x;
    TVec2 y;
};


// --- Matrix operators -------------------------------------------------------

TVec2& operator *= (TVec2& v, const TMat2& m);        // v *= m
TVec2  operator *  (const TMat2& m, const TVec2& v);  // m * v
TVec2  operator *  (const TVec2& v, const TMat2& m);  // v * m
TMat2  operator *  (const TElt   s, const TMat2& m);  // s * m

TVec2  row(const TMat2& m, int i);             // Return row i of 'm' (same as m[i])
TVec2  col(const TMat2& m, int j);             // Return column i of 'm'

TMat2  trans(const TMat2& m);                  // Transpose
TElt   trace(const TMat2& m);                  // Trace
TMat2  adj  (const TMat2& m);                  // Adjoint
TElt   det  (const TMat2& m);                  // Determinant
#ifndef VL_NO_REAL
TMat2  inv  (const TMat2& m);                  // Inverse
#endif
TMat2  abs  (const TMat2& m);                  // abs(m_ij)
TMat2  oprod(const TVec2& a, const TVec2& b);  // Outer product

// The xform functions help avoid dependence on whether row or column
// vectors are used to represent points and vectors.
TVec2  xform(const TMat2& m, const TVec2& v);  // Transform of v by m
TMat2  xform(const TMat2& m, const TMat2& n);  // Xform v -> m(n(v))


// --- Inlines ----------------------------------------------------------------


inline TMat2::TMat2()
{
}

inline TMat2::TMat2(TElt a, TElt b, TElt c, TElt d) :
    x(a, b),
    y(c, d)
{
}

inline TMat2::TMat2(TVec2 v0, TVec2 v1) :
    x(v0),
    y(v1)
{
}

inline TMat2::TMat2(const TMat2& m) :
    x(m.x),
    y(m.y)
{
}

inline TMat2::TMat2(TVec2 diag)
{
    MakeDiag(diag);
}

inline TMat2::TMat2(VLDiag k)
{
    MakeDiag(TElt(k));
}

inline TMat2::TMat2(VLBlock k)
{
    MakeBlock(TElt(k));
}

inline TMat2::TMat2(const TElt m[4])
{
    TElt* elts = (TElt*) this;
    for (int i = 0; i < 4; i++)
        *elts++ = *m++;
}

template<class T, class U> inline TMat2::TMat2(const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat2) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];
}

inline TVec2& TMat2::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::[i]) index out of range");
    return (&x)[i];
}

inline const TVec2& TMat2::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::[i]) index out of range");
    return (&x)[i];
}

inline TElt& TMat2::operator () (int i, int j)
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 2, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline TElt TMat2::operator () (int i, int j) const
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 2, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline TElt* TMat2::Ref()
{
    return &x.x;
}

inline const TElt* TMat2::Ref() const
{
    return &x.x;
}

inline void TMat2::MakeZero()
{
    x.x = vl_zero; x.y = vl_zero;
    y.x = vl_zero; y.y = vl_zero;
}

inline void TMat2::MakeDiag(TElt k)
{
    x.x = k;          x.y = vl_zero;
    y.x = vl_zero;    y.y = k;
}

inline void TMat2::MakeDiag(TVec2 d)
{
    x.x = d.x;        x.y = vl_zero;
    y.x = vl_zero;    y.y = d.y;
}

inline void TMat2::MakeIdentity()
{
    x.x = vl_one;     x.y = vl_zero;
    y.x = vl_zero;    y.y = vl_one;
}

inline void TMat2::MakeBlock(TElt k)
{
    x.x = k; x.y = k;
    y.x = k; y.y = k;
}

inline TMat2& TMat2::operator = (VLDiag k)
{
    MakeDiag(TElt(k));
    return *this;
}

inline TMat2& TMat2::operator = (VLBlock k)
{
    MakeBlock(TElt(k));
    return *this;
}

inline TMat2& TMat2::operator = (const TMat2& m)
{
    x = m.x;
    y = m.y;

    return *this;
}

template<class T, class U> inline TMat2& TMat2::operator = (const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat2::=) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];

    return *this;
}

inline TMat2& TMat2::operator += (const TMat2& m)
{
    x += m.x;
    y += m.y;

    return *this;
}

inline TMat2& TMat2::operator -= (const TMat2& m)
{
    x -= m.x;
    y -= m.y;

    return *this;
}

inline TMat2& TMat2::operator *= (const TMat2& m)
{
    TVec2 t;

    t = x.x * m.x + x.y * m.y;
    y = y.x * m.x + y.y * m.y;
    x = t;

    return *this;
}

inline TMat2& TMat2::operator *= (TElt s)
{
    x *= s;
    y *= s;

    return *this;
}

inline TMat2& TMat2::operator /= (TElt s)
{
    x /= s;
    y /= s;

    return *this;
}


inline TMat2 TMat2::operator + (const TMat2& m) const
{
    TMat2 result;

    result.x = x + m.x;
    result.y = y + m.y;

    return result;
}

inline TMat2 TMat2::operator - (const TMat2& m) const
{
    TMat2 result;

    result.x = x - m.x;
    result.y = y - m.y;

    return result;
}

inline const TMat2& TMat2::operator + () const
{
    return *this;
}

inline TMat2 TMat2::operator - () const
{
    TMat2 result;

    result.x = -x;
    result.y = -y;

    return result;
}

inline TMat2 TMat2::operator * (const TMat2& m) const
{
    TMat2 result;

    result.x.x = x.x * m.x.x + x.y * m.y.x;
    result.x.y = x.x * m.x.y + x.y * m.y.y;
    result.y.x = y.x * m.x.x + y.y * m.y.x;
    result.y.y = y.x * m.x.y + y.y * m.y.y;

    return result;
}

inline TMat2 TMat2::operator * (TElt s) const
{
    TMat2 result;

    result.x = x * s;
    result.y = y * s;

    return result;
}

inline TMat2 TMat2::operator / (TElt s) const
{
    TMat2 result;

    result.x = x / s;
    result.y = y / s;

    return result;
}

inline TMat2  operator *  (TElt s, const TMat2& m)
{
    return m * s;
}

inline TVec2 operator * (const TMat2& m, const TVec2& v)
{
    TVec2 result;

    result.x = m.x.x * v.x + m.x.y * v.y;
    result.y = m.y.x * v.x + m.y.y * v.y;

    return result;
}

inline TVec2 operator * (const TVec2& v, const TMat2& m)
{
    TVec2 result;

    result.x = v.x * m.x.x + v.y * m.y.x;
    result.y = v.x * m.x.y + v.y * m.y.y;

    return result;
}

inline TVec2& operator *= (TVec2& v, const TMat2& m)
{
    TElt t;

    t   = v.x * m.x.x + v.y * m.y.x;
    v.y = v.x * m.x.y + v.y * m.y.y;
    v.x = t;

    return v;
}


inline TVec2 row(const TMat2& m, int i)
{
    VL_INDEX(i, 2);
    return TVec2(*(&m.x + i));
}

inline TVec2 col(const TMat2& m, int j)
{
    VL_INDEX(j, 2);
    return TVec2(m.x[j], m.y[j]);
}

inline TMat2 trans(const TMat2& m)
{
    TMat2 result;

    result.x.x = m.x.x; result.x.y = m.y.x;
    result.y.x = m.x.y; result.y.y = m.y.y;

    return result;
}

inline TElt trace(const TMat2& m)
{
    return m.x.x + m.y.y;
}

inline TMat2 adj(const TMat2& m)
{
    TMat2 result;

    result.x = -cross(m.y);
    result.y =  cross(m.x);

    return result;
}

#endif
