/*
    File:       LibVLv3f.cpp

    Function:   Instantiates code necessary for VLv3f.h

    Copyright:  Andrew Willmott
*/

#include "VL234f.h"

#define VL_V_ELT Vec3f
#define VL_V_SUFF(X) X ## v3f
#define VL_NO_SOLVE

#include "VL/Begin.h"

// this shouldn't be necessary if we switch to requiring len() etc. to always return a scalar rather TElt.
inline Vec3f sqrt(Vec3f v) { return Vec3f(sqrtf(v[0]), sqrtf(v[1]), sqrtf(v[2])); }

#include "VL/Vec.cpp"
#include "VL/VecSlice.cpp"

#include "VL/Mat.cpp"
#include "VL/MatSlice.cpp"

#include "VL/Vol.cpp"
#include "VL/VolSlice.cpp"

#include "VL/End.h"
