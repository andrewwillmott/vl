/*
    File:       Stream234.h

    Function:   iostream support

    Copyright:  Andrew Willmott
 */

#ifndef VL_NO_IOSTREAM

#ifndef VL_STREAM_234_H
#define VL_STREAM_234_H

VL_NS_END
#include <iostream>
VL_NS_BEGIN

// --- Stream Operators -------------------------------------------------------

class TVec2;
class TVec3;
class TVec4;
class TMat2;
class TMat3;
class TMat4;

std::ostream& operator << (std::ostream& s, const TVec2& v);
std::istream& operator >> (std::istream& s, TVec2& v);
std::ostream& operator << (std::ostream& s, const TVec3& v);
std::istream& operator >> (std::istream& s, TVec3& v);
std::ostream& operator << (std::ostream& s, const TVec4& v);
std::istream& operator >> (std::istream& s, TVec4& v);

std::ostream& operator << (std::ostream& s, const TMat2& m);
std::istream& operator >> (std::istream& s, TMat2& m);
std::ostream& operator << (std::ostream& s, const TMat3& m);
std::istream& operator >> (std::istream& s, TMat3& m);
std::ostream& operator << (std::ostream& s, const TMat4& m);
std::istream& operator >> (std::istream& s, TMat4& m);

#endif
#endif