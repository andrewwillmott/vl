/*
    File:       VL234f.hpp

    Function:   Master header for a 2/3/4-dim version of the VL library based on
                floats. The various classes are named Vec2f, Mat2f, ... Mat4f

    Copyright:  Andrew Willmott
 */


#ifndef VL234f_H
#define VL234f_H

#define VL_V_ELT float
#define VL_V_SUFF(X) X ## f

#include "VL/Begin.hpp"

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

#include "VL/End.hpp"

#endif
