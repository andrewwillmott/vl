/*
    File:       VLu8.h

    Function:   Master header for Vecu8, Matu8, etc.

    Copyright:  Andrew Willmott
 */

#ifndef VLu8_H
#define VLu8_H

#include <stdint.h>

#define VL_V_ELT uint8_t
#define VL_V_SUFF(X) X ## u8
#define VL_NO_REAL
#define VL_PRINT_INT

#include "VL/Begin.h"

namespace
{
    inline uint8_t abs (uint8_t a) { return a; }
    inline uint8_t len (uint8_t a) { return a; }
}

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

#include "VL/Vec.h"
#include "VL/Mat.h"
#include "VL/Vol.h"

#include "VL/Print.h"
#include "VL/Stream.h"

#include "VL/End.h"

#undef VL_PRINT_INT
#undef VL_NO_REAL
#endif
