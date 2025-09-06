/*
    File:       VLTest.cpp

    Function:   Regression tests for VLLib.

    Copyright:  Andrew Willmott
*/

#include <VLfd.h>

#include <iomanip>

using std::cout;
using std::endl;
using std::ostream;
using std::setprecision;

void TestBasics();

#define TEST_VL_234
void Test2DStuff();
void Test3DStuff();
void Test4DStuff();
void TestH2DStuff();
void TestH3DStuff();
void TestComparisons();

#define TEST_VL_N
#define TEST_VL_SOLVE
void TestNInit();
void TestND();
void TestNDSub();
void TestNDNumerical();
void TestNDFunc();
void TestNComparisons();

#ifdef VL_NS
using namespace VL_NS;
#endif

// --- Test routines ----------------------------------------------------------

void TestBasics()
{
    cout << "\n+ TestBasics\n\n";

    int a;

    VL_ASSERT(1 + 1 == 3);
    VL_EXPECT((a = 1) == 2);
    VL_RANGE(11, 0, 10);
}

#ifdef TEST_VL_234

void Test2DStuff()
{
    Vec2f x(1,2);
    Vec2f y(5,6);

    cout << "\n+ Test2DStuff\n\n";

    cout << "x: " << x << ", y: " << y << "\n\n";

    cout << "x + y * (y * x * 2) : " << x + y * (y * x * 2) << endl;
    cout << "x dot y               : " << dot(x, y) << endl;

    cout << "cross(x)    : " << cross(x) << endl;
    cout << "len         : " << len(x) << endl;
    cout << "sqrlen      : " << sqrlen(x) << endl;
    cout << "norm        : " << norm(x) << endl;
    cout << "len of norm : " << len(norm(x)) << "\n\n";

    Mat2d M(1,2,3,4);
    Mat2d N; N.MakeDiag(2.0);
    Mat2d I = vl_I;

    cout << "M       : " << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     :\n" << adj(M) << endl;
    cout << "det     : "  << det(M) << endl;
    cout << "trace   : "  << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << clamped(M * inv(M)) << "\n" << endl;

    cout << "Vec2 consts: " << Vec2f(vl_0) << Vec2f(vl_x)
         << Vec2f(vl_y) << Vec2f(vl_1) << endl;
    cout << "Mat2 consts:\n" << Mat2d(vl_0) << endl << Mat2d(vl_I)
         << endl << Mat2d(vl_1) << "\n\n";

    M = Rot2d(1.3) * Scale2d(Vec2d(2,1));

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     :\n" << adj(M) << endl;
    cout << "det     : "  << det(M) << endl;
    cout << "trace   : "  << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << clamped(M * inv(M)) << "\n" << endl;

    M *= I;
    cout << "M *= I  :\n" << M << endl;
    N += M;
    M *= N;
    cout << "M *= N  :\n" << M << endl;
    M += N;
    cout << "M += N  :\n" << M << endl;
    M -= N;
    cout << "M -= N  :\n" << M << endl;
    M *= 6.0f;
    M /= 3.0f;
    cout << "M *= 6/3:\n" << M << endl;
}

void Test3DStuff()
{
    Vec3f x(1,2,3);
    Vec3f y(5,6,7);

    cout << "\n+ Test3DStuff\n\n";

    cout << "x: " << x << ", y: " << y << "\n\n";

    cout << "x + y * (y * x * 2) : " << x + y * (y * x * 2) << endl;
    cout << "x dot y               : " << dot(x, y) << endl;

    cout << "cross(x,y)  : " << cross(x,y) << endl;
    cout << "cross(x, y) . x : " << dot(cross(x, y), x) << endl;
    cout << "cross(x, y) . y : " << dot(cross(x, y), y) << endl;
    cout << "len         : " << len(x) << endl;
    cout << "sqrlen      : " << sqrlen(x) << endl;
    cout << "norm        : " << norm(x) << endl;
    cout << "len of norm : " << len(norm(x)) << "\n\n";

    Mat3d M(1,2,3,3,2,1,2,1,3);
    Mat3d N; N.MakeDiag(2.0);
    Mat3d I = vl_I;

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     :\n" << adj(M) << endl;
    cout << "det     : "  << det(M) << endl;
    cout << "trace   : "  << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << clamped(M * inv(M)) << endl;

    cout << "Vec3 consts: " << Vec3f(vl_0) << Vec3f(vl_x)
         << Vec3f(vl_y) << Vec3f(vl_z) << Vec3f(vl_1) << endl;
    cout << "Mat3 consts:\n" << Mat3d(vl_0) << endl << Mat3d(vl_I)
         << endl << Mat3d(vl_1) << "\n\n";

    M = Rot3d(vl_y, 1.3) * Scale3d(Vec3d(2,4,2));

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     :\n" << adj(M) << endl;
    cout << "det     : "  << det(M) << endl;
    cout << "trace   : "  << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << clamped(M * inv(M)) << endl;

    M *= I;
    cout << "M *= I  :\n" << M << endl;
    N += M;
    M *= N;
    cout << "M *= N  :\n" << M << endl;
    M += N;
    cout << "M += N  :\n" << M << endl;
    M -= N;
    cout << "M -= N  :\n" << M << endl;
    M *= 6.0f;
    M /= 3.0f;
    cout << "M *= 6/3:\n" << M << endl;
}

void Test4DStuff()
{
    Vec4f x(1,2,3,4);
    Vec4f y(5,6,7,8);
    Vec4f z(1,0,0,0);

    cout << "\n+ Test4DStuff\n\n";

    cout << "x: " << x << ", y: " << y << ", z: " << z << "\n\n";

    cout << "x + y * (z * x * 2) : " << x + y * (z * x * 2) << endl;
    cout << "x dot y               : " << dot(x, y) << "\n\n";

    cout << "cross(x,y,z)   : " << cross(x,y,z) << endl;
    cout << "cross(x,y,z).x : " << dot(cross(x,y,z), x) << endl;
    cout << "cross(x,y,z).y : " << dot(cross(x,y,z), y) << endl;
    cout << "cross(x,y,z).z : " << dot(cross(x,y,z), z) << endl;
    cout << "len            : " << len(x) << endl;
    cout << "sqrlen         : " << sqrlen(x) << endl;
    cout << "norm           : " << norm(x) << endl;
    cout << "len of norm    : " << len(norm(x)) << "\n\n";


    Mat4d M(1,2,3,0, 2,3,0,5, 3,0,5,6, 0,5,6,7);
    Mat4d N; N.MakeDiag(2.0);
    Mat4d I = vl_I;

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     :\n" << adj(M) << endl;
    cout << "det     : "  << det(M) << endl;
    cout << "trace   : "  << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << clamped(M * inv(M)) << endl;

    cout << "Vec4 consts: " << Vec4f(vl_0) << Vec4f(vl_x) << Vec4f(vl_y)
         << Vec4f(vl_z) << Vec4f(vl_w) << Vec4f(vl_1) << endl;
    cout << "Mat4 consts:\n" << Mat4d(vl_0) << endl << Mat4d(vl_I) << endl
         << Mat4d(vl_1) << "\n\n";

    M = HScale4d(Vec3d(2,3,4));
    M *= HRot4d(vl_y, 1.256);

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     :\n" << adj(M) << endl;
    cout << "det     : "  << det(M) << endl;
    cout << "trace   : "  << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << clamped(M * inv(M)) << endl;

    M *= I;
    cout << "M *= I  :\n" << M << endl;
    N += M;
    M *= N;
    cout << "M *= N  :\n" << M << endl;
    M += N;
    cout << "M += N  :\n" << M << endl;
    M -= N;
    cout << "M -= N:\n" << M << endl;
    M *= 6.0f;
    M /= 3.0f;
    cout << "M *= 6/3 :\n" << M << endl;
}

void TestH2DStuff()
{
    cout << "\n+ TestH2DStuff\n\n";

    Vec2f x = Vec2f(1,2);
    cout << "x is: " << x << endl;

    cout << "rot(pi/2) is: " <<  Rot2d(vl_halfPi) << endl;
    x = Rot2d(vl_halfPi) * x;
    cout << "x after rot(pi/2) is: " << x << endl;
    x = Scale2d(Vec2d(0.3, 0.2)) * x;
    cout << "x after scale(0.3, 0.2) is: " << x << endl;

    Vec3f y = Vec3f(x, 0.5);
    cout << "y is: " << y << endl;
    x = proj(y);
    cout << "proj(y) is: " << x << endl;

    x = proj
        (
              HRot3d(1.3)
            * HTrans3d(Vec2d(1,1))
            * HScale3d(Vec2d(1,2))
            * Vec3f(x, 1)
        );
    cout << "HRot3(1.3) * HTrans3(Vec2(1,1)) * HScale3(Vec2(1,2)) * y = "
         << x << endl;
}

void TestH3DStuff()
{
    cout << "\n+ TestH3DStuff\n\n";

    Vec3f x = Vec3f(1,2,3);
    cout << "x is: " << x << endl;

    cout << "rot(pi/2, vl_x) is: " <<  Rot3d(vl_x, vl_halfPi) << endl;
    x = x * Rot3d(vl_x, vl_halfPi);
    cout << "x after rot(pi/2, vl_x) is: " << x << endl;
    x = x * Scale3d(Vec3d(0.3, 0.2, 0.3));
    cout << "x after scale(0.3, 0.2, 0.3) is: " << x << endl;

    Vec4f y = Vec4f(x, 0.5);
    cout << "y is: " << y << endl;
    x = proj(y);
    cout << "proj(y) is: " << x << endl;

    x = proj(HRot4d(vl_x, 1.3) * HTrans4d(vl_1) * HScale4d(Vec3d(1,2,1)) * y);
    cout << "HRot4(vl_x, 1.3) * HTrans4(vl_1) "
        "* HScale4(Vec3(1,2,1)) * y = " << x << endl;
}

void TestComparisons()
{
    cout << "\n+ TestComparisons\n" << endl;

    cout << (Mat2d(vl_I) == vl_I) << ":" << (Mat2d(vl_I) != vl_I) << endl;
    cout << (Mat3d(vl_I) == vl_I) << ":" << (Mat3d(vl_I) != vl_I) << endl;
    cout << (Mat4d(vl_I) == vl_I) << ":" << (Mat4d(vl_I) != vl_I) << endl;

    cout << (Mat2d(vl_I) == vl_0) << ":" << (Mat2d(vl_I) != vl_0) << endl;
    cout << (Mat3d(vl_I) == vl_0) << ":" << (Mat3d(vl_I) != vl_0) << endl;
    cout << (Mat4d(vl_I) == vl_0) << ":" << (Mat4d(vl_I) != vl_0) << endl;
}

#endif


#ifdef TEST_VL_N

void TestNInit()
{
    cout << "\n+ TestInit\n" << endl;

    Vecf    v00(10, vl_zero);
    Vecf    v01(10, vl_one);
    Vecf    v02(10, vl_x);
    Vecf    v03(10, vl_axis(5));
    Vecf    v04(10); v04.MakeBlock(5.0);

    cout << v00 << endl;
    cout << v01 << endl;
    cout << v02 << endl;
    cout << v03 << endl;
    cout << v04 << endl;
    cout << endl;

    Matd    m00(5, 5, vl_zero);
    Matd    m01(5, 5, vl_I);
    Matd    m02(5, 5); m02.MakeDiag(4.0);
    Matd    m03(5, 5); m03.MakeBlock(2.2);
    Matd    m04(5, 5); m04.MakeBlock(8.8);

    sub(m04, 2, 2, 2, 2) = Mat2d(vl_1) * 111.0;

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

    Vecf x(4, 1.0, 2.0, 3.0, 4.0);
    Vecf sx(3, 1.0, 2.0, 3.0);
    Vecf y(4, 5.0, 6.0, 7.0, 8.0);
    Vecf z(4, 4.0, 3.0, 2.0, 1.0);

    Matd M(4, 3, 4.0, 3.0, 2.0,
                 1.0, 4.0, 3.0,
                 2.0, 1.0, 5.0,
                 2.0, 1.0, 4.0,
                 3.0, 2.0, 1.0, 5.0);
    Matd N(4, 3, 1.0, 2.0, 3.0, 4.0,
                 5.0, 6.0, 7.0, 8.0,
                 9.0, 2.0, 3.0, 4.0,
                 5.0, 6.0, 7.0, 8.0);

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
    cout << "x + (y dot z) * x * 2 : " << x + (dot(y, z) * x * 2.0) << endl;

    cout << "len : " << len(x) << endl;
    cout << "sqrlen : " << sqrlen(x) << endl;
    cout << "norm : " << norm(x) << endl;
    cout << "len of norm : " << len(norm(x)) << endl;
}

void TestNDSub()
{
    cout << "\n+ TestNDSub\n\n";

    Vecf x(8, 1.0, 2.0, 3.0, 4.0, 1.0, 2.0, 3.0, 4.0);
    Vecf y(16, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
           1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    Vecf z;

    cout << "x: " << x << ", y: " << y << endl;

    cout << "sub(y, 3, 3): " << sub(y, 3, 3) << endl;
    z = sub(x, 2, 6) + sub(y, 10, 6);
    cout << "sub(x, 2, 6) + sub(y, 10, 6): " << z << endl;

    sub(y, 5, 6) = Vecf(6, 88.0, 77.0, 66.0, 55.0, 44.0, 33.0);
    sub(x, 0, 2) = Vecf(2, 22.0, 11.0);

    cout << "x: " << x << ", y: " << y << endl;

    z = z + sub(y, 5, 6);
    sub(y, 5, 6) =  sub(y, 5, 6) + z;

    cout << "z: " << z << ", y: " << y << endl;

    cout << "\n\n";

    Matd M(10, 10, vl_I);
    Matd N(4, 3, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
           9.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    cout << "sub(N, 1, 1, 2, 2):" << endl << sub(N, 1, 1, 2, 2);

    sub(M, 5, 3, 4, 3) = N;

    cout << "\nM:\n" << M;

    cout << "\nDiagonals of M:\n\n";

    for (int i = 1 - M.Rows(); i < M.Cols(); i++)
        cout << diag(M, i) << endl;

    cout << "\nCol 4 of M:\n" << col(M, 4);

    diag(M, 0) = Vecd(10, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0);

    diag(M, 1) = Vecd(Vecf(9, vl_1) * 2.0f);

    diag(M, -1) = diag(M, 1) * 3.0;

    cout << "\nM:\n" << M << endl;
}

#ifdef TEST_VL_SOLVE

void TestNDNumerical()
{
    Matd    P(4, 4,
                1.0, 2.0, 3.0, 0.0,
                2.0, 3.0, 0.0, 5.0,
                3.0, 0.0, 5.0, 6.0,
                0.0, 5.0, 6.0, 7.0
            );
    Matd    Q;
    Mat4d   P1(
                1.0, 2.0, 3.0, 0.0,
                2.0, 3.0, 0.0, 5.0,
                3.0, 0.0, 5.0, 6.0,
                0.0, 5.0, 6.0, 7.0
            );
    Mat4d   Q1;

    cout << "\n+ TestNDNumerical\n" << endl;

    cout << "P:\n";
    cout << P;

    cout << "\ninv(P):" << endl;
    Q = inv(P);
    cout << Q;

    cout << "\nP * inv(P):\n";
    cout << clamped(P * Q);

    cout << "\n\nReal:\n";

    cout << "P1: " << P1 << endl;
    cout << "\ninv(P1):\n";
    Q1 = inv(P1);
    cout << Q1 << endl;

    cout << "\nP1 * inv(P1): " << endl << clamped(P1 * Q1) << endl;
    cout << "\ninv(P) - inv(P1): " << endl << clamped(inv(P) - inv(P1));
    cout << endl << endl;

    // --- SolveOverRelax -----------------------------------------------------

    Matd    A(4, 4,
                29.0,   2.0,  3.0,  0.0,
                 2.0,  29.0,  0.0,  5.0,
                 3.0,   0.0, 29.0,  6.0,
                 0.0,   5.0,  6.0, 29.0);

    Vecf    x;
    Vecf    b;
    double  error = 1.0;

    b.SetSize(4);
    b = A * Vecf(Vec4f(1.0, 2.0, 3.0, 4.0));

    x = b;
    cout << "Solving Ax = b with over-relaxation..." << endl;
    cout << "A:\n" << A << endl;
    cout << "b: " << b << endl;
    cout << "start x: " << x << endl;

    error = SolveOverRelax(A, x, b, 1e-8, 1.1);

    cout << "x: " << x << endl;
    cout << "Ax - b: " << A * x - b << endl;
    cout << "Returned error: " << error << ", real error: " << sqrlen(A * x - b) << endl;
    cout << endl;

    // --- SolveConjGrad ------------------------------------------------------

    x = b;

    cout << "Solving Ax = b with conjugate-gradient..." << endl;
    cout << "A:\n" << A;
    cout << "b: " << b << endl;
    cout << "start x: " << x << endl;

    int steps = 100;
    error = SolveConjGrad(A, x, b, 1e-12, &steps);

    cout << "iterations: " << steps << endl;
    cout << "x: " << x << endl;
    cout << "Ax - b: " << clamped(A * x - b) << endl;
    cout << "Returned error: " << error << ", real error: " <<
        sqrlen(A * x - b) << endl;

    cout << endl;

    // --- QRFactorization ----------------------------------------------------

    cout << "Factoring A into Q and R..." << endl;

    Matd AM(A);
    Matd R;
    error =  QRFactorization(AM, Q, R);

    cout << "error: " << error;
    cout << "Q:\n" << Q;
    cout << "R:\n" << R;
    cout << "Q * R - A:\n" << clamped(Q * R - A);
    cout << "QtQ:\n" << clamped(trans(Q) * Q);

    cout << endl;

    // --- SVDFactorization ---------------------------------------------------

    cout << "SVD Factorisation..." << endl;

    AM = A;
    Matd U, V;
    Vecd diagonal;

    SVDFactorization(AM, U, V, diagonal);

    cout << "U:\n" << U;
    cout << "V:\n" << V;
    cout << "D:\n" << diagonal << endl;

    Matd D(diagonal.Elts(), diagonal.Elts(), vl_0);
    diag(D) = diagonal;

    cout << "UtV:\n" << clamped(trans(U) * U);
    cout << "VtV:\n" << clamped(trans(V) * V);
    cout << "U D V^t - A:\n" << clamped(U * D * trans(V) - A);

    cout << endl;

    // --- ReducedRowEchelonForm ----------------------------------------------

    D(1, 1) = vl_0;
    D(2, 2) = vl_0;
    AM = U * D * trans(V);
    ReducedRowEchelonForm(AM, 1e-6);
    cout << "rref(A):\n" << clamped(AM);

    cout << endl;
}

#endif

void TestNDFunc()
{
    cout << "\n+ TestND\n\n";

    Vecf x(4, 1.0, 2.0, 3.0, 4.0);
    Vecf sx(3, 1.0, 2.0, 3.0);
    Vecf y(4, 5.0, 6.0, 7.0, 8.0);
    Vecf z(4, 4.0, 3.0, 2.0, 1.0);

    Matd M(4, 3, 4.0, 3.0, 2.0, 1.0, 4.0, 3.0, 2.0, 1.0, 5.0,
           2.0, 1.0, 4.0, 3.0, 2.0, 1.0, 5.0);
    Matd N(4, 3, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
           2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

    Matd R;
    Transpose(N, R);
    cout << "\nTranspose(N, R):\n" << R;
    Add(N, M, R);
    cout << "\nAdd(M, N, R):\n" << M + N;
    Multiply(M, trans(N), R);
    cout << "\nMultiply(M, trans(N), R):\n" << R;

    Vecf r, s;
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

    Vecd va(8, vl_w);
    Vecd vb(8, vl_y);

    cout << (va == va) << ":" << (va != va) << endl;
    cout << (va == vb) << ":" << (va != vb) << endl;

    Matd ma(8, 8, vl_I);
    Matd mb(8, 8, vl_0);

    cout << (ma == ma) << ":" << (ma != ma) << endl;
    cout << (ma == mb) << ":" << (ma != mb) << endl;
}

#endif


int main(int, char **)
{
    cout << "Testing VL library, version " << VL_VERSION << endl;

    cout << "----------------------------------" << endl;

#ifdef TEST_VL_234
    Test2DStuff();
    Test3DStuff();
    Test4DStuff();

    TestH2DStuff();
    TestH3DStuff();

    TestComparisons();
#endif

#ifdef TEST_VL_N
    TestNInit();
    TestND();
    TestNDSub();
#ifdef TEST_VL_SOLVE
    TestNDNumerical();
#endif
    TestNComparisons();
#endif

    cout << "\n\n--- Finished! ---" << endl;

    return 0;
}
