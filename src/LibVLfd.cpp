/*
    File:       LibVLfd.cpp

    Purpose:    Compiles mixed float/double code.

    Copyright:  Andrew Willmott
*/

#include "VLd.hpp"

#define VL_V_ELT float
#define VL_V_SUFF(X) X ## f
#define VL_M_ELT double
#define VL_M_SUFF(X) X ## d
#define VL_MIXED

#include "VL/Begin.hpp"

#include "VL/Constants.hpp"
#include "VL/Vec2.hpp"
#include "VL/Vec3.hpp"
#include "VL/Vec4.hpp"
#include "VL/Vec.hpp"

#include "VL/Mixed.cpp"
#include "VL/Solve.cpp"
#include "VL/Factor.cpp"

#include "VL/End.hpp"
