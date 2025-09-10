/*
    File:       LibVLi.cpp

    Function:   Instantiates code necessary for VLi.hpp

    Copyright:  Andrew Willmott
*/

#include <stdint.h>
#include <string.h>

#define VL_V_ELT int
#define VL_V_SUFF(X) X ## i

#define VL_NO_REAL
#define VL_PRINT_INT

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
