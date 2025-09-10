/*
    File:       VLv3f.hpp

    Function:   Master header for Vecv3f, Matv3f, etc.

    Copyright:  Andrew Willmott
 */

#ifndef VLv3f_H
#define VLv3f_H

#include "VL234f.hpp"

#define VL_V_ELT Vec3f
#define VL_V_SUFF(X) X ## v3f
#define VL_NO_REAL

#include "VL/Begin.hpp"

// this shouldn't be necessary if we switch to requiring len() etc. to always return a scalar rather TElt.
inline Vec3f sqrt(Vec3f v) { return Vec3f(sqrtf(v[0]), sqrtf(v[1]), sqrtf(v[2])); }

#include "VL/Vec.hpp"
#include "VL/Mat.hpp"
#include "VL/Vol.hpp"

#include "VL/End.hpp"

#endif
