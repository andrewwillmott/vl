/*
    File:       Ops.hpp

    Function:   Defines various bits of operation boiler plate for vec/mat
                transforms and interoperation.

    Copyright:  Andrew Willmott
 */

#ifndef VL_OPS_H
#define VL_OPS_H

#if !defined(VL_NO_REAL)
    #define VL_OPS(OUT, IN) \
        inline OUT sqrt (const IN& v) { return transformed(v, std::sqrt ); } \
        inline OUT ceil (const IN& v) { return transformed(v, std::ceil ); } \
        inline OUT floor(const IN& v) { return transformed(v, std::floor); } \
        inline OUT round(const IN& v) { return transformed(v, std::round); } \
        inline OUT log  (const IN& v) { return transformed(v, std::log  ); } \
        inline OUT exp  (const IN& v) { return transformed(v, std::exp  ); } \
        inline OUT sin  (const IN& v) { return transformed(v, std::sin  ); } \
        inline OUT cos  (const IN& v) { return transformed(v, std::cos  ); } \
        inline OUT tan  (const IN& v) { return transformed(v, std::tan  ); } \
        inline OUT asin (const IN& v) { return transformed(v, std::asin ); } \
        inline OUT acos (const IN& v) { return transformed(v, std::acos ); } \
        inline OUT atan (const IN& v) { return transformed(v, std::atan ); } \
        \
        inline OUT::Elt vl_min(const IN& v) { return (OUT::Elt) reduced(v, vl_min); } \
        inline OUT::Elt vl_max(const IN& v) { return (OUT::Elt) reduced(v, vl_max); } \

#else
    #define VL_OPS(IN, OUT)
#endif

#define VL_OPS_INTEROP1(A, B, TA, TB) \
    inline void operator += (A a, B b) { (TA) a += (TB) b; }    \
    inline void operator -= (A a, B b) { (TA) a -= (TB) b; }    \
    inline void operator *= (A a, B b) { (TA) a *= (TB) b; }    \
    inline void operator /= (A a, B b) { (TA) a /= (TB) b; }    \

#define VL_OPS_INTEROP2(R, A, B) \
    inline R operator + (A a, B b)     { return a + (A) b; }     \
    inline R operator - (A a, B b)     { return a - (A) b; }     \
    inline R operator * (A a, B b)     { return a * (A) b; }     \
    inline R operator / (A a, B b)     { return a / (A) b; }     \
    inline R operator + (B b, A a)     { return (A) b + a; }     \
    inline R operator - (B b, A a)     { return (A) b - a; }     \
    inline R operator * (B b, A a)     { return (A) b * a; }     \
    inline R operator / (B b, A a)     { return (A) b / a; }     \

#endif
