/*
    File:       Constants.hpp

    Function:   Contains various constants for VL.

    Copyright:  Andrew Willmott
*/

#ifndef VL_CONSTANTS_H
#define VL_CONSTANTS_H

// --- Mathematical constants -------------------------------------------------

enum    VLDiag       { vl_I = 1, vl_minus_I = -1, vl_nI = -1 };
enum    VLBlock      { vl_zero = 0, vl_one = 1, vl_minus_one = -1, vl_0 = 0, vl_1 = 1, vl_n1 = -1 };
enum    VLAxis       { vl_x, vl_y, vl_z, vl_w };
enum    VLMinusAxis  { vl_minus_x, vl_minus_y, vl_minus_z, vl_minus_w, vl_nx = 0, vl_ny, vl_nz, vl_nw };

typedef VLAxis      vl_axis;        // e.g., Vecf(10, vl_axis(4)), Vec3f(vl_axis(i))
typedef VLMinusAxis vl_minus_axis;  // e.g., Vecf(10, vl_minus_axis(4))

const double vl_pi           = 3.14159265358979323846264338327950288;  // prefer vlf_pi, vld_pi etc.
const double vl_halfPi       = vl_pi / 2.0;
const double vl_quarterPi    = vl_pi / 4.0;
const double vl_twoPi        = vl_pi * 2.0;

#ifdef HUGE_VAL
    const float  vlf_huge = HUGE_VALF;
    const double vld_huge = HUGE_VAL;
#else
    const float  vlf_huge = 1e50f;
    const double vld_huge = 1e500;
#endif

const double vl_huge = vld_huge;

const float  vlf_eps = 1.19209290E-07F;
const double vld_eps = 2.2204460492503131e-016;

struct VLVecType { typedef void IsVec; typedef TElt Elt; };
struct VLMatType { typedef void IsMat; typedef TElt Elt; };
struct VLVolType { typedef void IsVol; typedef TElt Elt; };

#define VL_PREFIX_(PREFIX, NAME) PREFIX ## _ ## NAME
#define VL_PREFIX(PREFIX, NAME) VL_PREFIX_(PREFIX, NAME)
#define VL_CS(NAME) VL_PREFIX(VL_V_SUFF(vl), NAME)

#endif

#ifndef VL_NO_REAL
const TElt VL_CS(pi)        = TElt(3.14159265358979323846264338327950288);
const TElt VL_CS(halfPi)    = TElt(VL_CS(pi) / 2);
const TElt VL_CS(quarterPi) = TElt(VL_CS(pi) / 4);
const TElt VL_CS(twoPi)     = TElt(VL_CS(pi) * 2);
#endif
