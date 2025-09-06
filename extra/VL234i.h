//
// VL234i.h
//
// Copyright Andrew Willmott
//


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

struct VLVecType { typedef void IsVec; typedef int Elt; };
struct VLMatType { typedef void IsMat; typedef int Elt; };
struct VLVolType { typedef void IsVol; typedef int Elt; };

#define VL_PREFIX_(PREFIX, NAME) PREFIX ## _ ## NAME
#define VL_PREFIX(PREFIX, NAME) VL_PREFIX_(PREFIX, NAME)
#define VL_CS(NAME) VL_PREFIX(vli, NAME)

#endif

#ifndef VL_NO_REAL
const int VL_CS(pi)        = int(3.14159265358979323846264338327950288);
const int VL_CS(halfPi)    = int(VL_CS(pi) / 2);
const int VL_CS(quarterPi) = int(VL_CS(pi) / 4);
const int VL_CS(twoPi)     = int(VL_CS(pi) * 2);
#endif

#ifndef VL_MATH_H
#define VL_MATH_H



using ::abs;
using ::sqrt;

// --- Inlines ----------------------------------------------------------------

// additions to arithmetic functions

inline float  len   (float  x) { return std::abs(x); }
inline double len   (double x) { return std::abs(x); }
inline int    len   (int    x) { return std::abs(x); }

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


class Vec2i : public VLVecType
{
public:
    // Constructors
    Vec2i();
    Vec2i(int x, int y);                 // (x, y)
    Vec2i(const Vec2i& v);                 // Copy constructor

    Vec2i(VLBlock      b);                 // vl_0, vl_1, ...
    Vec2i(VLAxis       a, int s = vl_1);  // vl_x, vl_y
    Vec2i(VLMinusAxis  a, int s = vl_1);  // vl_minus_x, vl_minus_y

    explicit Vec2i(int s);
    explicit Vec2i(const int v[]);

    template<class T, class U = typename T::IsVec> explicit Vec2i(const T& v);

    // Accessor functions
    int          Elts() const { return 2; };   // Element count

    int&        operator [] (int i);          // Indexing by row
    const int&  operator [] (int i) const;    // Indexing by row

    int*        Ref();                        // Return pointer to data
    const int*  Ref() const;                  // Return pointer to data

    // Assignment operators
    Vec2i&       operator =  (const Vec2i& a);
    Vec2i&       operator =  (VLBlock k);
    Vec2i&       operator =  (VLAxis k);
    Vec2i&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> Vec2i& operator = (const T& v);

    Vec2i&       operator += (const Vec2i& a);
    Vec2i&       operator -= (const Vec2i& a);
    Vec2i&       operator *= (const Vec2i& a);
    Vec2i&       operator *= (int s);
    Vec2i&       operator /= (const Vec2i& a);
    Vec2i&       operator /= (int s);

    // Comparison operators
    bool         operator == (const Vec2i& a) const; // v == a?
    bool         operator != (const Vec2i& a) const; // v != a?
    bool         operator <  (const Vec2i& a) const; // All v.i <  a.i?
    bool         operator >  (const Vec2i& a) const; // All v.i >  a.i?
    bool         operator <= (const Vec2i& a) const; // All v.i <= a.i?
    bool         operator >= (const Vec2i& a) const; // All v.i >= a.i?

    // Arithmetic operators
    Vec2i        operator + (const Vec2i& a) const;  // v + a
    Vec2i        operator - (const Vec2i& a) const;  // v - a
    const Vec2i& operator + () const;                // +v
    Vec2i        operator - () const;                // -v
    Vec2i        operator * (const Vec2i& a) const;  // v * a (vx * ax, ...)
    Vec2i        operator * (int s) const;          // v * s
    Vec2i        operator / (const Vec2i& a) const;  // v / a (vx / ax, ...)
    Vec2i        operator / (int s) const;          // v / s

    // Initialisers
    Vec2i&       MakeZero();                         // Zero vector
    Vec2i&       MakeUnit(int i, int k = vl_one);   // I[i]
    Vec2i&       MakeBlock(int k = vl_one);         // All-k vector

    // Data
    int  x;
    int  y;
};


// --- Vec2 operators ---------------------------------------------------------

Vec2i operator * (int s, const Vec2i& v);       // s * v

int  dot      (const Vec2i& a, const Vec2i& b); // a . b
Vec2i cross    (const Vec2i& v);                 // ccw orthogonal vector to 'v'. cross(vl_x) = vl_y.
int  sqrlen   (const Vec2i& v);                 // v . v
#ifndef VL_NO_REAL
int  len      (const Vec2i& v);                 // || v ||
Vec2i norm     (const Vec2i& v);                 // v / || v ||
Vec2i norm_safe(const Vec2i& v);                 // v / || v ||, handles || v || = 0
Vec2i inv      (const Vec2i& v);                 // inverse: 1 / v
#endif
Vec2i abs      (const Vec2i& v);                 // abs(v_i)


// --- Inlines ----------------------------------------------------------------


inline Vec2i::Vec2i()
{
}

inline Vec2i::Vec2i(int a, int b) :
    x(a),
    y(b)
{}

inline Vec2i::Vec2i(const Vec2i& v) :
    x(v.x),
    y(v.y)
{}

inline Vec2i::Vec2i(int s) :
    x(s),
    y(s)
{
}

inline Vec2i::Vec2i(const int v[]) :
    x(v[0]),
    y(v[1])
{
}

template<class T, class U> inline Vec2i::Vec2i(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec2) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = int(v[i]);
}

inline int& Vec2i::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 2, "(Vec2::[i]) index out of range");
    return (&x)[i];
}

inline const int& Vec2i::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 2, "(Vec2::[i]) index out of range");
    return (&x)[i];
}

inline int* Vec2i::Ref()
{
    return &x;
}

inline const int* Vec2i::Ref() const
{
    return &x;
}

inline Vec2i& Vec2i::operator = (const Vec2i& v)
{
    x = v.x;
    y = v.y;

    return *this;
}

template<class T, class U> inline Vec2i& Vec2i::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec2::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = int(v[i]);

    return *this;
}

inline Vec2i& Vec2i::operator += (const Vec2i& v)
{
    x += v.x;
    y += v.y;

    return *this;
}

inline Vec2i& Vec2i::operator -= (const Vec2i& v)
{
    x -= v.x;
    y -= v.y;

    return *this;
}

inline Vec2i& Vec2i::operator *= (const Vec2i& v)
{
    x *= v.x;
    y *= v.y;

    return *this;
}

inline Vec2i& Vec2i::operator *= (int s)
{
    x *= s;
    y *= s;

    return *this;
}

inline Vec2i& Vec2i::operator /= (const Vec2i& v)
{
    x /= v.x;
    y /= v.y;

    return *this;
}

inline Vec2i& Vec2i::operator /= (int s)
{
    x /= s;
    y /= s;

    return *this;
}

inline Vec2i Vec2i::operator + (const Vec2i& a) const
{
    Vec2i result;

    result.x = x + a.x;
    result.y = y + a.y;

    return result;
}

inline Vec2i Vec2i::operator - (const Vec2i& a) const
{
    Vec2i result;

    result.x = x - a.x;
    result.y = y - a.y;

    return result;
}

inline const Vec2i& Vec2i::operator + () const
{
    return *this;
}

inline Vec2i Vec2i::operator - () const
{
    Vec2i result;

    result.x = -x;
    result.y = -y;

    return result;
}

inline Vec2i Vec2i::operator * (const Vec2i& a) const
{
    Vec2i result;

    result.x = x * a.x;
    result.y = y * a.y;

    return result;
}

inline Vec2i Vec2i::operator * (int s) const
{
    Vec2i result;

    result.x = x * s;
    result.y = y * s;

    return result;
}

inline Vec2i operator * (int s, const Vec2i& v)
{
    return v * s;
}

inline Vec2i Vec2i::operator / (const Vec2i& a) const
{
    Vec2i result;

    result.x = x / a.x;
    result.y = y / a.y;

    return result;
}

inline Vec2i Vec2i::operator / (int s) const
{
    Vec2i result;

    result.x = x / s;
    result.y = y / s;

    return result;
}

inline int dot(const Vec2i& a, const Vec2i& b)
{
    return a.x * b.x + a.y * b.y;
}

inline Vec2i cross(const Vec2i& a)
{
    Vec2i result;

    result.x = -a.y;
    result.y =  a.x;

    return result;
}

inline int sqrlen(const Vec2i& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline int len(const Vec2i& v)
{
    return sqrt(dot(v, v));
}

inline Vec2i norm(const Vec2i& v)
{
    VL_ASSERT_MSG(sqrlen(v) > int(vl_zero), "normalising length-zero vector");
    return v / len(v);
}

inline Vec2i norm_safe(const Vec2i& v)
{
    return v / (len(v) + int(1e-8));
}

inline Vec2i inv(const Vec2i& v)
{
    return Vec2i(int(1) / v.x, int(1) / v.y);
}
#endif

inline Vec2i abs(const Vec2i& v)
{
    return Vec2i(abs(v.x), abs(v.y));
}

inline Vec2i& Vec2i::MakeUnit(int i, int k)
{
    if (i == 0)
    { x = k; y = vl_zero; }
    else if (i == 1)
    { x = vl_zero; y = k; }
    else
        VL_ERROR("(Vec2::Unit) illegal unit vector");

    return *this;
}

inline Vec2i& Vec2i::MakeZero()
{
    x = vl_zero; y = vl_zero;
    return *this;
}

inline Vec2i& Vec2i::MakeBlock(int k)
{
    x = k; y = k;
    return *this;
}


inline Vec2i::Vec2i(VLBlock k) :
    x(int(k)),
    y(int(k))
{
}

inline Vec2i::Vec2i(VLAxis k, int s)
{
    MakeUnit(k, s);
}

inline Vec2i::Vec2i(VLMinusAxis k, int s)
{
    MakeUnit(k, -s);
}

inline Vec2i& Vec2i::operator = (VLBlock k)
{
    MakeBlock(int(k));
    return *this;
}

inline Vec2i& Vec2i::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline Vec2i& Vec2i::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline bool Vec2i::operator == (const Vec2i& a) const
{
    return x == a.x && y == a.y;
}

inline bool Vec2i::operator != (const Vec2i& a) const
{
    return x != a.x || y != a.y;
}

inline bool Vec2i::operator < (const Vec2i& a) const
{
    return x < a.x && y < a.y;
}

inline bool Vec2i::operator > (const Vec2i& a) const
{
    return x > a.x && y > a.y;
}

inline bool Vec2i::operator <= (const Vec2i& a) const
{
    return x <= a.x && y <= a.y;
}

inline bool Vec2i::operator >= (const Vec2i& a) const
{
    return x >= a.x && y >= a.y;
}

#endif

#ifndef VL_VEC3_H
#define VL_VEC3_H


// --- Vec3 Class -------------------------------------------------------------


class Vec2i;

class Vec3i : public VLVecType
{
public:
    // Constructors
    Vec3i();
    Vec3i(int x, int y, int z);         // [x, y, z]
    Vec3i(const Vec3i& v);                 // Copy constructor
    Vec3i(const Vec2i& v, int w);         // Hom. 2D vector

    Vec3i(VLBlock     b);                  // vl_0, vl_1, ...
    Vec3i(VLAxis      a,  int s = vl_1);  // vl_x, vl_y
    Vec3i(VLMinusAxis a,  int s = vl_1);  // vl_minus_x, vl_minus_y

    explicit Vec3i(int s);
    explicit Vec3i(const int v[]);

    template<class T, class U = typename T::IsVec> explicit Vec3i(const T& v);

    // Accessor functions
    int          Elts() const { return 3; };   // Element count

    int&        operator [] (int i);          // Indexing by row
    const int&  operator [] (int i) const;    // Indexing by row

    int*        Ref();                        // Return pointer to data
    const int*  Ref() const;                  // Return pointer to data

    // Assignment operators
    Vec3i&       operator =  (const Vec3i& a);
    Vec3i&       operator =  (VLBlock k);
    Vec3i&       operator =  (VLAxis k);
    Vec3i&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> Vec3i& operator = (const T& v);

    Vec3i&       operator += (const Vec3i& a);
    Vec3i&       operator -= (const Vec3i& a);
    Vec3i&       operator *= (const Vec3i& a);
    Vec3i&       operator *= (int s);
    Vec3i&       operator /= (const Vec3i& a);
    Vec3i&       operator /= (int s);

    // Comparison operators
    bool         operator == (const Vec3i& a) const; // v == a?
    bool         operator != (const Vec3i& a) const; // v != a?
    bool         operator <  (const Vec3i& a) const; // All v.i <  a.i?
    bool         operator >= (const Vec3i& a) const; // All v.i >= a.i?

    // Arithmetic operators
    Vec3i        operator + (const Vec3i& a) const;  // v + a
    Vec3i        operator - (const Vec3i& a) const;  // v - a
    const Vec3i& operator + () const;                // -v
    Vec3i        operator - () const;                // -v
    Vec3i        operator * (const Vec3i& a) const;  // v * a (vx * ax, ...)
    Vec3i        operator * (int s) const;          // v * s
    Vec3i        operator / (const Vec3i& a) const;  // v / a (vx / ax, ...)
    Vec3i        operator / (int s) const;          // v / s

    // Initialisers
    Vec3i&       MakeZero();                        // Zero vector
    Vec3i&       MakeUnit(int i, int k = vl_one);  // I[i]
    Vec3i&       MakeBlock(int k = vl_one);        // All-k vector

    // Conversion
    Vec2i&       AsVec2();
    const Vec2i& AsVec2() const;

    // Data
    int x;
    int y;
    int z;
};


// --- Vec3 operators ---------------------------------------------------------

Vec3i operator * (int s, const Vec3i& v);       // s * v

int  dot(const Vec3i& a, const Vec3i& b);       // a . b
Vec3i cross    (const Vec3i& a, const Vec3i& b); // a x b
Vec3i cross_x  (const Vec3i& v);                 // v x e_x
Vec3i cross_y  (const Vec3i& v);                 // v x e_y
Vec3i cross_z  (const Vec3i& v);                 // v x e_z
int  sqrlen   (const Vec3i& v);                 // v . v
#ifndef VL_NO_REAL
int  len      (const Vec3i& v);                 // || v ||
Vec3i norm     (const Vec3i& v);                 // v / || v ||
Vec3i norm_safe(const Vec3i& v);                 // v / || v ||, handles || v || = 0
Vec3i inv      (const Vec3i& v);                 // inverse: 1 / v
Vec2i proj     (const Vec3i& v);                 // homogeneous projection
#endif
Vec3i abs      (const Vec3i& v);                 // abs(v_i)


// --- Inlines ----------------------------------------------------------------


inline Vec3i::Vec3i()
{
}

inline Vec3i::Vec3i(int a, int b, int c) :
    x(a),
    y(b),
    z(c)
{}

inline Vec3i::Vec3i(const Vec3i& v)  :
    x(v.x),
    y(v.y),
    z(v.z)
{}

inline Vec3i::Vec3i(const Vec2i& v, int z_in) :
    x(v.x),
    y(v.y),
    z(z_in)
{}

inline Vec3i::Vec3i(int s) :
    x(s),
    y(s),
    z(s)
{}

inline Vec3i::Vec3i(const int v[]) :
    x(v[0]),
    y(v[1]),
    z(v[2])
{}

template<class T, class U> inline Vec3i::Vec3i(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec3) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = int(v[i]);
}

inline int& Vec3i::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 3, "(Vec3::[i]) index out of range");
    return (&x)[i];
}

inline const int& Vec3i::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 3, "(Vec3::[i]) index out of range");
    return (&x)[i];
}

inline int* Vec3i::Ref()
{
    return &x;
}

inline const int* Vec3i::Ref() const
{
    return &x;
}

inline Vec3i& Vec3i::operator = (const Vec3i& v)
{
    x = v.x;
    y = v.y;
    z = v.z;

    return *this;
}

template<class T, class U> inline Vec3i& Vec3i::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec3::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = int(v[i]);

    return *this;
}

inline Vec3i& Vec3i::operator += (const Vec3i& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

    return *this;
}

inline Vec3i& Vec3i::operator -= (const Vec3i& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
}

inline Vec3i& Vec3i::operator *= (const Vec3i& a)
{
    x *= a.x;
    y *= a.y;
    z *= a.z;

    return *this;
}

inline Vec3i& Vec3i::operator *= (int s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

inline Vec3i& Vec3i::operator /= (const Vec3i& a)
{
    x /= a.x;
    y /= a.y;
    z /= a.z;

    return *this;
}

inline Vec3i& Vec3i::operator /= (int s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}

inline Vec3i Vec3i::operator + (const Vec3i& a) const
{
    Vec3i result;

    result.x = x + a.x;
    result.y = y + a.y;
    result.z = z + a.z;

    return result;
}

inline Vec3i Vec3i::operator - (const Vec3i& a) const
{
    Vec3i result;

    result.x = x - a.x;
    result.y = y - a.y;
    result.z = z - a.z;

    return result;
}

inline const Vec3i& Vec3i::operator + () const
{
    return *this;
}

inline Vec3i Vec3i::operator - () const
{
    Vec3i result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

inline Vec3i Vec3i::operator * (const Vec3i& a) const
{
    Vec3i result;

    result.x = x * a.x;
    result.y = y * a.y;
    result.z = z * a.z;

    return result;
}

inline Vec3i Vec3i::operator * (int s) const
{
    Vec3i result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

inline Vec3i Vec3i::operator / (const Vec3i& a) const
{
    Vec3i result;

    result.x = x / a.x;
    result.y = y / a.y;
    result.z = z / a.z;

    return result;
}

inline Vec3i Vec3i::operator / (int s) const
{
    Vec3i result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;

    return result;
}

inline Vec3i operator * (int s, const Vec3i& v)
{
    return v * s;
}

inline Vec3i& Vec3i::MakeUnit(int n, int k)
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

inline Vec3i& Vec3i::MakeZero()
{
    x = vl_zero; y = vl_zero; z = vl_zero;
    return *this;
}

inline Vec3i& Vec3i::MakeBlock(int k)
{
    x = k; y = k; z = k;
    return *this;
}


inline Vec3i::Vec3i(VLBlock k) :
    x(int(k)),
    y(int(k)),
    z(int(k))
{
}

inline Vec3i::Vec3i(VLAxis a, int s)
{
    MakeUnit(a, s);
}

inline Vec3i::Vec3i(VLMinusAxis a, int s)
{
    MakeUnit(a, -s);
}

inline Vec3i& Vec3i::operator = (VLBlock k)
{
    MakeBlock(int(k));
    return *this;
}

inline Vec3i& Vec3i::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline Vec3i& Vec3i::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline bool Vec3i::operator == (const Vec3i& a) const
{
    return x == a.x && y == a.y && z == a.z;
}

inline bool Vec3i::operator != (const Vec3i& a) const
{
    return x != a.x || y != a.y || z != a.z;
}

inline bool Vec3i::operator < (const Vec3i& a) const
{
    return x < a.x && y < a.y && z < a.z;
}

inline bool Vec3i::operator >= (const Vec3i& a) const
{
    return x >= a.x && y >= a.y && z >= a.z;
}

inline Vec2i& Vec3i::AsVec2()
{
    return (Vec2i&) *this;
}

inline const Vec2i& Vec3i::AsVec2() const
{
    return (const Vec2i&) *this;
}


inline int dot(const Vec3i& a, const Vec3i& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3i cross(const Vec3i& a, const Vec3i& b)
{
    Vec3i result;

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}

inline Vec3i cross_x(const Vec3i& v)
{ return Vec3i(int(vl_zero), v.z, -v.y); }

inline Vec3i cross_y(const Vec3i& v)
{ return Vec3i(-v.z, int(vl_zero), v.x); }

inline Vec3i cross_z(const Vec3i& v)
{ return Vec3i(v.y, -v.x, int(vl_zero)); }

inline int sqrlen(const Vec3i& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline int len(const Vec3i& v)
{
    return sqrt(int(dot(v, v)));
}

inline Vec3i norm(const Vec3i& v)
{
    VL_ASSERT_MSG(sqrlen(v) > int(vl_zero), "normalising length-zero vector");
    return v / len(v);
}

inline Vec3i norm_safe(const Vec3i& v)
{
    return v / (len(v) + int(1e-8));
}

inline Vec3i inv(const Vec3i& v)
{
    return Vec3i(int(1) / v.x, int(1) / v.y, int(1) / v.z);
}

inline Vec2i proj(const Vec3i& v)
{
    Vec2i result;

    VL_ASSERT_MSG(v.z != int(vl_zero), "(Vec3/proj) last elt. is zero");

    result.x = v.x / v.z;
    result.y = v.y / v.z;

    return result;
}
#endif

inline Vec3i abs(const Vec3i& v)
{
    return Vec3i(abs(v.x), abs(v.y), abs(v.z));
}

#endif

#ifndef VL_VEC4_H
#define VL_VEC4_H


// --- Vec4 Class -------------------------------------------------------------


class Vec2i;
class Vec3i;

class Vec4i : public VLVecType
{
public:
    // Constructors
    Vec4i();
    Vec4i(int x, int y, int z, int w);      // [x, y, z, w]
    Vec4i(const Vec4i& v);                      // Copy constructor
    Vec4i(const Vec3i& v, int w);              // Homogeneous 3D vector

    Vec4i(VLBlock     b);                       // vl_0, vl_1, ...
    Vec4i(VLAxis      a, int s = vl_1);        // vl_x, vl_y
    Vec4i(VLMinusAxis a, int s = vl_1);        // vl_x, vl_y

    explicit Vec4i(int s);
    explicit Vec4i(const int v[]);

    template<class T, class U = typename T::IsVec> explicit Vec4i(const T& v);

    // Accessor functions
    int          Elts() const { return 4; };   // Element count

    int&        operator [] (int i);          // Indexing by row
    const int&  operator [] (int i) const;    // Indexing by row

    int*        Ref();                        // Return pointer to data
    const int*  Ref() const;                  // Return pointer to data

    // Assignment operators
    Vec4i&       operator =  (const Vec4i& a);
    Vec4i&       operator =  (VLBlock k);
    Vec4i&       operator =  (VLAxis k);
    Vec4i&       operator =  (VLMinusAxis k);

    template<class T, class U = typename T::IsVec> Vec4i& operator = (const T& v);

    Vec4i&       operator += (const Vec4i& a);
    Vec4i&       operator -= (const Vec4i& a);
    Vec4i&       operator *= (const Vec4i& a);
    Vec4i&       operator *= (int s);
    Vec4i&       operator /= (const Vec4i& a);
    Vec4i&       operator /= (int s);

    // Comparison operators
    bool         operator == (const Vec4i& a) const; // v == a ?
    bool         operator != (const Vec4i& a) const; // v != a ?
    bool         operator <  (const Vec4i& a) const; // All v.i <  a.i?
    bool         operator >= (const Vec4i& a) const; // All v.i >= a.i?

    // Arithmetic operators
    Vec4i        operator + (const Vec4i& a) const;  // v + a
    Vec4i        operator - (const Vec4i& a) const;  // v - a
    const Vec4i& operator + () const;                // -v
    Vec4i        operator - () const;                // -v
    Vec4i        operator * (const Vec4i& a) const;  // v * a (vx * ax, ...)
    Vec4i        operator * (int s) const;        // v * s
    Vec4i        operator / (const Vec4i& a) const;  // v / a (vx / ax, ...)
    Vec4i        operator / (int s) const;        // v / s

    // Initialisers
    Vec4i&       MakeZero();                        // Zero vector
    Vec4i&       MakeUnit(int i, int k = vl_one);  // kI[i]
    Vec4i&       MakeBlock(int k = vl_one);        // All-k vector

    // Conversion
    Vec2i&       AsVec2();
    const Vec2i& AsVec2() const;
    Vec3i&       AsVec3();
    const Vec3i& AsVec3() const;

    // Data
    int x;
    int y;
    int z;
    int w;
};


// --- Vec4 operators ---------------------------------------------------------

Vec4i operator * (int s, const Vec4i& v);    // s * v

int  dot  (const Vec4i& a, const Vec4i& b);  // a . b
Vec4i cross(const Vec4i& a, const Vec4i& b, const Vec4i& c); // 4D cross prod.
int  sqrlen   (const Vec4i& v);              // v . v
#ifndef VL_NO_REAL
int  len      (const Vec4i& v);              // || v ||
Vec4i norm     (const Vec4i& v);              // v / || v ||
Vec4i norm_safe(const Vec4i& v);              // v / || v ||, handles || v || = 0
Vec4i inv      (const Vec4i& v);              // inverse: 1 / v
Vec3i proj     (const Vec4i& v);              // hom. projection
#endif
Vec4i abs      (const Vec4i& v);              // abs(v_i)


// --- Inlines ----------------------------------------------------------------


inline Vec4i::Vec4i()
{
}

inline Vec4i::Vec4i(int a, int b, int c, int d) :
    x(a),
    y(b),
    z(c),
    w(d)
{}

inline Vec4i::Vec4i(const Vec4i& v) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(v.w)
{}

inline Vec4i::Vec4i(const Vec3i& v, int w_in) :
    x(v.x),
    y(v.y),
    z(v.z),
    w(w_in)
{
}

inline Vec4i::Vec4i(int s) :
    x(s),
    y(s),
    z(s),
    w(s)
{}

inline Vec4i::Vec4i(const int v[]) :
    x(v[0]),
    y(v[1]),
    z(v[2]),
    w(v[3])
{
}

template<class T, class U> inline Vec4i::Vec4i(const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec4) Vector sizes don't match");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = int(v[i]);
}

inline int& Vec4i::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 4, "(Vec4::[i]) index out of range");
    return (&x)[i];
}

inline const int& Vec4i::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 4, "(Vec4::[i]) index out of range");
    return (&x)[i];
}

inline int* Vec4i::Ref()
{
    return &x;
}

inline const int* Vec4i::Ref() const
{
    return &x;
}

inline Vec4i& Vec4i::operator = (const Vec4i& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;

    return *this;
}

template<class T, class U> inline Vec4i& Vec4i::operator = (const T& v)
{
    VL_ASSERT_MSG(Elts() == v.Elts() || v.Elts() == VL_REPEAT, "(Vec4::=) Vector sizes don't match");

    for (int i = 0; i < Elts(); i++)
        (*this)[i] = Elt(v[i]);

    return *this;
}

inline Vec4i& Vec4i::operator += (const Vec4i& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
}

inline Vec4i& Vec4i::operator -= (const Vec4i& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
}

inline Vec4i& Vec4i::operator *= (const Vec4i& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;

    return *this;
}

inline Vec4i& Vec4i::operator *= (int s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

inline Vec4i& Vec4i::operator /= (const Vec4i& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;

    return *this;
}

inline Vec4i& Vec4i::operator /= (int s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}


inline Vec4i Vec4i::operator + (const Vec4i& a) const
{
    Vec4i result;

    result.x = x + a.x;
    result.y = y + a.y;
    result.z = z + a.z;
    result.w = w + a.w;

    return result;
}

inline Vec4i Vec4i::operator - (const Vec4i& a) const
{
    Vec4i result;

    result.x = x - a.x;
    result.y = y - a.y;
    result.z = z - a.z;
    result.w = w - a.w;

    return result;
}

inline const Vec4i& Vec4i::operator + () const
{
    return *this;
}

inline Vec4i Vec4i::operator - () const
{
    Vec4i result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

inline Vec4i Vec4i::operator * (const Vec4i& a) const
{
    Vec4i result;

    result.x = x * a.x;
    result.y = y * a.y;
    result.z = z * a.z;
    result.w = w * a.w;

    return result;
}

inline Vec4i Vec4i::operator * (int s) const
{
    Vec4i result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    result.w = w * s;

    return result;
}

inline Vec4i Vec4i::operator / (const Vec4i& a) const
{
    Vec4i result;

    result.x = x / a.x;
    result.y = y / a.y;
    result.z = z / a.z;
    result.w = w / a.w;

    return result;
}

inline Vec4i Vec4i::operator / (int s) const
{
    Vec4i result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;
    result.w = w / s;

    return result;
}

inline Vec4i operator * (int s, const Vec4i& v)
{
    return v * s;
}

inline Vec4i& Vec4i::MakeZero()
{
    x = vl_zero; y = vl_zero; z = vl_zero; w = vl_zero;
    return *this;
}

inline Vec4i& Vec4i::MakeBlock(int k)
{
    x = k; y = k; z = k; w = k;
    return *this;
}


inline Vec4i::Vec4i(VLBlock k)
{
    MakeBlock(int(k));
}

inline Vec4i::Vec4i(VLAxis k, int s)
{
    MakeUnit(k, s);
}

inline Vec4i::Vec4i(VLMinusAxis k, int s)
{
    MakeUnit(k, -s);
}

inline Vec4i& Vec4i::operator = (VLBlock k)
{
    MakeBlock(int(k));
    return *this;
}

inline Vec4i& Vec4i::operator = (VLAxis k)
{
    MakeUnit(k);
    return *this;
}

inline Vec4i& Vec4i::operator = (VLMinusAxis k)
{
    MakeUnit(k, vl_minus_one);
    return *this;
}

inline Vec2i& Vec4i::AsVec2()
{
    return (Vec2i&) *this;
}

inline const Vec2i& Vec4i::AsVec2() const
{
    return (const Vec2i&) *this;
}

inline Vec3i& Vec4i::AsVec3()
{
    return (Vec3i&) *this;
}

inline const Vec3i& Vec4i::AsVec3() const
{
    return (const Vec3i&) *this;
}



inline int dot(const Vec4i& a, const Vec4i& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline int sqrlen(const Vec4i& v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline int len(const Vec4i& v)
{
    return sqrt(dot(v, v));
}

inline Vec4i norm(const Vec4i& v)
{
    VL_ASSERT_MSG(sqrlen(v) > vl_zero, "normalising length-zero vector");
    return v / len(v);
}

inline Vec4i norm_safe(const Vec4i& v)
{
    return v / (len(v) + int(1e-8));
}

inline Vec4i inv(const Vec4i& v)
{
    return Vec4i(int(1) / v.x, int(1) / v.y, int(1) / v.z, int(1) / v.w);
}
#endif

inline Vec4i abs(const Vec4i& v)
{
    return Vec4i(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}

#endif
