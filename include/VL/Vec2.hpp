/*
    File:       Vec2.hpp

    Function:   Defines a length-2 vector.

    Copyright:  Andrew Willmott
 */

#ifndef VL_VEC2_H
#define VL_VEC2_H


// --- Vec2 Class -------------------------------------------------------------


class TVec2 : public VLVecType
{
public:
    // Constructors
    TVec2();
    TVec2(TElt x, TElt y);                 // (x, y)
    TVec2(const TVec2& v);                 // Copy constructor

    TVec2(VLBlock      b);                 // vl_0, vl_1, ...
    TVec2(VLAxis       a, TElt s = vl_1);  // vl_x, vl_y
    TVec2(VLMinusAxis  a, TElt s = vl_1);  // vl_minus_x, vl_minus_y

    explicit TVec2(TElt s);
    explicit TVec2(const TElt v[]);

    template<class T, class U = typename T::IsVec> explicit TVec2(const T& v);

    // Accessor functions
    int          Elts() const { return 2; };   // Element count

    TElt&        operator [] (int i);          // Indexing by row
    const TElt&  operator [] (int i) const;    // Indexing by row

    TElt*        Ref();                        // Return pointer to data
    const TElt*  Ref() const;                  // Return pointer to data

    // Assignment operators
    TVec2&       operator =  (const TVec2& a);
    TVec2&       operator =  (VLBlock k);
    TVec2&       operator =  (VLAxis k);
    TVec2&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> TVec2& operator = (const T& v);

    TVec2&       operator += (const TVec2& a);
    TVec2&       operator -= (const TVec2& a);
    TVec2&       operator *= (const TVec2& a);
    TVec2&       operator *= (TElt s);
    TVec2&       operator /= (const TVec2& a);
    TVec2&       operator /= (TElt s);

    // Comparison operators
    bool         operator == (const TVec2& a) const; // v == a?
    bool         operator != (const TVec2& a) const; // v != a?
    bool         operator <  (const TVec2& a) const; // All v.i <  a.i?
    bool         operator >  (const TVec2& a) const; // All v.i >  a.i?
    bool         operator <= (const TVec2& a) const; // All v.i <= a.i?
    bool         operator >= (const TVec2& a) const; // All v.i >= a.i?

    // Arithmetic operators
    TVec2        operator + (const TVec2& a) const;  // v + a
    TVec2        operator - (const TVec2& a) const;  // v - a
    const TVec2& operator + () const;                // +v
    TVec2        operator - () const;                // -v
    TVec2        operator * (const TVec2& a) const;  // v * a (vx * ax, ...)
    TVec2        operator * (TElt s) const;          // v * s
    TVec2        operator / (const TVec2& a) const;  // v / a (vx / ax, ...)
    TVec2        operator / (TElt s) const;          // v / s

    // Initialisers
    TVec2&       MakeZero();                         // Zero vector
    TVec2&       MakeUnit(int i, TElt k = vl_one);   // I[i]
    TVec2&       MakeBlock(TElt k = vl_one);         // All-k vector

    // Data
    TElt  x;
    TElt  y;
};


// --- Vec2 operators ---------------------------------------------------------

TVec2 operator * (TElt s, const TVec2& v);       // s * v

TElt  dot      (const TVec2& a, const TVec2& b); // a . b
TVec2 cross    (const TVec2& v);                 // ccw orthogonal vector to 'v'. cross(vl_x) = vl_y.
TElt  sqrlen   (const TVec2& v);                 // v . v
#ifndef VL_NO_REAL
TElt  len      (const TVec2& v);                 // || v ||
TVec2 norm     (const TVec2& v);                 // v / || v ||
TVec2 norm_safe(const TVec2& v);                 // v / || v ||, handles || v || = 0
TVec2 inv      (const TVec2& v);                 // inverse: 1 / v
#endif
TVec2 abs      (const TVec2& v);                 // abs(v_i)


// --- Inlines ----------------------------------------------------------------


inline TVec2::TVec2()
{
}

inline TVec2::TVec2(TElt a, TElt b) :
    x(a),
    y(b)
{}

inline TVec2::TVec2(const TVec2& v) :
    x(v.x),
    y(v.y)
{}

inline TVec2::TVec2(TElt s) :
    x(s),
    y(s)
{
}

inline TVec2::TVec2(const TElt v[]) :
    x(v[0]),
    y(v[1])
{
}

template<class T, class U> inline TVec2::TVec2(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec2) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = TElt(v[i]);
}

inline TElt& TVec2::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 2, "(Vec2::[i]) index out of range");
    return (&x)[i];
}

inline const TElt& TVec2::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 2, "(Vec2::[i]) index out of range");
    return (&x)[i];
}

inline TElt* TVec2::Ref()
{
    return &x;
}

inline const TElt* TVec2::Ref() const
{
    return &x;
}

inline TVec2& TVec2::operator = (const TVec2& v)
{
    x = v.x;
    y = v.y;

    return *this;
}

template<class T, class U> inline TVec2& TVec2::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec2::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = TElt(v[i]);

    return *this;
}

inline TVec2& TVec2::operator += (const TVec2& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

inline TVec2& TVec2::operator -= (const TVec2& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

inline TVec2& TVec2::operator *= (const TVec2& v)
{
    x *= v.x;
    y *= v.y;

    return *this;
}

inline TVec2& TVec2::operator *= (TElt s)
{
    x *= s;
    y *= s;

    return *this;
}

inline TVec2& TVec2::operator /= (const TVec2& v)
{
    x /= v.x;
    y /= v.y;

    return *this;
}

inline TVec2& TVec2::operator /= (TElt s)
{
    x /= s;
    y /= s;

    return *this;
}

inline TVec2 TVec2::operator + (const TVec2& a) const
{
    TVec2 result;

    result.x = x + a.x;
    result.y = y + a.y;

    return result;
}

inline TVec2 TVec2::operator - (const TVec2& a) const
{
    TVec2 result;

    result.x = x - a.x;
    result.y = y - a.y;

    return result;
}

inline const TVec2& TVec2::operator + () const
{
    return *this;
}

inline TVec2 TVec2::operator - () const
{
    TVec2 result;

    result.x = -x;
    result.y = -y;

    return result;
}

inline TVec2 TVec2::operator * (const TVec2& a) const
{
    TVec2 result;

    result.x = x * a.x;
    result.y = y * a.y;

    return result;
}

inline TVec2 TVec2::operator * (TElt s) const
{
    TVec2 result;

    result.x = x * s;
    result.y = y * s;

    return result;
}

inline TVec2 operator * (TElt s, const TVec2& v)
{
    return v * s;
}

inline TVec2 TVec2::operator / (const TVec2& a) const
{
    TVec2 result;

    result.x = x / a.x;
    result.y = y / a.y;

    return result;
}

inline TVec2 TVec2::operator / (TElt s) const
{
    TVec2 result;

    result.x = x / s;
    result.y = y / s;

    return result;
}

inline TElt dot(const TVec2& a, const TVec2& b)
{
    return a.x * b.x + a.y * b.y;
}

inline TVec2 cross(const TVec2& a)
{
    TVec2 result;

    result.x = -a.y;
    result.y =  a.x;

    return result;
}

inline TElt sqrlen(const TVec2& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline TElt len(const TVec2& v)
{
    return sqrt(dot(v, v));
}

inline TVec2 norm(const TVec2& v)
{
    VL_ASSERT_MSG(sqrlen(v) > TElt(vl_zero), "normalising length-zero vector");
    return v / len(v);
}

inline TVec2 norm_safe(const TVec2& v)
{
    return v / (len(v) + TElt(1e-8));
}

inline TVec2 inv(const TVec2& v)
{
    return TVec2(TElt(1) / v.x, TElt(1) / v.y);
}
#endif

inline TVec2 abs(const TVec2& v)
{
    return TVec2(abs(v.x), abs(v.y));
}

inline TVec2& TVec2::MakeUnit(int i, TElt k)
{
    if (i == 0)
    { x = k; y = vl_zero; }
    else if (i == 1)
    { x = vl_zero; y = k; }
    else
        VL_ERROR("(Vec2::Unit) illegal unit vector");

    return *this;
}

inline TVec2& TVec2::MakeZero()
{
    x = vl_zero; y = vl_zero;
    return *this;
}

inline TVec2& TVec2::MakeBlock(TElt k)
{
    x = k; y = k;
    return *this;
}


inline TVec2::TVec2(VLBlock k) :
    x(TElt(k)),
    y(TElt(k))
{
}

inline TVec2::TVec2(VLAxis k, TElt s)
{
    MakeUnit(k, s);
}

inline TVec2::TVec2(VLMinusAxis k, TElt s)
{
    MakeUnit(k, -s);
}

inline TVec2& TVec2::operator = (VLBlock k)
{
    MakeBlock(TElt(k));
    return *this;
}

inline TVec2& TVec2::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline TVec2& TVec2::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline bool TVec2::operator == (const TVec2& a) const
{
    return x == a.x && y == a.y;
}

inline bool TVec2::operator != (const TVec2& a) const
{
    return x != a.x || y != a.y;
}

inline bool TVec2::operator < (const TVec2& a) const
{
    return x < a.x && y < a.y;
}

inline bool TVec2::operator > (const TVec2& a) const
{
    return x > a.x && y > a.y;
}

inline bool TVec2::operator <= (const TVec2& a) const
{
    return x <= a.x && y <= a.y;
}

inline bool TVec2::operator >= (const TVec2& a) const
{
    return x >= a.x && y >= a.y;
}

#endif
