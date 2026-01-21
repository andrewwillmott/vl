#include "VLi.hpp"
#include "VLf.hpp"

using namespace std;

void Test2DStuff()
{
    Vec2i x(1,2);
    Vec2i y(5,6);

    cout << "\n+ Test2DStuff\n\n";

    cout << "x: " << x << ", y: " << y << "\n\n";

    cout << "x + y * (y * x * 2) : " << x + y * (y * x * 2) << endl;
    cout << "x dot y               : " << dot(x, y) << endl;

    cout << "cross(x)    : " << cross(x) << endl;
    cout << "len         : " << len(Vec2f(x)) << endl;
    cout << "sqrlen      : " << sqrlen(x) << endl;
    cout << "norm        : " << norm(Vec2f(x)) << endl;
    cout << "len of norm : " << len(norm(Vec2f(x))) << "\n\n";

    Mat2i M(1,2,3,4);
    Mat2i N; N.MakeDiag(2);
    Mat2i I = vl_I;

    cout << "M       : " << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(Mat2f(M)) << endl;
    cout << "M * inv :\n" << Mat2f(M) * inv(Mat2f(M)) << endl;

    cout << "Vec2 consts: " << Vec2i(vl_0) << Vec2i(vl_x)
         << Vec2i(vl_y) << Vec2i(vl_1) << endl;
    cout << "Mat2 consts:\n" << Mat2i(vl_0) << endl << Mat2i(vl_I)
         << endl << Mat2i(vl_1) << "\n\n";

    M = { x, y };

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(Mat2f(M)) << endl;
    cout << "M * inv :\n" << Mat2f(M) * inv(Mat2f(M)) << endl;

    M *= I;
    cout << "M *= I  :\n" << M << endl;
    N += M;
    M *= N;
    cout << "M *= N  :\n" << M << endl;
    M += N;
    cout << "M += N  :\n" << M << endl;
    M -= N;
    cout << "M -= N  :\n" << M << endl;
    M *= 6;
    M /= 3;
    cout << "M *= 6/3:\n" << M << endl;
}

void Test3DStuff()
{
    Vec3i x(1,2,3);
    Vec3i y(5,6,7);

    cout << "\n+ Test3DStuff\n\n";

    cout << "x: " << x << ", y: " << y << "\n\n";

    cout << "x + y * (y * x * 2) : " << x + y * (y * x * 2) << endl;
    cout << "x dot y               : " << dot(x, y) << endl;

    cout << "cross(x,y)  : " << cross(x,y) << endl;
    cout << "cross(x, y) . x : " << dot(cross(x, y), x) << endl;
    cout << "cross(x, y) . y : " << dot(cross(x, y), y) << endl;
    cout << "len         : " << len(Vec3f(x)) << endl;
    cout << "sqrlen      : " << sqrlen(x) << endl;
    cout << "norm        : " << norm(Vec3f(x)) << endl;
    cout << "len of norm : " << len(norm(Vec3f(x))) << "\n\n";

    Mat3i M(1,2,3,3,2,1,2,1,3);
    Mat3i N; N.MakeDiag(2);
    Mat3i I = vl_I;

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(Mat3f(M)) << endl;
    cout << "M * inv :\n" << Mat3f(M) * inv(Mat3f(M)) << endl;

    cout << "Vec3 consts: " << Vec3i(vl_0) << Vec3i(vl_x)
         << Vec3i(vl_y) << Vec3i(vl_z) << Vec3i(vl_1) << endl;
    cout << "Mat3 consts:\n" << Mat3i(vl_0) << endl << Mat3i(vl_I)
         << endl << Mat3i(vl_1) << "\n\n";

    M = { x, y, vl_z };

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(Mat3f(M)) << endl;
    cout << "M * inv :\n" << Mat3f(M) * inv(Mat3f(M)) << endl;

    M *= I;
    cout << "M *= I  :\n" << M << endl;
    N += M;
    M *= N;
    cout << "M *= N  :\n" << M << endl;
    M += N;
    cout << "M += N  :\n" << M << endl;
    M -= N;
    cout << "M -= N  :\n" << M << endl;
    M *= 6;
    M /= 3;
    cout << "M *= 6/3:\n" << M << endl;
}

void Test4DStuff()
{
    Vec4i x(1,2,3,4);
    Vec4i y(5,6,7,8);
    Vec4i z(1,0,0,0);

    cout << "\n+ Test4DStuff\n\n";

    cout << "x: " << x << ", y: " << y << ", z: " << z << "\n\n";

    cout << "x + y * (z * x * 2) : " << x + y * (z * x * 2) << endl;
    cout << "x dot y               : " << dot(x, y) << "\n\n";

    cout << "cross(x,y,z)   : " << cross(x,y,z) << endl;
    cout << "cross(x,y,z).x : " << dot(cross(x,y,z), x) << endl;
    cout << "cross(x,y,z).y : " << dot(cross(x,y,z), y) << endl;
    cout << "cross(x,y,z).z : " << dot(cross(x,y,z), z) << endl;
    cout << "len            : " << len(Vec4f(x)) << endl;
    cout << "sqrlen         : " << sqrlen(x) << endl;
    cout << "norm           : " << norm(Vec4f(x)) << endl;
    cout << "len of norm    : " << len(norm(Vec4f(x))) << "\n\n";


    Mat4i M(1,2,3,0, 2,3,0,5, 3,0,5,6, 0,5,6,7);
    Mat4i N; N.MakeDiag(2);
    Mat4i I = vl_I;

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(Mat4f(M)) << endl;
    cout << "M * inv :\n" << Mat4f(M) * inv(Mat4f(M)) << endl;

    cout << "Vec4 consts: " << Vec4i(vl_0) << Vec4i(vl_x) << Vec4i(vl_y)
         << Vec4i(vl_z) << Vec4i(vl_w) << Vec4i(vl_1) << endl;
    cout << "Mat4 consts:\n" << Mat4i(vl_0) << endl << Mat4i(vl_I) << endl
         << Mat4i(vl_1) << "\n\n";

    M = { x, y, vl_minus_w, vl_y };

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(Mat4f(M)) << endl;
    cout << "M * inv :\n" << Mat4f(M) * inv(Mat4f(M)) << endl;

    M *= I;
    cout << "M *= I  :\n" << M << endl;
    N += M;
    M *= N;
    cout << "M *= N  :\n" << M << endl;
    M += N;
    cout << "M += N  :\n" << M << endl;
    M -= N;
    cout << "M -= N:\n" << M << endl;
    M *= 6;
    M /= 3;
    cout << "M *= 6/3 :\n" << M << endl;
}

void TestComparisons()
{
    cout << "\n+ TestComparisons\n" << endl;

    cout << (Mat2i(vl_0) == vl_0) << ":" << (Mat2i(vl_0) != vl_0) << endl;
    cout << (Mat3i(vl_0) == vl_0) << ":" << (Mat3i(vl_0) != vl_0) << endl;
    cout << (Mat4i(vl_0) == vl_0) << ":" << (Mat4i(vl_0) != vl_0) << endl;

    cout << (Mat2i(vl_1) == vl_0) << ":" << (Mat2i(vl_1) != vl_0) << endl;
    cout << (Mat3i(vl_1) == vl_0) << ":" << (Mat3i(vl_1) != vl_0) << endl;
    cout << (Mat4i(vl_1) == vl_0) << ":" << (Mat4i(vl_1) != vl_0) << endl;
}

void TestNInit()
{
    cout << "\n+ TestInit\n" << endl;

    Veci    v00(10, vl_zero);
    Veci    v01(10, vl_one);
    Veci    v02(10, vl_x);
    Veci    v03(10, vl_axis(5));
    Veci    v04(10); v04.MakeBlock(5);

    cout << v00 << endl;
    cout << v01 << endl;
    cout << v02 << endl;
    cout << v03 << endl;
    cout << v04 << endl;
    cout << endl;

    Mati    m00(5, 5, vl_zero);
    Mati    m01(5, 5, vl_I);
    Mati    m02(5, 5); m02.MakeDiag(4);
    Mati    m03(5, 5); m03.MakeBlock(2);
    Mati    m04(5, 5); m04.MakeBlock(8);

    sub(m04, 2, 2, 2, 2) = Mat2i(vl_1) * 111;

    cout << m00 << endl;
    cout << m01 << endl;
    cout << m02 << endl;
    cout << m03 << endl;
    cout << m04 << endl;
    cout << endl;
}

void TestND()
{
    cout << "\n+ TestND\n\n";

    Veci x(4, 1, 2, 3, 4);
    Veci sx(3, 1, 2, 3);
    Veci y(4, 5, 6, 7, 8);
    Veci z(4, 4, 3, 2, 1);

    Mati M(4, 3, 4.0, 3.0, 2.0,
                 1.0, 4.0, 3.0,
                 2.0, 1.0, 5.0,
                 2.0, 1.0, 4.0,
                 3.0, 2.0, 1.0, 5.0);
    Mati N(4, 3, 1, 2, 3, 4,
                 5, 6, 7, 8,
                 9, 2, 3, 4,
                 5, 6, 7, 8);

    cout << "M:\n" << M;
    cout << "\nN:\n" << N;
    cout << "\ntrans(N):\n" << trans(N);
    cout << "\nM + N:\n" << M + N;
    cout << "\nM * trans(N):\n" << M * trans(N);
    cout << "x: " << x << ", sx: " << sx << endl;

    z = x + y;
    cout << "z: " << z << endl;

    cout << "M * sx   : " << (M * sx) << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "x: " << x << ", y: " << y << ", z: " << z << endl;

    cout << "x + y: " << x + y << endl;
    cout << "x * y: " << x * y << endl;
    cout << "x dot y: " << dot(x, y) << endl;
    cout << "x + (y dot z) * x * 2 : " << x + (dot(y, z) * x * 2) << endl;

    cout << "len : " << len(Vecf(x)) << endl;
    cout << "sqrlen : " << sqrlen(x) << endl;
    cout << "norm : " << norm(Vecf(x)) << endl;
    cout << "len of norm : " << len(norm(Vecf(x))) << endl;
}

void TestNDSub()
{
    cout << "\n+ TestNDSub\n\n";

    Veci x(8, 1, 2, 3, 4, 1, 2, 3, 4);
    Veci y(16, 1, 2, 3, 4, 5, 6, 7, 8,
               1, 2, 3, 4, 5, 6, 7, 8);
    cout << "x: " << x << ", y: " << y << endl;

    cout << "sub(y, 3, 3): " << sub(y, 3, 3) << endl;
    Veci z = sub(x, 2, 6) + sub(y, 10, 6);
    cout << "sub(x, 2, 6) + sub(y, 10, 6): " << z << endl;

    sub(y, 5, 6) = Veci(6, 88, 77, 66, 55, 44, 33);
    sub(x, 0, 2) = Veci(2, 22, 11);

    cout << "x: " << x << ", y: " << y << endl;

    z = z + sub(y, 5, 6);
    sub(y, 5, 6) =  sub(y, 5, 6) + z;

    cout << "z: " << z << ", y: " << y << endl;

    cout << "\n\n";

    Mati M(10, 10, vl_I);
    Mati N(4, 3, 1, 2, 3, 4, 5, 6, 7, 8,
           9, 2, 3, 4, 5, 6, 7, 8);

    cout << "sub(N, 1, 1, 2, 2):" << endl << sub(N, 1, 1, 2, 2);

    sub(M, 5, 3, 4, 3) = N;

    cout << "\nM:\n" << M;

    cout << "\nDiagonals of M:\n\n";

    for (int i = 1 - M.Rows(); i < M.Cols(); i++)
        cout << diag(M, i) << endl;

    cout << "\nCol 4 of M:\n" << col(M, 4);

    diag(M, 0) = Veci(10, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3);

    diag(M, 1) = Veci(Veci(9, vl_1) * 2);

    diag(M, -1) = diag(M, 1) * 3;

    cout << "\nM:\n" << M << endl;
}

void TestNDFunc()
{
    cout << "\n+ TestND\n\n";

    Veci x(4, 1, 2, 3, 4);
    Veci sx(3, 1, 2, 3);
    Veci y(4, 5, 6, 7, 8);
    Veci z(4, 4, 3, 2, 1);

    Mati M(4, 3, 4, 3, 2, 1, 4, 3, 2, 1, 5,
           2, 1, 4, 3, 2, 1, 5);
    Mati N(4, 3, 1, 2, 3, 4, 5, 6, 7, 8, 9,
           2, 3, 4, 5, 6, 7, 8);

    Mati R;
    Transpose(N, R);
    cout << "\nTranspose(N, R):\n" << R;
    Add(N, M, R);
    cout << "\nAdd(M, N, R):\n" << M + N;
    Multiply(M, trans(N), R);
    cout << "\nMultiply(M, trans(N), R):\n" << R;

    Veci r, s;
    Multiply(M, sx, r);
    cout << "Multiply(M, sx, r)   : " << r << endl;
    Multiply(x, M, r);
    cout << "Multiply(x, M, r)   : " << r << endl;

    Add(x, y, r);
    cout << "x + y: " << r << endl;
    Multiply(x, y, r);
    cout << "x * y: " << r << endl;
    Multiply(x, 2 * dot(y, z), r);
    Add(r, x, s);
    cout << "Multiply(x, 2 * dot(y, z), r), Add(r, x, s) : " << s << endl;
    Multiply(x, 2 * dot(y, z), s);
    s += x;
    cout << "Multiply(x, 2 * dot(y, z), r), Add(r, x, s) : " << s << endl;
}

void TestNComparisons()
{
    cout << "\n+ TestNComparisons\n" << endl;

    Veci va(8, vl_w);
    Veci vb(8, vl_y);

    cout << (va == va) << ":" << (va != va) << endl;
    cout << (va == vb) << ":" << (va != vb) << endl;

    Mati ma(8, 8, vl_I);
    Mati mb(8, 8, vl_0);

    cout << (ma == ma) << ":" << (ma != ma) << endl;
    cout << (ma == mb) << ":" << (ma != mb) << endl;
}

int main(int, char **)
{
    cout << "Testing VL234i library" << endl;

    cout << "----------------------------------" << endl;

    Test2DStuff();
    Test3DStuff();
    Test4DStuff();

    TestComparisons();

    TestNInit();
    TestND();
    TestNDSub();
    TestNComparisons();

    cout << "\n\n--- Finished! ---" << endl;

    return 0;
}
