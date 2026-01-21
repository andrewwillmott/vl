//
// VL234f.cpp
//
// Andrew Willmott
//


#include "VL234f.hpp"










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

#ifndef VL_NO_REAL
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
#endif

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

#ifndef VL_NO_REAL
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
#endif

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

#ifndef VL_NO_REAL
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
#endif

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

#ifndef VL_PRINT_BASE_H
#define VL_PRINT_BASE_H




// Base routines used by Print/Print234

// Print according to specific format, see VL_FORMAT below
int vl_fprintf     (FILE* file, const char* format, int n,               const float* elts, int width = 1, int precision = 3);
int vl_fprintf     (FILE* file, const char* format, int r, int c,        const float* elts, int width = 1, int precision = 3);
int vl_fprintf     (FILE* file, const char* format, int s, int r, int c, const float* elts, int width = 1, int precision = 3);

// Print in format that can be compiled as C, 'name' is variable name.
int vl_fprint_as_c(FILE* file, const char* name,   int n,               const float* elts, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name,   int r, int c,        const float* elts, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name,   int s, int r, int c, const float* elts, int width = 1, int precision = 3);

// Write string according to specific format, see VL_FORMAT below. Behaviour same as unix snprintf.
int vl_snprintf(char* str, size_t sz, const char* fmt, int n,               const float* elts, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t sz, const char* fmt, int r, int c,        const float* elts, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t sz, const char* fmt, int s, int r, int c, const float* elts, int width = 1, int precision = 3);

// Variant that advances 'str' and reduces 'size' accordingly.
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int n,               const float* elts, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int r, int c,        const float* elts, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int s, int r, int c, const float* elts, int width = 1, int precision = 3);

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

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int n, const float* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, n, elts, w, p);
}

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int r, int c, const float* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, r, c, elts, w, p);
}

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int s, int r, int c, const float* elts, int w, int p)
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
int vl_fprint(FILE* file, const Vec2f& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 2, &v.x, width); }
int vl_fprint(FILE* file, const Vec3f& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 3, &v.x, width); }
int vl_fprint(FILE* file, const Vec4f& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 4, &v.x, width); }
int vl_fprint(FILE* file, const Mat2f& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 2, 2, &m.x.x, width); }
int vl_fprint(FILE* file, const Mat3f& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 3, 3, &m.x.x, width); }
int vl_fprint(FILE* file, const Mat4f& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 4, 4, &m.x.x, width); }
#else
int vl_fprint(FILE* file, const Vec2f& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 2, &v.x, width, prec); }
int vl_fprint(FILE* file, const Vec3f& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 3, &v.x, width, prec); }
int vl_fprint(FILE* file, const Vec4f& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 4, &v.x, width, prec); }
int vl_fprint(FILE* file, const Mat2f& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 2, 2, &m.x.x, width, prec); }
int vl_fprint(FILE* file, const Mat3f& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 3, 3, &m.x.x, width, prec); }
int vl_fprint(FILE* file, const Mat4f& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 4, 4, &m.x.x, width, prec); }
#endif

int vl_fprintf(FILE* file, const char* fmt, const Vec2f& v, int width, int prec) { return vl_fprintf(file, fmt, 2, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Vec3f& v, int width, int prec) { return vl_fprintf(file, fmt, 3, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Vec4f& v, int width, int prec) { return vl_fprintf(file, fmt, 4, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Mat2f& m, int width, int prec) { return vl_fprintf(file, fmt, 2, 2, &m.x.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Mat3f& m, int width, int prec) { return vl_fprintf(file, fmt, 3, 3, &m.x.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const Mat4f& m, int width, int prec) { return vl_fprintf(file, fmt, 4, 4, &m.x.x, width, prec); }

int vl_fprint_as_c(FILE* file, const char* name, const Vec2f& v, int width, int prec) { return vl_fprint_as_c(file, name, 2, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Vec3f& v, int width, int prec) { return vl_fprint_as_c(file, name, 3, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Vec4f& v, int width, int prec) { return vl_fprint_as_c(file, name, 4, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Mat2f& m, int width, int prec) { return vl_fprint_as_c(file, name, 2, 2, &m.x.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Mat3f& m, int width, int prec) { return vl_fprint_as_c(file, name, 3, 3, &m.x.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const Mat4f& m, int width, int prec) { return vl_fprint_as_c(file, name, 4, 4, &m.x.x, width, prec); }

int vl_snprintf(char* str, size_t size, const char* fmt, const Vec2f& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Vec3f& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Vec4f& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Mat2f& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Mat3f& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const Mat4f& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }

int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Vec2f& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Vec3f& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Vec4f& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Mat2f& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Mat3f& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const Mat4f& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }


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

int vl_fprintf(FILE* file, const char* format, int n, const float* v, int width, int precision)
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

int vl_fprintf(FILE* file, const char* format, int nr, int nc, const float* m, int width, int precision)
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

int vl_fprintf(FILE* file, const char* format, int ns, int nr, int nc, const float* elts, int width, int precision)
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

int vl_fprint_as_c(FILE* file, const char* name, int n, const float* v, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d] = ", name, n);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_VI_C ";\n", n, v, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_VF_C ";\n", n, v, width, precision);
#endif

    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int nr, int nc, const float* m, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d][%d] = \n", name, nr, nc);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_MI_C ";\n", nr, nc, m, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_MF_C ";\n", nr, nc, m, width, precision);
#endif
    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int ns, int nr, int nc, const float* elts, int width, int precision)
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

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int n, const float* v, int width, int precision)
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

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int nr, int nc, const float* m, int width, int precision)
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

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int ns, int nr, int nc, const float* elts, int width, int precision)
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
