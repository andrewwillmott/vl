/*
    File:       Math.h

    Function:   Various math definitions for VL

    Copyright:  Andrew Willmott
 */

#ifndef VL_MATH_H
#define VL_MATH_H

VL_NS_BEGIN

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

VL_NS_END


//
// Implementation
//

VL_NS_BEGIN

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

VL_NS_END

#endif
