/*
    File:       VL234i.hpp

    Function:   Master header for a version of the VL library based on
                integers. The various classes are named Veci, Mat3i, etc.

    Copyright:  Andrew Willmott
 */


#ifndef VL234i_H
#define VL234i_H

#define VL_V_ELT int
#define VL_V_SUFF(X) X ## i

#include "VL/Begin.hpp"

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

#include "VL/End.hpp"

#endif
