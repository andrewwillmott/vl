/*
    File:       LibVL234f.cpp

    Purpose:    Compiles all code necessary for VL234f.hpp.

    Copyright:  Andrew Willmott
*/


#define VL_V_ELT float
#define VL_V_SUFF(X) X ## f

#include "VL/Begin.hpp"

#include "VL/Vec2.cpp"
#include "VL/Vec3.cpp"
#include "VL/Vec4.cpp"

#include "VL/Mat2.cpp"
#include "VL/Mat3.cpp"
#include "VL/Mat4.cpp"

#include "VL/Transform.cpp"

#include "VL/Print234.cpp"
#include "VL/Stream234.cpp"

#include "VL/End.hpp"
