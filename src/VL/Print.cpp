/*
    File:       Print.cpp

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_STDIO

#include "VL/Print.hpp"

int fprint(FILE* file, TConstRefVec v, int width, int precision)
{
    return fprint(file, VL_FMT_VF "\n", v, width, precision);
}

int fprint(FILE* file, TConstRefMat m, int width, int precision)
{
    return fprint(file, VL_FMT_MF, m, width, precision);
}

int fprint(FILE* file, TConstRefVol l, int width, int precision)
{
    return fprint(file, VL_FMT_LF, l, width, precision);
}

int fprint(FILE* file, const char* format, TConstRefVec v, int width, int precision)
{
    return fprint(file, format, v.Elts(), v.Ref(), width, precision);
}

int fprint(FILE* file, const char* format, TConstRefMat m, int width, int precision)
{
    return fprint(file, format, m.Rows(), m.Cols(), m.Ref(), width, precision);
}

int fprint(FILE* file, const char* format, TConstRefVol l, int width, int precision)
{
    return fprint(file, format, l.Slices(), l.Rows(), l.Cols(), l.Ref(), width, precision);
}

int fprint_as_c(FILE* file, const char* name, TConstRefVec v, int width, int precision)
{
    return fprint_as_c(file, name, v.Elts(), v.Ref(), width, precision);
}

int fprint_as_c(FILE* file, const char* name, TConstRefMat m, int width, int precision)
{
    return fprint_as_c(file, name, m.Rows(), m.Cols(), m.Ref(), width, precision);
}

int fprint_as_c(FILE* file, const char* name, TConstRefVol l, int width, int precision)
{
    return fprint_as_c(file, name, l.Slices(), l.Rows(), l.Cols(), l.Ref(), width, precision);
}

#include "PrintBase.cpp"

#endif
