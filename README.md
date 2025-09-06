# VL

This is a classic vector/matrix math library, requiring C++11. It's been mainly
used for graphics work over the years, so has the classic 2/3/4 vector and
square matrix types, plus associated functions, some transform support, and a
set of quaternion manipulation utilities. However, it also comes with
generically sized Vec and Mat classes, and a set of solvers and factorisation
routines.

The basic component types supported are float/double/int (e.g., Vec2f, Mat3d,
Vec4i), but these can be extended relatively easily.

The USP for this library is that its focus has been on keeping compile speeds
down, while still supporting ease of use. The main build time hit from including
a VL header is typically the `cmath` and `iostream` headers it brings in. (The
latter can be disabled if you are not using that functionality.) This is in
contrast to those libraries implemented entirely with templates, particularly
those that use template metaprogramming heavily. In VL, most of the
implementation is in the library, not the headers you include in each file.

A secondary feature is the use of a 'slice' type to allow in-place manipulation
of sub vectors and matrices, plus a few other tricks. Something that for
instance [numpy](https://numpy.org) has popularised in the scientific computing
sphere.

Documentation is available [here](doc/vl.md).

On Unix style platforms, the library can be built and installed as follows:

    cd build
    make install PREFIX=/usr/local  # (say)

However, you can also include it directly in your projects, by adding the
include directory, and then the src/LibVL*.cpp files for those types you're
using, plus src/VL. This is the usual approach for MSVC projects on Windows, as
there is not the same facility for system-installed development libraries there.

The [extra](extra) directory contains single .h/.cpp pairs for cut-down variants
of the library, for quick use in smaller projects.