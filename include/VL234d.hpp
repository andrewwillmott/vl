/*
    File:       VL234d.hpp

    Function:   Master header for a 2/3/4-dim version of the VL library based on
                doubles. The various classes are named Vec2d, Mat2d, ... Mat4d

    Copyright:  Andrew Willmott
 */


#ifndef VL234d_H
#define VL234d_H

#define VL_V_ELT double
#define VL_V_SUFF(X) X ## d

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
