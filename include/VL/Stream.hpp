/*
    File:       Stream.hpp

    Function:   iostream support

    Copyright:  Andrew Willmott
 */

#ifndef VL_NO_IOSTREAM

#ifndef VL_STREAM_H
#define VL_STREAM_H

VL_NS_END
#include <iostream>
VL_NS_BEGIN

class TVec;
class TConstRefVec;
class TSliceVec;
class TConstSliceVec;

class TMat;
class TConstRefMat;
class TSliceMat;
class TConstSliceMat;

class TVol;
class TConstRefVol;
class TSliceVol;
class TConstSliceVol;

class TSparseVec;
class TSubSVec;
class TSparseMat;
class TSubSMat;

std::ostream& operator << (std::ostream& s, TConstRefVec v);
std::istream& operator >> (std::istream& s, TVec& v);
std::ostream& operator << (std::ostream& s, TConstSliceVec v);
std::istream& operator >> (std::istream& s, TSliceVec v);
std::ostream& operator << (std::ostream& s, const TSparseVec& v);
std::istream& operator >> (std::istream& s, TSparseVec& v);
std::ostream& operator << (std::ostream& s, const TSubSVec& v);
std::istream& operator >> (std::istream& s, TSubSVec& v);

std::ostream& operator << (std::ostream& s, TConstRefMat m);
std::istream& operator >> (std::istream& s, TMat& m);
std::ostream& operator << (std::ostream& s, TConstSliceMat m);
std::istream& operator >> (std::istream& s, TSliceMat m);
std::ostream& operator << (std::ostream& s, const TSparseMat& m);
std::istream& operator >> (std::istream& s, TSparseMat& m);
std::ostream& operator << (std::ostream& s, const TSubSMat& m);
std::istream& operator >> (std::istream& s, TSubSMat& m);

std::ostream& operator << (std::ostream& s, TConstRefVol m);
std::istream& operator >> (std::istream& s, TVol& m);
std::ostream& operator << (std::ostream& s, TConstSliceVol m);
std::istream& operator >> (std::istream& s, TSliceVol m);

#endif
#endif
