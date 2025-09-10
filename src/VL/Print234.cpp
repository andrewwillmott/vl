/*
    File:       Print234.cpp

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_STDIO

#include "VL/Print234.hpp"

#ifdef VL_PRINT_INT
int fprint(FILE* file, const TVec2& v, int width, int prec) { return fprint(file, VL_FMT_VI "\n", 2, &v.x, width); }
int fprint(FILE* file, const TVec3& v, int width, int prec) { return fprint(file, VL_FMT_VI "\n", 3, &v.x, width); }
int fprint(FILE* file, const TVec4& v, int width, int prec) { return fprint(file, VL_FMT_VI "\n", 4, &v.x, width); }
int fprint(FILE* file, const TMat2& m, int width, int prec) { return fprint(file, VL_FMT_MI     , 2, 2, &m.x.x, width); }
int fprint(FILE* file, const TMat3& m, int width, int prec) { return fprint(file, VL_FMT_MI     , 3, 3, &m.x.x, width); }
int fprint(FILE* file, const TMat4& m, int width, int prec) { return fprint(file, VL_FMT_MI     , 4, 4, &m.x.x, width); }
#else
int fprint(FILE* file, const TVec2& v, int width, int prec) { return fprint(file, VL_FMT_VF "\n", 2, &v.x, width, prec); }
int fprint(FILE* file, const TVec3& v, int width, int prec) { return fprint(file, VL_FMT_VF "\n", 3, &v.x, width, prec); }
int fprint(FILE* file, const TVec4& v, int width, int prec) { return fprint(file, VL_FMT_VF "\n", 4, &v.x, width, prec); }
int fprint(FILE* file, const TMat2& m, int width, int prec) { return fprint(file, VL_FMT_MF     , 2, 2, &m.x.x, width, prec); }
int fprint(FILE* file, const TMat3& m, int width, int prec) { return fprint(file, VL_FMT_MF     , 3, 3, &m.x.x, width, prec); }
int fprint(FILE* file, const TMat4& m, int width, int prec) { return fprint(file, VL_FMT_MF     , 4, 4, &m.x.x, width, prec); }
#endif

int fprint(FILE* file, const char* format, const TVec2& v, int width, int prec) { return fprint(file, format, 2, &v.x, width, prec); }
int fprint(FILE* file, const char* format, const TVec3& v, int width, int prec) { return fprint(file, format, 3, &v.x, width, prec); }
int fprint(FILE* file, const char* format, const TVec4& v, int width, int prec) { return fprint(file, format, 4, &v.x, width, prec); }
int fprint(FILE* file, const char* format, const TMat2& m, int width, int prec) { return fprint(file, format, 2, 2, &m.x.x, width, prec); }
int fprint(FILE* file, const char* format, const TMat3& m, int width, int prec) { return fprint(file, format, 3, 3, &m.x.x, width, prec); }
int fprint(FILE* file, const char* format, const TMat4& m, int width, int prec) { return fprint(file, format, 4, 4, &m.x.x, width, prec); }

int fprint_as_c(FILE* file, const char* name, const TVec2& v, int width, int prec) { return fprint_as_c(file, name, 2, &v.x, width, prec); }
int fprint_as_c(FILE* file, const char* name, const TVec3& v, int width, int prec) { return fprint_as_c(file, name, 3, &v.x, width, prec); }
int fprint_as_c(FILE* file, const char* name, const TVec4& v, int width, int prec) { return fprint_as_c(file, name, 4, &v.x, width, prec); }
int fprint_as_c(FILE* file, const char* name, const TMat2& m, int width, int prec) { return fprint_as_c(file, name, 2, 2, &m.x.x, width, prec); }
int fprint_as_c(FILE* file, const char* name, const TMat3& m, int width, int prec) { return fprint_as_c(file, name, 3, 3, &m.x.x, width, prec); }
int fprint_as_c(FILE* file, const char* name, const TMat4& m, int width, int prec) { return fprint_as_c(file, name, 4, 4, &m.x.x, width, prec); }

#include "PrintBase.cpp"

#endif
