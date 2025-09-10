/*
    File:       End.hpp

    Function:   Undefines the type macros used by Begin.hpp, so that that
                file can be re-included, usually with different types.
                See VLfd.hpp, for example.

    Copyright:  Andrew Willmott

 */

VL_NS_END

#undef VL_H
//#undef VL_VERSION

#undef TElt
#undef TMElt
#undef TVec2
#undef TMat2
#undef TVec3
#undef TMat3
#undef TVec4
#undef TMat4
#undef TQuat

#undef TVec
#undef TRefVec
#undef TSliceVec
#undef TConstVec
#undef TConstRefVec
#undef TConstSliceVec

#undef TMVec
#undef TMRefVec
#undef TMSliceVec
#undef TMConstVec
#undef TMConstRefVec
#undef TMConstSliceVec

#undef TMat
#undef TRefMat
#undef TSliceMat
#undef TConstMat
#undef TConstRefMat
#undef TConstSliceMat

#undef TVol
#undef TRefVol
#undef TSliceVol
#undef TConstVol
#undef TConstRefVol
#undef TConstSliceVol

#undef Scale2
#undef Rot2

#undef Scale3
#undef Rot3
#undef HScale3
#undef HRot3
#undef HTrans3

#undef HScale4
#undef HRot4
#undef HTrans4

#undef VL_V_ELT
#undef VL_M_ELT
#undef VL_V_SUFF
#undef VL_M_SUFF

#undef VL_VEC_H
#undef VL_VEC_SLICE_H
#undef VL_VEC2_H
#undef VL_VEC3_H
#undef VL_VEC4_H
#undef VL_MAT_H
#undef VL_MAT_SLICE_H
#undef VL_MAT2_H
#undef VL_MAT3_H
#undef VL_MAT4_H
#undef VL_QUAT_H
#undef VL_TRANSFORM_H
#undef VL_VOL_H
#undef VL_VOL_SLICE_H
#undef VL_SOLVE_H
#undef VL_FACTOR_H
#undef VL_STREAM_H
#undef VL_STREAM_234_H
#undef VL_PRINT_H
#undef VL_PRINT_234_H

#undef VL_OPS_H
#undef VL_OPS
#undef VL_OPS_INTEROP1
#undef VL_OPS_INTEROP2
