/*
    File:       LibVLNf.cpp

    Purpose:    Compiles all code necessary for VLNf.h.

    Copyright:  Andrew Willmott
*/


#define VL_V_ELT float
#define VL_V_SUFF(X) X ## f

#include "VL/Begin.h"

#include "VL/Vec.cpp"
#include "VL/VecSlice.cpp"

#include "VL/Mat.cpp"
#include "VL/MatSlice.cpp"

#include "VL/SparseVec.cpp"
#include "VL/SubSVec.cpp"

#include "VL/SparseMat.cpp"
#include "VL/SubSMat.cpp"

#include "VL/Solve.cpp"
#include "VL/Factor.cpp"

#include "VL/End.h"
