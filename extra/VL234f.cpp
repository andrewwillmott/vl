//
// VL234f.cpp
//
// Andrew Willmott
//


#include "VL234f.hpp"

#include <ctype.h>
#include <iomanip>
#include <vector>









Vec4f& Vec4f::MakeUnit(int n, float k)
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

bool Vec4f::operator == (const Vec4f& a) const
{
    return x == a.x && y == a.y && z == a.z && w == a.w;
}

bool Vec4f::operator != (const Vec4f& a) const
{
    return x != a.x || y != a.y || z != a.z || w != a.w;
}

bool Vec4f::operator < (const Vec4f& a) const
{
    return x < a.x && y < a.y && z < a.z && w < a.w;
}

bool Vec4f::operator >= (const Vec4f& a) const
{
    return x >= a.x && y >= a.y && z >= a.z && w >= a.w;
}

Vec4f cross(const Vec4f& a, const Vec4f& b, const Vec4f& c)
{
    Vec4f result;

    result.x =  dot(Vec3f(a.y, b.y, c.y), cross(Vec3f(a.z, b.z, c.z), Vec3f(a.w, b.w, c.w)));
    result.y = -dot(Vec3f(a.x, b.x, c.x), cross(Vec3f(a.z, b.z, c.z), Vec3f(a.w, b.w, c.w)));
    result.z =  dot(Vec3f(a.x, b.x, c.x), cross(Vec3f(a.y, b.y, c.y), Vec3f(a.w, b.w, c.w)));
    result.w = -dot(Vec3f(a.x, b.x, c.x), cross(Vec3f(a.y, b.y, c.y), Vec3f(a.z, b.z, c.z)));

    return result;
}

Vec3f proj(const Vec4f& v)
{
    Vec3f result;

    VL_ASSERT_MSG(v.w != 0, "(Vec4/proj) last elt. is zero");

    result.x = v.x / v.w;
    result.y = v.y / v.w;
    result.z = v.z / v.w;

    return result;
}



bool Mat2f::operator == (const Mat2f& m) const
{
    return x == m.x && y == m.y;
}

bool Mat2f::operator != (const Mat2f& m) const
{
    return x != m.x || y != m.y;
}


float det(const Mat2f& m)
{
    return m.x.x * m.y.y - m.x.y * m.y.x;
}

Mat2f inv(const Mat2f& m)
{
    float  det;
    Mat2f result;

    result.x.x =  m.y.y; result.x.y = -m.x.y;
    result.y.x = -m.y.x; result.y.y =  m.x.x;

    det = m.x.x * result.x.x + m.x.y * result.y.x;
    VL_ASSERT_MSG(det != 0.0, "(Mat2::inv) matrix is non-singular");
    result /= det;

    return result;
}

Mat2f abs(const Mat2f& m)
{
    return Mat2f(abs(m.x), abs(m.y));
}

Mat2f oprod(const Vec2f& a, const Vec2f& b)
// returns outerproduct of a and b:  a * trans(b)
{
    Mat2f   result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}





Mat3f::Mat3f(const Mat2f& m, float s) :
    x(m.x,  vl_0),
    y(m.y,  vl_0),
    z(vl_0, s)
{
}

Mat3f& Mat3f::operator = (const Mat3f& m)
{
    x = m.x;
    y = m.y;
    z = m.z;

    return *this;
}

Mat3f& Mat3f::operator += (const Mat3f& m)
{
    x += m.x;
    y += m.y;
    z += m.z;

    return *this;
}

Mat3f& Mat3f::operator -= (const Mat3f& m)
{
    x -= m.x;
    y -= m.y;
    z -= m.z;

    return *this;
}

Mat3f& Mat3f::operator *= (const Mat3f& m)
{
    Vec3f t0, t1;

    t0 = x.x * m.x + x.y * m.y + x.z * m.z;
    t1 = y.x * m.x + y.y * m.y + y.z * m.z;
    z  = z.x * m.x + z.y * m.y + z.z * m.z;
    x  = t0;
    y  = t1;

    return *this;
}

Mat3f& Mat3f::operator *= (float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

Mat3f& Mat3f::operator /= (float s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}


bool Mat3f::operator == (const Mat3f& m) const
{
    return x == m.x && y == m.y && z == m.z;
}

bool Mat3f::operator != (const Mat3f& m) const
{
    return x != m.x || y != m.y || z != m.z;
}


Mat3f Mat3f::operator + (const Mat3f& m) const
{
    Mat3f result;

    result.x = x + m.x;
    result.y = y + m.y;
    result.z = z + m.z;

    return result;
}

Mat3f Mat3f::operator - (const Mat3f& m) const
{
    Mat3f result;

    result.x = x - m.x;
    result.y = y - m.y;
    result.z = z - m.z;

    return result;
}

Mat3f Mat3f::operator - () const
{
    Mat3f result;

    result.x = -x;
    result.y = -y;
    result.z = -z;

    return result;
}

Mat3f Mat3f::operator * (const Mat3f& m) const
{
    Mat3f result;

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

Mat3f Mat3f::operator * (float s) const
{
    Mat3f result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

Mat3f Mat3f::operator / (float s) const
{
    Mat3f result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;

    return result;
}

Mat3f trans(const Mat3f& m)
{
    Mat3f t;

    t.x.x = m.x.x; t.x.y = m.y.x; t.x.z = m.z.x;
    t.y.x = m.x.y; t.y.y = m.y.y; t.y.z = m.z.y;
    t.z.x = m.x.z; t.z.y = m.y.z; t.z.z = m.z.z;

    return t;
}

Mat3f adj(const Mat3f& m)
{
    Mat3f result;

    result.x = cross(m.y, m.z);
    result.y = cross(m.z, m.x);
    result.z = cross(m.x, m.y);

    return result;
}


float trace(const Mat3f& m)
{
    return m.x.x + m.y.y + m.z.z;
}

float det(const Mat3f& m)
{
    return dot(m.x, cross(m.y, m.z));
}

Mat3f inv(const Mat3f& m)
{
    float  det;
    Mat3f adjoint;
    Mat3f result;

    adjoint = adj(m);
    det = dot(adjoint.x, m.x);

    VL_ASSERT_MSG(det != 0, "(Mat3::inv) matrix is non-singular");

    result = trans(adjoint);
    result /= det;

    return result;
}

Mat3f abs(const Mat3f& m)
{
    return Mat3f(abs(m.x), abs(m.y), abs(m.z));
}

Mat3f oprod(const Vec3f& a, const Vec3f& b)
// returns outerproduct of a and b:  a * trans(b)
{
    Mat3f result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}




Mat4f::Mat4f(float a, float b, float c, float d,
             float e, float f, float g, float h,
             float i, float j, float k, float l,
             float m, float n, float o, float p)
{
    x.x = a;  x.y = b;  x.z = c;  x.w = d;
    y.x = e;  y.y = f;  y.z = g;  y.w = h;
    z.x = i;  z.y = j;  z.z = k;  z.w = l;
    w.x = m;  w.y = n;  w.z = o;  w.w = p;
}

Mat4f::Mat4f(const Mat3f& m, float s)
{
    x.AsVec3() = m.x ; x.w = float(vl_0);
    y.AsVec3() = m.y ; y.w = float(vl_0);
    z.AsVec3() = m.z ; z.w = float(vl_0);
    w.AsVec3() = vl_0; w.w = s;
}

Mat4f& Mat4f::operator = (const Mat4f& m)
{
    x = m.x;
    y = m.y;
    z = m.z;
    w = m.w;

    return *this;
}

Mat4f& Mat4f::operator += (const Mat4f& m)
{
    x += m.x;
    y += m.y;
    z += m.z;
    w += m.w;

    return *this;
}

Mat4f& Mat4f::operator -= (const Mat4f& m)
{
    x -= m.x;
    y -= m.y;
    z -= m.z;
    w -= m.w;

    return *this;
}

Mat4f& Mat4f::operator *= (const Mat4f& m)
{
    Vec4f  t0, t1, t2;

    t0   = x.x * m.x + x.y * m.y + x.z * m.z + x.w * m.w;
    t1   = y.x * m.x + y.y * m.y + y.z * m.z + y.w * m.w;
    t2   = z.x * m.x + z.y * m.y + z.z * m.z + z.w * m.w;
    w    = w.x * m.x + w.y * m.y + w.z * m.z + w.w * m.w;
    x = t0;
    y = t1;
    z = t2;

    return *this;
}

Mat4f& Mat4f::operator *= (float s)
{
    x *= s;
    y *= s;
    z *= s;
    w *= s;

    return *this;
}

Mat4f& Mat4f::operator /= (float s)
{
    x /= s;
    y /= s;
    z /= s;
    w /= s;

    return *this;
}


bool Mat4f::operator == (const Mat4f& m) const
{
    return x == m.x && y == m.y && z == m.z && w == m.w;
}

bool Mat4f::operator != (const Mat4f& m) const
{
    return x != m.x || y != m.y || z != m.z || w != m.w;
}


Mat4f Mat4f::operator + (const Mat4f& m) const
{
    Mat4f result;

    result.x = x + m.x;
    result.y = y + m.y;
    result.z = z + m.z;
    result.w = w + m.w;

    return result;
}

Mat4f Mat4f::operator - (const Mat4f& m) const
{
    Mat4f result;

    result.x = x - m.x;
    result.y = y - m.y;
    result.z = z - m.z;
    result.w = w - m.w;

    return result;
}

Mat4f Mat4f::operator - () const
{
    Mat4f result;

    result.x = -x;
    result.y = -y;
    result.z = -z;
    result.w = -w;

    return result;
}

Mat4f Mat4f::operator * (const Mat4f& m) const
{
    Mat4f result;

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

Mat4f Mat4f::operator * (float s) const
{
    Mat4f result;

    result.x = x * s;
    result.y = y * s;
    result.z = z * s;
    result.w = w * s;

    return result;
}

Mat4f Mat4f::operator / (float s) const
{
    Mat4f result;

    result.x = x / s;
    result.y = y / s;
    result.z = z / s;
    result.w = w / s;

    return result;
}

Vec4f operator * (const Mat4f& m, const Vec4f& v)         // m * v
{
    Vec4f result;

    result.x = v.x * m.x.x + v.y * m.x.y + v.z * m.x.z + v.w * m.x.w;
    result.y = v.x * m.y.x + v.y * m.y.y + v.z * m.y.z + v.w * m.y.w;
    result.z = v.x * m.z.x + v.y * m.z.y + v.z * m.z.z + v.w * m.z.w;
    result.w = v.x * m.w.x + v.y * m.w.y + v.z * m.w.z + v.w * m.w.w;

    return result;
}

Vec4f operator * (const Vec4f& v, const Mat4f& m)         // v * m
{
    Vec4f result;

    result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + v.w * m.w.x;
    result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + v.w * m.w.y;
    result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + v.w * m.w.z;
    result.w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + v.w * m.w.w;

    return result;
}

Vec4f& operator *= (Vec4f& v, const Mat4f& m)             // v *= m
{
    float  t0, t1, t2;

    t0   = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + v.w * m.w.x;
    t1   = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + v.w * m.w.y;
    t2   = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + v.w * m.w.z;
    v.w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + v.w * m.w.w;
    v.x = t0;
    v.y = t1;
    v.z = t2;

    return v;
}

Mat4f trans(const Mat4f& m)
{
    Mat4f t;

    t.x.x = m.x.x; t.x.y = m.y.x; t.x.z = m.z.x; t.x.w = m.w.x;
    t.y.x = m.x.y; t.y.y = m.y.y; t.y.z = m.z.y; t.y.w = m.w.y;
    t.z.x = m.x.z; t.z.y = m.y.z; t.z.z = m.z.z; t.z.w = m.w.z;
    t.w.x = m.x.w; t.w.y = m.y.w; t.w.z = m.z.w; t.w.w = m.w.w;

    return t;
}

Mat4f adj(const Mat4f& m)
{
    Mat4f   result;

    result.x =  cross(m.y, m.z, m.w);
    result.y = -cross(m.x, m.z, m.w);
    result.z =  cross(m.x, m.y, m.w);
    result.w = -cross(m.x, m.y, m.z);

    return result;
}

float trace(const Mat4f& m)
{
    return m.x.x + m.y.y + m.z.z + m.w.w;
}

float det(const Mat4f& m)
{
    return dot(m.x, cross(m.y, m.z, m.w));
}

Mat4f inv(const Mat4f& m)
{
    float  det;
    Mat4f adjoint;
    Mat4f result;

    adjoint = adj(m);               // Find the adjoint
    det = dot(adjoint.x, m.x);

    VL_ASSERT_MSG(det != 0, "(Mat4::inv) matrix is non-singular");

    result = trans(adjoint);
    result /= det;

    return result;
}

Mat4f abs(const Mat4f& m)
{
    return Mat4f(abs(m.x), abs(m.y), abs(m.z), abs(m.w));
}

Mat4f oprod(const Vec4f& a, const Vec4f& b)
// returns outerproduct of a and b:  a * trans(b)
{
    Mat4f   result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

void Mat4f::MakeZero()
{
    float* data = &x.x;

    for (int i = 0; i < 16; i++)
        data[i] = vl_zero;
}

void Mat4f::MakeIdentity()
{
    Vec4f* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = vl_one;
            else
                row[i][j] = vl_zero;
}

void Mat4f::MakeDiag(Vec4f d)
{
    Vec4f* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = d[i];
            else
                row[i][j] = vl_zero;
}

void Mat4f::MakeDiag(float k)
{
    Vec4f* row = &x;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i == j)
                row[i][j] = k;
            else
                row[i][j] = vl_zero;
}

void Mat4f::MakeBlock(float k)
{
    float* data = &x.x;

    for (int i = 0; i < 16; i++)
        data[i] = k;
}

Mat3f Mat4f::AsMat3() const
{
    return Mat3f(x.AsVec3(), y.AsVec3(), z.AsVec3());
}




Quatf MakeQuat(const Vec3f& v1, const Vec3f& v2)
{
    Vec3f half = norm_safe(v1 + v2);

    float w = dot(half, v1);

    if (w != float(0))
        return Quatf(cross(v1, half), w);

    Vec3f altDir(v2.z, v2.x, v2.y);

    return Quatf(norm(cross(v1, altDir)), w);
}

Quatf MakeQuat(const Vec3f& axis, float theta)
{
    theta *= float(0.5);

    float s, c;
    vl_sincos(theta, &s, &c);

    return Quatf(s * axis.x, s * axis.y, s * axis.z, c);
}

#ifdef REFERENCE
Quatf QuatMult(const Quatf& a, const Quatf& b)
{
    Quatf  result;
    const Vec3f& va = a.AsVec3();
    const Vec3f& vb = b.AsVec3();

    result = Quatf(a.w * vb + b.w * va + cross(vb, va), a.w * b.w - dot(va, vb));

    return result;
}
#endif

Quatf MakeQuatFromCRot(const Mat3f& R)
{
#ifdef REFERENCE
    // Classic algorithm
    Quatf q;
    float s;

    if (R.z.z <= float(0))   // x^2 + y^2 >= z^2 + w^2
    {
        float yx = R.y.y - R.x.x;
        float zz = float(1) - R.z.z;

        if (yx <= float(0))   // x^2 >= y^2
        {
            s = zz - yx;
            q = Quatf(s, R.x.y + R.y.x, R.x.z + R.z.x, R.z.y - R.y.z);
        }
        else     // y^2 >= x^2
        {
            s = zz + yx;
            q = Quatf(R.x.y + R.y.x, s, R.y.z + R.z.y, R.x.z - R.z.x);
        }
    }
    else     // z^2 + w^2 >= x^2 + y^2
    {
        float yx = R.y.y + R.x.x;
        float zz = float(1) + R.z.z;

        if (yx <= float(0))   // z^2 >= w^2
        {
            s = zz - yx;
            q = Quatf(R.x.z + R.z.x, R.y.z + R.z.y, s, R.y.x - R.x.y);
        }
        else     // w^2 >= z^2
        {
            s = zz + yx;
            q = Quatf(R.z.y - R.y.z, R.x.z - R.z.x, R.y.x - R.x.y, s);
        }
    }

    q *= float(0.5) / sqrt(s);
    VL_ASSERT(!HasNAN(q));

    return q;
#else
    // Branchless version
    int qc = R.z.z < float(0) ? (R.x.x > R.y.y ? 0 : 1) : (R.x.x < -R.y.y ? 2 : 3);

    float qs1 = ( qc      & 2) > 0 ? float(-1) : float(1);
    float qs2 = ( qc      & 1) > 0 ? float(-1) : float(1);
    float qs3 = ((qc - 1) & 2) > 0 ? float(-1) : float(1);

    float qt = float(1) - qs3 * R.x.x - qs2 * R.y.y - qs1 * R.z.z;
    float qs = float(0.5) / sqrt(qt);

    Quatf result;
    result[qc ^ 0] = qs * qt;
    result[qc ^ 1] = qs * (R.y.x + qs1 * R.x.y);
    result[qc ^ 2] = qs * (R.x.z + qs2 * R.z.x);
    result[qc ^ 3] = qs * (R.z.y + qs3 * R.y.z);

    return result;
#endif
}

Quatf MakeQuatFromRRot(const Mat3f& R)
{
#ifdef REFERENCE
    // Classic algorithm
    Quatf q;
    float s;

    if (R.z.z <= float(0))   // x^2 + y^2 >= z^2 + w^2
    {
        float yx = R.y.y - R.x.x;
        float zz = float(1) - R.z.z;

        if (yx <= float(0))   // x^2 >= y^2
        {
            s = zz - yx;
            q = Quatf(s, R.x.y + R.y.x, R.x.z + R.z.x, R.y.z - R.z.y);
        }
        else     // y^2 >= x^2
        {
            s = zz + yx;
            q = Quatf(R.x.y + R.y.x, q.y = s, q.z = R.y.z + R.z.y, q.w = R.z.x - R.x.z);
        }
    }
    else     // z^2 + w^2 >= x^2 + y^2
    {
        float yx = R.y.y + R.x.x;
        float zz = float(1) + R.z.z;

        if (yx <= float(0))   // z^2 >= w^2
        {
            s = zz - yx;
            q = Quatf(R.x.z + R.z.x, q.y = R.y.z + R.z.y, q.z = s, q.w = R.x.y - R.y.x);
        }
        else     // w^2 >= z^2
        {
            s = zz + yx;
            q = Quatf(R.y.z - R.z.y, R.z.x - R.x.z, R.x.y - R.y.x, s);
        }
    }

    q *= float(0.5) / sqrt(s);
    VL_ASSERT(!HasNAN(q));

    return q;
#else
    // Branchless version
    int qc = R.z.z < float(0) ? (R.x.x > R.y.y ? 0 : 1) : (R.x.x < -R.y.y ? 2 : 3);

    float qs1 = ( qc      & 2) > 0 ? float(-1) : float(1);
    float qs2 = ( qc      & 1) > 0 ? float(-1) : float(1);
    float qs3 = ((qc - 1) & 2) > 0 ? float(-1) : float(1);

    float qt = float(1) - qs3 * R.x.x - qs2 * R.y.y - qs1 * R.z.z;
    float qs = float(0.5) / sqrt(qt);

    Quatf result;
    result[qc ^ 0] = qs * qt;
    result[qc ^ 1] = qs * (R.x.y + qs1 * R.y.x);
    result[qc ^ 2] = qs * (R.z.x + qs2 * R.x.z);
    result[qc ^ 3] = qs * (R.y.z + qs3 * R.z.y);

    return result;
#endif
}

Mat3f CRotFromQuat(const Quatf& q)
{
    float i2 =  2 * q.x,
         j2 =  2 * q.y,
         k2 =  2 * q.z,
         ij = i2 * q.y,
         ik = i2 * q.z,
         jk = j2 * q.z,
         ri = i2 * q.w,
         rj = j2 * q.w,
         rk = k2 * q.w;

    i2 *= q.x;
    j2 *= q.y;
    k2 *= q.z;

    Mat3f m;

    m.x.x = 1 - j2 - k2;  m.x.y = ij - rk    ;  m.x.z = ik + rj;
    m.y.x = ij + rk    ;  m.y.y = 1 - i2 - k2;  m.y.z = jk - ri;
    m.z.x = ik - rj    ;  m.z.y = jk + ri    ;  m.z.z = 1 - i2 - j2;

    return m;
}

Mat3f RRotFromQuat(const Quatf& q)
{
    float i2 =  2 * q.x,
         j2 =  2 * q.y,
         k2 =  2 * q.z,
         ij = i2 * q.y,
         ik = i2 * q.z,
         jk = j2 * q.z,
         ri = i2 * q.w,
         rj = j2 * q.w,
         rk = k2 * q.w;

    i2 *= q.x;
    j2 *= q.y;
    k2 *= q.z;

    Mat3f m;

    m.x.x = 1 - j2 - k2;  m.x.y = ij + rk    ;  m.x.z = ik - rj;
    m.y.x = ij - rk    ;  m.y.y = 1 - i2 - k2;  m.y.z = jk + ri;
    m.z.x = ik + rj    ;  m.z.y = jk - ri    ;  m.z.z = 1 - i2 - j2;

    return m;
}

Vec4f AxisAngleFromQuat(const Quatf& q)
{
    Vec4f qn = norm(q);

    float ct = qn.w;
    float st = sqrt(float(1) - sqr(ct));

    qn.AsVec3() /= st + float(1e-6);
    qn.w = float(2) * atan2(st, ct);  // rather than acos(ct), more stable, no nans on ct = 1 + eps

    return qn;
}

Quatf SLerp(const Quatf& q1, const Quatf& q2, float s)
{
    VL_ASSERT(vl_is_unit(q1));
    VL_ASSERT(vl_is_unit(q2));
    VL_ASSERT(s >= float(0) && s <= float(1));

    // Calculate angle between them.
    float cosHalfTheta = dot(q1, q2);

    // If q1 = q2 or q1 = -q2 then theta = 0 and we can return q1
    if (abs(cosHalfTheta) >= float(0.99999))
        return q1;

    float sinHalfTheta = sqrt(float(1) - cosHalfTheta * cosHalfTheta);

    // If theta = pi then result is not fully defined, we could rotate around
    // any axis normal to q1 or q2.
    if (sinHalfTheta < float(1e-5))
        return float(0.5) * (q1 + q2);

    float halfTheta = std::atan2(sinHalfTheta, cosHalfTheta);

    float t = float(1) - s;
    float ratio1 = std::sin(t * halfTheta) / sinHalfTheta;
    float ratio2 = std::sin(s * halfTheta) / sinHalfTheta;

    return ratio1 * q1 + ratio2 * q2;
}

void DecomposeTwist
(
    const Quatf& q,
    const Vec3f& axis,
    Quatf*       noTwist,
    Quatf*       twist
)
{
    Vec3f rotAxis = QuatApply(axis, q);

    *noTwist = MakeQuat(axis, rotAxis);
    *twist = MakeQuat(*noTwist, q);
}

// See Eberly's "Constrained Quaternions"
// Returns closest rotation about X to qd

Quatf ClosestAxialRotTo(VLAxis a, const Quatf& qd)
{
    Quatf q(vl_w);

    float sqrLength = qd[a] * qd[a] + qd.w * qd.w;

    if (sqrLength > float(0))
    {
        float invLength = float(1) / sqrt(sqrLength);

        q[a] = qd[a] * invLength;
        q.w  = qd.w  * invLength;
    }

    return q;
}

Quatf ClosestRotXYTo(const Quatf& qd)
{
    float det = abs(qd.w * qd.z - qd.x * qd.y);

    if (det < float(0.5))
    {
        float disc = sqrt(float(1) - float(4) * det * det);
        float a = qd.w * qd.x + qd.y * qd.z;
        float b = qd.w * qd.w - qd.x * qd.x + qd.y * qd.y - qd.z * qd.z;

        float s0;
        float c0;

        if (b >= float(0))
        {
            s0 = a;
            c0 = float(0.5) * (disc + b);
        }
        else
        {
            s0 = float(0.5) * (disc - b);
            c0 = a;
        }

        float invLength0 = float(1) / sqrt(sqr(s0) + sqr(c0));
        s0 *= invLength0;
        c0 *= invLength0;

        float s1 = qd.y * c0 + qd.z * s0;
        float c1 = qd.w * c0 + qd.x * s0;

        float invLength1 = float(1) / sqrt(sqr(s1) + sqr(c1));
        s1 *= invLength1;
        c1 *= invLength1;

        return Quatf(s0 * c1, c0 * s1, s0 * s1, c0 * c1);
    }

    float invLength = float(1) / sqrt(det);

    return Quatf(qd.x * invLength, float(0), float(0), qd.w * invLength);
}

Vec3f QuatDiff3(const Quatf& a, const Quatf& b)
{
    Vec3f v;
    v.x = + a.w * b.x - a.z * b.y + a.y * b.z - a.x * b.w;
    v.y = + a.z * b.x + a.w * b.y - a.x * b.z - a.y * b.w;
    v.z = - a.y * b.x + a.x * b.y + a.w * b.z - a.z * b.w;

    float c = dot(a, b);
    float s = len(v);

    v *= (std::atan2(s, c) / (s + float(1e-8)));

    return v;
}

Quatf SLerp(Quatf q, Vec3f wd, float t)
{
    return QuatMult(q, ExpUnit3(wd * t));
}

Quatf SLerp(Quatf q, Vec3f n, float w, float t)
{
    float s, c;
    vl_sincos(w * t, &s, &c);
    n *= s;

    Quatf result;
    result.x = + q.w * n.x + q.z * n.y - q.y * n.z;
    result.y = - q.z * n.x + q.w * n.y + q.x * n.z;
    result.z = + q.y * n.x - q.x * n.y + q.w * n.z;
    result.w = - q.x * n.x - q.y * n.y - q.z * n.z;
    result += q * c;
    return result;
}




Mat2f CRot2f(float theta)
{
    float s, c;
    vl_sincos(theta, &s, &c);

    Mat2f m;

    m.x.x = c; m.x.y = -s;
    m.y.x = s; m.y.y =  c;

    return m;
}

Mat2f RRot2f(float theta)
{
    float s, c;
    vl_sincos(theta, &s, &c);

    Mat2f m;

    m.x.x =  c; m.x.y = s;
    m.y.x = -s; m.y.y = c;

    return m;
}

Mat2f Scale2f(const Vec2f& s)
{
    Mat2f m;

    m.x.x = s.x ; m.x.y = vl_0;
    m.y.x = vl_0; m.y.y = s.y ;

    return m;
}


// Mat3

Mat3f CRot3f(const Vec3f& axis, float theta)
{
    theta /= float(2);

    float s, c;
    vl_sincos(theta, &s, &c);

    Quatf q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return CRot3f(q);
}

Mat3f RRot3f(const Vec3f& axis, float theta)
{
    theta /= float(2);

    float s, c;
    vl_sincos(theta, &s, &c);

    Quatf q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return RRot3f(q);
}

Mat3f CRot3f(VLAxis axis, float angle)
{
    int a0 = axis;
    int a1 = (axis + 1) % 3;
    int a2 = (axis + 2) % 3;

    float s, c;
    vl_sincos(angle, &s, &c);

    Mat3f rot = vl_0;
    rot(a0, a0) =  1;
    rot(a1, a1) =  c;
    rot(a1, a2) = -s;
    rot(a2, a2) =  c;
    rot(a2, a1) = +s;

    return rot;
}

Mat3f RRot3f(VLAxis axis, float angle)
{
    int a0 = axis;
    int a1 = (axis + 1) % 3;
    int a2 = (axis + 2) % 3;

    float s, c;
    vl_sincos(angle, &s, &c);

    Mat3f rot = vl_0;
    rot(a0, a0) =  1;
    rot(a1, a1) =  c;
    rot(a1, a2) =  s;
    rot(a2, a2) =  c;
    rot(a2, a1) = -s;

    return rot;
}

namespace
{
    inline Vec3f FindOrthoVector(const Vec3f& v)
    {
        Vec3f u;

        // we choose the axis that is most orthogonal to v,
        // and return the cross product of it and v.

        if (abs(v.x) < abs(v.y))
            if (abs(v.x) < abs(v.z))
            {   u.x =     0; u.y =  v.z; u.z = -v.y; }
            else
            {   u.x =  v.y; u.y = -v.x; u.z =     0; }
        else
            if (abs(v.y) < abs(v.z))
            {   u.x = -v.z; u.y =     0; u.z =  v.x; }
            else
            {   u.x =  v.y; u.y = -v.x; u.z =     0; }

        return u;
    }
}

Mat3f CRot3f(const Vec3f& from, const Vec3f& to)
{
    Vec3f axis(cross(from, to));

    float s = len(axis);        // sin(theta) between from & to
    float c = dot(from, to);    // cos(theta)

    if (s < 1e-6f) // identical or opposing directions; substitute arbitrary orthogonal vector
        axis = norm(FindOrthoVector(from));
    else
        axis /= s;

    // Rodrigues' rotation formula for rotating about unit-length axis by theta.
    Vec3f ta = axis * (1 - c);
    Vec3f sa = axis * s;

    // oprod(t, axis) + c/s mix
    Mat3f result
    (
        ta[0] * axis[0] + c    ,  ta[1] * axis[0] - sa[2],  ta[2] * axis[0] + sa[1],
        ta[0] * axis[1] + sa[2],  ta[1] * axis[1] + c   ,   ta[2] * axis[1] - sa[0],
        ta[0] * axis[2] - sa[1],  ta[1] * axis[2] + sa[0],  ta[2] * axis[2] + c
    );

    return result;
}

Mat3f RRot3f(const Vec3f& from, const Vec3f& to)
{
    Vec3f axis(cross(from, to));

    float s = len(axis);        // sin(theta) between from & to
    float c = dot(from, to);    // cos(theta)

    if (s < 1e-6f) // identical or opposing directions; substitute arbitrary orthogonal vector
        axis = norm(FindOrthoVector(from));
    else
        axis /= s;

    // Rodrigues' rotation formula for rotating about unit-length axis by theta.
    Vec3f ta = axis * (1 - c);
    Vec3f sa = axis * s;

    // oprod(t, axis) + c/s mix
    Mat3f result
    (
        ta[0] * axis[0] + c    ,  ta[0] * axis[1] + sa[2],  ta[0] * axis[2] - sa[1],
        ta[1] * axis[0] - sa[2],  ta[1] * axis[1] + c   ,   ta[1] * axis[2] + sa[0],
        ta[2] * axis[0] + sa[1],  ta[2] * axis[1] - sa[0],  ta[2] * axis[2] + c
    );

    return result;
}


Mat3f Scale3f(const Vec3f& s)
{
    Mat3f m(vl_0);

    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = s.z;

    return m;
}

Mat3f HCRot3f(float theta)
{
    float s, c;
    vl_sincos(theta, &s, &c);

    Mat3f m;

    m.x.x =  c; m.x.y = -s; m.x.z =  vl_0;
    m.y.x =  s; m.y.y =  c; m.y.z =  vl_0;
    m.z = vl_z;

    return m;
}

Mat3f HRRot3f(float theta)
{
    float s, c;
    vl_sincos(theta, &s, &c);

    Mat3f m;

    m.x.x =  c; m.x.y =  s; m.x.z =  vl_0;
    m.y.x = -s; m.y.y =  c; m.y.z =  vl_0;
    m.z = vl_z;

    return m;
}

Mat3f HScale3f(const Vec2f& s)
{
    Mat3f m(vl_0);

    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = vl_1;

    return m;
}

Mat3f HCTrans3f(const Vec2f& t)
{
    Mat3f m(vl_I);

    m.x.z = t.x;
    m.y.z = t.y;

    return m;
}

Mat3f HRTrans3f(const Vec2f& t)
{
    Mat3f m(vl_I);

    m.z.x = t.x;
    m.z.y = t.y;

    return m;
}


// Mat4

Mat4f HCRot4f(const Vec3f& axis, float theta)
{
    theta /= float(2);

    float s, c;
    vl_sincos(theta, &s, &c);

    Vec4f q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return HCRot4f(q);
}

Mat4f HRRot4f(const Vec3f& axis, float theta)
{
    theta /= float(2);

    float s, c;
    vl_sincos(theta, &s, &c);

    Vec4f q
    (
        s * axis.x,
        s * axis.y,
        s * axis.z,
        c
    );

    return HRRot4f(q);
}

Mat4f HCRot4f(VLAxis axis, float theta)
{
    Mat3f m3 = CRot3f(axis, theta);
    return Mat4f(m3, vl_1);
}

Mat4f HRRot4f(VLAxis axis, float theta)
{
    Mat3f m3 = RRot3f(axis, theta);
    return Mat4f(m3, vl_1);
}

Mat4f HCRot4f(const Vec3f& from, const Vec3f& to)
{
    Mat3f m3 = CRot3f(from, to);
    return Mat4f(m3, vl_1);
}

Mat4f HRRot4f(const Vec3f& from, const Vec3f& to)
{
    Mat3f m3 = RRot3f(from, to);
    return Mat4f(m3, vl_1);
}

Mat4f HScale4f(const Vec3f& s)
{
    Mat4f m(vl_0);

    m.x.x = s.x;
    m.y.y = s.y;
    m.z.z = s.z;
    m.w.w = vl_1;

    return m;
}

Mat4f HCTrans4f(const Vec3f& t)
{
    Mat4f m(vl_I);

    m.x.w = t.x;
    m.y.w = t.y;
    m.z.w = t.z;

    return m;
}

Mat4f HRTrans4f(const Vec3f& t)
{
    Mat4f m(vl_I);

    m.w.x = t.x;
    m.w.y = t.y;
    m.w.z = t.z;

    return m;
}

#ifndef VL_NO_IOSTREAM





using namespace std;

ostream& operator << (ostream& s, const Vec2f& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ']';
}

istream& operator >> (istream& s, Vec2f& v)
{
    Vec2f   result;
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


ostream& operator << (ostream& s, const Vec3f& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ' ' << setw(w) << v[2] << ']';
}

istream& operator >> (istream& s, Vec3f& v)
{
    Vec3f   result;
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


ostream& operator << (ostream& s, const Vec4f& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ' '
        << setw(w) << v[2] << ' ' << setw(w) << v[3] << ']';
}

istream& operator >> (istream& s, Vec4f& v)
{
    Vec4f   result;
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

ostream& operator << (ostream& s, const Mat2f& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << ']' << endl;
}

istream& operator >> (istream& s, Mat2f& m)
{
    Mat2f   result;
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


ostream& operator << (ostream& s, const Mat3f& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << endl
             << ' ' << setw(w) << m[2] << ']' << endl;
}

istream& operator >> (istream& s, Mat3f& m)
{
    Mat3f   result;
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


ostream& operator << (ostream& s, const Mat4f& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << endl
             << ' ' << setw(w) << m[2] << endl
             << ' ' << setw(w) << m[3] << ']' << endl;
}

istream& operator >> (istream& s, Mat4f& m)
{
    Mat4f   result;
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
