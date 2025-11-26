/*
    File:       VLi.hpp

    Function:   Master header for Vec[]i, Mat[]i, etc.

    Copyright:  Andrew Willmott
 */

#ifndef VLi_H
#define VLi_H

#define VL_V_ELT int
#define VL_V_SUFF(X) X ## i

#define VL_NO_REAL
#define VL_PRINT_INT

#include "VL/Begin.hpp"

// Allow interoperatibility with 234-only header
#ifndef VL234i_H
    #define VL234i_H
    #include "VL/Constants.hpp"
    #include "VL/Vec2.hpp"
    #include "VL/Vec3.hpp"
    #include "VL/Vec4.hpp"
    #include "VL/Swizzle.hpp"

    #include "VL/Mat2.hpp"
    #include "VL/Mat3.hpp"
    #include "VL/Mat4.hpp"

    #include "VL/Print234.hpp"
    #include "VL/Stream234.hpp"
#else
    #define VL_VEC2_H
    #define VL_MAT2_H
#endif

#include "VL/Vec.hpp"
#include "VL/Mat.hpp"
#include "VL/Vol.hpp"

#include "VL/Print.hpp"
#include "VL/Stream.hpp"

#include "VL/End.hpp"

#endif
