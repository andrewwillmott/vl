/*
    File:       Print.hpp

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_STDIO

#ifndef VL_PRINT_H
#define VL_PRINT_H

#include "PrintBase.hpp"

class TConstRefVec;
class TConstRefMat;

// Print in standard format
int vl_fprint(FILE* file, TConstRefVec v, int width = 1, int precision = 3);
int vl_fprint(FILE* file, TConstRefMat m, int width = 1, int precision = 3);
int vl_fprint(FILE* file, TConstRefVol l, int width = 1, int precision = 3);

// Print according to specific format, see VL_FORMAT from PrintBase.hpp
int vl_fprintf(FILE* file, const char* format, TConstRefVec v, int width = 1, int precision = 3);
int vl_fprintf(FILE* file, const char* format, TConstRefMat m, int width = 1, int precision = 3);
int vl_fprintf(FILE* file, const char* format, TConstRefVol l, int width = 1, int precision = 3);

// Print in format that can be compiled as C, 'name' is variable name.
int vl_fprint_as_c(FILE* file, const char* name, TConstRefVec v, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name, TConstRefMat m, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name, TConstRefVol l, int width = 1, int precision = 3);

// Write string according to specific format, see VL_FORMAT from PrintBase.hpp
int vl_snprintf(char* str, size_t size, const char* format, TConstRefVec v, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t size, const char* format, TConstRefMat m, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t size, const char* format, TConstRefVol l, int width = 1, int precision = 3);

// Variant that advances 'str' and reduces 'size' accordingly.
int vl_snprintf_adv(char*& str, size_t& size, const char* format, TConstRefVec v, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& size, const char* format, TConstRefMat m, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& size, const char* format, TConstRefVol l, int width = 1, int precision = 3);

#endif
#endif
