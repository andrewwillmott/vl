#include "VL234i.hpp"
#include "VL234f.hpp"

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
    Mat2i N; N.MakeDiag(2.0);
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
    Mat3i N; N.MakeDiag(2.0);
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
    Mat4i N; N.MakeDiag(2.0);
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

int main(int, char **)
{
    cout << "Testing VL234i library" << endl;

    cout << "----------------------------------" << endl;

    Test2DStuff();
    Test3DStuff();
    Test4DStuff();

    TestComparisons();

    cout << "\n\n--- Finished! ---" << endl;

    return 0;
}
