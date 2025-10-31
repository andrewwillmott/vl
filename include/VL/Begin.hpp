/*
    File:       Begin.hpp

    Function:   Initial header file for the VL library. Provides macro
                definitions such that the library can be templated by type.

    Copyright:  Andrew Willmott
 */

#ifndef VL_H
#define VL_H

#define VL_VERSION "3.1.0"
#define VL_VER_NUM 30100

/*
    This header file is included before any other when compiling VL. Its purpose
    is to translate the types that VL is templated on (TElt, TVec2, TVec3,
    etc.), replacing them with real types. In this way the same code can be used
    to compile float-based, double-based, and other type-based versions of the
    vector and matrix routines.

    VL.hpp expects VL_V_ELT and VL_M_ELT to be set to the element types for
    vectors and matrices respectively, and the VL_V_SUFF and VL_M_SUFF macros to
    append a suffix indicating the vector or matrix type to their arguments.

    See VLf.hpp, and VLfd.hpp for examples of how this facility is used.
*/

#include <VLConfig.hpp>  // angle brackets to work around MSVC looking up in parent directories.
#include "Defs.hpp"

#include <cmath>  // TODO: could use tgmath.hpp instead to work around MSVC

#ifndef VL_V_ELT
    #error "VL base type not defined!"
#endif

#ifndef VL_V_SUFF
    #define VL_V_SUFF(X) X
#endif

#ifndef VL_M_ELT
    #define VL_M_ELT VL_V_ELT
    #define VL_M_SUFF(X) VL_V_SUFF(X)
#endif

#define VL_CS(NAME) VL_PREFIX(VL_V_SUFF(vl), NAME)

#define TElt            VL_V_ELT
#define TMElt           VL_M_ELT

#define TVec2           VL_V_SUFF(Vec2)
#define TMat2           VL_M_SUFF(Mat2)

#define TVec3           VL_V_SUFF(Vec3)
#define TMat3           VL_M_SUFF(Mat3)

#define TVec4           VL_V_SUFF(Vec4)
#define TQuat           VL_V_SUFF(Quat)
#define TMat4           VL_M_SUFF(Mat4)

#define TVec            VL_V_SUFF(Vec)
#define TRefVec         VL_V_SUFF(RefVec)
#define TSliceVec       VL_V_SUFF(SliceVec)
#define TConstVec       VL_V_SUFF(ConstVec)
#define TConstRefVec    VL_V_SUFF(ConstRefVec)
#define TConstSliceVec  VL_V_SUFF(ConstSliceVec)

#define TMVec           VL_M_SUFF(Vec)
#define TMRefVec        VL_M_SUFF(RefVec)
#define TMSliceVec      VL_M_SUFF(SliceVec)
#define TMConstVec      VL_M_SUFF(ConstVec)
#define TMConstRefVec   VL_M_SUFF(ConstRefVec)
#define TMConstSliceVec VL_M_SUFF(ConstSliceVec)

#define TMat            VL_M_SUFF(Mat)
#define TRefMat         VL_M_SUFF(RefMat)
#define TSliceMat       VL_M_SUFF(SliceMat)
#define TConstMat       VL_M_SUFF(ConstMat)
#define TConstRefMat    VL_M_SUFF(ConstRefMat)
#define TConstSliceMat  VL_M_SUFF(ConstSliceMat)

#define TVol            VL_M_SUFF(Vol)
#define TRefVol         VL_M_SUFF(RefVol)
#define TSliceVol       VL_M_SUFF(SliceVol)
#define TConstVol       VL_M_SUFF(ConstVol)
#define TConstRefVol    VL_M_SUFF(ConstRefVol)
#define TConstSliceVol  VL_M_SUFF(ConstSliceVol)

#define Scale2          VL_M_SUFF(Scale2)
#define CRot2           VL_M_SUFF(CRot2 )
#define RRot2           VL_M_SUFF(RRot2 )
#define Rot2            VL_M_SUFF(Rot2  )

#define Scale3          VL_M_SUFF(Scale3)
#define CRot3           VL_M_SUFF(CRot3 )
#define RRot3           VL_M_SUFF(RRot3 )
#define Rot3            VL_M_SUFF(Rot3  )

#define HScale3         VL_M_SUFF(HScale3 )
#define HCRot3          VL_M_SUFF(HCRot3  )
#define HRRot3          VL_M_SUFF(HRRot3  )
#define HRot3           VL_M_SUFF(HRot3   )
#define HCTrans3        VL_M_SUFF(HCTrans3)
#define HRTrans3        VL_M_SUFF(HRTrans3)
#define HTrans3         VL_M_SUFF(HTrans3 )

#define HScale4         VL_M_SUFF(HScale4 )
#define HCRot4          VL_M_SUFF(HCRot4  )
#define HRRot4          VL_M_SUFF(HRRot4  )
#define HRot4           VL_M_SUFF(HRot4   )
#define HCTrans4        VL_M_SUFF(HCTrans4)
#define HRTrans4        VL_M_SUFF(HRTrans4)
#define HTrans4         VL_M_SUFF(HTrans4 )

#include "Math.hpp"

VL_NS_BEGIN

#endif
