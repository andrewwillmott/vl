/*
    File:       VLConfig.hpp

    Function:   Contains configuration options for compiling the VL
                library.

    Copyright:  Andrew Willmott
*/

//
//  Current options are as follows:
//
//  VL_DEBUG       - Whether to enable debug mode, usually better set in a build system.
//  VL_NO_IOSTREAM - Exclude iostream support
//  VL_NO_STDIO    - Exclude stdio/fprint support
//  VL_ROW_ORIENT  - Use row-vector transforms by default. If this is defined, 
//                   transformations are of the form v = v * Rot3x(u, 0.5), 
//                   rather than v = Rot3x(u, 0.5) * v.
//  VL_ASSERT_FULL - Hook for redirecting asserts to your own system
//  VL_EXPECT_FULL - Ditto for warnings
//  VL_NEW         - Hook for redirecting memory allocations
//  VL_DELETE      - 
//  VL_SINCOS      - specify sincos function
//

// --- Configuration ----------------------------------------------------------

// #define VL_NEW MY_NEW
// #define VL_DELETE MY_DELETE

// #define VL_ASSERT_FULL MY_ASSERT_FULL
// #define VL_EXPECT_FULL MY_EXPECT_FULL
