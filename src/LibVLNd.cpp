/*
    File:       LibVLNd.cpp

    Purpose:    Compiles all code necessary for VLNd.h.

    Copyright:  Andrew Willmott
*/


#define VL_V_ELT double
#define VL_V_SUFF(X) X ## d

#include "VL/Begin.h"

#include "VL/Vec.cpp"
#include "VL/VecSlice.cpp"

#include "VL/Mat.cpp"
#include "VL/MatSlice.cpp"

#include "VL/Solve.cpp"
#include "VL/Factor.cpp"

#include "VL/End.h"