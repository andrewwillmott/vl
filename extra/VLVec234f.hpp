//
// VLVec234f.hpp
//
// Andrew Willmott
//

#ifndef VL234f_H
#define VL234f_H

#include <cmath>
// Default definitions

#ifdef VL_NS
    #define VL_NS_BEGIN namespace VL_NS {
    #define VL_NS_END   }
#else
    #define VL_NS_BEGIN
    #define VL_NS_END
#endif

#define VL_REPEAT 0x7FFFFFFF

#define VL_PREFIX_(PREFIX, NAME) PREFIX ## _ ## NAME
#define VL_PREFIX(PREFIX, NAME) VL_PREFIX_(PREFIX, NAME)

// Assertions

#ifndef VL_ASSERT_FULL
    #ifdef VL_DEBUG
        #include <assert.h>
        #define VL_ASSERT_FULL(M_TYPE, M_B, ...) assert(M_B)
    #else
        #define VL_ASSERT_FULL(M_TYPE, M_B, ...)
    #endif
    #define VL_EXPECT_FULL(M_TYPE, M_B, ...) (void)(M_B)
#endif

#define VL_ASSERT_MSG(M_B, ...) VL_ASSERT_FULL("Assert Error", M_B, __VA_ARGS__)
#define VL_EXPECT_MSG(M_B, ...) VL_EXPECT_FULL("Warning", M_B, __VA_ARGS__)
#define VL_INDEX_MSG(M_I, M_N, ...) VL_ASSERT_FULL("Index Error", (unsigned int)(M_I) < (unsigned int)(M_N), __VA_ARGS__)
#define VL_RANGE_MSG(M_I, M_MIN, M_MAX, ...) VL_ASSERT_FULL("Range Error", ((M_MIN) <= (M_I) && (M_I) < (M_MAX)), __VA_ARGS__)
#define VL_ERROR(...) VL_ASSERT_FULL("Error", false, __VA_ARGS__)
#define VL_WARNING(...) VL_EXPECT_FULL("Warning", false, __VA_ARGS__)

#define VL_ASSERT(M_B) VL_ASSERT_MSG(M_B, #M_B)
#define VL_EXPECT(M_B) VL_EXPECT_MSG(M_B, #M_B)
#define VL_INDEX(M_I, M_N) VL_INDEX_MSG(M_I, M_N, "0 <= " #M_I " < " #M_N)
#define VL_RANGE(M_I, M_MIN, M_MAX) VL_RANGE_MSG(M_I, M_MIN, M_MAX, #M_MIN " <= " #M_I " < " #M_MAX)

// Memory

#ifndef VL_NEW
    #define VL_NEW new
    #define VL_DELETE delete
#endif

// Misc

#ifndef VL_CXX_11
    #define VL_CXX_11 __cplusplus >= 201103L
#endif

#ifndef VL_CONSTANTS_H
#define VL_CONSTANTS_H

// --- Mathematical constants -------------------------------------------------

enum    VLDiag       { vl_I = 1, vl_minus_I = -1, vl_nI = -1 };
enum    VLBlock      { vl_zero = 0, vl_one = 1, vl_minus_one = -1, vl_0 = 0, vl_1 = 1, vl_n1 = -1 };
enum    VLAxis       { vl_x, vl_y, vl_z, vl_w };
enum    VLMinusAxis  { vl_minus_x, vl_minus_y, vl_minus_z, vl_minus_w, vl_nx = 0, vl_ny, vl_nz, vl_nw };

typedef VLAxis      vl_axis;        // e.g., Vecf(10, vl_axis(4)), Vec3f(vl_axis(i))
typedef VLMinusAxis vl_minus_axis;  // e.g., Vecf(10, vl_minus_axis(4))

const double vl_pi           = 3.14159265358979323846264338327950288;  // prefer vlf_pi, vld_pi etc.
const double vl_halfPi       = vl_pi / 2.0;
const double vl_quarterPi    = vl_pi / 4.0;
const double vl_twoPi        = vl_pi * 2.0;

#ifdef HUGE_VAL
    const float  vlf_huge = HUGE_VALF;
    const double vld_huge = HUGE_VAL;
#else
    const float  vlf_huge = 1e50f;
    const double vld_huge = 1e500;
#endif

const double vl_huge = vld_huge;

const float  vlf_eps = 1.19209290E-07F;
const double vld_eps = 2.2204460492503131e-016;

struct VLVecType { typedef void IsVec; typedef float Elt; };
struct VLMatType { typedef void IsMat; typedef float Elt; };
struct VLVolType { typedef void IsVol; typedef float Elt; };

#define VL_PREFIX_(PREFIX, NAME) PREFIX ## _ ## NAME
#define VL_PREFIX(PREFIX, NAME) VL_PREFIX_(PREFIX, NAME)
#define VL_CS(NAME) VL_PREFIX(vlf, NAME)

#endif

#ifndef VL_NO_REAL
const float VL_CS(pi)        = float(3.14159265358979323846264338327950288);
const float VL_CS(halfPi)    = float(VL_CS(pi) / 2);
const float VL_CS(quarterPi) = float(VL_CS(pi) / 4);
const float VL_CS(twoPi)     = float(VL_CS(pi) * 2);
#endif

#ifndef VL_MATH_H
#define VL_MATH_H



using std::abs;
using std::sqrt;

// --- Inlines ----------------------------------------------------------------

// additions to arithmetic functions

inline float  len   (float  x) { return abs(x); }
inline double len   (double x) { return abs(x); }
inline int    len   (int    x) { return abs(x); }

inline float  sqrlen(float  x) { return x * x; }
inline double sqrlen(double x) { return x * x; }
inline int    sqrlen(int    x) { return x * x; }

template<class T> inline T sqr (T x) { return x * x; }
template<class T> inline T cube(T x) { return x * x * x; }

inline float  sign(float a ) { return a < 0.0f ? -1.0f : 1.0f; }
inline double sign(double a) { return a < 0.0  ? -1.0  : 1.0 ; }

inline float  lerp(float  a, float  b, float  s) { return (1.0f - s) * a + s * b; }
inline double lerp(double a, double b, double s) { return (1.0  - s) * a + s * b; }

template<class T, class S> T lerp(T x, T y, S s);

template<class T> inline T vl_min(T a, T b);
template<class T> inline T vl_max(T a, T b);
template<class T> inline T vl_clamp(T x, T min, T max);
template<class T> inline T vl_clamp_lower(T x, T min);
template<class T> inline T vl_clamp_upper(T x, T max);

void vl_sincos(double phi, double* sinv, double* cosv);
void vl_sincos(float phi, float* sinv, float* cosv);




//
// Implementation
//



template<class T, class S> inline T lerp(T x, T y, S s)
{
    return x + (y - x) * s;
}

template<class T> inline T vl_min(T a, T b)
{
    return a < b ? a : b;
}

template<class T> inline T vl_max(T a, T b)
{
    return a > b ? a : b;
}

template<class T> inline T vl_clamp(T x, T min, T max)
{
    return x < min ? min : (x > max ? max : x);
}

template<class T> inline T vl_clamp_lower(T x, T min)
{
    return x < min ? min : x;
}

template<class T> inline T vl_clamp_upper(T x, T max)
{
    return x > max ? max : x;
}

#ifdef VL_SINCOSF
    inline void vl_sincos(double phi, double* sinv, double* cosv) { VL_SINCOS (phi, sinv, cosv); }
    inline void vl_sincos(float  phi, float*  sinv, float*  cosv) { VL_SINCOSF(phi, sinv, cosv); }
#elif defined(VL_SINCOS)
    #define vl_sincos VL_SINCOS
#else
    inline void vl_sincos(double phi, double* sinv, double* cosv)
    {
        *sinv = sin(phi);
        *cosv = cos(phi);
    }
    inline void vl_sincos(float phi, float* sinv, float* cosv)
    {
        *sinv = sinf(phi);
        *cosv = cosf(phi);
    }
#endif



#endif

#ifndef VL_VEC2_H
#define VL_VEC2_H


// --- Vec2 Class -------------------------------------------------------------


class Vec2f : public VLVecType
{
public:
    // Constructors
    Vec2f();
    Vec2f(float x, float y);                 // (x, y)
    Vec2f(const Vec2f& v);                 // Copy constructor

    Vec2f(VLBlock      b);                 // vl_0, vl_1, ...
    Vec2f(VLAxis       a, float s = vl_1);  // vl_x, vl_y
    Vec2f(VLMinusAxis  a, float s = vl_1);  // vl_minus_x, vl_minus_y

    explicit Vec2f(float s);
    explicit Vec2f(const float v[]);

    template<class T, class U = typename T::IsVec> explicit Vec2f(const T& v);

    // Accessor functions
    int          Elts() const { return 2; };   // Element count

    float&        operator [] (int i);          // Indexing by row
    const float&  operator [] (int i) const;    // Indexing by row

    float*        Ref();                        // Return pointer to data
    const float*  Ref() const;                  // Return pointer to data

    // Assignment operators
    Vec2f&       operator =  (const Vec2f& a);
    Vec2f&       operator =  (VLBlock k);
    Vec2f&       operator =  (VLAxis k);
    Vec2f&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> Vec2f& operator = (const T& v);

    Vec2f&       operator += (const Vec2f& a);
    Vec2f&       operator -= (const Vec2f& a);
    Vec2f&       operator *= (const Vec2f& a);
    Vec2f&       operator *= (float s);
    Vec2f&       operator /= (const Vec2f& a);
    Vec2f&       operator /= (float s);

    // Comparison operators
    bool         operator == (const Vec2f& a) const; // v == a?
    bool         operator != (const Vec2f& a) const; // v != a?
    bool         operator <  (const Vec2f& a) const; // All v.i <  a.i?
    bool         operator >  (const Vec2f& a) const; // All v.i >  a.i?
    bool         operator <= (const Vec2f& a) const; // All v.i <= a.i?
    bool         operator >= (const Vec2f& a) const; // All v.i >= a.i?

    // Arithmetic operators
    Vec2f        operator + (const Vec2f& a) const;  // v + a
    Vec2f        operator - (const Vec2f& a) const;  // v - a
    const Vec2f& operator + () const;                // +v
    Vec2f        operator - () const;                // -v
    Vec2f        operator * (const Vec2f& a) const;  // v * a (vx * ax, ...)
    Vec2f        operator * (float s) const;          // v * s
    Vec2f        operator / (const Vec2f& a) const;  // v / a (vx / ax, ...)
    Vec2f        operator / (float s) const;          // v / s

    // Initialisers
    Vec2f&       MakeZero();                         // Zero vector
    Vec2f&       MakeUnit(int i, float k = vl_one);   // I[i]
    Vec2f&       MakeBlock(float k = vl_one);         // All-k vector

    // Data
    float  x;
    float  y;
};


// --- Vec2 operators ---------------------------------------------------------

Vec2f operator * (float s, const Vec2f& v);       // s * v

float  dot      (const Vec2f& a, const Vec2f& b); // a . b
Vec2f cross    (const Vec2f& v);                 // ccw orthogonal vector to 'v'. cross(vl_x) = vl_y.
float  sqrlen   (const Vec2f& v);                 // v . v
#ifndef VL_NO_REAL
float  len      (const Vec2f& v);                 // || v ||
Vec2f norm     (const Vec2f& v);                 // v / || v ||
Vec2f norm_safe(const Vec2f& v);                 // v / || v ||, handles || v || = 0
Vec2f inv      (const Vec2f& v);                 // inverse: 1 / v
#endif
Vec2f abs      (const Vec2f& v);                 // abs(v_i)


// --- Inlines ----------------------------------------------------------------


inline Vec2f::Vec2f()
{
}

inline Vec2f::Vec2f(float a, float b) :
    x(a),
    y(b)
{}

inline Vec2f::Vec2f(const Vec2f& v) :
    x(v.x),
    y(v.y)
{}

inline Vec2f::Vec2f(float s) :
    x(s),
    y(s)
{
}

inline Vec2f::Vec2f(const float v[]) :
    x(v[0]),
    y(v[1])
{
}

template<class T, class U> inline Vec2f::Vec2f(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec2) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = float(v[i]);
}

inline float& Vec2f::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 2, "(Vec2::[i]) index out of range");
    return (&x)[i];
}

inline const float& Vec2f::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 2, "(Vec2::[i]) index out of range");
    return (&x)[i];
}

inline float* Vec2f::Ref()
{
    return &x;
}

inline const float* Vec2f::Ref() const
{
    return &x;
}

inline Vec2f& Vec2f::operator = (const Vec2f& v)
{
    x = v.x;
    y = v.y;

    return *this;
}

template<class T, class U> inline Vec2f& Vec2f::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec2::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = float(v[i]);

    return *this;
}

inline Vec2f& Vec2f::operator += (const Vec2f& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

inline Vec2f& Vec2f::operator -= (const Vec2f& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

inline Vec2f& Vec2f::operator *= (const Vec2f& v)
{
    x *= v.x;
    y *= v.y;

    return *this;
}

inline Vec2f& Vec2f::operator *= (float s)
{
    x *= s;
    y *= s;

    return *this;
}

inline Vec2f& Vec2f::operator /= (const Vec2f& v)
{
    x /= v.x;
    y /= v.y;

    return *this;
}

inline Vec2f& Vec2f::operator /= (float s)
{
    x /= s;
    y /= s;

    return *this;
}

inline Vec2f Vec2f::operator + (const Vec2f& a) const
{
    Vec2f result;

    result.x = x + a.x;
    result.y = y + a.y;

    return result;
}

inline Vec2f Vec2f::operator - (const Vec2f& a) const
{
    Vec2f result;

    result.x = x - a.x;
    result.y = y - a.y;

    return result;
}

inline const Vec2f& Vec2f::operator + () const
{
    return *this;
}

inline Vec2f Vec2f::operator - () const
{
    Vec2f result;

    result.x = -x;
    result.y = -y;

    return result;
}

inline Vec2f Vec2f::operator * (const Vec2f& a) const
{
    Vec2f result;

    result.x = x * a.x;
    result.y = y * a.y;

    return result;
}

inline Vec2f Vec2f::operator * (float s) const
{
    Vec2f result;

    result.x = x * s;
    result.y = y * s;

    return result;
}

inline Vec2f operator * (float s, const Vec2f& v)
{
    return v * s;
}

inline Vec2f Vec2f::operator / (const Vec2f& a) const
{
    Vec2f result;

    result.x = x / a.x;
    result.y = y / a.y;

    return result;
}

inline Vec2f Vec2f::operator / (float s) const
{
    Vec2f result;

    result.x = x / s;
    result.y = y / s;

    return result;
}

inline float dot(const Vec2f& a, const Vec2f& b)
{
    return a.x * b.x + a.y * b.y;
}

inline Vec2f cross(const Vec2f& a)
{
    Vec2f result;

    result.x = -a.y;
    result.y =  a.x;

    return result;
}

inline float sqrlen(const Vec2f& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline float len(const Vec2f& v)
{
    return sqrt(dot(v, v));
}

inline Vec2f norm(const Vec2f& v)
{
    VL_ASSERT_MSG(sqrlen(v) > float(vl_zero), "normalising length-zero vector");
    return v / len(v);
}

inline Vec2f norm_safe(const Vec2f& v)
{
    return v / (len(v) + float(1e-8));
}

inline Vec2f inv(const Vec2f& v)
{
    return Vec2f(float(1) / v.x, float(1) / v.y);
}
#endif

inline Vec2f abs(const Vec2f& v)
{
    return Vec2f(abs(v.x), abs(v.y));
}

inline Vec2f& Vec2f::MakeUnit(int i, float k)
{
    if (i == 0)
    { x = k; y = vl_zero; }
    else if (i == 1)
    { x = vl_zero; y = k; }
    else
        VL_ERROR("(Vec2::Unit) illegal unit vector");

    return *this;
}

inline Vec2f& Vec2f::MakeZero()
{
    x = vl_zero; y = vl_zero;
    return *this;
}

inline Vec2f& Vec2f::MakeBlock(float k)
{
    x = k; y = k;
    return *this;
}


inline Vec2f::Vec2f(VLBlock k) :
    x(float(k)),
    y(float(k))
{
}

inline Vec2f::Vec2f(VLAxis k, float s)
{
    MakeUnit(k, s);
}

inline Vec2f::Vec2f(VLMinusAxis k, float s)
{
    MakeUnit(k, -s);
}

inline Vec2f& Vec2f::operator = (VLBlock k)
{
    MakeBlock(float(k));
    return *this;
}

inline Vec2f& Vec2f::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline Vec2f& Vec2f::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline bool Vec2f::operator == (const Vec2f& a) const
{
    return x == a.x && y == a.y;
}

inline bool Vec2f::operator != (const Vec2f& a) const
{
    return x != a.x || y != a.y;
}

inline bool Vec2f::operator < (const Vec2f& a) const
{
    return x < a.x && y < a.y;
}

inline bool Vec2f::operator > (const Vec2f& a) const
{
    return x > a.x && y > a.y;
}

inline bool Vec2f::operator <= (const Vec2f& a) const
{
    return x <= a.x && y <= a.y;
}

inline bool Vec2f::operator >= (const Vec2f& a) const
{
    return x >= a.x && y >= a.y;
}

#endif

#ifndef VL_VEC3_H
#define VL_VEC3_H


// --- Vec3 Class -------------------------------------------------------------


class Vec2f;

class Vec3f : public VLVecType
{
public:
    // Constructors
    Vec3f();
    Vec3f(float x, float y, float z);         // [x, y, z]
    Vec3f(const Vec3f& v);                 // Copy constructor
    Vec3f(const Vec2f& v, float w);         // Hom. 2D vector

    Vec3f(VLBlock     b);                  // vl_0, vl_1, ...
    Vec3f(VLAxis      a,  float s = vl_1);  // vl_x, vl_y
    Vec3f(VLMinusAxis a,  float s = vl_1);  // vl_minus_x, vl_minus_y

    explicit Vec3f(float s);
    explicit Vec3f(const float v[]);

    template<class T, class U = typename T::IsVec> explicit Vec3f(const T& v);

    // Accessor functions
    int          Elts() const { return 3; };   // Element count

    float&        operator [] (int i);          // Indexing by row
    const float&  operator [] (int i) const;    // Indexing by row

    float*        Ref();                        // Return pointer to data
    const float*  Ref() const;                  // Return pointer to data

    // Assignment operators
    Vec3f&       operator =  (const Vec3f& a);
    Vec3f&       operator =  (VLBlock k);
    Vec3f&       operator =  (VLAxis k);
    Vec3f&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> Vec3f& operator = (const T& v);

    Vec3f&       operator += (const Vec3f& a);
    Vec3f&       operator -= (const Vec3f& a);
    Vec3f&       operator *= (const Vec3f& a);
    Vec3f&       operator *= (float s);
    Vec3f&       operator /= (const Vec3f& a);
    Vec3f&       operator /= (float s);

    // Comparison operators
    bool         operator == (const Vec3f& a) const; // v == a?
    bool         operator != (const Vec3f& a) const; // v != a?
    bool         operator <  (const Vec3f& a) const; // All v.i <  a.i?
    bool         operator >= (const Vec3f& a) const; // All v.i >= a.i?

    // Arithmetic operators
    Vec3f        operator + (const Vec3f& a) const;  // v + a
    Vec3f        operator - (const Vec3f& a) const;  // v - a
    const Vec3f& operator + () const;                // -v
    Vec3f        operator - () const;                // -v
    Vec3f        operator * (const Vec3f& a) const;  // v * a (vx * ax, ...)
    Vec3f        operator * (float s) const;          // v * s
    Vec3f        operator / (const Vec3f& a) const;  // v / a (vx / ax, ...)
    Vec3f        operator / (float s) const;          // v / s

    // Initialisers
    Vec3f&       MakeZero();                        // Zero vector
    Vec3f&       MakeUnit(int i, float k = vl_one);  // I[i]
    Vec3f&       MakeBlock(float k = vl_one);        // All-k vector

    // Conversion
    Vec2f&       AsVec2();
    const Vec2f& AsVec2() const;

    // Data
    float x;
    float y;
    float z;
};


// --- Vec3 operators ---------------------------------------------------------

Vec3f operator * (float s, const Vec3f& v);       // s * v

float  dot(const Vec3f& a, const Vec3f& b);       // a . b
Vec3f cross    (const Vec3f& a, const Vec3f& b); // a x b
Vec3f cross_x  (const Vec3f& v);                 // v x e_x
Vec3f cross_y  (const Vec3f& v);                 // v x e_y
Vec3f cross_z  (const Vec3f& v);                 // v x e_z
float  sqrlen   (const Vec3f& v);                 // v . v
#ifndef VL_NO_REAL
float  len      (const Vec3f& v);                 // || v ||
Vec3f norm     (const Vec3f& v);                 // v / || v ||
Vec3f norm_safe(const Vec3f& v);                 // v / || v ||, handles || v || = 0
Vec3f inv      (const Vec3f& v);                 // inverse: 1 / v
Vec2f proj     (const Vec3f& v);                 // homogeneous projection
#endif
Vec3f abs      (const Vec3f& v);                 // abs(v_i)


// --- Inlines ----------------------------------------------------------------


inline Vec3f::Vec3f()
{
}

inline Vec3f::Vec3f(float a, float b, float c) :
    x(a),
    y(b),
    z(c)
{}

inline Vec3f::Vec3f(const Vec3f& v)  :
    x(v.x),
    y(v.y),
    z(v.z)
{}

inline Vec3f::Vec3f(const Vec2f& v, float z_in) :
    x(v.x),
    y(v.y),
    z(z_in)
{}

inline Vec3f::Vec3f(float s) :
    x(s),
    y(s),
    z(s)
{}

inline Vec3f::Vec3f(const float v[]) :
    x(v[0]),
    y(v[1]),
    z(v[2])
{}

template<class T, class U> inline Vec3f::Vec3f(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec3) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = float(v[i]);
}

inline float& Vec3f::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 3, "(Vec3::[i]) index out of range");
    return (&x)[i];
}

inline const float& Vec3f::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 3, "(Vec3::[i]) index out of range");
    return (&x)[i];
}

inline float* Vec3f::Ref()
{
    return &x;
}

inline const float* Vec3f::Ref() const
{
    return &x;
}

inline Vec3f& Vec3f::operator = (const Vec3f& v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

template<class T, class U> inline Vec3f& Vec3f::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec3::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = float(v[i]);

    return *this;
}

inline Vec3f& Vec3f::operator += (const Vec3f& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

inline Vec3f& Vec3f::operator -= (const Vec3f& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

inline Vec3f& Vec3f::operator *= (const Vec3f& a)
{
    x *= a.x;
    y *= a.y;
    z *= a.z;

    return *this;
}

inline Vec3f& Vec3f::operator *= (float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

inline Vec3f& Vec3f::operator /= (const Vec3f& a)
{
    x /= a.x;
    y /= a.y;
    z /= a.z;

    return *this;
}

inline Vec3f& Vec3f::operator /= (float s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}

inline Vec3f Vec3f::operator + (const Vec3f& a) const
{
    Vec3f result;

    result.x = x + a.x;
    result.y = y + a.y;
    result.z = z + a.z;

    return result;
}

inline Vec3f Vec3f::operator - (const Vec3f& a) const
{
    Vec3f result;

    result.x = x - a.x;
    result.y = y - a.y;
    result.z = z - a.z;

    return result;
}

inline const Vec3f& Vec3f::operator + () const
{
    return *this;
}

inline Vec3f Vec3f::operator - () const
{
    Vec3f result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

inline Vec3f Vec3f::operator * (const Vec3f& a) const
{
    Vec3f result;

    result.x = x * a.x;
    result.y = y * a.y;
    result.z = z * a.z;

    return result;
}

inline Vec3f Vec3f::operator * (float s) const
{
    Vec3f result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

inline Vec3f Vec3f::operator / (const Vec3f& a) const
{
    Vec3f result;

    result.x = x / a.x;
    result.y = y / a.y;
    result.z = z / a.z;

    return result;
}

inline Vec3f Vec3f::operator / (float s) const
{
    Vec3f result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;

    return result;
}

inline Vec3f operator * (float s, const Vec3f& v)
{
    return v * s;
}

inline Vec3f& Vec3f::MakeUnit(int n, float k)
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

inline Vec3f& Vec3f::MakeZero()
{
    x = vl_zero; y = vl_zero; z = vl_zero;
    return *this;
}

inline Vec3f& Vec3f::MakeBlock(float k)
{
    x = k; y = k; z = k;
    return *this;
}


inline Vec3f::Vec3f(VLBlock k) :
    x(float(k)),
    y(float(k)),
    z(float(k))
{
}

inline Vec3f::Vec3f(VLAxis a, float s)
{
    MakeUnit(a, s);
}

inline Vec3f::Vec3f(VLMinusAxis a, float s)
{
    MakeUnit(a, -s);
}

inline Vec3f& Vec3f::operator = (VLBlock k)
{
    MakeBlock(float(k));
    return *this;
}

inline Vec3f& Vec3f::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline Vec3f& Vec3f::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline bool Vec3f::operator == (const Vec3f& a) const
{
    return x == a.x && y == a.y && z == a.z;
}

inline bool Vec3f::operator != (const Vec3f& a) const
{
    return x != a.x || y != a.y || z != a.z;
}

inline bool Vec3f::operator < (const Vec3f& a) const
{
    return x < a.x && y < a.y && z < a.z;
}

inline bool Vec3f::operator >= (const Vec3f& a) const
{
    return x >= a.x && y >= a.y && z >= a.z;
}

inline Vec2f& Vec3f::AsVec2()
{
    return (Vec2f&) *this;
}

inline const Vec2f& Vec3f::AsVec2() const
{
    return (const Vec2f&) *this;
}


inline float dot(const Vec3f& a, const Vec3f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3f cross(const Vec3f& a, const Vec3f& b)
{
    Vec3f result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}

inline Vec3f cross_x(const Vec3f& v)
{ return Vec3f(float(vl_zero), v.z, -v.y); }

inline Vec3f cross_y(const Vec3f& v)
{ return Vec3f(-v.z, float(vl_zero), v.x); }

inline Vec3f cross_z(const Vec3f& v)
{ return Vec3f(v.y, -v.x, float(vl_zero)); }

inline float sqrlen(const Vec3f& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline float len(const Vec3f& v)
{
    return sqrt(float(dot(v, v)));
}

inline Vec3f norm(const Vec3f& v)
{
    VL_ASSERT_MSG(sqrlen(v) > float(vl_zero), "normalising length-zero vector");
    return v / len(v);
}

inline Vec3f norm_safe(const Vec3f& v)
{
    return v / (len(v) + float(1e-8));
}

inline Vec3f inv(const Vec3f& v)
{
    return Vec3f(float(1) / v.x, float(1) / v.y, float(1) / v.z);
}

inline Vec2f proj(const Vec3f& v)
{
    Vec2f result;

    VL_ASSERT_MSG(v.z != float(vl_zero), "(Vec3/proj) last elt. is zero");

    result.x = v.x / v.z;
    result.y = v.y / v.z;

    return result;
}
#endif

inline Vec3f abs(const Vec3f& v)
{
    return Vec3f(abs(v.x), abs(v.y), abs(v.z));
}

#endif

#ifndef VL_VEC4_H
#define VL_VEC4_H


// --- Vec4 Class -------------------------------------------------------------


class Vec2f;
class Vec3f;

class Vec4f : public VLVecType
{
public:
    // Constructors
    Vec4f();
    Vec4f(float x, float y, float z, float w);      // [x, y, z, w]
    Vec4f(const Vec4f& v);                      // Copy constructor
    Vec4f(const Vec3f& v, float w);              // Homogeneous 3D vector

    Vec4f(VLBlock     b);                       // vl_0, vl_1, ...
    Vec4f(VLAxis      a, float s = vl_1);        // vl_x, vl_y
    Vec4f(VLMinusAxis a, float s = vl_1);        // vl_x, vl_y

    explicit Vec4f(float s);
    explicit Vec4f(const float v[]);

    template<class T, class U = typename T::IsVec> explicit Vec4f(const T& v);

    // Accessor functions
    int          Elts() const { return 4; };   // Element count

    float&        operator [] (int i);          // Indexing by row
    const float&  operator [] (int i) const;    // Indexing by row

    float*        Ref();                        // Return pointer to data
    const float*  Ref() const;                  // Return pointer to data

    // Assignment operators
    Vec4f&       operator =  (const Vec4f& a);
    Vec4f&       operator =  (VLBlock k);
    Vec4f&       operator =  (VLAxis k);
    Vec4f&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> Vec4f& operator = (const T& v);

    Vec4f&       operator += (const Vec4f& a);
    Vec4f&       operator -= (const Vec4f& a);
    Vec4f&       operator *= (const Vec4f& a);
    Vec4f&       operator *= (float s);
    Vec4f&       operator /= (const Vec4f& a);
    Vec4f&       operator /= (float s);

    // Comparison operators
    bool         operator == (const Vec4f& a) const; // v == a ?
    bool         operator != (const Vec4f& a) const; // v != a ?
    bool         operator <  (const Vec4f& a) const; // All v.i <  a.i?
    bool         operator >= (const Vec4f& a) const; // All v.i >= a.i?

    // Arithmetic operators
    Vec4f        operator + (const Vec4f& a) const;  // v + a
    Vec4f        operator - (const Vec4f& a) const;  // v - a
    const Vec4f& operator + () const;                // -v
    Vec4f        operator - () const;                // -v
    Vec4f        operator * (const Vec4f& a) const;  // v * a (vx * ax, ...)
    Vec4f        operator * (float s) const;        // v * s
    Vec4f        operator / (const Vec4f& a) const;  // v / a (vx / ax, ...)
    Vec4f        operator / (float s) const;        // v / s

    // Initialisers
    Vec4f&       MakeZero();                        // Zero vector
    Vec4f&       MakeUnit(int i, float k = vl_one);  // kI[i]
    Vec4f&       MakeBlock(float k = vl_one);        // All-k vector

    // Conversion
    Vec2f&       AsVec2();
    const Vec2f& AsVec2() const;
    Vec3f&       AsVec3();
    const Vec3f& AsVec3() const;

    // Data
    float x;
    float y;
    float z;
    float w;
};


// --- Vec4 operators ---------------------------------------------------------

Vec4f operator * (float s, const Vec4f& v);    // s * v

float  dot  (const Vec4f& a, const Vec4f& b);  // a . b
Vec4f cross(const Vec4f& a, const Vec4f& b, const Vec4f& c); // 4D cross prod.
float  sqrlen   (const Vec4f& v);              // v . v
#ifndef VL_NO_REAL
float  len      (const Vec4f& v);              // || v ||
Vec4f norm     (const Vec4f& v);              // v / || v ||
Vec4f norm_safe(const Vec4f& v);              // v / || v ||, handles || v || = 0
Vec4f inv      (const Vec4f& v);              // inverse: 1 / v
Vec3f proj     (const Vec4f& v);              // hom. projection
#endif
Vec4f abs      (const Vec4f& v);              // abs(v_i)


// --- Inlines ----------------------------------------------------------------


inline Vec4f::Vec4f()
{
}

inline Vec4f::Vec4f(float a, float b, float c, float d) :
    x(a),
    y(b),
    z(c),
    w(d)
{}

inline Vec4f::Vec4f(const Vec4f& v) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(v.w)
{}

inline Vec4f::Vec4f(const Vec3f& v, float w_in) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(w_in)
{
}

inline Vec4f::Vec4f(float s) :
    x(s),
    y(s),
    z(s),
    w(s)
{}

inline Vec4f::Vec4f(const float v[]) :
    x(v[0]),
    y(v[1]),
    z(v[2]),
    w(v[3])
{
}

template<class T, class U> inline Vec4f::Vec4f(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec4) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = float(v[i]);
}

inline float& Vec4f::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 4, "(Vec4::[i]) index out of range");
    return (&x)[i];
}

inline const float& Vec4f::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 4, "(Vec4::[i]) index out of range");
    return (&x)[i];
}

inline float* Vec4f::Ref()
{
    return &x;
}

inline const float* Vec4f::Ref() const
{
    return &x;
}

inline Vec4f& Vec4f::operator = (const Vec4f& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;

    return *this;
}

template<class T, class U> inline Vec4f& Vec4f::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec4::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = Elt(v[i]);

    return *this;
}

inline Vec4f& Vec4f::operator += (const Vec4f& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
}

inline Vec4f& Vec4f::operator -= (const Vec4f& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
}

inline Vec4f& Vec4f::operator *= (const Vec4f& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;

    return *this;
}

inline Vec4f& Vec4f::operator *= (float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

inline Vec4f& Vec4f::operator /= (const Vec4f& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;

    return *this;
}

inline Vec4f& Vec4f::operator /= (float s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}


inline Vec4f Vec4f::operator + (const Vec4f& a) const
{
    Vec4f result;

    result.x = x + a.x;
    result.y = y + a.y;
    result.z = z + a.z;
    result.w = w + a.w;

    return result;
}

inline Vec4f Vec4f::operator - (const Vec4f& a) const
{
    Vec4f result;

    result.x = x - a.x;
    result.y = y - a.y;
    result.z = z - a.z;
    result.w = w - a.w;

    return result;
}

inline const Vec4f& Vec4f::operator + () const
{
    return *this;
}

inline Vec4f Vec4f::operator - () const
{
    Vec4f result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

inline Vec4f Vec4f::operator * (const Vec4f& a) const
{
    Vec4f result;

    result.x = x * a.x;
    result.y = y * a.y;
    result.z = z * a.z;
    result.w = w * a.w;

    return result;
}

inline Vec4f Vec4f::operator * (float s) const
{
    Vec4f result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    result.w = w * s;

    return result;
}

inline Vec4f Vec4f::operator / (const Vec4f& a) const
{
    Vec4f result;

    result.x = x / a.x;
    result.y = y / a.y;
    result.z = z / a.z;
    result.w = w / a.w;

    return result;
}

inline Vec4f Vec4f::operator / (float s) const
{
    Vec4f result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;
    result.w = w / s;

    return result;
}

inline Vec4f operator * (float s, const Vec4f& v)
{
    return v * s;
}

inline Vec4f& Vec4f::MakeZero()
{
    x = vl_zero; y = vl_zero; z = vl_zero; w = vl_zero;
    return *this;
}

inline Vec4f& Vec4f::MakeBlock(float k)
{
    x = k; y = k; z = k; w = k;
    return *this;
}


inline Vec4f::Vec4f(VLBlock k)
{
    MakeBlock(float(k));
}

inline Vec4f::Vec4f(VLAxis k, float s)
{
    MakeUnit(k, s);
}

inline Vec4f::Vec4f(VLMinusAxis k, float s)
{
    MakeUnit(k, -s);
}

inline Vec4f& Vec4f::operator = (VLBlock k)
{
    MakeBlock(float(k));
    return *this;
}

inline Vec4f& Vec4f::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline Vec4f& Vec4f::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline Vec2f& Vec4f::AsVec2()
{
    return (Vec2f&) *this;
}

inline const Vec2f& Vec4f::AsVec2() const
{
    return (const Vec2f&) *this;
}

inline Vec3f& Vec4f::AsVec3()
{
    return (Vec3f&) *this;
}

inline const Vec3f& Vec4f::AsVec3() const
{
    return (const Vec3f&) *this;
}



inline float dot(const Vec4f& a, const Vec4f& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline float sqrlen(const Vec4f& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline float len(const Vec4f& v)
{
    return sqrt(dot(v, v));
}

inline Vec4f norm(const Vec4f& v)
{
    VL_ASSERT_MSG(sqrlen(v) > vl_zero, "normalising length-zero vector");
    return v / len(v);
}

inline Vec4f norm_safe(const Vec4f& v)
{
    return v / (len(v) + float(1e-8));
}

inline Vec4f inv(const Vec4f& v)
{
    return Vec4f(float(1) / v.x, float(1) / v.y, float(1) / v.z, float(1) / v.w);
}
#endif

inline Vec4f abs(const Vec4f& v)
{
    return Vec4f(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

#endif

#endif
