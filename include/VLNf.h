/*
    File:       VLNf.h

    Function:   Master header for Vecf, Matf, etc.

    Copyright:  Andrew Willmott
 */


#ifndef VLf_H
#define VLf_H

#define VL_V_REAL float
#define VL_V_SUFF(X) X ## f

#include "VL.h"

#include "VLVec.h"
#include "VLMat.h"
#include "VLVol.h"

#include "VLSolve.h"
#include "VLFactor.h"

#include "VL/Print.h"
#include "VL/Stream.h"

#include "VLUndef.h"

#endif
