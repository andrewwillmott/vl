/*
    File:       Vec3.h

    Function:   Defines a length-3 vector.

    Copyright:  Andrew Willmott
 */

#ifndef VL_VEC3_H
#define VL_VEC3_H


// --- Vec3 Class -------------------------------------------------------------


class TVec2;

class TVec3 : public VLVecType
{
public:
    // Constructors
    TVec3();
    TVec3(TElt x, TElt y, TElt z);         // [x, y, z]
    TVec3(const TVec3& v);                 // Copy constructor
    TVec3(const TVec2& v, TElt w);         // Hom. 2D vector

    TVec3(VLBlock     b);                  // vl_0, vl_1, ...
    TVec3(VLAxis      a,  TElt s = vl_1);  // vl_x, vl_y
    TVec3(VLMinusAxis a,  TElt s = vl_1);  // vl_minus_x, vl_minus_y

    explicit TVec3(TElt s);
    explicit TVec3(const TElt v[]);

    template<class T, class U = typename T::IsVec> explicit TVec3(const T& v);

    // Accessor functions
    int          Elts() const { return 3; };   // Element count

    TElt&        operator [] (int i);          // Indexing by row
    const TElt&  operator [] (int i) const;    // Indexing by row

    TElt*        Ref();                        // Return pointer to data
    const TElt*  Ref() const;                  // Return pointer to data

    // Assignment operators
    TVec3&       operator =  (const TVec3& a);
    TVec3&       operator =  (VLBlock k);
    TVec3&       operator =  (VLAxis k);
    TVec3&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> TVec3& operator = (const T& v);

    TVec3&       operator += (const TVec3& a);
    TVec3&       operator -= (const TVec3& a);
    TVec3&       operator *= (const TVec3& a);
    TVec3&       operator *= (TElt s);
    TVec3&       operator /= (const TVec3& a);
    TVec3&       operator /= (TElt s);

    // Comparison operators
    bool         operator == (const TVec3& a) const; // v == a?
    bool         operator != (const TVec3& a) const; // v != a?
    bool         operator <  (const TVec3& a) const; // All v.i <  a.i?
    bool         operator >= (const TVec3& a) const; // All v.i >= a.i?

    // Arithmetic operators
    TVec3        operator + (const TVec3& a) const;  // v + a
    TVec3        operator - (const TVec3& a) const;  // v - a
    const TVec3& operator + () const;                // -v
    TVec3        operator - () const;                // -v
    TVec3        operator * (const TVec3& a) const;  // v * a (vx * ax, ...)
    TVec3        operator * (TElt s) const;          // v * s
    TVec3        operator / (const TVec3& a) const;  // v / a (vx / ax, ...)
    TVec3        operator / (TElt s) const;          // v / s

    // Initialisers
    TVec3&       MakeZero();                        // Zero vector
    TVec3&       MakeUnit(int i, TElt k = vl_one);  // I[i]
    TVec3&       MakeBlock(TElt k = vl_one);        // All-k vector

    // Conversion
    TVec2&       AsVec2();
    const TVec2& AsVec2() const;

    // Data
    TElt x;
    TElt y;
    TElt z;
};


// --- Vec3 operators ---------------------------------------------------------

TVec3 operator * (TElt s, const TVec3& v);       // s * v

TElt  dot(const TVec3& a, const TVec3& b);       // a . b
TVec3 cross    (const TVec3& a, const TVec3& b); // a x b
TVec3 cross_x  (const TVec3& v);                 // v x e_x
TVec3 cross_y  (const TVec3& v);                 // v x e_y
TVec3 cross_z  (const TVec3& v);                 // v x e_z
TElt  sqrlen   (const TVec3& v);                 // v . v
#ifndef VL_NO_REAL
TElt  len      (const TVec3& v);                 // || v ||
TVec3 norm     (const TVec3& v);                 // v / || v ||
TVec3 norm_safe(const TVec3& v);                 // v / || v ||, handles || v || = 0
TVec3 inv      (const TVec3& v);                 // inverse: 1 / v
TVec2 proj     (const TVec3& v);                 // homogeneous projection
#endif
TVec3 abs      (const TVec3& v);                 // abs(v_i)


// --- Inlines ----------------------------------------------------------------

#include "Vec2.h"

inline TVec3::TVec3()
{
}

inline TVec3::TVec3(TElt a, TElt b, TElt c) :
    x(a),
    y(b),
    z(c)
{}

inline TVec3::TVec3(const TVec3& v)  :
    x(v.x),
    y(v.y),
    z(v.z)
{}

inline TVec3::TVec3(const TVec2& v, TElt z_in) :
    x(v.x),
    y(v.y),
    z(z_in)
{}

inline TVec3::TVec3(TElt s) :
    x(s),
    y(s),
    z(s)
{}

inline TVec3::TVec3(const TElt v[]) :
    x(v[0]),
    y(v[1]),
    z(v[2])
{}

template<class T, class U> inline TVec3::TVec3(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec3) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = TElt(v[i]);
}

inline TElt& TVec3::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 3, "(Vec3::[i]) index out of range");
    return (&x)[i];
}

inline const TElt& TVec3::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 3, "(Vec3::[i]) index out of range");
    return (&x)[i];
}

inline TElt* TVec3::Ref()
{
    return &x;
}

inline const TElt* TVec3::Ref() const
{
    return &x;
}

inline TVec3& TVec3::operator = (const TVec3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

template<class T, class U> inline TVec3& TVec3::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec3::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = TElt(v[i]);

    return *this;
}

inline TVec3& TVec3::operator += (const TVec3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

inline TVec3& TVec3::operator -= (const TVec3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

inline TVec3& TVec3::operator *= (const TVec3& a)
{
    x *= a.x;
    y *= a.y;
    z *= a.z;

    return *this;
}

inline TVec3& TVec3::operator *= (TElt s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

inline TVec3& TVec3::operator /= (const TVec3& a)
{
    x /= a.x;
    y /= a.y;
    z /= a.z;

    return *this;
}

inline TVec3& TVec3::operator /= (TElt s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}

inline TVec3 TVec3::operator + (const TVec3& a) const
{
    TVec3 result;

    result.x = x + a.x;
    result.y = y + a.y;
    result.z = z + a.z;

    return result;
}

inline TVec3 TVec3::operator - (const TVec3& a) const
{
    TVec3 result;

    result.x = x - a.x;
    result.y = y - a.y;
    result.z = z - a.z;

    return result;
}

inline const TVec3& TVec3::operator + () const
{
    return *this;
}

inline TVec3 TVec3::operator - () const
{
    TVec3 result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

inline TVec3 TVec3::operator * (const TVec3& a) const
{
    TVec3 result;

    result.x = x * a.x;
    result.y = y * a.y;
    result.z = z * a.z;

    return result;
}

inline TVec3 TVec3::operator * (TElt s) const
{
    TVec3 result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

inline TVec3 TVec3::operator / (const TVec3& a) const
{
    TVec3 result;

    result.x = x / a.x;
    result.y = y / a.y;
    result.z = z / a.z;

    return result;
}

inline TVec3 TVec3::operator / (TElt s) const
{
    TVec3 result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;

    return result;
}

inline TVec3 operator * (TElt s, const TVec3& v)
{
    return v * s;
}

inline TVec3& TVec3::MakeUnit(int n, TElt k)
{
    switch (n)
    {
    case 0:
        { x = k; y = vl_zero; z = vl_zero; } break;
    case 1:
        { x = vl_zero; y = k; z = vl_zero; } break;
    case 2:
        { x = vl_zero; y = vl_zero; z = k; } break;
    default:
        VL_ERROR("(Vec3::Unit) illegal unit vector");
    }

    return *this;
}

inline TVec3& TVec3::MakeZero()
{
    x = vl_zero; y = vl_zero; z = vl_zero;
    return *this;
}

inline TVec3& TVec3::MakeBlock(TElt k)
{
    x = k; y = k; z = k;
    return *this;
}


inline TVec3::TVec3(VLBlock k) :
    x(TElt(k)),
    y(TElt(k)),
    z(TElt(k))
{
}

inline TVec3::TVec3(VLAxis a, TElt s)
{
    MakeUnit(a, s);
}

inline TVec3::TVec3(VLMinusAxis a, TElt s)
{
    MakeUnit(a, -s);
}

inline TVec3& TVec3::operator = (VLBlock k)
{
    MakeBlock(TElt(k));
    return *this;
}

inline TVec3& TVec3::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline TVec3& TVec3::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline bool TVec3::operator == (const TVec3& a) const
{
    return x == a.x && y == a.y && z == a.z;
}

inline bool TVec3::operator != (const TVec3& a) const
{
    return x != a.x || y != a.y || z != a.z;
}

inline bool TVec3::operator < (const TVec3& a) const
{
    return x < a.x && y < a.y && z < a.z;
}

inline bool TVec3::operator >= (const TVec3& a) const
{
    return x >= a.x && y >= a.y && z >= a.z;
}

inline TVec2& TVec3::AsVec2()
{
    return (TVec2&) *this;
}

inline const TVec2& TVec3::AsVec2() const
{
    return (const TVec2&) *this;
}


inline TElt dot(const TVec3& a, const TVec3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline TVec3 cross(const TVec3& a, const TVec3& b)
{
    TVec3 result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}

inline TVec3 cross_x(const TVec3& v)
{ return TVec3(TElt(vl_zero), v.z, -v.y); }

inline TVec3 cross_y(const TVec3& v)
{ return TVec3(-v.z, TElt(vl_zero), v.x); }

inline TVec3 cross_z(const TVec3& v)
{ return TVec3(v.y, -v.x, TElt(vl_zero)); }

inline TElt sqrlen(const TVec3& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline TElt len(const TVec3& v)
{
    return sqrt(TElt(dot(v, v)));
}

inline TVec3 norm(const TVec3& v)
{
    VL_ASSERT_MSG(sqrlen(v) > TElt(vl_zero), "normalising length-zero vector");
    return v / len(v);
}

inline TVec3 norm_safe(const TVec3& v)
{
    return v / (len(v) + TElt(1e-8));
}

inline TVec3 inv(const TVec3& v)
{
    return TVec3(TElt(1) / v.x, TElt(1) / v.y, TElt(1) / v.z);
}

inline TVec2 proj(const TVec3& v)
{
    TVec2 result;

    VL_ASSERT_MSG(v.z != TElt(vl_zero), "(Vec3/proj) last elt. is zero");

    result.x = v.x / v.z;
    result.y = v.y / v.z;

    return result;
}
#endif

inline TVec3 abs(const TVec3& v)
{
    return TVec3(abs(v.x), abs(v.y), abs(v.z));
}

#endif
