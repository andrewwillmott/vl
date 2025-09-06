This directory contains cut-down float-only variants of VL, useful for code that
only needs 234 variants, or indeed quick copy-and-paste into single files.

    VL234f.h/VL234f.cpp // Vec[234]f and Mat[234]f support
    VLVec234.h          // Vec[234]f only
    VL234i.h/VL234i.cpp // Vec[234]i support
    VLMini.h            // One line per operation, easy to copy and paste

The `VL[Vec]234` files can be regenerated via `make`, and the `VL234f.h` code
tested via `make test`.

The `VLMini.h` file in addition has some support for clang vector type
attributes.
