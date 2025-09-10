/*
    File:       VLu8.hpp

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

#include "VL/Begin.hpp"

namespace
{
    inline uint8_t abs (uint8_t a) { return a; }
    inline uint8_t len (uint8_t a) { return a; }
}

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

#include "VL/Vec.hpp"
#include "VL/Mat.hpp"
#include "VL/Vol.hpp"

#include "VL/Print.hpp"
#include "VL/Stream.hpp"

#include "VL/End.hpp"

#undef VL_PRINT_INT
#undef VL_NO_REAL
#endif
