/*
    File:       VLi.h

    Function:   Master header for Vec[]i, Mat[]i, etc.

    Copyright:  Andrew Willmott
 */

#ifndef VLi_H
#define VLi_H

#define VL_V_ELT int
#define VL_V_SUFF(X) X ## i

#define VL_NO_REAL
#define VL_PRINT_INT

#include "VL/Begin.h"

// Allow interoperatibility with 234-only header
#ifndef VL234i_H
    #define VL234i_H
    #include "VL/Constants.h"
    #include "VL/Vec2.h"
    #include "VL/Vec3.h"
    #include "VL/Vec4.h"
    #include "VL/Swizzle.h"

    #include "VL/Mat2.h"
    #include "VL/Mat3.h"
    #include "VL/Mat4.h"
    
    #include "VL/Print234.h"
    #include "VL/Stream234.h"
#else
    #define VL_VEC2_H
    #define VL_MAT2_H
#endif

#include "VL/Vec.h"
#include "VL/Mat.h"
#include "VL/Vol.h"

#include "VL/Print.h"
#include "VL/Stream.h"

#include "VL/End.h"

#undef VL_PRINT_INT
#undef VL_NO_REAL

#endif
