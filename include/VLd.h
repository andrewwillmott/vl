/*
    File:       VLd.h

    Function:   Master header for a version of the VL library based on
                doubles. The various classes are named Vecd, Mat3d, etc.

    Copyright:  Andrew Willmott
 */


#ifndef VLd_H
#define VLd_H

#define VL_V_ELT double
#define VL_V_SUFF(X) X ## d

#include "VL/Begin.h"

// Allow interoperatibility with 234-only header
#ifndef VL234d_H
    #define VL234d_H
    #include "VL/Constants.h"
    #include "VL/Vec2.h"
    #include "VL/Vec3.h"
    #include "VL/Vec4.h"
    #include "VL/Swizzle.h"

    #include "VL/Mat2.h"
    #include "VL/Mat3.h"
    #include "VL/Mat4.h"

    #include "VL/Quat.h"
    #include "VL/Transform.h"

    #include "VL/Print234.h"
    #include "VL/Stream234.h"
#else
    #define VL_VEC2_H
    #define VL_MAT2_H
#endif

#include "VL/Vec.h"
#include "VL/Mat.h"
#include "VL/Vol.h"

#include "VL/Solve.h"
#include "VL/Factor.h"

#include "VL/Print.h"
#include "VL/Stream.h"

#include "VL/End.h"

#endif
