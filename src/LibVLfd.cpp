/*
    File:       LibVLfd.cpp

    Purpose:    Compiles mixed float/double code.

    Copyright:  Andrew Willmott
*/

#include "VLd.h"

#define VL_V_ELT float
#define VL_V_SUFF(X) X ## f
#define VL_M_ELT double
#define VL_M_SUFF(X) X ## d
#define VL_MIXED

#include "VL/Begin.h"

#include "VL/Constants.h"
#include "VL/Vec2.h"
#include "VL/Vec3.h"
#include "VL/Vec4.h"
#include "VL/Vec.h"

#include "VL/Mixed.cpp"
#include "VL/Solve.cpp"
#include "VL/Factor.cpp"

#include "VL/End.h"
