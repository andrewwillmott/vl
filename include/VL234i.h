/*
    File:       VL234i.h

    Function:   Master header for a version of the VL library based on
                integers. The various classes are named Veci, Mat3i, etc.

    Copyright:  Andrew Willmott
 */


#ifndef VL234i_H
#define VL234i_H

#define VL_V_ELT int
#define VL_V_SUFF(X) X ## i

#include "VL/Begin.h"

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

#include "VL/End.h"

#endif
