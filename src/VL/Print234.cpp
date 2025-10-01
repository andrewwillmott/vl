/*
    File:       Print234.cpp

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_STDIO

#include "VL/Print234.hpp"

#ifdef VL_PRINT_INT
int vl_fprint(FILE* file, const TVec2& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 2, &v.x, width); }
int vl_fprint(FILE* file, const TVec3& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 3, &v.x, width); }
int vl_fprint(FILE* file, const TVec4& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VI "\n", 4, &v.x, width); }
int vl_fprint(FILE* file, const TMat2& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 2, 2, &m.x.x, width); }
int vl_fprint(FILE* file, const TMat3& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 3, 3, &m.x.x, width); }
int vl_fprint(FILE* file, const TMat4& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MI     , 4, 4, &m.x.x, width); }
#else
int vl_fprint(FILE* file, const TVec2& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 2, &v.x, width, prec); }
int vl_fprint(FILE* file, const TVec3& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 3, &v.x, width, prec); }
int vl_fprint(FILE* file, const TVec4& v, int width, int prec) { return vl_fprintf(file, VL_FMT_VF "\n", 4, &v.x, width, prec); }
int vl_fprint(FILE* file, const TMat2& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 2, 2, &m.x.x, width, prec); }
int vl_fprint(FILE* file, const TMat3& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 3, 3, &m.x.x, width, prec); }
int vl_fprint(FILE* file, const TMat4& m, int width, int prec) { return vl_fprintf(file, VL_FMT_MF     , 4, 4, &m.x.x, width, prec); }
#endif

int vl_fprintf(FILE* file, const char* fmt, const TVec2& v, int width, int prec) { return vl_fprintf(file, fmt, 2, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const TVec3& v, int width, int prec) { return vl_fprintf(file, fmt, 3, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const TVec4& v, int width, int prec) { return vl_fprintf(file, fmt, 4, &v.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const TMat2& m, int width, int prec) { return vl_fprintf(file, fmt, 2, 2, &m.x.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const TMat3& m, int width, int prec) { return vl_fprintf(file, fmt, 3, 3, &m.x.x, width, prec); }
int vl_fprintf(FILE* file, const char* fmt, const TMat4& m, int width, int prec) { return vl_fprintf(file, fmt, 4, 4, &m.x.x, width, prec); }

int vl_fprint_as_c(FILE* file, const char* name, const TVec2& v, int width, int prec) { return vl_fprint_as_c(file, name, 2, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const TVec3& v, int width, int prec) { return vl_fprint_as_c(file, name, 3, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const TVec4& v, int width, int prec) { return vl_fprint_as_c(file, name, 4, &v.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const TMat2& m, int width, int prec) { return vl_fprint_as_c(file, name, 2, 2, &m.x.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const TMat3& m, int width, int prec) { return vl_fprint_as_c(file, name, 3, 3, &m.x.x, width, prec); }
int vl_fprint_as_c(FILE* file, const char* name, const TMat4& m, int width, int prec) { return vl_fprint_as_c(file, name, 4, 4, &m.x.x, width, prec); }

int vl_snprintf(char* str, size_t size, const char* fmt, const TVec2& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const TVec3& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const TVec4& v, int width, int precision) { return vl_snprintf(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const TMat2& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const TMat3& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf(char* str, size_t size, const char* fmt, const TMat4& m, int width, int precision) { return vl_snprintf(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }

int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const TVec2& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const TVec3& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const TVec4& v, int width, int precision) { return vl_snprintf_adv(str, size, fmt, v.Elts(), v.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const TMat2& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const TMat3& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }
int vl_snprintf_adv(char*& str, size_t& size, const char* fmt, const TMat4& m, int width, int precision) { return vl_snprintf_adv(str, size, fmt, m.Rows(), m.Cols(), m.Ref(), width, precision); }

#include "PrintBase.cpp"

#endif
