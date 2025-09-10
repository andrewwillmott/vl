/*
    File:       VLf.hpp

    Function:   Master header for a version of the VL library based on
                floats. The various classes are named Vecf, Mat3f, etc.

    Copyright:  Andrew Willmott
 */


#ifndef VLf_H
#define VLf_H

#define VL_V_ELT float
#define VL_V_SUFF(X) X ## f

#include "VL/Begin.hpp"

// Allow interoperatibility with 234-only header
#ifndef VL234f_H
    #define VL234f_H
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
