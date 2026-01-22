//
// VL234i.hpp
//
// Andrew Willmott
//

#ifndef VL234i_H
#define VL234i_H

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
#define VL_NO_REAL
#define VL_PRINT_INT

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

#ifndef VLI_VEC2_H
#define VLI_VEC2_H


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

#ifndef VLI_VEC3_H
#define VLI_VEC3_H


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

#ifndef VLI_VEC4_H
#define VLI_VEC4_H


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

#ifndef VLI_MAT2_H
#define VLI_MAT2_H



// --- Mat2 Class -------------------------------------------------------------

class Mat2i : public VLMatType
{
public:
    typedef Vec2i Vec;

    // Constructors
    Mat2i();
    Mat2i(int a, int b, int c, int d);
    Mat2i(const Vec2i v0, const Vec2i v1);
    Mat2i(const Mat2i& m);

    Mat2i(Vec2i diagonal);
    Mat2i(VLDiag k);
    Mat2i(VLBlock k);

    explicit Mat2i(const int m[4]);

    template<class T, class U = typename T::IsMat> explicit Mat2i(const T& v);

    // Accessor functions
    int          Elts() const { return 4; };
    int          Rows() const { return 2; };
    int          Cols() const { return 2; };

    Vec2i&       operator [] (int i);
    const Vec2i& operator [] (int i) const;

    int&        operator () (int i, int j);
    int         operator () (int i, int j) const;

    int*        Ref();
    const int*  Ref() const;

    // Assignment operators
    Mat2i&       operator =  (const Mat2i& m);
    Mat2i&       operator =  (VLDiag k);
    Mat2i&       operator =  (VLBlock k);

    template<class T, class U = typename T::IsMat> Mat2i& operator = (const T& m);

    Mat2i&       operator += (const Mat2i& m);
    Mat2i&       operator -= (const Mat2i& m);
    Mat2i&       operator *= (const Mat2i& m);
    Mat2i&       operator *= (int s);
    Mat2i&       operator /= (int s);

    // Comparison operators
    bool         operator == (const Mat2i& m) const; // M == N?
    bool         operator != (const Mat2i& m) const; // M != N?

    // Arithmetic operators
    Mat2i        operator + (const Mat2i& m) const;  // M + N
    Mat2i        operator - (const Mat2i& m) const;  // M - N
    const Mat2i& operator + () const;                // +M
    Mat2i        operator - () const;                // -M
    Mat2i        operator * (const Mat2i& m) const;  // M * N
    Mat2i        operator * (int s) const;          // M * s
    Mat2i        operator / (int s) const;          // M / s

    // Initialisers
    void         MakeZero();                         // Zero matrix
    void         MakeIdentity();                     // Identity matrix
    void         MakeDiag (Vec2i d);                 // Diagonal = d, 0 otherwise
    void         MakeDiag (int k = vl_one);         // Diagonal = k, 0 otherwise
    void         MakeBlock(int k = vl_one);         // all elts = k

    // Data
    Vec2i x;
    Vec2i y;
};


// --- Matrix operators -------------------------------------------------------

Vec2i& operator *= (Vec2i& v, const Mat2i& m);        // v *= m
Vec2i  operator *  (const Mat2i& m, const Vec2i& v);  // m * v
Vec2i  operator *  (const Vec2i& v, const Mat2i& m);  // v * m
Mat2i  operator *  (const int   s, const Mat2i& m);  // s * m

Vec2i  row(const Mat2i& m, int i);             // Return row i of 'm' (same as m[i])
Vec2i  col(const Mat2i& m, int j);             // Return column i of 'm'

Mat2i  trans(const Mat2i& m);                  // Transpose
int   trace(const Mat2i& m);                  // Trace
Mat2i  adj  (const Mat2i& m);                  // Adjoint
int   det  (const Mat2i& m);                  // Determinant
#ifndef VL_NO_REAL
Mat2i  inv  (const Mat2i& m);                  // Inverse
#endif
Mat2i  abs  (const Mat2i& m);                  // abs(m_ij)
Mat2i  oprod(const Vec2i& a, const Vec2i& b);  // Outer product

// The xform functions help avoid dependence on whether row or column
// vectors are used to represent points and vectors.
Vec2i  xform(const Mat2i& m, const Vec2i& v);  // Transform of v by m
Mat2i  xform(const Mat2i& m, const Mat2i& n);  // Xform v -> m(n(v))


// --- Inlines ----------------------------------------------------------------


inline Mat2i::Mat2i()
{
}

inline Mat2i::Mat2i(int a, int b, int c, int d) :
    x(a, b),
    y(c, d)
{
}

inline Mat2i::Mat2i(Vec2i v0, Vec2i v1) :
    x(v0),
    y(v1)
{
}

inline Mat2i::Mat2i(const Mat2i& m) :
    x(m.x),
    y(m.y)
{
}

inline Mat2i::Mat2i(Vec2i diag)
{
    MakeDiag(diag);
}

inline Mat2i::Mat2i(VLDiag k)
{
    MakeDiag(int(k));
}

inline Mat2i::Mat2i(VLBlock k)
{
    MakeBlock(int(k));
}

inline Mat2i::Mat2i(const int m[4])
{
    int* elts = (int*) this;
    for (int i = 0; i < 4; i++)
        *elts++ = *m++;
}

template<class T, class U> inline Mat2i::Mat2i(const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat2) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];
}

inline Vec2i& Mat2i::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::[i]) index out of range");
    return (&x)[i];
}

inline const Vec2i& Mat2i::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::[i]) index out of range");
    return (&x)[i];
}

inline int& Mat2i::operator () (int i, int j)
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 2, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline int Mat2i::operator () (int i, int j) const
{
    VL_RANGE_MSG(i, 0, 2, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 2, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline int* Mat2i::Ref()
{
    return &x.x;
}

inline const int* Mat2i::Ref() const
{
    return &x.x;
}

inline void Mat2i::MakeZero()
{
    x.x = vl_zero; x.y = vl_zero;
    y.x = vl_zero; y.y = vl_zero;
}

inline void Mat2i::MakeDiag(int k)
{
    x.x = k;          x.y = vl_zero;
    y.x = vl_zero;    y.y = k;
}

inline void Mat2i::MakeDiag(Vec2i d)
{
    x.x = d.x;        x.y = vl_zero;
    y.x = vl_zero;    y.y = d.y;
}

inline void Mat2i::MakeIdentity()
{
    x.x = vl_one;     x.y = vl_zero;
    y.x = vl_zero;    y.y = vl_one;
}

inline void Mat2i::MakeBlock(int k)
{
    x.x = k; x.y = k;
    y.x = k; y.y = k;
}

inline Mat2i& Mat2i::operator = (VLDiag k)
{
    MakeDiag(int(k));
    return *this;
}

inline Mat2i& Mat2i::operator = (VLBlock k)
{
    MakeBlock(int(k));
    return *this;
}

inline Mat2i& Mat2i::operator = (const Mat2i& m)
{
    x = m.x;
    y = m.y;

    return *this;
}

template<class T, class U> inline Mat2i& Mat2i::operator = (const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat2::=) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];

    return *this;
}

inline Mat2i& Mat2i::operator += (const Mat2i& m)
{
    x += m.x;
    y += m.y;

    return *this;
}

inline Mat2i& Mat2i::operator -= (const Mat2i& m)
{
    x -= m.x;
    y -= m.y;

    return *this;
}

inline Mat2i& Mat2i::operator *= (const Mat2i& m)
{
    Vec2i t;

    t = x.x * m.x + x.y * m.y;
    y = y.x * m.x + y.y * m.y;
    x = t;

    return *this;
}

inline Mat2i& Mat2i::operator *= (int s)
{
    x *= s;
    y *= s;

    return *this;
}

inline Mat2i& Mat2i::operator /= (int s)
{
    x /= s;
    y /= s;

    return *this;
}


inline Mat2i Mat2i::operator + (const Mat2i& m) const
{
    Mat2i result;

    result.x = x + m.x;
    result.y = y + m.y;

    return result;
}

inline Mat2i Mat2i::operator - (const Mat2i& m) const
{
    Mat2i result;

    result.x = x - m.x;
    result.y = y - m.y;

    return result;
}

inline const Mat2i& Mat2i::operator + () const
{
    return *this;
}

inline Mat2i Mat2i::operator - () const
{
    Mat2i result;

    result.x = -x;
    result.y = -y;

    return result;
}

inline Mat2i Mat2i::operator * (const Mat2i& m) const
{
    Mat2i result;

    result.x.x = x.x * m.x.x + x.y * m.y.x;
    result.x.y = x.x * m.x.y + x.y * m.y.y;
    result.y.x = y.x * m.x.x + y.y * m.y.x;
    result.y.y = y.x * m.x.y + y.y * m.y.y;

    return result;
}

inline Mat2i Mat2i::operator * (int s) const
{
    Mat2i result;

    result.x = x * s;
    result.y = y * s;

    return result;
}

inline Mat2i Mat2i::operator / (int s) const
{
    Mat2i result;

    result.x = x / s;
    result.y = y / s;

    return result;
}

inline Mat2i  operator *  (int s, const Mat2i& m)
{
    return m * s;
}

inline Vec2i operator * (const Mat2i& m, const Vec2i& v)
{
    Vec2i result;

    result.x = m.x.x * v.x + m.x.y * v.y;
    result.y = m.y.x * v.x + m.y.y * v.y;

    return result;
}

inline Vec2i operator * (const Vec2i& v, const Mat2i& m)
{
    Vec2i result;

    result.x = v.x * m.x.x + v.y * m.y.x;
    result.y = v.x * m.x.y + v.y * m.y.y;

    return result;
}

inline Vec2i& operator *= (Vec2i& v, const Mat2i& m)
{
    int t;

    t   = v.x * m.x.x + v.y * m.y.x;
    v.y = v.x * m.x.y + v.y * m.y.y;
    v.x = t;

    return v;
}


inline Vec2i row(const Mat2i& m, int i)
{
    VL_INDEX(i, 2);
    return Vec2i(*(&m.x + i));
}

inline Vec2i col(const Mat2i& m, int j)
{
    VL_INDEX(j, 2);
    return Vec2i(m.x[j], m.y[j]);
}

inline Mat2i trans(const Mat2i& m)
{
    Mat2i result;

    result.x.x = m.x.x; result.x.y = m.y.x;
    result.y.x = m.x.y; result.y.y = m.y.y;

    return result;
}

inline int trace(const Mat2i& m)
{
    return m.x.x + m.y.y;
}

inline Mat2i adj(const Mat2i& m)
{
    Mat2i result;

    result.x = -cross(m.y);
    result.y =  cross(m.x);

    return result;
}

#endif

#ifndef VLI_MAT3_H
#define VLI_MAT3_H



// --- Mat3 Class -------------------------------------------------------------

class Vec4i;

class Mat3i : public VLMatType
{
public:
    typedef Vec3i Vec;

    // Constructors
    Mat3i();
    Mat3i(int a, int b, int c,
          int d, int e, int f,
          int g, int h, int i);
    Mat3i(Vec3i v0, Vec3i v1, Vec3i v2);
    Mat3i(const Mat3i& m);

    Mat3i(Vec3i diagonal);
    Mat3i(VLDiag k);
    Mat3i(VLBlock k);

    explicit Mat3i(const Mat2i& m, int scale = int(vl_1));
    explicit Mat3i(const int m[9]);

    template<class T, class U = typename T::IsMat> explicit Mat3i(const T& v);

    // Accessor functions
    int          Elts() const { return 9; };
    int          Rows() const { return 3; };
    int          Cols() const { return 3; };

    Vec3i&       operator [] (int i);
    const Vec3i& operator [] (int i) const;

    int&        operator () (int i, int j);
    int         operator () (int i, int j) const;

    int*        Ref();
    const int*  Ref() const;

    // Assignment operators
    Mat3i&       operator =  (const Mat3i& m);
    Mat3i&       operator =  (VLDiag k);
    Mat3i&       operator =  (VLBlock k);

    template<class T, class U = typename T::IsMat> Mat3i& operator = (const T& m);

    Mat3i&       operator += (const Mat3i& m);
    Mat3i&       operator -= (const Mat3i& m);
    Mat3i&       operator *= (const Mat3i& m);
    Mat3i&       operator *= (int s);
    Mat3i&       operator /= (int s);

    // Comparison operators
    bool         operator == (const Mat3i& m) const; // M == N?
    bool         operator != (const Mat3i& m) const; // M != N?

    // Arithmetic operators
    Mat3i        operator + (const Mat3i& m) const;  // M + N
    Mat3i        operator - (const Mat3i& m) const;  // M - N
    const Mat3i& operator + () const;                // +M
    Mat3i        operator - () const;                // -M
    Mat3i        operator * (const Mat3i& m) const;  // M * N
    Mat3i        operator * (int s) const;          // M * s
    Mat3i        operator / (int s) const;          // M / s

    // Initialisers
    void         MakeZero();                         // Zero matrix
    void         MakeIdentity();                     // Identity matrix
    void         MakeDiag (Vec3i d);                 // Diagonal = d, 0 otherwise
    void         MakeDiag (int k = vl_one);         // Diagonal = k, 0 otherwise
    void         MakeBlock(int k = vl_one);         // all elts = k

    // Conversion
    Mat2i        AsMat2() const;

    // Data
    Vec3i x;
    Vec3i y;
    Vec3i z;
};


// --- Matrix operators -------------------------------------------------------

Vec3i& operator *= (Vec3i& v, const Mat3i& m);        // v *= m
Vec3i  operator *  (const Mat3i& m, const Vec3i& v);  // m * v
Vec3i  operator *  (const Vec3i& v, const Mat3i& m);  // v * m
Mat3i  operator *  (const int   s, const Mat3i& m);  // s * m

Vec3i  row(const Mat3i& m, int i);             // Return row i of 'm' (same as m[i])
Vec3i  col(const Mat3i& m, int j);             // Return column i of 'm'

Mat3i  trans(const Mat3i& m);                  // Transpose
int   trace(const Mat3i& m);                  // Trace
Mat3i  adj  (const Mat3i& m);                  // Adjoint
int   det  (const Mat3i& m);                  // Determinant
#ifndef VL_NO_REAL
Mat3i  inv  (const Mat3i& m);                  // Inverse
#endif
Mat3i  abs  (const Mat3i& m);                  // abs(m_ij)
Mat3i  oprod(const Vec3i& a, const Vec3i& b);  // Outer product

// The xform functions help avoid dependence on whether row or column
// vectors are used to represent points and vectors.
Vec3i  xform(const Mat3i& m, const Vec3i& v);  // Transform of v by m
Vec2i  xform(const Mat3i& m, const Vec2i& v);  // Hom. xform of v by m
Mat3i  xform(const Mat3i& m, const Mat3i& n);  // Xform v -> m(n(v))


// --- Inlines ----------------------------------------------------------------

inline Mat3i::Mat3i()
{
}

inline Mat3i::Mat3i
(
    int a, int b, int c,
    int d, int e, int f,
    int g, int h, int i
) :
    x(a, b, c),
    y(d, e, f),
    z(g, h, i)
{
}

inline Mat3i::Mat3i(Vec3i v0, Vec3i v1, Vec3i v2) :
    x(v0),
    y(v1),
    z(v2)
{
}

inline Mat3i::Mat3i(const Mat3i& m) :
    x(m.x),
    y(m.y),
    z(m.z)
{
}

inline Mat3i::Mat3i(Vec3i d)
{
    MakeDiag(d);
}

inline Mat3i::Mat3i(VLDiag k)
{
    MakeDiag(int(k));
}

inline Mat3i::Mat3i(VLBlock k)
{
    MakeBlock(int(k));
}

inline Mat3i::Mat3i(const int m[9])
{
    int* elts = (int*) this;
    for (int i = 0; i < 9; i++)
        *elts++ = *m++;
}

template<class T, class U> inline Mat3i::Mat3i(const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat3) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];
}

inline Vec3i& Mat3i::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 3, "(Mat3::[i]) index out of range");
    return (&x)[i];
}

inline const Vec3i& Mat3i::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 3, "(Mat3::[i]) index out of range");
    return (&x)[i];
}

inline int& Mat3i::operator () (int i, int j)
{
    VL_RANGE_MSG(i, 0, 3, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 3, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline int Mat3i::operator () (int i, int j) const
{
    VL_RANGE_MSG(i, 0, 3, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 3, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline int* Mat3i::Ref()
{
    return &x.x;
}

inline const int* Mat3i::Ref() const
{
    return &x.x;
}

inline void Mat3i::MakeZero()
{
    x.x = vl_zero; x.y = vl_zero; x.z = vl_zero;
    y.x = vl_zero; y.y = vl_zero; y.z = vl_zero;
    z.x = vl_zero; z.y = vl_zero; z.z = vl_zero;
}

inline void Mat3i::MakeIdentity()
{
    x.x = vl_one;     x.y = vl_zero;    x.z = vl_zero;
    y.x = vl_zero;    y.y = vl_one;     y.z = vl_zero;
    z.x = vl_zero;    z.y = vl_zero;    z.z = vl_one;
}

inline void Mat3i::MakeDiag(Vec3i d)
{
    x.x = d.x;        x.y = vl_zero;    x.z = vl_zero;
    y.x = vl_zero;    y.y = d.y;        y.z = vl_zero;
    z.x = vl_zero;    z.y = vl_zero;    z.z = d.z;
}

inline void Mat3i::MakeDiag(int k)
{
    x.x = k;          x.y = vl_zero;    x.z = vl_zero;
    y.x = vl_zero;    y.y = k;          y.z = vl_zero;
    z.x = vl_zero;    z.y = vl_zero;    z.z = k;
}

inline void Mat3i::MakeBlock(int k)
{
    x.x = k; x.y = k; x.z = k;
    y.x = k; y.y = k; y.z = k;
    z.x = k; z.y = k; z.z = k;
}

inline Mat2i Mat3i::AsMat2() const
{
    return Mat2i(x.AsVec2(), y.AsVec2());
}

inline Mat3i& Mat3i::operator = (VLDiag k)
{
    MakeDiag(int(k));
    return *this;
}

inline Mat3i& Mat3i::operator = (VLBlock k)
{
    MakeBlock(int(k));
    return *this;
}

template<class T, class U> inline Mat3i& Mat3i::operator = (const T& m)
{
   VL_ASSERT_MSG(m.Rows() == Rows()|| m.Rows() == VL_REPEAT, "(Mat3::=) Matrix rows don't match");

   for (int i = 0; i < Rows(); i++)
       (*this)[i] = m[i];

   return *this;
}

inline const Mat3i& Mat3i::operator + () const
{
    return *this;
}

inline Mat3i operator *  (const int s, const Mat3i& m)
{
    return m * s;
}

inline Vec3i operator * (const Mat3i& m, const Vec3i& v)
{
    Vec3i result;

    result.x = v.x * m.x.x + v.y * m.x.y + v.z * m.x.z;
    result.y = v.x * m.y.x + v.y * m.y.y + v.z * m.y.z;
    result.z = v.x * m.z.x + v.y * m.z.y + v.z * m.z.z;

    return result;
}

inline Vec3i operator * (const Vec3i& v, const Mat3i& m)
{
    Vec3i result;

    result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
    result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
    result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;

    return result;
}

inline Vec3i& operator *= (Vec3i& v, const Mat3i& m)
{
    int t0, t1;

    t0  = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
    t1  = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
    v.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
    v.x = t0;
    v.y = t1;

    return v;
}

inline Vec3i row(const Mat3i& m, int i)
{
    VL_INDEX(i, 3);
    return Vec3i(*(&m.x + i));
}

inline Vec3i col(const Mat3i& m, int j)
{
    VL_INDEX(j, 3);
    return Vec3i(m.x[j], m.y[j], m.z[j]);
}

#endif


#ifndef VLI_MAT4_H
#define VLI_MAT4_H



// --- Mat4 Class -------------------------------------------------------------

class Vec3i;

class Mat4i : public VLMatType
{
public:
    typedef Vec4i Vec;

    // Constructors
    Mat4i();
    Mat4i(int a, int b, int c, int d,
          int e, int f, int g, int h,
          int i, int j, int k, int l,
          int m, int n, int o, int p);
    Mat4i(Vec4i v0, Vec4i v1, Vec4i v2, Vec4i v3);
    Mat4i(const Mat4i& m);

    Mat4i(Vec4i diagonal);
    Mat4i(VLDiag k);
    Mat4i(VLBlock k);

    explicit Mat4i(const Mat3i& m, int scale = int(vl_1));
    explicit Mat4i(const int data[16]);

    template<class T, class U = typename T::IsMat> explicit Mat4i(const T& v);

    // Accessor functions
    int          Elts() const { return 16; };
    int          Rows() const { return  4; };
    int          Cols() const { return  4; };

    Vec4i&       operator [] (int i);
    const Vec4i& operator [] (int i) const;

    int&        operator () (int i, int j);
    int         operator () (int i, int j) const;

    int*        Ref();
    const int*  Ref() const;

    // Assignment operators
    Mat4i&       operator =  (const Mat4i& m);
    Mat4i&       operator =  (VLDiag k);
    Mat4i&       operator =  (VLBlock k);

    template<class T, class U = typename T::IsMat> Mat4i& operator = (const T& m);

    Mat4i&       operator += (const Mat4i& m);
    Mat4i&       operator -= (const Mat4i& m);
    Mat4i&       operator *= (const Mat4i& m);
    Mat4i&       operator *= (int s);
    Mat4i&       operator /= (int s);

    // Comparison operators
    bool         operator == (const Mat4i& m) const; // M == N?
    bool         operator != (const Mat4i& m) const; // M != N?

    // Arithmetic operators
    Mat4i        operator + (const Mat4i& m) const;  // M + N
    Mat4i        operator - (const Mat4i& m) const;  // M - N
    const Mat4i& operator + () const;                // +M
    Mat4i        operator - () const;                // -M
    Mat4i        operator * (const Mat4i& m) const;  // M * N
    Mat4i        operator * (int s) const;          // M * s
    Mat4i        operator / (int s) const;          // M / s

    // Initialisers
    void         MakeZero();                         // Zero matrix
    void         MakeIdentity();                     // Identity matrix
    void         MakeDiag (Vec4i d);                 // Diagonal = d, 0 otherwise
    void         MakeDiag (int k = vl_one);         // Diagonal = k, 0 otherwise
    void         MakeBlock(int k = vl_one);         // All elts = k

    // Conversion
    Mat3i        AsMat3() const;

    // Data
    Vec4i x;
    Vec4i y;
    Vec4i z;
    Vec4i w;
};


// --- Matrix operators -------------------------------------------------------

Vec4i& operator *= (Vec4i& a, const Mat4i& m);        // v *= m
Vec4i  operator *  (const Mat4i& m, const Vec4i& v);  // m * v
Vec4i  operator *  (const Vec4i& v, const Mat4i& m);  // v * m
Mat4i  operator *  (const int   s, const Mat4i& m);  // s * m

Vec4i  row(const Mat4i& m, int i);             // Return row i of 'm' (same as m[i])
Vec4i  col(const Mat4i& m, int j);             // Return column i of 'm'

Mat4i  trans(const Mat4i& m);                  // Transpose
int   trace(const Mat4i& m);                  // Trace
Mat4i  adj  (const Mat4i& m);                  // Adjoint
int   det  (const Mat4i& m);                  // Determinant
#ifndef VL_NO_REAL
Mat4i  inv  (const Mat4i& m);                  // Inverse
#endif
Mat4i  abs  (const Mat4i& m);                  // abs(m_ij)
Mat4i  oprod(const Vec4i& a, const Vec4i& b);  // Outer product

// The xform functions help avoid dependence on whether row or column
// vectors are used to represent points and vectors.
Vec4i  xform(const Mat4i& m, const Vec4i& v);  // Transform of v by m
Vec3i  xform(const Mat4i& m, const Vec3i& v);  // Hom. xform of v by m
Mat4i  xform(const Mat4i& m, const Mat4i& n);  // Xform v -> m(n(v))


// --- Inlines ----------------------------------------------------------------

inline Mat4i::Mat4i()
{
}

inline Mat4i::Mat4i(Vec4i v0, Vec4i v1, Vec4i v2, Vec4i v3) :
    x(v0),
    y(v1),
    z(v2),
    w(v3)
{
}

inline Mat4i::Mat4i(const Mat4i& m) :
    x(m.x),
    y(m.y),
    z(m.z),
    w(m.w)
{
}

inline Mat4i::Mat4i(Vec4i d)
{
    MakeDiag(d);
}

inline Mat4i::Mat4i(VLDiag k)
{
    MakeDiag(int(k));
}

inline Mat4i::Mat4i(VLBlock k)
{
    MakeBlock(int(k));
}

inline Mat4i::Mat4i(const int m[16])
{
    int* elts = (int*) this;
    for (int i = 0; i < 16; i++)
        *elts++ = *m++;
}

template<class T, class U> inline Mat4i::Mat4i(const T& m)
{
    VL_ASSERT_MSG(m.Rows() == Rows() || m.Rows() == VL_REPEAT, "(Mat4) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];
}

inline Vec4i& Mat4i::operator [] (int i)
{
    VL_RANGE_MSG(i, 0, 4, "(Mat4::[i]) index out of range");
    return (&x)[i];
}

inline const Vec4i& Mat4i::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, 4, "(Mat4::[i]) index out of range");
    return (&x)[i];
}

inline int& Mat4i::operator () (int i, int j)
{
    VL_RANGE_MSG(i, 0, 4, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 4, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline int Mat4i::operator () (int i, int j) const
{
    VL_RANGE_MSG(i, 0, 4, "(Mat2::(i,j)) index out of range");
    VL_RANGE_MSG(j, 0, 4, "(Mat2::(i,j)) index out of range");

    return (&x)[i][j];
}

inline int* Mat4i::Ref()
{
    return &x.x;
}

inline const int* Mat4i::Ref() const
{
    return &x.x;
}

inline Mat4i& Mat4i::operator = (VLDiag k)
{
    MakeDiag(int(k));
    return *this;
}

inline Mat4i& Mat4i::operator = (VLBlock k)
{
    MakeBlock(int(k));
    return *this;
}

template<class T, class U> inline Mat4i& Mat4i::operator = (const T& m)
{
    VL_ASSERT_MSG(Rows() == m.Rows() || m.Rows() == VL_REPEAT, "(Mat4::=) Matrix rows don't match");

    for (int i = 0; i < Rows(); i++)
        (*this)[i] = m[i];

    return *this;
}

inline const Mat4i& Mat4i::operator + () const
{
    return *this;
}

inline Mat4i operator * (int s, const Mat4i& m)
{
    return m * s;
}

inline Vec4i row(const Mat4i& m, int i)
{
    VL_INDEX(i, 4);
    return Vec4i(*(&m.x + i));
}

inline Vec4i col(const Mat4i& m, int j)
{
    VL_INDEX(j, 4);
    return Vec4i(m.x[j], m.y[j], m.z[j], m.w[j]);
}

#endif

#ifndef VLI_SWIZZLE_H
#define VLI_SWIZZLE_H

// Vec3->Vec2
const Vec2i& xy(const Vec3i& v);
      Vec2i& xy(      Vec3i& v);
const Vec2i  yz(const Vec3i& v);
const Vec2i  xz(const Vec3i& v);

// Vec4->Vec2
const Vec2i& xy(const Vec4i& v);
      Vec2i& xy(      Vec4i& v);
const Vec2i  yz(const Vec4i& v);
const Vec2i  zw(const Vec4i& v);

const Vec2i  xw(const Vec4i& v);
const Vec2i  yw(const Vec4i& v);
const Vec2i  zw(const Vec4i& v);

// Vec4->Vec3
const Vec3i& xyz(const Vec4i& v);
      Vec3i& xyz(      Vec4i& v);
const Vec3i  xyw(const Vec4i& v);
const Vec3i  yzw(const Vec4i& v);
const Vec3i  xzw(const Vec4i& v);

// Reversal
const Vec2i reverse(const Vec2i& v);
const Vec3i reverse(const Vec3i& v);
const Vec4i reverse(const Vec4i& v);


// --- Inlines ----------------------------------------------------------------

inline const Vec2i& xy(const Vec3i& v) { return (const Vec2i&) v; }
inline       Vec2i& xy(      Vec3i& v) { return (      Vec2i&) v; }

inline const Vec2i  yz(const Vec3i& v) { return Vec2i(v.y, v.z); }
inline const Vec2i  xz(const Vec3i& v) { return Vec2i(v.x, v.z); }

inline const Vec2i& xy(const Vec4i& v) { return (const Vec2i&) v; }
inline       Vec2i& xy(      Vec4i& v) { return (      Vec2i&) v; }

inline const Vec2i  yz(const Vec4i& v) { return Vec2i(v.y, v.z); }
inline const Vec2i  xw(const Vec4i& v) { return Vec2i(v.x, v.w); }
inline const Vec2i  yw(const Vec4i& v) { return Vec2i(v.y, v.w); }
inline const Vec2i  zw(const Vec4i& v) { return Vec2i(v.z, v.w); }

inline const Vec3i& xyz(const Vec4i& v) { return (const Vec3i&) v; }
inline       Vec3i& xyz(      Vec4i& v) { return (      Vec3i&) v; }

inline const Vec3i  xyw(const Vec4i& v) { return Vec3i(v.x, v.y, v.w); }
inline const Vec3i  yzw(const Vec4i& v) { return Vec3i(v.y, v.z, v.w); }
inline const Vec3i  xzw(const Vec4i& v) { return Vec3i(v.x, v.z, v.w); }

inline const Vec2i reverse(const Vec2i& v) { return Vec2i(v.y, v.x); }
inline const Vec3i reverse(const Vec3i& v) { return Vec3i(v.z, v.y, v.x); }
inline const Vec4i reverse(const Vec4i& v) { return Vec4i(v.w, v.z, v.y, v.x); }

#endif

#include <stdio.h>

#include <string.h>

#ifndef VL_PRINT_BASE_H
#define VL_PRINT_BASE_H




// Base routines used by Print/Print234

// Print according to specific format, see VL_FORMAT below
int vl_fprintf     (FILE* file, const char* format, int n,               const int* elts, int width = 1, int precision = 3);
int vl_fprintf     (FILE* file, const char* format, int r, int c,        const int* elts, int width = 1, int precision = 3);
int vl_fprintf     (FILE* file, const char* format, int s, int r, int c, const int* elts, int width = 1, int precision = 3);

// Print in format that can be compiled as C, 'name' is variable name.
int vl_fprint_as_c(FILE* file, const char* name,   int n,               const int* elts, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name,   int r, int c,        const int* elts, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name,   int s, int r, int c, const int* elts, int width = 1, int precision = 3);

// Write string according to specific format, see VL_FORMAT below. Behaviour same as unix snprintf.
int vl_snprintf(char* str, size_t sz, const char* fmt, int n,               const int* elts, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t sz, const char* fmt, int r, int c,        const int* elts, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t sz, const char* fmt, int s, int r, int c, const int* elts, int width = 1, int precision = 3);

// Variant that advances 'str' and reduces 'size' accordingly.
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int n,               const int* elts, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int r, int c,        const int* elts, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int s, int r, int c, const int* elts, int width = 1, int precision = 3);

int sn_adv(char*& str, size_t& size, int chars);  // Wrapper to get same behaviour from snprintf variants -- chars = sn_adv(str, sz, snprintf(str, sz, ...))

#if VL_CXX_11
// Some C++11 adapters that allow using the same '_adv' pattern as above with snprintf
template<class... Args> int snprintf_adv   (char*& str, size_t& size, const char* fmt, Args... args);
template<class... Args> int snprintf_append(char*  str, size_t  size, const char* fmt, Args... args);  // appends, returns size of final string

// Allow direct usage with, e.g., std::string, without having to bring in the header.
template<class S, class... Args> S& ssprintf       (S& str, const char* fmt, Args... args);
template<class S, class... Args> S& ssprintf_append(S& str, const char* fmt, Args... args);
template<class S, class... Args> S& ssprintf_adv   (S& str, size_t& cursor, const char* fmt, Args... args);

template<class S, class... Args> S& vl_ssprintf        (S& str, const char* fmt, Args... args);
template<class S, class... Args> S& vl_ssprintf_append (S& str, const char* fmt, Args... args);
template<class S, class... Args> S& vl_ssprintf_adv    (S& str, size_t& cursor, const char* fmt, Args... args);

// Shortcuts for fprintf(stdout, ...)
template<class... Args> int vl_printf(Args... args);
template<class... Args> int vl_print (Args... args);
#endif

//
// For the 'format' argument above, you can use one of the pre-defined formats:
//
//   VL_FMT_VF                ->  [1.0 2.0 3.0]
//   VL_FMT_VF_ROUND          ->  (1.0 2.0 3.0)
//   VL_FMT_VF_COL            ->  [1.0]\n[2.0]\n[3.0]\n
//   VL_FMT_VF_C              ->  { 1.0f, 2.0f, 3.0f }
//   VL_FMT_VF_PY             ->  [1.0, 2.0, 3.0]
//
//   VL_FMT_MF                ->  [1.0 2.0]\n[3.0 4.0]\n
//   VL_FMT_MF_INLINE         ->  [[1.0 2.0] [3.0 4.0]]
//   VL_FMT_MF_C              ->  {\n  { 1, 2 },\n  { 3, 4 }\n}\n
//   VL_FMT_MF_C_INLINE       ->  { { 1, 2 }, { 3, 4 } }
//   VL_FMT_MF_PY             ->  [[1.0, 2.0],\n [3.0, 4.0]]\n
//   VL_FMT_MF_PY_INLINE      ->  [[1.0, 2.0], [3.0, 4.0]]
//
// There are also '_VI' and '_MI' integer variants of these formats, e.g.,
//
//    vl_printf(VL_FMT_VI, Veci(...));
//
// For the _C formats, you can use 'D' as the type specifier, e.g., VL_FMT_VD_C,
// to print without the 'f' suffix.
//
// You can also construct your own custom format with the VL_FORMAT macro:
//
//     VL_FORMAT(start_text, element_separator, end_text, element_format)
//
// For matrices the element_format is the vector format, and for vectors it's a
// printf-style format with *.* corresponding to width/precision. E.g.,
//
//     vl_fprintf(stdout, VL_FORMAT("[", " ", "]", "%*.*f"), v);
//     vl_fprintf(stdout, VL_FORMAT("", "", "", VL_FORMAT("[", " ", "]\n", "%*.*f")), m);
//
// Finally, you can take advantage of preprocessor string gluing to add prefixes
// and suffixes to custom formats, e.g.,
//
//     vl_printf("Result: " VL_FMT_VF_INLINE " m/s\n", dir_ms);
//     -> Result: [0.1 0.3 0.1] m/s
//


// --- Implementation ---------------------------------------------------------

#ifndef VL_FORMAT

#define VL_FORMAT(M_START, M_SEP, M_END, M_FMT) M_START "\0" M_FMT "\0\3" M_SEP "\0" M_END

#define VL_FMT_F "%*.*f"

#define VL_FMT_VF              VL_FORMAT("[", " ", "]", VL_FMT_F)
#define VL_FMT_VF_ROUND        VL_FORMAT("(", " ", ")", VL_FMT_F)
#define VL_FMT_VF_COL          VL_FORMAT("", "\n", "\n", "[ " VL_FMT_F " ]")
#define VL_FMT_VF_C            VL_FORMAT("{ ", ", ", " }", VL_FMT_F "f")
#define VL_FMT_VD_C            VL_FORMAT("{ ", ", ", " }", VL_FMT_F)
#define VL_FMT_VF_PY           VL_FORMAT("[", ", ", "]", VL_FMT_F)

#define VL_FMT_MF              VL_FORMAT("", "\n", "\n", VL_FMT_VF)
#define VL_FMT_MF_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_VF)
#define VL_FMT_MF_C            VL_FORMAT("{\n", ",\n", "\n}\n", "  " VL_FMT_VF_C)
#define VL_FMT_MF_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_VF_C)
#define VL_FMT_MF_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FMT_VF_PY)
#define VL_FMT_MF_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_VF_PY)

#define VL_FMT_LF              VL_FORMAT("", ".\n", "\n", VL_FMT_MF)
#define VL_FMT_LF_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_MF_INLINE)
#define VL_FMT_LF_C            VL_FORMAT("{\n", ",\n", "\n}\n", VL_FORMAT("  {\n", ",\n", "\n  }", "    " VL_FMT_VF_C))
#define VL_FMT_LF_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_MF_C_INLINE)
#define VL_FMT_LF_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FORMAT("[", ",\n  ", "]", VL_FMT_VF_PY))
#define VL_FMT_LF_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_MF_PY_INLINE)

#define VL_FMT_I "%*d"

#define VL_FMT_VI              VL_FORMAT("[", " ", "]", VL_FMT_I)
#define VL_FMT_VI_ROUND        VL_FORMAT("(", " ", ")", VL_FMT_I)
#define VL_FMT_VI_COL          VL_FORMAT("", "\n", "\n", "[ " VL_FMT_I " ]")
#define VL_FMT_VI_C            VL_FORMAT("{ ", ", ", " }", VL_FMT_I)
#define VL_FMT_VI_PY           VL_FORMAT("[", ", ", "]", VL_FMT_I)

#define VL_FMT_MI              VL_FORMAT("", "\n", "\n", VL_FMT_VI)
#define VL_FMT_MI_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_VI)
#define VL_FMT_MI_C            VL_FORMAT("{\n", ",\n", "\n}\n", "  " VL_FMT_VI_C)
#define VL_FMT_MI_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_VI_C)
#define VL_FMT_MI_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FMT_VI_PY)
#define VL_FMT_MI_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_VI_PY)

#define VL_FMT_LI              VL_FORMAT("", ".\n", "\n", VL_FMT_MI)
#define VL_FMT_LI_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_MI_INLINE)
#define VL_FMT_LI_C            VL_FORMAT("{\n", ",\n", "\n}\n", VL_FORMAT("  {\n", ",\n", "\n  }", "    " VL_FMT_VI_C))
#define VL_FMT_LI_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_MI_C_INLINE)
#define VL_FMT_LI_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FORMAT("[", ",\n  ", "]", VL_FMT_VI_PY))
#define VL_FMT_LI_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_MI_PY_INLINE)

#endif

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int n, const int* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, n, elts, w, p);
}

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int r, int c, const int* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, r, c, elts, w, p);
}

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int s, int r, int c, const int* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, s, r, c, elts, w, p);
}

inline int sn_adv(char*& str, size_t& size, int chars)
{
    size_t write = (size_t(chars) > size) ? size : chars;
    str += write;
    size -= write;
    return chars;
}

#if VL_CXX_11

template<class... Args> inline int snprintf_adv(char*& str, size_t& size, const char* fmt, Args... args)
{
    int chars = snprintf(str, size, fmt, args...);
    size_t write = (size_t(chars) > size) ? size : chars;
    str += write;
    size -= write;
    return chars;
}

template<class... Args> inline int snprintf_append(char* str, size_t size, const char* fmt, Args... args)
{
    while (*str && size)
    {
        str++;
        size--;
    }
    return snprintf(str, size, fmt, args...);
}

template<class S, class... Args> S& ssprintf(S& str, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    str.resize(size);
    int chars = snprintf(str.data(), size + 1, fmt, args...);
    str.resize(chars);
    if (chars >= size)
        snprintf(str.data(), chars + 1, fmt, args...);
    return str;
}

template<class S, class... Args> S& ssprintf_adv(S& str, size_t& cursor, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    VL_ASSERT(cursor <= size);

    str.resize(size);
    int chars = snprintf(str.data() + cursor, size + 1 - cursor, fmt, args...);
    str.resize(cursor + chars);
    if (cursor + chars >= size)
        snprintf(str.data() + cursor, chars + 1, fmt, args...);
    cursor += chars;
    return str;
}

template<class S, class... Args> S& ssprintf_append(S& str, const char* fmt, Args... args)
{
    size_t cursor = str.size();
    return ssprintf_adv(str, cursor, fmt, args...);
}

template<class S, class... Args> S& vl_ssprintf(S& str, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    str.resize(size);
    int chars = vl_snprintf(str.data(), size + 1, fmt, args...);
    str.resize(chars);
    if (chars >= size)
        vl_snprintf(str.data(), chars + 1, fmt, args...);
    return str;
}

template<class S, class... Args> inline S& vl_ssprintf_adv(S& str, size_t& cursor, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    VL_ASSERT(cursor <= size);

    str.resize(size);
    int chars = vl_snprintf(str.data() + cursor, size + 1 - cursor, fmt, args...);
    str.resize(cursor + chars);
    if (cursor + chars >= size)
        vl_snprintf(str.data() + cursor, chars + 1, fmt, args...);
    cursor += chars;
    return str;
}

template<class S, class... Args> S& vl_ssprintf_append(S& str, const char* fmt, Args... args)
{
    size_t cursor = str.size();
    return vl_ssprintf_adv(str, cursor, fmt, args...);
}

template<class... Args> int vl_printf(Args... args)
{
    return vl_fprintf(stdout, args...);
}

template<class... Args> int vl_print(Args... args)
{
    return vl_fprint(stdout, args...);
}

#endif

#endif

#ifndef VL_NO_STDIO

#ifndef VLI_PRINT_234_H
#define VLI_PRINT_234_H


// Print with default formatting
int vl_fprint(FILE* file, const Vec2i& v, int width = 1, int precision = 3);
int vl_fprint(FILE* file, const Vec3i& v, int width = 1, int precision = 3);
int vl_fprint(FILE* file, const Vec4i& v, int width = 1, int precision = 3);
int vl_fprint(FILE* file, const Mat2i& m, int width = 1, int precision = 3);
int vl_fprint(FILE* file, const Mat3i& m, int width = 1, int precision = 3);
int vl_fprint(FILE* file, const Mat4i& m, int width = 1, int precision = 3);

// Print according to specific format, see VL_FORMAT from PrintBase.hpp
int vl_fprintf(FILE* file, const char* format, const Vec2i& v, int width = 1, int precision = 3);
int vl_fprintf(FILE* file, const char* format, const Vec3i& v, int width = 1, int precision = 3);
int vl_fprintf(FILE* file, const char* format, const Vec4i& v, int width = 1, int precision = 3);
int vl_fprintf(FILE* file, const char* format, const Mat2i& m, int width = 1, int precision = 3);
int vl_fprintf(FILE* file, const char* format, const Mat3i& m, int width = 1, int precision = 3);
int vl_fprintf(FILE* file, const char* format, const Mat4i& m, int width = 1, int precision = 3);

// Print in format that can be compiled as C, 'name' is variable name.
int vl_fprint_as_c(FILE* file, const char* name, const Vec2i& v, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name, const Vec3i& v, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name, const Vec4i& v, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name, const Mat2i& m, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name, const Mat3i& m, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name, const Mat4i& m, int width = 1, int precision = 3);

// Write string according to specific format, see VL_FORMAT from PrintBase.hpp
int vl_snprintf(char* str, size_t size, const char* format, const Vec2i& v, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t size, const char* format, const Vec3i& v, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t size, const char* format, const Vec4i& v, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t size, const char* format, const Mat2i& m, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t size, const char* format, const Mat3i& m, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t size, const char* format, const Mat4i& m, int width = 1, int precision = 3);

// Variant that advances 'str' and reduces 'size' accordingly.
int vl_snprintf_adv(char*& str, size_t& size, const char* format, const Vec2i& v, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& size, const char* format, const Vec3i& v, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& size, const char* format, const Vec4i& v, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& size, const char* format, const Mat2i& m, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& size, const char* format, const Mat3i& m, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& size, const char* format, const Mat4i& m, int width = 1, int precision = 3);

#endif
#endif

#include <iostream>

#ifndef VL_NO_IOSTREAM

#ifndef VLI_STREAM_234_H
#define VLI_STREAM_234_H




// --- Stream Operators -------------------------------------------------------

class Vec2i;
class Vec3i;
class Vec4i;
class Mat2i;
class Mat3i;
class Mat4i;

std::ostream& operator << (std::ostream& s, const Vec2i& v);
std::istream& operator >> (std::istream& s, Vec2i& v);
std::ostream& operator << (std::ostream& s, const Vec3i& v);
std::istream& operator >> (std::istream& s, Vec3i& v);
std::ostream& operator << (std::ostream& s, const Vec4i& v);
std::istream& operator >> (std::istream& s, Vec4i& v);

std::ostream& operator << (std::ostream& s, const Mat2i& m);
std::istream& operator >> (std::istream& s, Mat2i& m);
std::ostream& operator << (std::ostream& s, const Mat3i& m);
std::istream& operator >> (std::istream& s, Mat3i& m);
std::ostream& operator << (std::ostream& s, const Mat4i& m);
std::istream& operator >> (std::istream& s, Mat4i& m);

#endif
#endif
#undef VL_NO_REAL
#undef VL_PRINT_INT

#endif
