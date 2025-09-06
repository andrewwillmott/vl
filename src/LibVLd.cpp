/*
    File:       LibVLd.cpp

    Purpose:    Compiles all code necessary for VLd.h.

    Copyright:  Andrew Willmott
*/

#define VL_V_ELT double
#define VL_V_SUFF(X) X ## d

#include "VL/Begin.h"

#include "VL/Constants.h"
#include "VL/Vec2.cpp"
#include "VL/Vec3.cpp"
#include "VL/Vec4.cpp"

#include "VL/Mat2.cpp"
#include "VL/Mat3.cpp"
#include "VL/Mat4.cpp"

#include "VL/Quat.cpp"
#include "VL/Transform.cpp"

#include "VL/Print234.cpp"
#include "VL/Stream234.cpp"

#include "VL/Vec.cpp"
#include "VL/VecSlice.cpp"

#include "VL/Mat.cpp"
#include "VL/MatSlice.cpp"

#include "VL/Vol.cpp"
#include "VL/VolSlice.cpp"

#include "VL/Solve.cpp"
#include "VL/Factor.cpp"

#include "VL/Print.cpp"
#include "VL/Stream.cpp"

#include "VL/End.h"
