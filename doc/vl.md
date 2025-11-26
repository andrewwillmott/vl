# VL: Vector Library (3.1)

## Contents

- [Introduction](#introduction)
- [Types](#types)
- [Element Access](#element-access)
- [Arithmetic Operators and Functions](#arithmetic-operators-and-functions)
- [Constants](#constants)
- [Constructors](#constructors)
- [Input and Output](#input-and-output)
- [Transformations](#transformations)
- [Sub Vectors and Matrices](#sub-vectors-and-matrices)
- [Solving Systems of Linear Equations](#solving-systems-of-linear-equations)
- [Factoring Matrices](#factoring-matrices)
- [Compiling with VL](#compiling-with-vl)

## Introduction

The "VL" vector library provides a set of vector and matrix classes, as well as
a number of functions for performing arithmetic with them. Equation-like syntax
is supported via C++ class operators, for example:

    #include "VLfd.hpp"

    Vec3f   v(1.0, 2.0, 3.0);
    Mat3d   m(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    v =  2 * v + m * v;
    v *= (m / 3.0) * norm(v);

    cout << v << endl;

Both generic (arbitrarily-sized), and fixed-size (2, 3 and 4 element) vectors
and matrices are supported. The latter are provided for the efficient
manipulation of vectors or points in 2D or 3D space.

Vectors and matrices can be composed of either floats or doubles; the element
type is indicated by the suffix. It is possible to mix (for example) matrices of
doubles with vectors of floats, as in the example above. It is also possible to
instantiate VL for other other element types with their own suffixes. (E.g.,
complex numbers.) See the various VL*.hpp and LibVL*.cpp files for examples.

VL also contains extensive support for sub-vector/matrices (slices), and
implementations of some iterative solvers and factorisation routines.

VL has a different design to that of many of the other C++ vector libraries out
there, as it uses C macros to build the various types from a common set of
headers, rather than C++ templates. The primary reason for this old-school
approach is to keep the compile-time costs of using the library down, as the
latter approach leads to the entire source library being parsed when used. VL
also tries to avoid the poor debug performance of meta-programming oriented
libraries, not least because the author has observed that this deeply nested
style can defeat the optimizer in release builds too.

VL requires C++11. It's unlikely this requirement will be raised further.

VL is free for commercial and non-commercial use; see the LICENSE file for
redistribution conditions. (These apply only to the source code; binaries may be
freely redistributed, no strings attached.)

## Types

VL contains the following types by default, where f=float, d=double, i=int:

    Fixed-size:
        Vec2[fdi]       2-vector
        Vec3[fdi]       3-vector
        Vec4[fdi]       4-vector
        Mat2[fdi]       2 x 2 matrix
        Mat3[fdi]       3 x 3 matrix
        Mat4[fdi]       4 x 4 matrix

    Generic:
        [Const]Vec[fd]          n-vector with associated storage
        [Const]Mat[fd]          n x m matrix with associated storage
        [Const]RefVec[fd]       dense vector reference. Use in preference to const Vecd& etc.
        [Const]RefMat[fd]       dense vector reference. Use in preference to Vecd& etc.
        [Const]SliceVec[fd]     n-vector which is a subset of a dense vector
        [Const]SliceMat[fd]     n x m matrix which is a subset of a dense matrix

The use of the 'Const' prefixes allows more complete const protection than the
somewhat limited C++ type system can allow otherwise. The Ref* and Slice*
classes can be used to wrap external data for use with the rest of the library,
particularly bare C-style arrays. See the corresponding constructors.

If you only need the 2/3/4 types and basic operations, use includes of the form:

    #include "VL234f.hpp"
    #include "VL234i.hpp"

For the full library, including the generic Vec/Mat classes, use, e.g.,

    #include "VLf.hpp"
    #include "VLd.hpp"

If you want to use double-based matrices that act on float-based vectors, which
can be a useful space versus accuracy trade-off, use

    #include "VLfd.hpp"

Further details can be found in the [compiling section](#compiling-with-vl).

## Element Access

The elements of a vector or matrix are accessed with standard C array notation:

    v[2] = 4.0;         // set element 2 of the vector
    m[3][4] = 5.0       // set row 3, column 4 of the matrix
    m[2] = v;           // set row 2 of the matrix

For matrices an element can also be accessed using standard row/column notation:

    m(3, 4) = 5.0;      // set row 3, column 4 of the matrix

For the 2/3/4 types, you can also use direct access:

    v2.x = 3.0;
    m3.z.y = v2.y;      // See also VL/Swizzle.hpp

The size can be obtained from the Elts() method for vectors, and the Rows() and
Cols() methods for matrices. (These are constants for the fixed types.) To
iterate over all members of these types, you can use code of the form:

    for (int i = 0; i < v.Elts(); i++)
        v[i] = i;

    for (int i = 0; i < m.Rows(); i++)
        for (int j = 0; j < m.Cols(); j++)
            m[i][j] = i + j;

If you need a pointer to the data belonging to a vector or matrix, use the Ref()
method. (Note that matrices are stored by row.)

    float* vecDataPtr = v.Ref();
    float* matDataPtr = m.Ref();

**Warning:** Any pointer to the data of a generic matrix or vector will become
invalid as soon as it is resized.

**Note:** If you compile with -DVL_DEBUG, index range checks will be performed
on all element accesses.

## Arithmetic Operators and Functions

### Arithmetic Operators

The following binary operators are defined for all vector and matrix classes, as
long as both operands are of the same type.

    Basic arithmetic:         + - * /
    Accumulation arithmetic:  += -= *= /=
    Comparison:               ==, !=

Vector multiplication and division is component-wise: `(a * b)[i] = a[i] * b[i]`.
(See below for how to form the dot product of two vectors with dot().)

Matrix multiplication is defined in the usual way. For component-wise matrix
multiplication, see hprod below. For both matrices and vectors, multiplication
and division by a scalar is always allowed.

Matrices can be multiplied either on the left or the right by a vector. In the
expression m * v, v is treated as a column vector; in the expression v * m, it
is treated as a row vector.

### Vector Functions

The following is a list of the various vector functions, together with a short
description of what they return.

    float   dot      (Vec a, Vec b);        // inner product of a and b
    float   len      (Vec v);               // length of v: || v ||
    float   sqrlen   (Vec v);               // length of v, squared
    VecN    norm     (Vec v);               // v / || v ||
    VecN    norm_safe(Vec v);               // v / || v ||, handles || v || = 0.

    Vec2    cross(Vec2 a);                  // vector ccw orthogonal to a
    Vec3    cross(Vec3 a, Vec3 b);          // vector orthogonal to a and b
    Vec4    cross(Vec4 a, Vec4 b, Vec4 c);  // vector orthogonal to a, b and c
    Vec3    cross_x(Vec3 v);                // v x e_x
    Vec3    cross_y(Vec3 v);                // v x e_y
    Vec3    cross_z(Vec3 v);                // v x e_z

    VecN    inv(Vec v);                     // inverse: 1 / v
    VecN    abs(Vec v);                     // abs(v_i)

    Vec2    proj(Vec3 v);                   // homogenous projection: v[0..1] / v[2]
    Vec3    proj(Vec4 v);                   // homogenous projection: v[0..2] / v[3]

In the above, VecN is either a Vec or a Vec[234], and you should append 'f' or
'd' as usual. For more on the use of the proj() operator, see
[Transformations](#transformations).

With the full version of the library, you can also use various standard math
component-wise functions, such as sin(v), cos(v), ceil(v), and floor(v). See
`VL/Ops.hpp` for the full list.

### Matrix Functions

The following functions can be used with matrices.

    Mat   transpose(Mat m);         // Transpose of m
    Elt   trace    (Mat m);         // Trace of m
    Mat   adj      (Mat m);         // Adjoint of m
    Elt   det      (Mat m);         // Determinant of m
    Mat   inv      (Mat m);         // Inverse of m, if it exists.

    Elt   sum      (Mat m);         // ∑ m_i_j
    Mat   abs      (Mat m);         // | m_i_j |
    Mat   hprod    (Mat m, Mat n);  // Hadamard product: component-wise multiply
    Mat   oprod    (Vec b, Vec b);  // Outer product: a_t b

Here Mat is any matrix type, and Elt its corresponding element type, though
the det() and adj() functions are only defined for Mat[234][fd]. For Mat[fd],
inv() can optionally return the determinant, and the following additional
functions are supported:

    Elt   sumsqr   (Mat m);         // Sum of elements squared
    Elt   frob     (Mat m);         // Frobenius norm: sqrt(sumsqr(m))
    Mat   hprod    (Mat a, Mat b);  // Hadamard product: component-wise multiply of a and b
    Mat   oprod    (Vec a, Vec b);  // Outer product: a_t b


## Constants

There are a number of constants in VL that can be used to initialise vectors or
matrices with simple assignment statements or constructors. For example:

    Vec3f v; Mat3f m; Vecf v8(8);

    v = vl_0;           // [0, 0, 0]
    v = vl_y;           // [0, 1, 0]
    v = vl_1;           // [1, 1, 1]
    v = vl_minus_one;   // [-1, -1, -1]

    m = vl_0;           // 3 x 3 matrix, all elts. set to zero.
    m = vl_1;           // 3 x 3 matrix, all elts. set to one.
    m = vl_I;           // 3 x 3 identity matrix

    v8 = vl_axis(6);    // [0, 0, 0, 0, 0, 0, 1, 0]

Below is a summary of the constants defined by VL.

    vl_one/vl_1                   vector or matrix of all ones
    vl_minus_one/vl_n1            vector or matrix of negative ones
    vl_zero/vl_0                  vector or matrix of all zeroes
    vl_I                          identity matrix
    vl_x, vl_y, vl_z, vl_w        x, y, z and w +ve axis vectors
    vl_nx, vl_ny, vl_nz, vl_nw    x, y, z and w -ve axis vectors
    vl_axis(n)                    zero vector with element n set to 1
    vl_minus_axis(n)              zero vector with element n set to -1

    vl[fd]_pi                     pi
    vl[fd]_halfPi                 pi / 2
    vl[fd]_quarterPi              pi / 4
    vl[fd]_twoPi                  pi x 2

## Constructors

In general, a vector or matrix constructor should be given either one of the
initialiser constants listed above, or a list of values for its elements. If
neither of these is supplied, the elements will be uninitialised. The first
arguments to the constructor of a generic vector or matrix should always be the
required size. Thus matrices and vectors are declared as follows:

    Vec[fd][234]    v([initialisation_constant | element_list]);
    Vec[fd]         v([elements, [initialisation_constant | element_list]]);
    Mat[fd][234]    m([initialisation_constant | element_list]);
    Mat[fd]         m([rows, columns, [initialisation_constant | element_list]]);

If generic vectors or matrices are not given a size when first created, they are
regarded as empty, with no associated storage. This state persists until they
are assigned a matrix/vector or the result of some computation, at which point
they take on the dimensions of that result.

Examples:

    Vec3f    v(vl_1);
    Vec3f    v(1.0f, 2.0f, 3.0f);
    Vecf     v(6, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
    Vecf     v({ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f });  // initializer_list version
    Vecf     v(20, vl_axis(10));
    Mat2f    m(1.0f, 2.0f, 3.0f, 4.0f);
    Matf     m(10, 20, vl_I);

**Warning:** When initialising a generic vector or matrix with a list of
elements, you must ensure none of them are specified as integers. (This is due
to limitations of the stdarg package.) I.e., use '2.0' or '2.0f' rather than
just '2'. Or, use the std::initializer_list variants instead.

Finally, to set the size of a empty matrix or vector explicitly, or resize an
existing matrix or vector, use the SetSize method:

    v.SetSize(23);
    m.SetSize(10, 20);

## Input and Output

All of the vector and matrix types in VL can be used in iostream-type
expressions. For example:

    Vec3d v(vl_1);
    std::cout << v << 2 * v << std::endl;
    std::cin >> v;

will output

    [1 1 1][2 2 2]

and then prompt for input. Vectors and matrices are parsed in the same format
that they are output: vectors are delimited by square brackets, elements
separated by white space, and matrices consist of a series of row vectors, again
delimited by square brackets.

For those who prefer the classic `stdio.h` fprintf-style APIs, and in particular
their more explicit control over formatting, the following functions are
available:

    int vl_fprint(FILE* file, Vec v);  // Print vector to 'file', e.g., stdout
    int vl_fprint(FILE* file, Mat m);  // Print matrix to 'file', e.g., stdout

    int vl_fprintf(FILE* file, const char* format, Vec v);    // Print according to format
    int vl_fprintf(FILE* file, const char* format, Mat m);    // Print according to format

    int vl_fprint_as_c(FILE* file, const char* name, Vec v);  // Print as C code
    int vl_fprint_as_c(FILE* file, const char* name, Mat m);  // Print as C code

The corresponding vl_print[f]() calls that use `stdout` for `file` are also
available.

These calls all take the width and precision as additional arguments. The
'format' argument is one of `VL_FMT_[VM][FI][_STYLE]`, e.g., VL_FMT_MF for a
float-based matrix. You can also add a prefix and/or a suffix inline if desired,
e.g.,

    vl_printf("Result: " VL_FMT_VF "\n", Vec4f(1.1f));

will output

    Result: [1.100 1.100 1.100 1.100]

See `VL/PrintBase.hpp` for the full list of formats, plus how to define your
own.

Similarly, there are a range of snprintf-style calls for writing to buffers
rather than files. These include a set of 'ssprintf' adapters for STL-like
string containers, e.g.,

    std::string result;
    vl_ssprint(result, v1);
    vl_ssprint_append(result, " + " VL_FMT_VF "\n", v2);

**Note:** If only using the stdio-style API, you may wish to define
VL_NO_IOSTREAM to avoid the compile time hit of the `<iostream>` include. If
you use neither API, define VL_NO_STDIO as well.

## Transformations

The following are the 234-d transformations supported by VL.

    Mat2  [RC]Rot2  (Elt theta)            // Rotate a 2d vector CCW by theta
    Mat2      Scale2(Vec2 s)               // Scale 2d vector by s

    Mat3 H[RC]Rot3  (Elt theta)            // Rotate a 2d point CCW by theta
    Mat3 H    Scale3(Vec2 s)               // Scale 2d point by s
    Mat3 H[RC]Trans3(Vec2 t)               // Translate a 2d point by t

    Mat3  [RC]Rot3  (Vec3 axis, Elt theta) // Rotate a 3d vector CCW around axis by theta
    Mat3  [RC]Rot3  (Vec4 q)               // Rotate a 3d vector by the quaternion q
    Mat3      Scale3(Vec3 s)               // Scale 3d vector by s

    Mat4 H[RC]Rot4  (Vec3 axis, Elt theta) // Rotate a 3d point CCW around axis by theta
    Mat4 H[RC]Rot4  (Vec4 q)               // Rotate a 3d point by the quaternion q
    Mat4 H    Scale4(Vec3 s)               // Scale 3d point by s
    Mat4 H[RC]Trans4(Vec3 t)               // Rranslate a 3d point by t

Transformations with a prefix of 'H' operate in the homogeneous coordinate
system, which allows translation and shear transformations, as well as the usual
rotation and scale. In this coordinate system an n-vector is embedded in a
(n+1)-dimensional space, e.g., a homogeneous point in 2d is represented by a
3-vector, with 1 in the last component.

To convert from non-homogeneous to homogeneous vectors, simply cast to the
next-higher-dimension vector, supplying the extra coordinate. To project from a
homogeneous vector down to a non-homogeneous one (performing a homogeneous
divide in the process), use the proj() function. This process can be simplified
by the use of the xform() function, which applies a transform to a vector or
composes two transformations, performing homogeneous/non-homogeneous conversions
as necessary. For example:

    Vec3d x,y = ...;

    // apply homogeneous transformations to a 3-vector, assuming column vectors
    x = proj(Scale4d(...) * Trans4d(...) * Vec4d(y, 1.0));

    // do the same thing with xform()
    x = xform(xform(Scale4d(...), Trans4d(...)), y);

By default, VL assumes that transformations should operate on column vectors (v
= T * v), though it can be compiled to assume row vectors instead (v = v * T),
by using VL_ROW_ORIENT. Using the xform functions is a good way of isolating
yourself from this assumption.

Alternatively, you can use row- and column- specific version of the transforms,
by adding 'R' or 'C' to the function names as above. (Scale transforms do not
require this distinction, as they are symmetric.)

### Quaternions

As above, VL includes support for using quaternions to represent 3D rotations in
addition to 3x3 matrices. Quaternions are a Vec4 (typedef'd to Quat[fd] for
convenience), where xyz is the vector part, and w is the scalar part. The former
can be interpreted as the axis of rotation, and the latter as being related to
the angle of rotation, specifically, cos(theta/2). To be a valid rotation, the
quaternion must be normalized.

Quaternions can be constructed as follows:

    Quat MakeQuat(Vec3 a, Vec3 b);        // Returns a quaternion representing the rotation from a to b
    Quat MakeQuat(Vec3 axis, Elt theta);  // Returns a quaternion rotation about 'axis' by 'theta'

    Quat MakeQuat[XYZ](Elt theta);        // Returns a rotation about the x/y/z axis by 'theta'

Where theta is in radians. The library supports the classic operations:

    Vec3 QuatApply(Vec3 p, Quat q);       // Transform point p by applying quaternion q
    Quat QuatMult (Quat a, Quat b);       // Concatenate quaternions, the result represents applying 'a' then 'b'.
    Quat QuatInv  (Quat q);               // Quaternion inverse.

Quaternions are often used for interpolating between rotations. Two options
for this are provided:

    Quat SLerp(Quat q1, Quat q2, Elt s);  // Return spherical interpolation between q1 and q2
    Quat NLerp(Quat q1, Quat q2, Elt s);  // Return linear interpolation between q1 and q2 with a renormalisation step

SLerp is the traditional function for this, but NLerp can be used as a fast
replacement when taking small steps, as is often the case in animation.

Finally, quaternions can be interchanged with 3x3 rotation matrices via:

    Quat MakeQuatFrom[CR]Rot(Mat3 rot3);  // Make quaternion from column/row-based rotation matrix.
    Mat3 [CR]RotFromQuat(Quat q);         // Return the equivalent column/row-based rotation matrix for q

Further more specialised operations can be found in `VL/Quat.hpp`.

## Sub Vectors and Matrices

VL provides the following functions for accessing sub-regions of vectors and
matrices:

    RefVec   sub    (Vec v, int start, int length);
    RefVec   first  (Vec v, int length);
    RefVec   last   (Vec v, int length);

    SliceMat sub      (Mat m, int top, int left, int height, int width);
    SliceMat first    (Mat v, int rows, int cols);  // first (upper-left) rows/cols of matrix
    SliceMat last     (Mat v, int rows, int cols);  // last (lower-right) rows/cols of matrix
    SliceVec col      (Mat m, int i);
    SliceVec row      (Mat m, int i);
    SliceVec diag     (Mat m, int i);  // -i = diagonal starting on row i, +i = diagonal starting on col i

The utility of these functions is best illustrated with some examples:

    u = sub (v, 2, 4);        // return the 4 elements of v starting at element 2.
    u = first(v, 2);          // return the first 2 elements of v.
    u = last (v, 2);          // return the last 2 elements of v.

    v = m[i];                 // extract row i of m
    v = col(m, i);            // extract column i of m
    v = row(m, i);            // extract row i of m

    v = diag(m);              // extract main diagonal of m
    v = diag(m, i)            // extract diagonal starting on column i
    v = diag(m, -i)           // extract diagonal starting on row i

    n = sub(m, 2, 3);         // returns the upper-left 2 rows and three columns of m.
    n = sub(m, i, j, 2, 3);   // returns the 2 rows and 3 columns of m starting at
                              // row i, column j.

The results above are `Ref` or `Slice` types, meaning they can be used in a
zero-copy way with other library operations. For instance:

    sub(m, 2, 2) = sub(m, 2, 2) + Matf(2, 2, vl_1); // add 1 to each of the upper-left 2 x 2 elts. of m.
    diag(m) *= 2.0;                                 // multiply diagonal elements of m by 2

The slice approach also allows these additional useful operations:

    SliceVec reverse(Vec v);           // Returns reversed vector
    SliceVec repeat (Elt elt, int n);  // Returns vector of 'elt' repeated 'n' times

    SliceMat transpose(Mat m);         // Zero-copy transpose of 'm'
    SliceMat repeat   (Elt elt, int rows, int cols);  // return elt repeated for the given rows/cols count
    SliceMat repeat   (Vec v,   int rows);            // returns given vector repeated 'rows' times

## Solving Systems of Linear Equations

VL comes with a number of solvers, which are routines for finding the solution
of the linear system of equations Ax = b. Currently these include
`SolveOverRelax()`, which uses the overrelaxation form of Gauss-Seidel iteration,
and `SolveConjGrad()`, which uses the conjugate gradient algorithm.

The solvers are defined as follows:

    Elt SolveOverRelax(Mat A, RefVec x, ConstRefVec b, Elt epsilon, Elt omega = 1.0, int* steps = 0);
    Elt SolveConjGrad(Mat A, RefVec x, ConstRefVec b, Elt epsilon, int* steps = 0);

The conjugate gradient solver is asymptotically faster than Gauss-Seidel, but it
assumes that A is both positive definite and symmetric. If A is not symmetric,
the routine instead solves the system 0.5(A + AT)x = b.

### Parameters

Each iteration of a solver modifies the current approximate solution x. You must
set x to an initial guess before first calling the solver routine; a good
starting value is often just b.

The solvers return the squared residual of the linear system, ||Ax - b||^2,
which is a measure of the error in the solution.

The epsilon parameter controls the accuracy of the solution: the solver will
return as soon as its estimate of the squared residual drops below epsilon.

For `SolveOverRelax`, omega controls the amount of overrelaxation. A value of
one gives pure Gauss-Seidel iteration. Values higher than that cause the solver
to overshoot towards the estimated solution on each iteration. If the system is
smooth and well behaved, this can lead to faster convergence times. Generally,
setting omega somewhere between 1 and 2 results in the fastest convergence rate,
but the exact value is system-specific.

If you want, you can supply a maximum number of iterations to perform via steps.
In this case, the routines will set the actual number of interations performed
when they return. This can be useful if you wish to interleave steps of the
solver with some other activity.

### Examples

    // Solve Ax = b from an initial guess of x = b
    x = b;
    SolveOverRelax(A, x, b, 1e-6);

    // Perform one iteration of the conjugate gradient solver
    int steps = 1;
    error = SolveConjGrad(A, x, b, 0, &steps);

## Factoring Matrices

VL contains two routines for factoring matrices; the QR factorization, and the
SVD (singular value decomposition). The former factors any given matrix A into
two matrices Q and R, such that A = QR. The Q matrix is orthogonal, and the R
matrix is upper-triangular.

The SVD decomposes an m x n matrix A into three matrices, A = U D Vt, where:

* U is m x n, and orthogonal.
* D is n x n, and is diagonal and positive semi-definite; its elements are the
  square roots of the eigenvalues of At A.
* V is n x n, and orthogonal.

The SVD has the following interesting properties:

* The SVD says that we can view any matrix transformation as: rotate the vector
  from source space, scale about the axes, and rotate the vector again into the
  destination space.
* The matrix's condition number is the ratio of the largest entry of D to the
  smallest.
* U and Vt are column-orthonormal.
* The smallest least squares solution of Ax = b is x = V F Ut b, where F = 1 /
  D, but with zero entries on the diagonal of D kept as zero rather than
  replaced with their inverse.

The factoring routines are defined as follows:

    #include "VLFactor.hpp"

    void QRFactorization (RefMat A, RefMat Q, RefMat R);
    void SVDFactorization(RefMat A, RefMat U, RefMat V, RefVec diagonal);

Both routines destroy the input matrix, `A`. Currently, it is required that `A`
have the same or more rows than columns. If your matrix has more columns than
rows, add enough zero rows to the bottom of it to make it square.

## Compiling with VL

### Headers

You should include one of the following:

    VL234f.hpp   Just Vec2/3/4f and Mat2/3/4f and Quatf
    VL234i.hpp   Vec2/3/4i and Mat2/3/4i
    VLf.hpp      Float version: all of Vec[234]f and Mat[234]f
    VLd.hpp      Double version: all of Vec[234]d and Mat[234]d
    VLfd.hpp     Mixed version: matrices use doubles, vectors use floats.

The last variant is useful in the situation where you want the lower storage of
floats, but can't afford the loss of precision inherent in float-based matrix
transformations.

### Linking

For your final build, link with -lvl (libvl.a). To use the debugging version of
VL, which has assertions and range checking turned on, use -lvld (libvld.a), and
add -DVL_DEBUG to your compile flags. This debugging version includes checks for
correct matrix and vector sizes during arithmetic operations.

If including directly in your own project, add just the LibVL* variants you are
using, e.g., `LibVLf.cpp` for all float-based operations.

### Compile options

VL uses the following compile-time options:

    VL_DEBUG        - turn on index checking and assertions
    VL_ROW_ORIENT   - default transformations operate on row vectors instead of column vectors
    VL_NEW/DELETE   - optionally define to your own new/delete operators
    VL_ASSERT_FULL  - optionally define to hook in your own assert system

However, rather than using VL_ROW_ORIENT, consider instead using the explicit
R/C function variants.
