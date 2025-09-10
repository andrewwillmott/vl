/*
    File:       LibVLu8.cpp

    Function:   Instantiates code necessary for VLu8.hpp

    Copyright:  Andrew Willmott
*/

// To make the Mat stuff work, would need:
// - proper way of turning off sqrt() etc., or sqrt impl
//   - should dot() always return a scalar type?

#include <stdint.h>

#define VL_V_ELT uint8_t
#define VL_V_SUFF(X) X ## u8
#define VL_NO_REAL
#define VL_PRINT_INT

inline uint8_t abs(uint8_t u) { return u; }  // avoid warnings

#include "VL/Begin.hpp"

#include "VL/Constants.hpp"
#include "VL/Vec2.cpp"
#include "VL/Vec3.cpp"
#include "VL/Vec4.cpp"

#include "VL/Mat2.cpp"
#include "VL/Mat3.cpp"
#include "VL/Mat4.cpp"

#include "VL/Print234.cpp"
#include "VL/Stream234.cpp"

#include "VL/Vec.cpp"
#include "VL/VecSlice.cpp"

#include "VL/Mat.cpp"
#include "VL/MatSlice.cpp"

#include "VL/Vol.cpp"
#include "VL/VolSlice.cpp"

#include "VL/Print.cpp"
#include "VL/Stream.cpp"

#include "VL/End.hpp"
