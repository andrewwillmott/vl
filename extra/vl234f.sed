s/VL_NS_BEGIN//
s/VL_NS_END//
s/VL_V_SUFF(\([^)]*\))/\1f/
s/VL_M_SUFF(\([^)]*\))/\1f/
s/TElt/float/g
s/TVec2/Vec2f/g
s/TVec3/Vec3f/g
s/TVec4/Vec4f/g
s/TMat2/Mat2f/g
s/TMat3/Mat3f/g
s/TMat4/Mat4f/g
s/TQuat/Quatf/g
s/ Scale2/ Scale2f/g
s/ CRot2/ CRot2f/g
s/ RRot2/ RRot2f/g
s/ Rot2/ Rot2f/g
s/ Scale3/ Scale3f/g
s/ CRot3/ CRot3f/g
s/ RRot3/ RRot3f/g
s/ Rot3/ Rot3f/g
s/ HScale3/ HScale3f/g
s/ HCRot3/ HCRot3f/g
s/ HRRot3/ HRRot3f/g
s/ HRot3/ HRot3f/g
s/ HCTrans3/ HCTrans3f/g
s/ HRTrans3/ HRTrans3f/g
s/ HTrans3/ HTrans3f/g
s/ HScale4/ HScale4f/g
s/ HCRot4/ HCRot4f/g
s/ HRRot4/ HRRot4f/g
s/ HRot4/ HRot4f/g
s/ HCTrans4/ HCTrans4f/g
s/ HRTrans4/ HRTrans4f/g
s/ HTrans4/ HTrans4f/g
/\#include/d
/^\/\*/,/\*\//d
s/VL_VEC\([234]\)_H/VLF_VEC\1_H/g
s/VL_MAT\([234]\)_H/VLF_MAT\1_H/g
s/VL_SWIZZLE_H/VLF_SWIZZLE_H/g
s/VL_PRINT_234_H/VLF_PRINT_234_H/g
s/VL_STREAM_234_H/VLF_STREAM_234_H/g
