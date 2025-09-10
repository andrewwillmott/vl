/*
    File:       VLfd.hpp

    Function:   Master header for a version of the VL library based
                on floats and doubles: vectors are made up of
                floats, and matrices of doubles. The various classes
                are named Vecf, Mat3d, etc.

    Copyright:  Andrew Willmott
 */

#ifndef VLfd_H
#define VLfd_H

#include "VLd.hpp"
#include "VLf.hpp"

#define VL_V_ELT float
#define VL_V_SUFF(X) X ## f
#define VL_M_ELT double
#define VL_M_SUFF(X) X ## d
#define VL_MIXED

#include "VL/Begin.hpp"

#define VL_VEC2_H
#define VL_VEC_H
#define VL_MAT_H

#include "VL/Mixed.hpp"
#include "VL/Factor.hpp"
#include "VL/Solve.hpp"

#include "VL/End.hpp"

#endif
