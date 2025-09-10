/*
    File:       VLd.hpp

    Function:   Master header for a version of the VL library based on
                doubles. The various classes are named Vecd, Mat3d, etc.

    Copyright:  Andrew Willmott
 */


#ifndef VLd_H
#define VLd_H

#define VL_V_ELT double
#define VL_V_SUFF(X) X ## d

#include "VL/Begin.hpp"

// Allow interoperatibility with 234-only header
#ifndef VL234d_H
    #define VL234d_H
    #include "VL/Constants.hpp"
    #include "VL/Vec2.hpp"
    #include "VL/Vec3.hpp"
    #include "VL/Vec4.hpp"
    #include "VL/Swizzle.hpp"

    #include "VL/Mat2.hpp"
    #include "VL/Mat3.hpp"
    #include "VL/Mat4.hpp"

    #include "VL/Quat.hpp"
    #include "VL/Transform.hpp"

    #include "VL/Print234.hpp"
    #include "VL/Stream234.hpp"
#else
    #define VL_VEC2_H
    #define VL_MAT2_H
#endif

#include "VL/Vec.hpp"
#include "VL/Mat.hpp"
#include "VL/Vol.hpp"

#include "VL/Solve.hpp"
#include "VL/Factor.hpp"

#include "VL/Print.hpp"
#include "VL/Stream.hpp"

#include "VL/End.hpp"

#endif
