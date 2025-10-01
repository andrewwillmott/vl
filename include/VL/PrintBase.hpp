/*
    File:       PrintBase.hpp

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_PRINT_BASE_H
#define VL_PRINT_BASE_H

VL_NS_END
#include <stdio.h>
VL_NS_BEGIN

// Base routines used by Print/Print234

// Print according to specific format, see VL_FORMAT below
int vl_fprintf     (FILE* file, const char* format, int n,               const TElt* elts, int width = 1, int precision = 3);
int vl_fprintf     (FILE* file, const char* format, int r, int c,        const TElt* elts, int width = 1, int precision = 3);
int vl_fprintf     (FILE* file, const char* format, int s, int r, int c, const TElt* elts, int width = 1, int precision = 3);

// Print in format that can be compiled as C, 'name' is variable name.
int vl_fprint_as_c(FILE* file, const char* name,   int n,               const TElt* elts, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name,   int r, int c,        const TElt* elts, int width = 1, int precision = 3);
int vl_fprint_as_c(FILE* file, const char* name,   int s, int r, int c, const TElt* elts, int width = 1, int precision = 3);

// Write string according to specific format, see VL_FORMAT below. Behaviour same as unix snprintf.
int vl_snprintf(char* str, size_t sz, const char* fmt, int n,               const TElt* elts, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t sz, const char* fmt, int r, int c,        const TElt* elts, int width = 1, int precision = 3);
int vl_snprintf(char* str, size_t sz, const char* fmt, int s, int r, int c, const TElt* elts, int width = 1, int precision = 3);

// Variant that advances 'str' and reduces 'size' accordingly.
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int n,               const TElt* elts, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int r, int c,        const TElt* elts, int width = 1, int precision = 3);
int vl_snprintf_adv(char*& str, size_t& sz, const char* fmt, int s, int r, int c, const TElt* elts, int width = 1, int precision = 3);

int sn_adv(char*& str, size_t& size, int chars);  // Wrapper to get same behaviour from snprintf variants -- chars = sn_adv(str, sz, snprintf(str, sz, ...))

#if VL_CXX_11
// Some C++11 adapters that allow using the same '_adv' pattern as above with snprintf
template<class... Args> int snprintf_adv   (char*& str, size_t& size, const char* fmt, Args... args);
template<class... Args> int snprintf_append(char*  str, size_t  size, const char* fmt, Args... args);  // appends, returns size of final string

// Allow direct usage with, e.g., std::string, without having to bring in the header.
template<class S, class... Args> S& ssprintf       (S& str, const char* fmt, Args... args);
template<class S, class... Args> S& ssprintf_append(S& str, const char* fmt, Args... args);
template<class S, class... Args> S& ssprintf_adv   (S& str, size_t& cursor, const char* fmt, Args... args);

template<class S, class... Args> S& vl_ssprintf        (S& str, const char* fmt, Args... args);
template<class S, class... Args> S& vl_ssprintf_append (S& str, const char* fmt, Args... args);
template<class S, class... Args> S& vl_ssprintf_adv    (S& str, size_t& cursor, const char* fmt, Args... args);

// Shortcuts for fprintf(stdout, ...)
template<class... Args> int vl_printf(Args... args);
template<class... Args> int vl_print (Args... args);
#endif

//
// For the 'format' argument above, you can use one of the pre-defined formats:
//
//   VL_FMT_VF                ->  [1.0 2.0 3.0]
//   VL_FMT_VF_ROUND          ->  (1.0 2.0 3.0)
//   VL_FMT_VF_COL            ->  [1.0]\n[2.0]\n[3.0]\n
//   VL_FMT_VF_C              ->  { 1.0f, 2.0f, 3.0f }
//   VL_FMT_VF_PY             ->  [1.0, 2.0, 3.0]
//
//   VL_FMT_MF                ->  [1.0 2.0]\n[3.0 4.0]\n
//   VL_FMT_MF_INLINE         ->  [[1.0 2.0] [3.0 4.0]]
//   VL_FMT_MF_C              ->  {\n  { 1, 2 },\n  { 3, 4 }\n}\n
//   VL_FMT_MF_C_INLINE       ->  { { 1, 2 }, { 3, 4 } }
//   VL_FMT_MF_PY             ->  [[1.0, 2.0],\n [3.0, 4.0]]\n
//   VL_FMT_MF_PY_INLINE      ->  [[1.0, 2.0], [3.0, 4.0]]
//
// There are also '_VI' and '_MI' integer variants of these formats, e.g.,
//
//    vl_printf(VL_FMT_VI, Veci(...));
//
// For the _C formats, you can use 'D' as the type specifier, e.g., VL_FMT_VD_C,
// to print without the 'f' suffix.
//
// You can also construct your own custom format with the VL_FORMAT macro:
//
//     VL_FORMAT(start_text, element_separator, end_text, element_format)
//
// For matrices the element_format is the vector format, and for vectors it's a
// printf-style format with *.* corresponding to width/precision. E.g.,
//
//     vl_fprintf(stdout, VL_FORMAT("[", " ", "]", "%*.*f"), v);
//     vl_fprintf(stdout, VL_FORMAT("", "", "", VL_FORMAT("[", " ", "]\n", "%*.*f")), m);
//
// Finally, you can take advantage of preprocessor string gluing to add prefixes
// and suffixes to custom formats, e.g.,
//
//     vl_printf("Result: " VL_FMT_VF_INLINE " m/s\n", dir_ms);
//     -> Result: [0.1 0.3 0.1] m/s
//


// --- Implementation ---------------------------------------------------------

#ifndef VL_FORMAT

#define VL_FORMAT(M_START, M_SEP, M_END, M_FMT) M_START "\0" M_FMT "\0\3" M_SEP "\0" M_END

#define VL_FMT_F "%*.*f"

#define VL_FMT_VF              VL_FORMAT("[", " ", "]", VL_FMT_F)
#define VL_FMT_VF_ROUND        VL_FORMAT("(", " ", ")", VL_FMT_F)
#define VL_FMT_VF_COL          VL_FORMAT("", "\n", "\n", "[ " VL_FMT_F " ]")
#define VL_FMT_VF_C            VL_FORMAT("{ ", ", ", " }", VL_FMT_F "f")
#define VL_FMT_VD_C            VL_FORMAT("{ ", ", ", " }", VL_FMT_F)
#define VL_FMT_VF_PY           VL_FORMAT("[", ", ", "]", VL_FMT_F)

#define VL_FMT_MF              VL_FORMAT("", "\n", "\n", VL_FMT_VF)
#define VL_FMT_MF_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_VF)
#define VL_FMT_MF_C            VL_FORMAT("{\n", ",\n", "\n}\n", "  " VL_FMT_VF_C)
#define VL_FMT_MF_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_VF_C)
#define VL_FMT_MF_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FMT_VF_PY)
#define VL_FMT_MF_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_VF_PY)

#define VL_FMT_LF              VL_FORMAT("", ".\n", "\n", VL_FMT_MF)
#define VL_FMT_LF_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_MF_INLINE)
#define VL_FMT_LF_C            VL_FORMAT("{\n", ",\n", "\n}\n", VL_FORMAT("  {\n", ",\n", "\n  }", "    " VL_FMT_VF_C))
#define VL_FMT_LF_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_MF_C_INLINE)
#define VL_FMT_LF_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FORMAT("[", ",\n  ", "]", VL_FMT_VF_PY))
#define VL_FMT_LF_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_MF_PY_INLINE)

#define VL_FMT_I "%*d"

#define VL_FMT_VI              VL_FORMAT("[", " ", "]", VL_FMT_I)
#define VL_FMT_VI_ROUND        VL_FORMAT("(", " ", ")", VL_FMT_I)
#define VL_FMT_VI_COL          VL_FORMAT("", "\n", "\n", "[ " VL_FMT_I " ]")
#define VL_FMT_VI_C            VL_FORMAT("{ ", ", ", " }", VL_FMT_I)
#define VL_FMT_VI_PY           VL_FORMAT("[", ", ", "]", VL_FMT_I)

#define VL_FMT_MI              VL_FORMAT("", "\n", "\n", VL_FMT_VI)
#define VL_FMT_MI_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_VI)
#define VL_FMT_MI_C            VL_FORMAT("{\n", ",\n", "\n}\n", "  " VL_FMT_VI_C)
#define VL_FMT_MI_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_VI_C)
#define VL_FMT_MI_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FMT_VI_PY)
#define VL_FMT_MI_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_VI_PY)

#define VL_FMT_LI              VL_FORMAT("", ".\n", "\n", VL_FMT_MI)
#define VL_FMT_LI_INLINE       VL_FORMAT("[", " ", "]", VL_FMT_MI_INLINE)
#define VL_FMT_LI_C            VL_FORMAT("{\n", ",\n", "\n}\n", VL_FORMAT("  {\n", ",\n", "\n  }", "    " VL_FMT_VI_C))
#define VL_FMT_LI_C_INLINE     VL_FORMAT("{ ", ", ", " }", VL_FMT_MI_C_INLINE)
#define VL_FMT_LI_PY           VL_FORMAT("[", ",\n ", "]\n", VL_FORMAT("[", ",\n  ", "]", VL_FMT_VI_PY))
#define VL_FMT_LI_PY_INLINE    VL_FORMAT("[", ", ", "]", VL_FMT_MI_PY_INLINE)

#endif

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int n, const TElt* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, n, elts, w, p);
}

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int r, int c, const TElt* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, r, c, elts, w, p);
}

inline int vl_snprintf(char* str, size_t sz, const char* fmt, int s, int r, int c, const TElt* elts, int w, int p)
{
    char* lstr = str; size_t lsz = sz;
    return vl_snprintf_adv(lstr, lsz, fmt, s, r, c, elts, w, p);
}

inline int sn_adv(char*& str, size_t& size, int chars)
{
    size_t write = (chars > size) ? size : chars;
    str += write;
    size -= write;
    return chars;
}

#if VL_CXX_11

template<class... Args> inline int snprintf_adv(char*& str, size_t& size, const char* fmt, Args... args)
{
    int chars = snprintf(str, size, fmt, args...);
    size_t write = (chars > size) ? size : chars;
    str += write;
    size -= write;
    return chars;
}

template<class... Args> inline int snprintf_append(char* str, size_t size, const char* fmt, Args... args)
{
    while (*str && size)
    {
        str++;
        size--;
    }
    return snprintf(str, size, fmt, args...);
}

template<class S, class... Args> S& ssprintf(S& str, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    str.resize(size);
    int chars = snprintf(str.data(), size + 1, fmt, args...);
    str.resize(chars);
    if (chars >= size)
        snprintf(str.data(), chars + 1, fmt, args...);
    return str;
}

template<class S, class... Args> S& ssprintf_adv(S& str, size_t& cursor, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    VL_ASSERT(cursor <= size);

    str.resize(size);
    int chars = snprintf(str.data() + cursor, size + 1 - cursor, fmt, args...);
    str.resize(cursor + chars);
    if (cursor + chars >= size)
        snprintf(str.data() + cursor, chars + 1, fmt, args...);
    cursor += chars;
    return str;
}

template<class S, class... Args> S& ssprintf_append(S& str, const char* fmt, Args... args)
{
    size_t cursor = str.size();
    return ssprintf_adv(str, cursor, fmt, args...);
}

template<class S, class... Args> S& vl_ssprintf(S& str, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    str.resize(size);
    int chars = vl_snprintf(str.data(), size + 1, fmt, args...);
    str.resize(chars);
    if (chars >= size)
        vl_snprintf(str.data(), chars + 1, fmt, args...);
    return str;
}

template<class S, class... Args> inline S& vl_ssprintf_adv(S& str, size_t& cursor, const char* fmt, Args... args)
{
    size_t size = str.capacity();
    VL_ASSERT(cursor <= size);

    str.resize(size);
    int chars = vl_snprintf(str.data() + cursor, size + 1 - cursor, fmt, args...);
    str.resize(cursor + chars);
    if (cursor + chars >= size)
        vl_snprintf(str.data() + cursor, chars + 1, fmt, args...);
    cursor += chars;
    return str;
}

template<class S, class... Args> S& vl_ssprintf_append(S& str, const char* fmt, Args... args)
{
    size_t cursor = str.size();
    return vl_ssprintf_adv(str, cursor, fmt, args...);
}

template<class... Args> int vl_printf(Args... args)
{
    return vl_fprintf(stdout, args...);
}

template<class... Args> int vl_print(Args... args)
{
    return vl_fprint(stdout, args...);
}

#endif

#endif
