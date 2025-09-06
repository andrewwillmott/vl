/*
    File:       Vec4.h

    Function:   Defines a length-4 vector.

    Copyright:  Andrew Willmott
 */

#ifndef VL_VEC4_H
#define VL_VEC4_H


// --- Vec4 Class -------------------------------------------------------------


class TVec2;
class TVec3;

class TVec4 : public VLVecType
{
public:
    // Constructors
    TVec4();
    TVec4(TElt x, TElt y, TElt z, TElt w);      // [x, y, z, w]
    TVec4(const TVec4& v);                      // Copy constructor
    TVec4(const TVec3& v, TElt w);              // Homogeneous 3D vector

    TVec4(VLBlock     b);                       // vl_0, vl_1, ...
    TVec4(VLAxis      a, TElt s = vl_1);        // vl_x, vl_y
    TVec4(VLMinusAxis a, TElt s = vl_1);        // vl_x, vl_y

    explicit TVec4(TElt s);
    explicit TVec4(const TElt v[]);

    template<class T, class U = typename T::IsVec> explicit TVec4(const T& v);

    // Accessor functions
    int          Elts() const { return 4; };   // Element count

    TElt&        operator [] (int i);          // Indexing by row
    const TElt&  operator [] (int i) const;    // Indexing by row

    TElt*        Ref();                        // Return pointer to data
    const TElt*  Ref() const;                  // Return pointer to data

    // Assignment operators
    TVec4&       operator =  (const TVec4& a);
    TVec4&       operator =  (VLBlock k);
    TVec4&       operator =  (VLAxis k);
    TVec4&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> TVec4& operator = (const T& v);

    TVec4&       operator += (const TVec4& a);
    TVec4&       operator -= (const TVec4& a);
    TVec4&       operator *= (const TVec4& a);
    TVec4&       operator *= (TElt s);
    TVec4&       operator /= (const TVec4& a);
    TVec4&       operator /= (TElt s);

    // Comparison operators
    bool         operator == (const TVec4& a) const; // v == a ?
    bool         operator != (const TVec4& a) const; // v != a ?
    bool         operator <  (const TVec4& a) const; // All v.i <  a.i?
    bool         operator >= (const TVec4& a) const; // All v.i >= a.i?

    // Arithmetic operators
    TVec4        operator + (const TVec4& a) const;  // v + a
    TVec4        operator - (const TVec4& a) const;  // v - a
    const TVec4& operator + () const;                // -v
    TVec4        operator - () const;                // -v
    TVec4        operator * (const TVec4& a) const;  // v * a (vx * ax, ...)
    TVec4        operator * (TElt s) const;        // v * s
    TVec4        operator / (const TVec4& a) const;  // v / a (vx / ax, ...)
    TVec4        operator / (TElt s) const;        // v / s

    // Initialisers
    TVec4&       MakeZero();                        // Zero vector
    TVec4&       MakeUnit(int i, TElt k = vl_one);  // kI[i]
    TVec4&       MakeBlock(TElt k = vl_one);        // All-k vector

    // Conversion
    TVec2&       AsVec2();
    const TVec2& AsVec2() const;
    TVec3&       AsVec3();
    const TVec3& AsVec3() const;

    // Data
    TElt x;
    TElt y;
    TElt z;
    TElt w;
};


// --- Vec4 operators ---------------------------------------------------------

TVec4 operator * (TElt s, const TVec4& v);    // s * v

TElt  dot  (const TVec4& a, const TVec4& b);  // a . b
TVec4 cross(const TVec4& a, const TVec4& b, const TVec4& c); // 4D cross prod.
TElt  sqrlen   (const TVec4& v);              // v . v
#ifndef VL_NO_REAL
TElt  len      (const TVec4& v);              // || v ||
TVec4 norm     (const TVec4& v);              // v / || v ||
TVec4 norm_safe(const TVec4& v);              // v / || v ||, handles || v || = 0
TVec4 inv      (const TVec4& v);              // inverse: 1 / v
TVec3 proj     (const TVec4& v);              // hom. projection
#endif
TVec4 abs      (const TVec4& v);              // abs(v_i)


// --- Inlines ----------------------------------------------------------------

#include "Vec3.h"

inline TVec4::TVec4()
{
}

inline TVec4::TVec4(TElt a, TElt b, TElt c, TElt d) :
    x(a),
    y(b),
    z(c),
    w(d)
{}

inline TVec4::TVec4(const TVec4& v) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(v.w)
{}

inline TVec4::TVec4(const TVec3& v, TElt w_in) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(w_in)
{
}

inline TVec4::TVec4(TElt s) :
    x(s),
    y(s),
    z(s),
    w(s)
{}

inline TVec4::TVec4(const TElt v[]) :
    x(v[0]),
    y(v[1]),
    z(v[2]),
    w(v[3])
{
}

template<class T, class U> inline TVec4::TVec4(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec4) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = TElt(v[i]);
}

inline TElt& TVec4::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 4, "(Vec4::[i]) index out of range");
    return (&x)[i];
}

inline const TElt& TVec4::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 4, "(Vec4::[i]) index out of range");
    return (&x)[i];
}

inline TElt* TVec4::Ref()
{
    return &x;
}

inline const TElt* TVec4::Ref() const
{
    return &x;
}

inline TVec4& TVec4::operator = (const TVec4& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;

    return *this;
}

template<class T, class U> inline TVec4& TVec4::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec4::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = Elt(v[i]);

    return *this;
}

inline TVec4& TVec4::operator += (const TVec4& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
}

inline TVec4& TVec4::operator -= (const TVec4& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
}

inline TVec4& TVec4::operator *= (const TVec4& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;

    return *this;
}

inline TVec4& TVec4::operator *= (TElt s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

inline TVec4& TVec4::operator /= (const TVec4& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;

    return *this;
}

inline TVec4& TVec4::operator /= (TElt s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}


inline TVec4 TVec4::operator + (const TVec4& a) const
{
    TVec4 result;

    result.x = x + a.x;
    result.y = y + a.y;
    result.z = z + a.z;
    result.w = w + a.w;

    return result;
}

inline TVec4 TVec4::operator - (const TVec4& a) const
{
    TVec4 result;

    result.x = x - a.x;
    result.y = y - a.y;
    result.z = z - a.z;
    result.w = w - a.w;

    return result;
}

inline const TVec4& TVec4::operator + () const
{
    return *this;
}

inline TVec4 TVec4::operator - () const
{
    TVec4 result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

inline TVec4 TVec4::operator * (const TVec4& a) const
{
    TVec4 result;

    result.x = x * a.x;
    result.y = y * a.y;
    result.z = z * a.z;
    result.w = w * a.w;

    return result;
}

inline TVec4 TVec4::operator * (TElt s) const
{
    TVec4 result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    result.w = w * s;

    return result;
}

inline TVec4 TVec4::operator / (const TVec4& a) const
{
    TVec4 result;

    result.x = x / a.x;
    result.y = y / a.y;
    result.z = z / a.z;
    result.w = w / a.w;

    return result;
}

inline TVec4 TVec4::operator / (TElt s) const
{
    TVec4 result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;
    result.w = w / s;

    return result;
}

inline TVec4 operator * (TElt s, const TVec4& v)
{
    return v * s;
}

inline TVec4& TVec4::MakeZero()
{
    x = vl_zero; y = vl_zero; z = vl_zero; w = vl_zero;
    return *this;
}

inline TVec4& TVec4::MakeBlock(TElt k)
{
    x = k; y = k; z = k; w = k;
    return *this;
}


inline TVec4::TVec4(VLBlock k)
{
    MakeBlock(TElt(k));
}

inline TVec4::TVec4(VLAxis k, TElt s)
{
    MakeUnit(k, s);
}

inline TVec4::TVec4(VLMinusAxis k, TElt s)
{
    MakeUnit(k, -s);
}

inline TVec4& TVec4::operator = (VLBlock k)
{
    MakeBlock(TElt(k));
    return *this;
}

inline TVec4& TVec4::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline TVec4& TVec4::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline TVec2& TVec4::AsVec2()
{
    return (TVec2&) *this;
}

inline const TVec2& TVec4::AsVec2() const
{
    return (const TVec2&) *this;
}

inline TVec3& TVec4::AsVec3()
{
    return (TVec3&) *this;
}

inline const TVec3& TVec4::AsVec3() const
{
    return (const TVec3&) *this;
}



inline TElt dot(const TVec4& a, const TVec4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline TElt sqrlen(const TVec4& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline TElt len(const TVec4& v)
{
    return sqrt(dot(v, v));
}

inline TVec4 norm(const TVec4& v)
{
    VL_ASSERT_MSG(sqrlen(v) > vl_zero, "normalising length-zero vector");
    return v / len(v);
}

inline TVec4 norm_safe(const TVec4& v)
{
    return v / (len(v) + TElt(1e-8));
}

inline TVec4 inv(const TVec4& v)
{
    return TVec4(TElt(1) / v.x, TElt(1) / v.y, TElt(1) / v.z, TElt(1) / v.w);
}
#endif

inline TVec4 abs(const TVec4& v)
{
    return TVec4(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

#endif
