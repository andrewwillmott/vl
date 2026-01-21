/*
    File:       VL234Test.cpp

    Function:   Regression tests for VL234f.hpp

    Copyright:  Andrew Willmott
*/

#include "VL234f.hpp"

using std::cout;
using std::endl;
using std::ostream;

void TestH2DStuff();
void TestH3DStuff();
void Test2DStuff();
void Test3DStuff();
void Test4DStuff();
void TestBasics();
void TestComparisons();


// --- Test routines ----------------------------------------------------------

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

    Mat2f M(1,2,3,4);
    Mat2f N; N.MakeDiag(2.0);
    Mat2f I = vl_I;

    cout << "M       : " << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << M * inv(M) << endl;

    cout << "Vec2 consts: " << Vec2f(vl_0) << Vec2f(vl_x)
         << Vec2f(vl_y) << Vec2f(vl_1) << endl;
    cout << "Mat2 consts:\n" << Mat2f(vl_0) << endl << Mat2f(vl_I)
         << endl << Mat2f(vl_1) << "\n\n";

    M = Rot2f(1.3) * Scale2f(Vec2f(2,1));

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << M * inv(M) << endl;

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

    Mat3f M(1,2,3,3,2,1,2,1,3);
    Mat3f N; N.MakeDiag(2.0);
    Mat3f I = vl_I;

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << M * inv(M) << endl;

    cout << "Vec3 consts: " << Vec3f(vl_0) << Vec3f(vl_x)
         << Vec3f(vl_y) << Vec3f(vl_z) << Vec3f(vl_1) << endl;
    cout << "Mat3 consts:\n" << Mat3f(vl_0) << endl << Mat3f(vl_I)
         << endl << Mat3f(vl_1) << "\n\n";

    M = Rot3f(vl_y, 1.3) * Scale3f(Vec3f(2,4,2));

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << M * inv(M) << endl;

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


    Mat4f M(1,2,3,0, 2,3,0,5, 3,0,5,6, 0,5,6,7);
    Mat4f N; N.MakeDiag(2.0);
    Mat4f I = vl_I;

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << M * inv(M) << endl;

    cout << "Vec4 consts: " << Vec4f(vl_0) << Vec4f(vl_x) << Vec4f(vl_y)
         << Vec4f(vl_z) << Vec4f(vl_w) << Vec4f(vl_1) << endl;
    cout << "Mat4 consts:\n" << Mat4f(vl_0) << endl << Mat4f(vl_I) << endl
         << Mat4f(vl_1) << "\n\n";

    M = HScale4f(Vec3f(2,3,4));
    M *= HRot4f(vl_y, 1.256);

    cout << "M       :\n" << M << endl;

    cout << "M * x   : " << M * x << endl;
    cout << "x * M   : " << x * M << endl;

    cout << "adj     : " << adj(M) << endl;
    cout << "det     : " << det(M) << endl;
    cout << "trace   : " << trace(M) << endl;
    cout << "inv     :\n" << inv(M) << endl;
    cout << "M * inv :\n" << M * inv(M) << endl;

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

    cout << "rot(pi/2) is: " <<  Rot2f(vl_halfPi) << endl;
    x = Rot2f(vl_halfPi) * x;
    cout << "x after rot(pi/2) is: " << x << endl;
    x = Scale2f(Vec2f(0.3, 0.2)) * x;
    cout << "x after scale(0.3, 0.2) is: " << x << endl;

    Vec3f y = Vec3f(x, 0.5);
    cout << "y is: " << y << endl;
    x = proj(y);
    cout << "proj(y) is: " << x << endl;

    x = proj
        (
              HRot3f(1.3)
            * HTrans3f(Vec2f(1,1))
            * HScale3f(Vec2f(1,2))
            * Vec3f(x, 1)
        );
    cout << "HRot3(1.3) * HTrans3(Vec2(1,1)) * HScale3(Vec2(1,2)) * y = "
         << x << endl;
}

void TestH3DStuff()
{
    cout << "\n+ TestH3DStuff\n\n";

    Vec3f x = Vec3f(1,2,3);
//    cout << "x is: " << x << endl;
    vl_fprintf(stdout, "x is: " VL_FMT_VF "\n", x, 1, 0);

#define VL_FMT_MFC VL_FORMAT("[", "\n ", "]\n", VL_FMT_VF)

    vl_fprintf(stdout, "rot(pi/2, vl_x) is: " VL_FMT_MFC "\n", Rot3f(vl_x, vl_halfPi), 1, 0);

//    cout << "rot(pi/2, vl_x) is: " <<  Rot3f(vl_x, vl_halfPi) << endl;

    x = x * Rot3f(vl_x, vl_halfPi);
    cout << "x after rot(pi/2, vl_x) is: " << x << endl;
    x = x * Scale3f(Vec3f(0.3, 0.2, 0.3));
    cout << "x after scale(0.3, 0.2, 0.3) is: " << x << endl;

    Vec4f y = Vec4f(x, 0.5);
    cout << "y is: " << y << endl;
    x = proj(y);
    cout << "proj(y) is: " << x << endl;

    x = proj(HRot4f(vl_x, 1.3) * HTrans4f(vl_1) * HScale4f(Vec3f(1,2,1)) * y);
    cout << "HRot4(vl_x, 1.3) * HTrans4(vl_1) "
        "* HScale4(Vec3(1,2,1)) * y = " << x << endl;
}

void TestComparisons()
{
    cout << "\n+ TestComparisons\n" << endl;

    cout << (Mat2f(vl_0) == vl_0) << ":" << (Mat2f(vl_0) != vl_0) << endl;
    cout << (Mat3f(vl_0) == vl_0) << ":" << (Mat3f(vl_0) != vl_0) << endl;
    cout << (Mat4f(vl_0) == vl_0) << ":" << (Mat4f(vl_0) != vl_0) << endl;

    cout << (Mat2f(vl_1) == vl_0) << ":" << (Mat2f(vl_1) != vl_0) << endl;
    cout << (Mat3f(vl_1) == vl_0) << ":" << (Mat3f(vl_1) != vl_0) << endl;
    cout << (Mat4f(vl_1) == vl_0) << ":" << (Mat4f(vl_1) != vl_0) << endl;
}

int main(int, char **)
{
    cout << "Testing VL234 library" << endl;

    cout << "----------------------------------" << endl;

    Test2DStuff();
    Test3DStuff();
    Test4DStuff();

    TestH2DStuff();
    TestH3DStuff();

    TestComparisons();

    cout << "\n\n--- Finished! ---" << endl;

    return 0;
}
