/*
    File:       PrintBase.cpp

    Function:   Shared utilities for printing/writing vectors and matrices in
                text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_FORMAT_IMPL
#define VL_FORMAT_IMPL

VL_NS_END
#include <string.h>
VL_NS_BEGIN

namespace
{
    inline int SpanFormat(int level, const char* format)
    {
        int c = 0;

        for (int i = 0; i < level; i++)
            while (format[c++] != '\3')
                ;
        return c - 1;
    }
}

int vl_fprintf(FILE* file, const char* format, int n, const TElt* v, int width, int precision)
{
    const char* s0 = format;        // vector start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // element format
    size_t      lf = SpanFormat(1, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vector end
    size_t      l2 = strlen(s2);

    int result = (int) fwrite(s0, l0, sizeof(char), file);

    for (int i = 0; i < n - 1; i++)
    {
    #ifdef VL_PRINT_INT
        result += fprintf(file, sf, width, v[i]);
    #else
        result += fprintf(file, sf, width, precision, double(v[i]));
    #endif
        result += (int) fwrite(s1, l1, sizeof(char), file);
    }

    if (n > 0)
    #ifdef VL_PRINT_INT
        result += fprintf(file, sf, width, v[n - 1]);
    #else
        result += fprintf(file, sf, width, precision, double(v[n - 1]));
    #endif

    result += (int) fwrite(s2, l2, sizeof(char), file);
    return result;
}

int vl_fprintf(FILE* file, const char* format, int nr, int nc, const TElt* m, int width, int precision)
{
    const char* s0 = format;        // matrix start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // vector format
    size_t      lf = SpanFormat(2, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // matrix end
    size_t      l2 = strlen(s2);

    int result = (int) fwrite(s0, l0, sizeof(char), file);

    for (int i = 0; i < nr - 1; i++)
    {
        result += vl_fprintf(file, sf, nc, m, width, precision);
        m += nc;

        result += (int) fwrite(s1, l1, sizeof(char), file);
    }

    if (nr > 0)
        result += vl_fprintf(file, sf, nc, m, width, precision);

    result += (int) fwrite(s2, l2, sizeof(char), file);
    return result;
}

int vl_fprintf(FILE* file, const char* format, int ns, int nr, int nc, const TElt* elts, int width, int precision)
{
    const char* s0 = format;        // vol start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // mat format
    size_t      lf = SpanFormat(3, sf);

    const char* s1 = sf + lf + 1;   // vol separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vol end
    size_t      l2 = strlen(s2);

    int result = (int) fwrite(s0, l0, sizeof(char), file);

    for (int i = 0; i < ns - 1; i++)
    {
        result += vl_fprintf(file, sf, nr, nc, elts, width, precision);
        elts += nr * nc;

        result += (int) fwrite(s1, l1, sizeof(char), file);
    }

    if (ns > 0)
        result += vl_fprintf(file, sf, nr, nc, elts, width, precision);

    result += (int) fwrite(s2, l2, sizeof(char), file);
    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int n, const TElt* v, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d] = ", name, n);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_VI_C ";\n", n, v, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_VF_C ";\n", n, v, width, precision);
#endif

    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int nr, int nc, const TElt* m, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d][%d] = \n", name, nr, nc);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_MI_C ";\n", nr, nc, m, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_MF_C ";\n", nr, nc, m, width, precision);
#endif
    return result;
}

int vl_fprint_as_c(FILE* file, const char* name, int ns, int nr, int nc, const TElt* elts, int width, int precision)
{
    int result = fprintf(file, "const float %s[%d][%d] = \n", name, nr, nc);

#ifdef VL_PRINT_INT
    result += vl_fprintf(file, VL_FMT_LI_C ";\n", nr, nc, elts, width, precision);
#else
    result += vl_fprintf(file, VL_FMT_LF_C ";\n", nr, nc, elts, width, precision);
#endif
    return result;
}

namespace
{
    inline int vl_snprintf_adv(char*& str, size_t& size, const char* s, size_t n)
    {
        if (size == 0)
            return (int) n;

        size_t write = (n >= size) ? size - 1 : n;

        memcpy(str, s, write);
        str += write;
        size -= write;

        *str = 0;

        return (int) n;
    }
}

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int n, const TElt* v, int width, int precision)
{
    const char* s0 = format;        // vector start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // element format
    size_t      lf = SpanFormat(1, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vector end
    size_t      l2 = strlen(s2);

    int result = vl_snprintf_adv(str, size, s0, l0);

    for (int i = 0; i < n - 1; i++)
    {
    #ifdef VL_PRINT_INT
        result += sn_adv(str, size, snprintf(str, size, sf, width, v[i]));
    #else
        result += sn_adv(str, size, snprintf(str, size, sf, width, precision, double(v[i])));
    #endif

        result += vl_snprintf_adv(str, size, s1, l1);
    }

    if (n > 0)
    #ifdef VL_PRINT_INT
        result += sn_adv(str, size, snprintf(str, size, sf, width, v[n - 1]));
    #else
        result += sn_adv(str, size, snprintf(str, size, sf, width, precision, double(v[n - 1])));
    #endif

    result += vl_snprintf_adv(str, size, s2, l2);
    return result;
}

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int nr, int nc, const TElt* m, int width, int precision)
{
    const char* s0 = format;        // matrix start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // vector format
    size_t      lf = SpanFormat(2, sf);

    const char* s1 = sf + lf + 1;   // separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // matrix end
    size_t      l2 = strlen(s2);

    int result = vl_snprintf_adv(str, size, s0, l0);

    for (int i = 0; i < nr - 1; i++)
    {
        result += vl_snprintf_adv(str, size, sf, nc, m, width, precision);
        m += nc;

        result += vl_snprintf_adv(str, size, s1, l1);
    }

    if (nr > 0)
        result += vl_snprintf_adv(str, size, sf, nc, m, width, precision);

    result += vl_snprintf_adv(str, size, s2, l2);
    return result;
}

int vl_snprintf_adv(char*& str, size_t& size, const char* format, int ns, int nr, int nc, const TElt* elts, int width, int precision)
{
    const char* s0 = format;        // vol start
    size_t      l0 = strlen(s0);

    const char* sf = s0 + l0 + 1;   // mat format
    size_t      lf = SpanFormat(3, sf);

    const char* s1 = sf + lf + 1;   // vol separator
    size_t      l1 = strlen(s1);

    const char* s2 = s1 + l1 + 1;   // vol end
    size_t      l2 = strlen(s2);

    int result = vl_snprintf_adv(str, size, s0, l0);

    for (int i = 0; i < ns - 1; i++)
    {
        result += vl_snprintf_adv(str, size, sf, nr, nc, elts, width, precision);
        elts += nr * nc;

        result += vl_snprintf_adv(str, size, s1, l1);
    }

    if (ns > 0)
        result += vl_snprintf_adv(str, size, sf, nr, nc, elts, width, precision);

    result += vl_snprintf_adv(str, size, s2, l2);
    return result;
}

#endif

