//
// VL234i.cpp
//
// Andrew Willmott
//


#include "VL234i.hpp"










Vec4i& Vec4i::MakeUnit(int n, int k)
{
    if (n == 0)
    { x = k; y = vl_zero; z = vl_zero; w = vl_zero; }
    else if (n == 1)
    { x = vl_zero; y = k; z = vl_zero; w = vl_zero; }
    else if (n == 2)
    { x = vl_zero; y = vl_zero; z = k; w = vl_zero; }
    else if (n == 3)
    { x = vl_zero; y = vl_zero; z = vl_zero; w = k; }
    else
        VL_ERROR("(Vec4::MakeUnit) illegal unit vector");

    return *this;
}

bool Vec4i::operator == (const Vec4i& a) const
{
    return x == a.x && y == a.y && z == a.z && w == a.w;
}

bool Vec4i::operator != (const Vec4i& a) const
{
    return x != a.x || y != a.y || z != a.z || w != a.w;
}

bool Vec4i::operator < (const Vec4i& a) const
{
    return x < a.x && y < a.y && z < a.z && w < a.w;
}

bool Vec4i::operator >= (const Vec4i& a) const
{
    return x >= a.x && y >= a.y && z >= a.z && w >= a.w;
}

Vec4i cross(const Vec4i& a, const Vec4i& b, const Vec4i& c)
{
    Vec4i result;

    result.x =  dot(Vec3i(a.y, b.y, c.y), cross(Vec3i(a.z, b.z, c.z), Vec3i(a.w, b.w, c.w)));
    result.y = -dot(Vec3i(a.x, b.x, c.x), cross(Vec3i(a.z, b.z, c.z), Vec3i(a.w, b.w, c.w)));
    result.z =  dot(Vec3i(a.x, b.x, c.x), cross(Vec3i(a.y, b.y, c.y), Vec3i(a.w, b.w, c.w)));
    result.w = -dot(Vec3i(a.x, b.x, c.x), cross(Vec3i(a.y, b.y, c.y), Vec3i(a.z, b.z, c.z)));

    return result;
}

Vec3i proj(const Vec4i& v)
{
    Vec3i result;

    VL_ASSERT_MSG(v.w != 0, "(Vec4/proj) last elt. is zero");

    result.x = v.x / v.w;
    result.y = v.y / v.w;
    result.z = v.z / v.w;

    return result;
}



bool Mat2i::operator == (const Mat2i& m) const
{
    return x == m.x && y == m.y;
}

bool Mat2i::operator != (const Mat2i& m) const
{
    return x != m.x || y != m.y;
}


int det(const Mat2i& m)
{
    return m.x.x * m.y.y - m.x.y * m.y.x;
}

#ifndef VL_NO_REAL
Mat2i inv(const Mat2i& m)
{
    int  det;
    Mat2i result;

    result.x.x =  m.y.y; result.x.y = -m.x.y;
    result.y.x = -m.y.x; result.y.y =  m.x.x;

    det = m.x.x * result.x.x + m.x.y * result.y.x;
    VL_ASSERT_MSG(det != 0.0, "(Mat2::inv) matrix is non-singular");
    result /= det;

    return result;
}
#endif

Mat2i abs(const Mat2i& m)
{
    return Mat2i(abs(m.x), abs(m.y));
}

Mat2i oprod(const Vec2i& a, const Vec2i& b)
// returns outerproduct of a and b:  a * trans(b)
{
    Mat2i   result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}





Mat3i::Mat3i(const Mat2i& m, int s) :
    x(m.x,  vl_0),
    y(m.y,  vl_0),
    z(vl_0, s)
{
}

Mat3i& Mat3i::operator = (const Mat3i& m)
{
    x = m.x;
    y = m.y;
    z = m.z;

    return *this;
}

Mat3i& Mat3i::operator += (const Mat3i& m)
{
    x += m.x;
    y += m.y;
    z += m.z;

    return *this;
}

Mat3i& Mat3i::operator -= (const Mat3i& m)
{
    x -= m.x;
    y -= m.y;
    z -= m.z;

    return *this;
}

Mat3i& Mat3i::operator *= (const Mat3i& m)
{
    Vec3i t0, t1;

    t0 = x.x * m.x + x.y * m.y + x.z * m.z;
    t1 = y.x * m.x + y.y * m.y + y.z * m.z;
    z  = z.x * m.x + z.y * m.y + z.z * m.z;
    x  = t0;
    y  = t1;

    return *this;
}

Mat3i& Mat3i::operator *= (int s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

Mat3i& Mat3i::operator /= (int s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}


bool Mat3i::operator == (const Mat3i& m) const
{
    return x == m.x && y == m.y && z == m.z;
}

bool Mat3i::operator != (const Mat3i& m) const
{
    return x != m.x || y != m.y || z != m.z;
}


Mat3i Mat3i::operator + (const Mat3i& m) const
{
    Mat3i result;

    result.x = x + m.x;
    result.y = y + m.y;
    result.z = z + m.z;

    return result;
}

Mat3i Mat3i::operator - (const Mat3i& m) const
{
    Mat3i result;

    result.x = x - m.x;
    result.y = y - m.y;
    result.z = z - m.z;

    return result;
}

Mat3i Mat3i::operator - () const
{
    Mat3i result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

Mat3i Mat3i::operator * (const Mat3i& m) const
{
    Mat3i result;

    result.x.x = x.x * m.x.x + x.y * m.y.x + x.z * m.z.x;
    result.x.y = x.x * m.x.y + x.y * m.y.y + x.z * m.z.y;
    result.x.z = x.x * m.x.z + x.y * m.y.z + x.z * m.z.z;

    result.y.x = y.x * m.x.x + y.y * m.y.x + y.z * m.z.x;
    result.y.y = y.x * m.x.y + y.y * m.y.y + y.z * m.z.y;
    result.y.z = y.x * m.x.z + y.y * m.y.z + y.z * m.z.z;

    result.z.x = z.x * m.x.x + z.y * m.y.x + z.z * m.z.x;
    result.z.y = z.x * m.x.y + z.y * m.y.y + z.z * m.z.y;
    result.z.z = z.x * m.x.z + z.y * m.y.z + z.z * m.z.z;

    return result;
}

Mat3i Mat3i::operator * (int s) const
{
    Mat3i result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

Mat3i Mat3i::operator / (int s) const
{
    Mat3i result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;

    return result;
}

Mat3i trans(const Mat3i& m)
{
    Mat3i t;

    t.x.x = m.x.x; t.x.y = m.y.x; t.x.z = m.z.x;
    t.y.x = m.x.y; t.y.y = m.y.y; t.y.z = m.z.y;
    t.z.x = m.x.z; t.z.y = m.y.z; t.z.z = m.z.z;

    return t;
}

Mat3i adj(const Mat3i& m)
{
    Mat3i result;

    result.x = cross(m.y, m.z);
    result.y = cross(m.z, m.x);
    result.z = cross(m.x, m.y);

    return result;
}


int trace(const Mat3i& m)
{
    return m.x.x + m.y.y + m.z.z;
}

int det(const Mat3i& m)
{
    return dot(m.x, cross(m.y, m.z));
}

#ifndef VL_NO_REAL
Mat3i inv(const Mat3i& m)
{
    int  det;
    Mat3i adjoint;
    Mat3i result;

    adjoint = adj(m);
    det = dot(adjoint.x, m.x);

    VL_ASSERT_MSG(det != 0, "(Mat3::inv) matrix is non-singular");

    result = trans(adjoint);
    result /= det;

    return result;
}
#endif

Mat3i abs(const Mat3i& m)
{
    return Mat3i(abs(m.x), abs(m.y), abs(m.z));
}

Mat3i oprod(const Vec3i& a, const Vec3i& b)
// returns outerproduct of a and b:  a * trans(b)
{
    Mat3i result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}




Mat4i::Mat4i(int a, int b, int c, int d,
             int e, int f, int g, int h,
             int i, int j, int k, int l,
             int m, int n, int o, int p)
{
    x.x = a;  x.y = b;  x.z = c;  x.w = d;
    y.x = e;  y.y = f;  y.z = g;  y.w = h;
    z.x = i;  z.y = j;  z.z = k;  z.w = l;
    w.x = m;  w.y = n;  w.z = o;  w.w = p;
}

Mat4i::Mat4i(const Mat3i& m, int s)
{
    x.AsVec3() = m.x ; x.w = int(vl_0);
    y.AsVec3() = m.y ; y.w = int(vl_0);
    z.AsVec3() = m.z ; z.w = int(vl_0);
    w.AsVec3() = vl_0; w.w = s;
}

Mat4i& Mat4i::operator = (const Mat4i& m)
{
    x = m.x;
    y = m.y;
    z = m.z;
    w = m.w;

    return *this;
}

Mat4i& Mat4i::operator += (const Mat4i& m)
{
    x += m.x;
    y += m.y;
    z += m.z;
    w += m.w;

    return *this;
}

Mat4i& Mat4i::operator -= (const Mat4i& m)
{
    x -= m.x;
    y -= m.y;
    z -= m.z;
    w -= m.w;

    return *this;
}

Mat4i& Mat4i::operator *= (const Mat4i& m)
{
    Vec4i  t0, t1, t2;

    t0   = x.x * m.x + x.y * m.y + x.z * m.z + x.w * m.w;
    t1   = y.x * m.x + y.y * m.y + y.z * m.z + y.w * m.w;
    t2   = z.x * m.x + z.y * m.y + z.z * m.z + z.w * m.w;
    w    = w.x * m.x + w.y * m.y + w.z * m.z + w.w * m.w;
    x = t0;
    y = t1;
    z = t2;

    return *this;
}

Mat4i& Mat4i::operator *= (int s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

Mat4i& Mat4i::operator /= (int s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}


bool Mat4i::operator == (const Mat4i& m) const
{
    return x == m.x && y == m.y && z == m.z && w == m.w;
}

bool Mat4i::operator != (const Mat4i& m) const
{
    return x != m.x || y != m.y || z != m.z || w != m.w;
}


Mat4i Mat4i::operator + (const Mat4i& m) const
{
    Mat4i result;

    result.x = x + m.x;
    result.y = y + m.y;
    result.z = z + m.z;
    result.w = w + m.w;

    return result;
}

Mat4i Mat4i::operator - (const Mat4i& m) const
{
    Mat4i result;

    result.x = x - m.x;
    result.y = y - m.y;
    result.z = z - m.z;
    result.w = w - m.w;

    return result;
}

Mat4i Mat4i::operator - () const
{
    Mat4i result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

Mat4i Mat4i::operator * (const Mat4i& m) const
{
    Mat4i result;

    result.x.x = x.x * m.x.x + x.y * m.y.x + x.z * m.z.x + x.w * m.w.x;
    result.x.y = x.x * m.x.y + x.y * m.y.y + x.z * m.z.y + x.w * m.w.y;
    result.x.z = x.x * m.x.z + x.y * m.y.z + x.z * m.z.z + x.w * m.w.z;
    result.x.w = x.x * m.x.w + x.y * m.y.w + x.z * m.z.w + x.w * m.w.w;

    result.y.x = y.x * m.x.x + y.y * m.y.x + y.z * m.z.x + y.w * m.w.x;
    result.y.y = y.x * m.x.y + y.y * m.y.y + y.z * m.z.y + y.w * m.w.y;
    result.y.z = y.x * m.x.z + y.y * m.y.z + y.z * m.z.z + y.w * m.w.z;
    result.y.w = y.x * m.x.w + y.y * m.y.w + y.z * m.z.w + y.w * m.w.w;

    result.z.x = z.x * m.x.x + z.y * m.y.x + z.z * m.z.x + z.w * m.w.x;
    result.z.y = z.x * m.x.y + z.y * m.y.y + z.z * m.z.y + z.w * m.w.y;
    result.z.z = z.x * m.x.z + z.y * m.y.z + z.z * m.z.z + z.w * m.w.z;
    result.z.w = z.x * m.x.w + z.y * m.y.w + z.z * m.z.w + z.w * m.w.w;

    result.w.x = w.x * m.x.x + w.y * m.y.x + w.z * m.z.x + w.w * m.w.x;
    result.w.y = w.x * m.x.y + w.y * m.y.y + w.z * m.z.y + w.w * m.w.y;
    result.w.z = w.x * m.x.z + w.y * m.y.z + w.z * m.z.z + w.w * m.w.z;
    result.w.w = w.x * m.x.w + w.y * m.y.w + w.z * m.z.w + w.w * m.w.w;

    return result;
}

Mat4i Mat4i::operator * (int s) const
{
    Mat4i result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    result.w = w * s;

    return result;
}

Mat4i Mat4i::operator / (int s) const
{
    Mat4i result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;
    result.w = w / s;

    return result;
}

Vec4i operator * (const Mat4i& m, const Vec4i& v)         // m * v
{
    Vec4i result;

    result.x = v.x * m.x.x + v.y * m.x.y + v.z * m.x.z + v.w * m.x.w;
    result.y = v.x * m.y.x + v.y * m.y.y + v.z * m.y.z + v.w * m.y.w;
    result.z = v.x * m.z.x + v.y * m.z.y + v.z * m.z.z + v.w * m.z.w;
    result.w = v.x * m.w.x + v.y * m.w.y + v.z * m.w.z + v.w * m.w.w;

    return result;
}

Vec4i operator * (const Vec4i& v, const Mat4i& m)         // v * m
{
    Vec4i result;

    result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + v.w * m.w.x;
    result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + v.w * m.w.y;
    result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + v.w * m.w.z;
    result.w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + v.w * m.w.w;

    return result;
}

Vec4i& operator *= (Vec4i& v, const Mat4i& m)             // v *= m
{
    int  t0, t1, t2;

    t0   = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + v.w * m.w.x;
    t1   = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + v.w * m.w.y;
    t2   = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + v.w * m.w.z;
    v.w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + v.w * m.w.w;
    v.x = t0;
    v.y = t1;
    v.z = t2;

    return v;
}

Mat4i trans(const Mat4i& m)
{
    Mat4i t;

    t.x.x = m.x.x; t.x.y = m.y.x; t.x.z = m.z.x; t.x.w = m.w.x;
    t.y.x = m.x.y; t.y.y = m.y.y; t.y.z = m.z.y; t.y.w = m.w.y;
    t.z.x = m.x.z; t.z.y = m.y.z; t.z.z = m.z.z; t.z.w = m.w.z;
    t.w.x = m.x.w; t.w.y = m.y.w; t.w.z = m.z.w; t.w.w = m.w.w;

    return t;
}

Mat4i adj(const Mat4i& m)
{
    Mat4i   result;

    result.x =  cross(m.y, m.z, m.w);
    result.y = -cross(m.x, m.z, m.w);
    result.z =  cross(m.x, m.y, m.w);
    result.w = -cross(m.x, m.y, m.z);

    return result;
}

int trace(const Mat4i& m)
{
    return m.x.x + m.y.y + m.z.z + m.w.w;
}

int det(const Mat4i& m)
{
    return dot(m.x, cross(m.y, m.z, m.w));
}

#ifndef VL_NO_REAL
Mat4i inv(const Mat4i& m)
{
    int  det;
    Mat4i adjoint;
    Mat4i result;

    adjoint = adj(m);               // Find the adjoint
    det = dot(adjoint.x, m.x);

    VL_ASSERT_MSG(det != 0, "(Mat4::inv) matrix is non-singular");

    result = trans(adjoint);
    result /= det;

    return result;
}
#endif

Mat4i abs(const Mat4i& m)
{
    return Mat4i(abs(m.x), abs(m.y), abs(m.z), abs(m.w));
}

Mat4i oprod(const Vec4i& a, const Vec4i& b)
// returns outerproduct of a and b:  a * trans(b)
{
    Mat4i   result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

void Mat4i::MakeZero()
{
    int* data = &x.x;

    for (int i = 0; i < 16; i++)
        data[i] = vl_zero;
}

void Mat4i::MakeIdentity()
{
    Vec4i* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = vl_one;
            else
                row[i][j] = vl_zero;
}

void Mat4i::MakeDiag(Vec4i d)
{
    Vec4i* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = d[i];
            else
                row[i][j] = vl_zero;
}

void Mat4i::MakeDiag(int k)
{
    Vec4i* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = k;
            else
                row[i][j] = vl_zero;
}

void Mat4i::MakeBlock(int k)
{
    int* data = &x.x;

    for (int i = 0; i < 16; i++)
        data[i] = k;
}

Mat3i Mat4i::AsMat3() const
{
    return Mat3i(x.AsVec3(), y.AsVec3(), z.AsVec3());
}

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


#ifdef VL_PRINT_INT
int vl_fprint(FILE* file, const Vec2i& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 2, &v.x, width); }
int vl_fprint(FILE* file, const Vec3i& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 3, &v.x, width); }
int vl_fprint(FILE* file, const Vec4i& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 4, &v.x, width); }
int vl_fprint(FILE* file, const Mat2i& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 2, 2, &m.x.x, width); }
int vl_fprint(FILE* file, const Mat3i& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 3, 3, &m.x.x, width); }
int vl_fprint(FILE* file, const Mat4i& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 4, 4, &m.x.x, width); }
#else
int vl_fprint(FILE* file, const Vec2i& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 2, &v.x, width, prec); }
int vl_fprint(FILE* file, const Vec3i& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 3, &v.x, width, prec); }
int vl_fprint(FILE* file, const Vec4i& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 4, &v.x, width, prec); }
int vl_fprint(FILE* file, const Mat2i& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 2, 2, &m.x.x, width, prec); }
int vl_fprint(FILE* file, const Mat3i& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 3, 3, &m.x.x, width, prec); }
int vl_fprint(FILE* file, const Mat4i& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 4, 4, &m.x.x, width, prec); }
#endif

int vl_fprintf(FILE* file, const char* fmt, const Vec2i& v, int width, int prec) { return vl_fprintf(file, fmt, 2, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Vec3i& v, int width, int prec) { return vl_fprintf(file, fmt, 3, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Vec4i& v, int width, int prec) { return vl_fprintf(file, fmt, 4, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Mat2i& m, int width, int prec) { return vl_fprintf(file, fmt, 2, 2, &m.x.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Mat3i& m, int width, int prec) { return vl_fprintf(file, fmt, 3, 3, &m.x.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Mat4i& m, int width, int prec) { return vl_fprintf(file, fmt, 4, 4, &m.x.x, width, prec); }

int vl_fprint_as_c(FILE* file, const char* name, const Vec2i& v, int width, int prec) { return vl_fprint_as_c(file, name, 2, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Vec3i& v, int width, int prec) { return vl_fprint_as_c(file, name, 3, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Vec4i& v, int width, int prec) { return vl_fprint_as_c(file, name, 4, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Mat2i& m, int width, int prec) { return vl_fprint_as_c(file, name, 2, 2, &m.x.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Mat3i& m, int width, int prec) { return vl_fprint_as_c(file, name, 3, 3, &m.x.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Mat4i& m, int width, int prec) { return vl_fprint_as_c(file, name, 4, 4, &m.x.x, width, prec); }

int vl_snprintf(char* str, size_t size, const char* fmt, const Vec2i& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Vec3i& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Vec4i& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Mat2i& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Mat3i& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Mat4i& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }

int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Vec2i& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Vec3i& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Vec4i& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Mat2i& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Mat3i& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Mat4i& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }


#endif

#ifndef VL_FORMAT_IMPL
#define VL_FORMAT_IMPL




namespace
{
    inline int SpanFormat(int level, const char* format)
    {
        int c = 0;

        for (int i = 0; i < level; i++)
            while (format[c++] != '\3')
                ;
        return c - 1;
    }
}

int vl_fprintf(FILE* file, const char* format, int n, const int* v, int width, int precision)
{
    const char* s0 = format;        // vector start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // element format
    size_t      lf = SpanFormat(1, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vector end
    size_t      l2 = strlen(s2);

    int result = (int) fwrite(s0, l0, sizeof(char), file);

    for (int i = 0; i < n - 1; i++)
    {
    #ifdef VL_PRINT_INT
        result += fprintf(file, sf, width, v[i]);
    #else
        result += fprintf(file, sf, width, precision, double(v[i]));
    #endif
        result += (int) fwrite(s1, l1, sizeof(char), file);
    }

    if (n > 0)
    #ifdef VL_PRINT_INT
        result += fprintf(file, sf, width, v[n - 1]);
    #else
        result += fprintf(file, sf, width, precision, double(v[n - 1]));
    #endif

    result += (int) fwrite(s2, l2, sizeof(char), file);
    return result;
}

int vl_fprintf(FILE* file, const char* format, int nr, int nc, const int* m, int width, int precision)
{
    const char* s0 = format;        // matrix start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // vector format
    size_t      lf = SpanFormat(2, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // matrix end
    size_t      l2 = strlen(s2);

    int result = (int) fwrite(s0, l0, sizeof(char), file);

    for (int i = 0; i < nr - 1; i++)
    {
        result += vl_fprintf(file, sf, nc, m, width, precision);
        m += nc;

        result += (int) fwrite(s1, l1, sizeof(char), file);
    }

    if (nr > 0)
        result += vl_fprintf(file, sf, nc, m, width, precision);

    result += (int) fwrite(s2, l2, sizeof(char), file);
    return result;
}

int vl_fprintf(FILE* file, const char* format, int ns, int nr, int nc, const int* elts, int width, int precision)
{
    const char* s0 = format;        // vol start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // mat format
    size_t      lf = SpanFormat(3, sf);

    const char* s1 = sf + lf + 1;   // vol separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vol end
    size_t      l2 = strlen(s2);

    int result = (int) fwrite(s0, l0, sizeof(char), file);

    for (int i = 0; i < ns - 1; i++)
    {
        result += vl_fprintf(file, sf, nr, nc, elts, width, precision);
        elts += nr * nc;

        result += (int) fwrite(s1, l1, sizeof(char), file);
    }

    if (ns > 0)
        result += vl_fprintf(file, sf, nr, nc, elts, width, precision);

    result += (int) fwrite(s2, l2, sizeof(char), file);
    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int n, const int* v, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d] = ", name, n);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_VI_C ";\n", n, v, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_VF_C ";\n", n, v, width, precision);
#endif

    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int nr, int nc, const int* m, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d][%d] = \n", name, nr, nc);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_MI_C ";\n", nr, nc, m, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_MF_C ";\n", nr, nc, m, width, precision);
#endif
    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int ns, int nr, int nc, const int* elts, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d][%d] = \n", name, nr, nc);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_LI_C ";\n", nr, nc, elts, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_LF_C ";\n", nr, nc, elts, width, precision);
#endif
    return result;
}

namespace
{
    inline int vl_snprintf_adv(char*& str, size_t& size, const char* s, size_t n)
    {
        if (size == 0)
            return (int) n;

        size_t write = (n >= size) ? size - 1 : n;

        memcpy(str, s, write);
        str += write;
        size -= write;

        *str = 0;

        return (int) n;
    }
}

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int n, const int* v, int width, int precision)
{
    const char* s0 = format;        // vector start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // element format
    size_t      lf = SpanFormat(1, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vector end
    size_t      l2 = strlen(s2);

    int result = vl_snprintf_adv(str, size, s0, l0);

    for (int i = 0; i < n - 1; i++)
    {
    #ifdef VL_PRINT_INT
        result += sn_adv(str, size, snprintf(str, size, sf, width, v[i]));
    #else
        result += sn_adv(str, size, snprintf(str, size, sf, width, precision, double(v[i])));
    #endif

        result += vl_snprintf_adv(str, size, s1, l1);
    }

    if (n > 0)
    #ifdef VL_PRINT_INT
        result += sn_adv(str, size, snprintf(str, size, sf, width, v[n - 1]));
    #else
        result += sn_adv(str, size, snprintf(str, size, sf, width, precision, double(v[n - 1])));
    #endif

    result += vl_snprintf_adv(str, size, s2, l2);
    return result;
}

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int nr, int nc, const int* m, int width, int precision)
{
    const char* s0 = format;        // matrix start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // vector format
    size_t      lf = SpanFormat(2, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // matrix end
    size_t      l2 = strlen(s2);

    int result = vl_snprintf_adv(str, size, s0, l0);

    for (int i = 0; i < nr - 1; i++)
    {
        result += vl_snprintf_adv(str, size, sf, nc, m, width, precision);
        m += nc;

        result += vl_snprintf_adv(str, size, s1, l1);
    }

    if (nr > 0)
        result += vl_snprintf_adv(str, size, sf, nc, m, width, precision);

    result += vl_snprintf_adv(str, size, s2, l2);
    return result;
}

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int ns, int nr, int nc, const int* elts, int width, int precision)
{
    const char* s0 = format;        // vol start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // mat format
    size_t      lf = SpanFormat(3, sf);

    const char* s1 = sf + lf + 1;   // vol separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vol end
    size_t      l2 = strlen(s2);

    int result = vl_snprintf_adv(str, size, s0, l0);

    for (int i = 0; i < ns - 1; i++)
    {
        result += vl_snprintf_adv(str, size, sf, nr, nc, elts, width, precision);
        elts += nr * nc;

        result += vl_snprintf_adv(str, size, s1, l1);
    }

    if (ns > 0)
        result += vl_snprintf_adv(str, size, sf, nr, nc, elts, width, precision);

    result += vl_snprintf_adv(str, size, s2, l2);
    return result;
}

#endif

#include <ctype.h>
#include <iomanip>
#include <vector>

#ifndef VL_NO_IOSTREAM





using namespace std;

ostream& operator << (ostream& s, const Vec2i& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ']';
}

istream& operator >> (istream& s, Vec2i& v)
{
    Vec2i   result;
    char    c;

    // Expected format: [1 2]

    while (s >> c && isspace(c))
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1];

        if (!s)
        {
            cerr << "Error: Expected number while reading vector\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Error: Expected ']' while reading vector\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Error: Expected '[' while reading vector\n";
        return s;
    }

    v = result;
    return s;
}


ostream& operator << (ostream& s, const Vec3i& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ' ' << setw(w) << v[2] << ']';
}

istream& operator >> (istream& s, Vec3i& v)
{
    Vec3i   result;
    char    c;

    // Expected format: [1 2 3]

    while (s >> c && isspace(c))
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2];

        if (!s)
        {
            cerr << "Error: Expected number while reading vector\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Error: Expected ']' while reading vector\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Error: Expected '[' while reading vector\n";
        return s;
    }

    v = result;
    return s;
}


ostream& operator << (ostream& s, const Vec4i& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ' '
        << setw(w) << v[2] << ' ' << setw(w) << v[3] << ']';
}

istream& operator >> (istream& s, Vec4i& v)
{
    Vec4i   result;
    char    c;

    // Expected format: [1 2 3 4]

    while (s >> c && isspace(c))
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2] >> result[3];

        if (!s)
        {
            cerr << "Error: Expected number while reading vector\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Error: Expected ']' while reading vector\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Error: Expected '[' while reading vector\n";
        return s;
    }

    v = result;
    return s;
}


// Mat234

ostream& operator << (ostream& s, const Mat2i& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << ']' << endl;
}

istream& operator >> (istream& s, Mat2i& m)
{
    Mat2i   result;
    char    c;

    // Expected format: [[1 2] [3 4]]
    // Each vector is a row of the row matrix.

    while (s >> c && isspace(c))        // ignore leading white space
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1];

        if (!s)
        {
            cerr << "Expected number while reading matrix\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Expected ']' while reading matrix\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Expected '[' while reading matrix\n";
        return s;
    }

    m = result;
    return s;
}


ostream& operator << (ostream& s, const Mat3i& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << endl
             << ' ' << setw(w) << m[2] << ']' << endl;
}

istream& operator >> (istream& s, Mat3i& m)
{
    Mat3i   result;
    char    c;

    // Expected format: [[1 2 3] [4 5 6] [7 8 9]]
    // Each vector is a column of the matrix.

    while (s >> c && isspace(c))        // ignore leading white space
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2];

        if (!s)
        {
            cerr << "Expected number while reading matrix\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Expected ']' while reading matrix\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Expected '[' while reading matrix\n";
        return s;
    }

    m = result;
    return s;
}


ostream& operator << (ostream& s, const Mat4i& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << endl
             << ' ' << setw(w) << m[2] << endl
             << ' ' << setw(w) << m[3] << ']' << endl;
}

istream& operator >> (istream& s, Mat4i& m)
{
    Mat4i   result;
    char    c;

    // Expected format: [[1 2 3] [4 5 6] [7 8 9]]
    // Each vector is a column of the matrix.

    while (s >> c && isspace(c))        // ignore leading white space
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2] >> result[3];

        if (!s)
        {
            cerr << "Expected number while reading matrix\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Expected ']' while reading matrix\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Expected '[' while reading matrix\n";
        return s;
    }

    m = result;
    return s;
}

#endif
