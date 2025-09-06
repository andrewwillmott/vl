/*
    File:       PrintBase.h

    Function:   Utilities for printing/writing vectors and matrices in text form

    Copyright:  Andrew Willmott
*/

#ifndef VL_PRINT_BASE_H
#define VL_PRINT_BASE_H

VL_NS_END
#include <stdio.h>
VL_NS_BEGIN

// Base routines
int fprint     (FILE* file, const char* format, int n,               const TElt* elts, int width = 1, int precision = 3);
int fprint     (FILE* file, const char* format, int r, int c,        const TElt* elts, int width = 1, int precision = 3);
int fprint     (FILE* file, const char* format, int s, int r, int c, const TElt* elts, int width = 1, int precision = 3);

int fprint_as_c(FILE* file, const char* name,   int n,               const TElt* elts, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name,   int r, int c,        const TElt* elts, int width = 1, int precision = 3);
int fprint_as_c(FILE* file, const char* name,   int s, int r, int c, const TElt* elts, int width = 1, int precision = 3);

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
//    fprint(stdout, VL_FMT_VI, Veci(...));
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
//     fprint(stdout, VL_FORMAT("[", " ", "]", "%*.*f"), v);
//     fprint(stdout, VL_FORMAT("", "", "", VL_FORMAT("[", " ", "]\n", "%*.*f")), m);
//
// Finally, you can take advantage of preprocessor string gluing to add prefixes
// and suffixes to custom formats, e.g., 
//
//     fprint(stdout, "Result: " VL_FMT_VF_INLINE " m/s\n", dir_ms);
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

#endif
