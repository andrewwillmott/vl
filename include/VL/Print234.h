/*
    File:       Print234.h

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_STDIO

#ifndef VL_PRINT_234_H
#define VL_PRINT_234_H

#include "PrintBase.h"

// Print with default formatting
int fprint(FILE* file, const TVec2& v, int width = 1, int precision = 3);
int fprint(FILE* file, const TVec3& v, int width = 1, int precision = 3);
int fprint(FILE* file, const TVec4& v, int width = 1, int precision = 3);
int fprint(FILE* file, const TMat2& m, int width = 1, int precision = 3);
int fprint(FILE* file, const TMat3& m, int width = 1, int precision = 3);
int fprint(FILE* file, const TMat4& m, int width = 1, int precision = 3);

// Print according to specific format, see VL_FORMAT from PrintBase.h
int fprint(FILE* file, const char* format, const TVec2& v, int width = 1, int precision = 3);
int fprint(FILE* file, const char* format, const TVec3& v, int width = 1, int precision = 3);
int fprint(FILE* file, const char* format, const TVec4& v, int width = 1, int precision = 3);
int fprint(FILE* file, const char* format, const TMat2& m, int width = 1, int precision = 3);
int fprint(FILE* file, const char* format, const TMat3& m, int width = 1, int precision = 3);
int fprint(FILE* file, const char* format, const TMat4& m, int width = 1, int precision = 3);

// Print in format that can be compiled as C, 'name' is variable name.
int fprint_as_c(FILE* file, const char* name, const TVec2& v, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name, const TVec3& v, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name, const TVec4& v, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name, const TMat2& m, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name, const TMat3& m, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name, const TMat4& m, int width = 1, int precision = 3);

#endif
#endif