/*
    File:       VL234d.h

    Function:   Master header for a 2/3/4-dim version of the VL library based on
                doubles. The various classes are named Vec2d, Mat2d, ... Mat4d

    Copyright:  Andrew Willmott
 */


#ifndef VL234d_H
#define VL234d_H

#define VL_V_ELT double
#define VL_V_SUFF(X) X ## d

#include "VL/Begin.h"

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

#include "VL/End.h"

#endif
