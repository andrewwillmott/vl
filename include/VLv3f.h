/*
    File:       VLv3f.h

    Function:   Master header for Vecv3f, Matv3f, etc.

    Copyright:  Andrew Willmott
 */

#ifndef VLv3f_H
#define VLv3f_H

#include "VL234f.h"

#define VL_V_ELT Vec3f
#define VL_V_SUFF(X) X ## v3f
#define VL_NO_REAL

#include "VL/Begin.h"

// this shouldn't be necessary if we switch to requiring len() etc. to always return a scalar rather TElt.
inline Vec3f sqrt(Vec3f v) { return Vec3f(sqrtf(v[0]), sqrtf(v[1]), sqrtf(v[2])); }

#include "VL/Vec.h"
#include "VL/Mat.h"
#include "VL/Vol.h"

#include "VL/End.h"

#endif
