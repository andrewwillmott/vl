/*
    File:       Print.h

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_STDIO

#ifndef VL_PRINT_H
#define VL_PRINT_H

#include "PrintBase.h"

class TConstRefVec;
class TConstRefMat;

// Print in standard format
int fprint(FILE* file, TConstRefVec v, int width = 1, int precision = 3);
int fprint(FILE* file, TConstRefMat m, int width = 1, int precision = 3);
int fprint(FILE* file, TConstRefVol l, int width = 1, int precision = 3);

// Print according to specific format, see VL_FORMAT from PrintBase.h
int fprint(FILE* file, const char* format, TConstRefVec v, int width = 1, int precision = 3);
int fprint(FILE* file, const char* format, TConstRefMat m, int width = 1, int precision = 3);
int fprint(FILE* file, const char* format, TConstRefVol l, int width = 1, int precision = 3);

// Print in format that can be compiled as C, 'name' is variable name.
int fprint_as_c(FILE* file, const char* name, TConstRefVec v, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name, TConstRefMat m, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name, TConstRefVol l, int width = 1, int precision = 3);

#endif
#endif