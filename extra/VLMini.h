// Extremely minimal version of a subset of Vec2/3/4f, intended for copy and paste
// into small projects that don't need the full library.

#ifndef VL_MINI
#define VL_MINI

#include <math.h>

#if __has_extension(attribute_ext_vector_type)

// Definitions
typedef float Vec2f __attribute__((ext_vector_type(2)));
typedef float Vec3f __attribute__((ext_vector_type(3)));
typedef float Vec4f __attribute__((ext_vector_type(4)));

// Ops are all provided, see https://clang.llvm.org/docs/LanguageExtensions.html#vectors-and-extended-vectors

#else

// Definitions
#define IOP float operator[](int i) const { return (&x)[i]; } float& operator[](int i){ return (&x)[i]; }
struct Vec2f { float x; float y;                   IOP };
struct Vec3f { float x; float y; float z;          IOP };
struct Vec4f { float x; float y; float z; float w; IOP };
#undef IOP

// Ops
inline Vec2f  operator+ (Vec2f  v)          { return { +v.x, +v.y }; }
inline Vec2f  operator- (Vec2f  v)          { return { -v.x, -v.y }; }
inline Vec2f  operator+ (Vec2f  a, Vec2f b) { return { a.x + b.x, a.y + b.y }; }
inline Vec2f  operator- (Vec2f  a, Vec2f b) { return { a.x - b.x, a.y - b.y }; }
inline Vec2f  operator* (Vec2f  a, Vec2f b) { return { a.x * b.x, a.y * b.y }; }
inline Vec2f  operator/ (Vec2f  a, Vec2f b) { return { a.x / b.x, a.y / b.y }; }
inline Vec2f  operator* (float  s, Vec2f a) { return { s * a.x, s * a.y }; }
inline Vec2f  operator* (Vec2f  a, float s) { return { s * a.x, s * a.y }; }
inline Vec2f  operator/ (float  s, Vec2f a) { return { s / a.x, s / a.y }; }
inline Vec2f  operator/ (Vec2f  a, float s) { return { s / a.x, s / a.y }; }
inline Vec2f& operator+=(Vec2f& a, Vec2f b) { a.x += b.x; a.y += b.y; return a; }
inline Vec2f& operator-=(Vec2f& a, Vec2f b) { a.x -= b.x; a.y -= b.y; return a; }
inline Vec2f& operator*=(Vec2f& a, Vec2f b) { a.x *= b.x; a.y *= b.y; return a; }
inline Vec2f& operator/=(Vec2f& a, Vec2f b) { a.x /= b.x; a.y /= b.y; return a; }
inline Vec2f& operator*=(Vec2f& a, float s) { a.x *= s  ; a.y *= s  ; return a; }
inline Vec2f& operator/=(Vec2f& a, float s) { a.x /= s  ; a.y /= s  ; return a; }

inline Vec3f  operator+ (Vec3f  v)          { return { +v.x, +v.y, +v.z }; }
inline Vec3f  operator- (Vec3f  v)          { return { -v.x, -v.y, -v.z }; }
inline Vec3f  operator+ (Vec3f  a, Vec3f b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
inline Vec3f  operator- (Vec3f  a, Vec3f b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
inline Vec3f  operator* (Vec3f  a, Vec3f b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; }
inline Vec3f  operator/ (Vec3f  a, Vec3f b) { return { a.x / b.x, a.y / b.y, a.z / b.z }; }
inline Vec3f  operator* (float  s, Vec3f a) { return { s   * a.x, s   * a.y, s   * a.z }; }
inline Vec3f  operator* (Vec3f  a, float s) { return { s   * a.x, s   * a.y, s   * a.z }; }
inline Vec3f  operator/ (float  s, Vec3f a) { return { s   / a.x, s   / a.y, s   / a.z }; }
inline Vec3f  operator/ (Vec3f  a, float s) { return { a.x / s  , a.y / s  , a.z / s   }; }
inline Vec3f& operator+=(Vec3f& a, Vec3f b) { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
inline Vec3f& operator-=(Vec3f& a, Vec3f b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
inline Vec3f& operator*=(Vec3f& a, Vec3f b) { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
inline Vec3f& operator/=(Vec3f& a, Vec3f b) { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; }
inline Vec3f& operator*=(Vec3f& a, float s) { a.x *= s  ; a.y *= s  ; a.z *= s  ; return a; }
inline Vec3f& operator/=(Vec3f& a, float s) { a.x /= s  ; a.y /= s  ; a.z /= s  ; return a; }

inline Vec4f  operator+ (Vec4f  v)          { return { +v.x, +v.y, +v.z, +v.w }; }
inline Vec4f  operator- (Vec4f  v)          { return { -v.x, -v.y, -v.z, -v.w }; }
inline Vec4f  operator+ (Vec4f  a, Vec4f b) { return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w }; }
inline Vec4f  operator- (Vec4f  a, Vec4f b) { return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w }; }
inline Vec4f  operator* (Vec4f  a, Vec4f b) { return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w }; }
inline Vec4f  operator/ (Vec4f  a, Vec4f b) { return { a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w }; }
inline Vec4f  operator* (float  s, Vec4f a) { return { s   * a.x, s   * a.y, s   * a.z, s   * a.w }; }
inline Vec4f  operator* (Vec4f  a, float s) { return { s   * a.x, s   * a.y, s   * a.z, s   * a.w }; }
inline Vec4f  operator/ (float  s, Vec4f a) { return { s   / a.x, s   / a.y, s   / a.z, s   / a.w }; }
inline Vec4f  operator/ (Vec4f  a, float s) { return { s   / a.x, s   / a.y, s   / a.z, s   / a.w }; }
inline Vec4f& operator+=(Vec4f& a, Vec4f b) { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }
inline Vec4f& operator-=(Vec4f& a, Vec4f b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }
inline Vec4f& operator*=(Vec4f& a, Vec4f b) { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; }
inline Vec4f& operator/=(Vec4f& a, Vec4f b) { a.x /= b.x; a.y /= b.y; a.z /= b.z; a.w /= b.w; return a; }
inline Vec4f& operator*=(Vec4f& a, float s) { a.x *= s  ; a.y *= s  ; a.z *= s  ; a.w *= s  ; return a; }
inline Vec4f& operator/=(Vec4f& a, float s) { a.x /= s  ; a.y /= s  ; a.z /= s  ; a.w /= s  ; return a; }
#endif

// Utils
inline float Max(float a, float b)       { return b < a ? a : b; }
inline float Min(float a, float b)       { return a < b ? a : b; }
inline float sqr(float x)                { return x * x; }

inline float lerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }

inline float dot      (Vec2f a, Vec2f b) { return a.x * b.x + a.y * b.y; }
inline float len      (Vec2f v)          { return sqrtf(v.x * v.x + v.y * v.y); }
inline float sqrlen   (Vec2f v)          { return       v.x * v.x + v.y * v.y; }
inline Vec2f norm     (Vec2f v)          { return (1.0f / len(v)) * v; }
inline Vec2f norm_safe(Vec2f v)          { return (1.0f / (len(v) + 1e-8f)) * v; }
inline Vec2f abs      (Vec2f v)          { return { fabsf(v.x), fabsf(v.y) }; }
inline Vec2f cross    (Vec2f v)          { return { -v.y, v.x }; }
inline Vec2f pow      (Vec2f v, float p) { return { powf(v.x, p), powf(v.y, p) }; }

inline Vec2f lerp(Vec2f a, Vec2f b, float t) { return (1.0f - t) * a + t * b; }

inline float dot      (Vec3f a, Vec3f b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float len      (Vec3f v)          { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
inline float sqrlen   (Vec3f v)          { return       v.x * v.x + v.y * v.y + v.z * v.z; }
inline Vec3f norm     (Vec3f v)          { return (1.0f / len(v)) * v; }
inline Vec3f norm_safe(Vec3f v)          { return (1.0f / (len(v) + 1e-8f)) * v; }
inline Vec3f abs      (Vec3f v)          { return { fabsf(v.x), fabsf(v.y), fabsf(v.z) }; }
inline Vec3f cross    (Vec3f a, Vec3f b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
inline Vec3f cross_z  (Vec3f v)          { return { v.y, -v.x, 0.0f }; }
inline Vec3f pow      (Vec3f v, float p) { return { powf(v.x, p), powf(v.y, p), powf(v.z, p) }; }

inline Vec3f lerp(Vec3f a, Vec3f b, float t) { return (1.0f - t) * a + t * b; }

inline float dot      (Vec4f a, Vec4f b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
inline float len      (Vec4f v)          { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
inline float sqrlen   (Vec4f v)          { return       v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w; }
inline Vec4f norm     (Vec4f v)          { return (1.0f / len(v)) * v; }
inline Vec4f norm_safe(Vec4f v)          { return (1.0f / (len(v) + 1e-8f)) * v; }
inline Vec4f abs      (Vec4f v)          { return { fabsf(v.x), fabsf(v.y), fabsf(v.z), fabsf(v.w) }; }
inline Vec4f pow      (Vec4f v, float p) { return { powf(v.x, p), powf(v.y, p), powf(v.z, p), powf(v.w, p) }; }

inline Vec4f lerp(Vec4f a, Vec4f b, float t) { return (1.0f - t) * a + t * b; }

// Matrices
#define IOP(N) Vec##N##f operator[](int i) const { return (&x)[i]; } Vec##N##f& operator[](int i){ return (&x)[i]; }
struct Mat2f { Vec2f x; Vec2f y;                   IOP(2) };
struct Mat3f { Vec3f x; Vec3f y; Vec3f z;          IOP(3) };
struct Mat4f { Vec4f x; Vec4f y; Vec4f z; Vec4f w; IOP(4) };
#undef IOP

inline Vec2f operator*(const Mat2f& m, const Vec2f& v) { return Vec2f { dot(m.x, v), dot(m.y, v)                           }; }
inline Vec3f operator*(const Mat3f& m, const Vec3f& v) { return Vec3f { dot(m.x, v), dot(m.y, v), dot(m.z, v)              }; }
inline Vec4f operator*(const Mat4f& m, const Vec4f& v) { return Vec4f { dot(m.x, v), dot(m.y, v), dot(m.z, v), dot(m.w, v) }; }

inline Vec2f operator*(const Vec2f& v, const Mat2f& m) { return v.x * m.x + v.y * m.y                        ; }
inline Vec3f operator*(const Vec3f& v, const Mat3f& m) { return v.x * m.x + v.y * m.y + v.z * m.z            ; }
inline Vec4f operator*(const Vec4f& v, const Mat4f& m) { return v.x * m.x + v.y * m.y + v.z * m.z + v.w * m.w; }

inline Mat2f operator*(const Mat2f& m, const Mat2f& n) { return { m.x * n, m.y * n                   }; }
inline Mat3f operator*(const Mat3f& m, const Mat3f& n) { return { m.x * n, m.y * n, m.z * n          }; }
inline Mat4f operator*(const Mat4f& m, const Mat4f& n) { return { m.x * n, m.y * n, m.z * n, m.w * n }; }

inline Vec2f& operator*=(Vec2f& v, const Mat2f& m) { v = v * m; return v; }
inline Vec3f& operator*=(Vec3f& v, const Mat3f& m) { v = v * m; return v; }
inline Vec4f& operator*=(Vec4f& v, const Mat4f& m) { v = v * m; return v; }
inline Mat2f& operator*=(Mat2f& m, const Mat2f& n) { m = m * n; return m; }
inline Mat3f& operator*=(Mat3f& m, const Mat3f& n) { m = m * n; return m; }
inline Mat4f& operator*=(Mat4f& m, const Mat4f& n) { m = m * n; return m; }

inline Mat2f trans(const Mat2f& m) { return { { m.x.x, m.y.x }, { m.x.y, m.y.y } }; }
inline Mat3f trans(const Mat3f& m) { return { { m.x.x, m.y.x, m.z.x }, { m.x.y, m.y.y, m.z.y }, { m.x.z, m.y.z, m.z.z } }; }
inline Mat4f trans(const Mat4f& m) { return { { m.x.x, m.y.x, m.z.x, m.w.x }, { m.x.y, m.y.y, m.z.y, m.w.y }, { m.x.z, m.y.z, m.z.z, m.w.z }, { m.x.w, m.y.w, m.z.w, m.w.w } }; }

#endif
