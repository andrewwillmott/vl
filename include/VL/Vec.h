/*
    File:       Vec.h

    Function:   Defines a generic resizeable vector, plus operations on
                const-savvy vector references.

    Copyright:  Andrew Willmott
 */

#ifndef VL_VEC_H
#define VL_VEC_H

#include "VecSlice.h"

VL_NS_END
#include <initializer_list>
#include <stdarg.h>
VL_NS_BEGIN


// --- RefVec Classes ---------------------------------------------------------

class TConstRefVec : public VLVecType
// Reference to a constant vector -- use this rather than const Vec&
{
public:
    // Constructors
                    TConstRefVec();
                    TConstRefVec(int n, const TElt* data); // Initialise reference to 'data'
    template<int N> TConstRefVec(const TElt (&array)[N]);  // Convenience C array wrapper

#ifdef VL_VEC2_H
    TConstRefVec(const TVec2& v);   // Vec234 interop
    TConstRefVec(const TVec3& v);
    TConstRefVec(const TVec4& v);
#endif

    operator TConstSliceVec() const;

    // Accessor methods
    int         Elts() const;                 // Element count
    const TElt& operator [] (int i) const;    // Indexing by element

    const TElt* Ref() const;                  // Return pointer to data
    bool        IsNull() const;               // True if we've not been initialised

    // Updating
    void        ReferTo(TConstRefVec v);      // Replace current reference with 'v'

    // Data
    const TElt* data;
    int         elts;

    // Prevent assignment
    void operator = (TConstRefVec v) = delete;
};


class TRefVec : public VLVecType
// Reference to a writable vector -- use this rather than Vec& or Vec*, unless
// you need to control vector size
{
public:
    // Constructors
                       TRefVec();
                       TRefVec(int n, TElt* data);    // Initialise reference to 'data'
    template<int ELTS> TRefVec(TElt (&array)[ELTS]);  // Convenience C array wrapper

#ifdef VL_VEC2_H
    TRefVec(TVec2& v);  // Vec234 interop
    TRefVec(TVec3& v);
    TRefVec(TVec4& v);
#endif

    operator TConstRefVec() const;
    operator TSliceVec() const;

    // Accessor methods
    int            Elts() const;                 // Element count
    TElt&          operator [] (int i) const;    // Indexing by element

    TElt*          Ref() const;                  // Return pointer to data
    bool           IsNull() const;               // True if we've not been initialised

    // Assignment operators
    const TRefVec& operator =  (const TRefVec& v) const; // Necessary to avoid default shallow copy behaviour
    const TRefVec& operator =  (TConstRefVec   v) const; // Assign from dense vector
    const TRefVec& operator =  (TConstSliceVec v) const; // Assign from vector slice

#ifdef VL_VEC2_H
    const TRefVec& operator =  (const TVec2& v) const;
    const TRefVec& operator =  (const TVec3& v) const;
    const TRefVec& operator =  (const TVec4& v) const;
#endif

    const TRefVec& operator =  (VLBlock     b) const;    // Set all elements to b
    const TRefVec& operator =  (VLAxis      a) const;    // Set to given axis vector
    const TRefVec& operator =  (VLMinusAxis a) const;    // Set to given -ve axis vector

    template<class T, class U = typename T::IsVec> const TRefVec& operator = (const T& v) const;

    // In-Place operators
    const TRefVec& operator += (TConstRefVec v) const;
    const TRefVec& operator -= (TConstRefVec v) const;
    const TRefVec& operator *= (TConstRefVec v) const;
    const TRefVec& operator /= (TConstRefVec v) const;
    const TRefVec& operator *= (TElt s) const;
    const TRefVec& operator /= (TElt s) const;

    // Vector initialisers
    void           MakeZero() const;
    void           MakeUnit(int i, TElt k = vl_one) const;
    void           MakeBlock(TElt k = vl_one) const;

    // Updating
    void           ReferTo(TRefVec v);  // Replace current reference with 'v'

    // Data
    TElt*          data;
    int            elts;
};


// --- Vec Classes ------------------------------------------------------------

class TVec : public TRefVec
// RefVec with associated storage
{
public:
    // Constructors
    TVec();                             // Null vector: no space allocated
    TVec(const TVec& v);                // Copy constructor
    TVec(TVec&& v);                     // Move constructor

    TVec(int n);                        // Uninitialised vector
    TVec(int n, double elt0, ...);      // Vec(3, 1.1, 2.0, 3.4)
    TVec(std::initializer_list<TElt>);  // Vec(1.1, 2.0, 3.4)

    TVec(int n, VLBlock k);             // VLBlock vector (vl_0, vl_1 ...)
    TVec(int n, VLAxis a);              // Unit vector (vl_x, vl_y, ...)
    TVec(int n, VLMinusAxis a);         // -ve unit vector (vl_minus_x, vl_minus_y, ...)

    explicit TVec(TConstRefVec m);
    explicit TVec(TConstSliceVec m);

    template<class T, class U = typename T::IsVec> explicit TVec(const T& v);

   ~TVec();

    // Accessor methods
    const TElt& operator [] (int i) const;  // Indexing by element
          TElt& operator [] (int i);        // Indexing by element

    // Assignment operators
    TVec&   operator = (const TVec& v);
    TVec&   operator = (TVec&& v);

    using TRefVec::operator =;

    // Sizing
    void    SetSize(int n);           // (Re)size the vector, data will be uninitialised
    void    SetSize(TConstRefVec v);  // Set to same size as 'v'

    void    MakeNull();               // Make this a null (unallocated) vector
    bool    IsNull() const;           // Returns true if this is a null vector
};


class TConstVec : public TConstRefVec  
// ConstRefVec with associated storage. Use in place of 'const Vec'.
{
public:
    // Constructors
    TConstVec(const TConstVec& v);       // Copy constructor
    TConstVec(TConstVec&& v);            // Move constuctor

    TConstVec(int n, double elt0, ...);      // Vec(3, 1.1, 2.0, 3.4)
    TConstVec(std::initializer_list<TElt>);  // Vec(1.1, 2.0, 3.4)

    TConstVec(int n, VLBlock k);             // VLBlock vector (vl_0, vl_1 ...)
    TConstVec(int n, VLAxis a);              // Unit vector (vl_x, vl_y, ...)
    TConstVec(int n, VLMinusAxis a);         // -ve unit vector (vl_minus_x, vl_minus_y, ...)

    explicit TConstVec(TConstRefVec v);
    explicit TConstVec(TConstSliceVec v);

    template<class T, class U = typename T::IsVec> explicit TConstVec(const T& v);

   ~TConstVec();

    // Accessor methods
    using TConstRefVec::operator [];
};


// --- Vec Comparison Operators -----------------------------------------------

bool    operator == (TConstRefVec a, TConstRefVec b);
bool    operator != (TConstRefVec a, TConstRefVec b);

bool    same_size(TConstRefVec a, TConstRefVec b);

// --- Vec Arithmetic Operators -----------------------------------------------

TVec    operator + (TConstRefVec a, TConstRefVec b);
TVec    operator - (TConstRefVec a, TConstRefVec b);
TVec    operator * (TConstRefVec a, TConstRefVec b);
TVec    operator / (TConstRefVec a, TConstRefVec b);
TConstRefVec
        operator + (TConstRefVec v);
TVec    operator - (TConstRefVec v);
TVec    operator * (TConstRefVec v, TElt s);
TVec    operator * (TElt s, TConstRefVec v);
TVec    operator / (TConstRefVec v, TElt s);

TElt    dot      (TConstRefVec a, TConstRefVec b); // v . a
TElt    sqrlen   (TConstRefVec v);                 // v . v
TElt    sum      (TConstRefVec v);                 // ∑ v_i
#ifndef VL_NO_REAL
TElt    len      (TConstRefVec v);                 // || v ||
TVec    norm     (TConstRefVec v);                 // v / || v ||
TVec    norm_safe(TConstRefVec v);                 // v / || v ||, handles || v || = 0
#endif
TVec    abs      (TConstRefVec v);                 // | v_i |
TVec    clamped  (TConstRefVec v, TElt eps = TElt(1e-7));  // Clamp each entry |v_i| < eps to 0.

// Arbitrary per-element function application. E.g., sin(v) = transformed(v, std::sin)
TVec transformed(TConstRefVec v, TElt op(TElt));        // Returns 'v with 'op' applied to each element
void transform  (     TRefVec v, TElt op(TElt));        // Applies 'op' to each element of v
TElt reduced    (TConstRefVec v, TElt op(TElt, TElt));  // Returns op(a, b) applied in turn to each element of v

// --- Sub-vector functions ---------------------------------------------------

TConstRefVec  sub  (TConstRefVec v, int start, int length); // Return subvector
TConstRefVec  first(TConstRefVec v, int length);    // Return first 'length' elements of v
TConstRefVec  last (TConstRefVec v, int length);    // Return last 'length' elements of v

TRefVec       sub  (TRefVec      v, int start, int length);
TRefVec       first(TRefVec      v, int length);
TRefVec       last (TRefVec      v, int length);

// See SliceVec.h for further functions, e.g., reverse()

// --- Vec Functions ----------------------------------------------------------

void Add          (TConstRefVec a, TConstRefVec b, TRefVec result);
void Subtract     (TConstRefVec a, TConstRefVec b, TRefVec result);
void Multiply     (TConstRefVec a, TConstRefVec b, TRefVec result);
void Divide       (TConstRefVec a, TConstRefVec b, TRefVec result);
void Negate       (TConstRefVec v, TRefVec result);
void Multiply     (TConstRefVec v, TElt s, TRefVec result);
void MultiplyAccum(TConstRefVec v, TElt s, TRefVec result);
void Divide       (TConstRefVec v, TElt s, TRefVec result);
#ifndef VL_NO_REAL
void Normalize    (TConstRefVec v, TRefVec result);
void NormalizeSafe(TConstRefVec v, TRefVec result);
#endif
void Absolute     (TConstRefVec v, TRefVec result);
void Clamp        (TRefVec v, TElt eps = TElt(1e-7));


// --- Vec inlines ------------------------------------------------------------


// TConstRefVec

inline TConstRefVec::TConstRefVec() : data(0), elts(0)
{
}

inline TConstRefVec::TConstRefVec(int n, const TElt* d) :
    data(d), elts(n)
{
}

template<int ELTS> inline TConstRefVec::TConstRefVec(const TElt (&array)[ELTS]) :
    data(array), elts(ELTS)
{
}

#ifdef VL_VEC2_H
inline TConstRefVec::TConstRefVec(const TVec2& v) : data(v.Ref()), elts(v.Elts())
{
}

inline TConstRefVec::TConstRefVec(const TVec3& v) : data(v.Ref()), elts(v.Elts())
{
}

inline TConstRefVec::TConstRefVec(const TVec4& v) : data(v.Ref()), elts(v.Elts())
{
}
#endif

inline TConstRefVec::operator TConstSliceVec() const
{
    return TConstSliceVec(elts, 1, data);
}

inline int TConstRefVec::Elts() const
{
    return elts;
}

inline const TElt& TConstRefVec::operator [] (int i) const
{
    VL_INDEX_MSG(i, elts, "(Vec::[i]) index out of range");

    return data[i];
}

inline const TElt* TConstRefVec::Ref() const
{
    return data;
}

inline bool TConstRefVec::IsNull() const
{
    return data == 0;
}

inline void TConstRefVec::ReferTo(TConstRefVec v)
{
    data = v.data;
    elts = v.elts;
}


// TRefVec

inline TRefVec::TRefVec() : data(0), elts(0)
{
}

inline TRefVec::TRefVec(int n, TElt* d) :
    data(d), elts(n)
{
}

template<int ELTS> inline TRefVec::TRefVec(TElt (&array)[ELTS]) :
    data(array), elts(ELTS)
{
}

#ifdef VL_VEC2_H
inline TRefVec::TRefVec(TVec2& v) : data(v.Ref()), elts(v.Elts())
{
}

inline TRefVec::TRefVec(TVec3& v) : data(v.Ref()), elts(v.Elts())
{
}

inline TRefVec::TRefVec(TVec4& v) : data(v.Ref()), elts(v.Elts())
{
}
#endif

inline TRefVec::operator TConstRefVec() const
{
    return (TConstRefVec&) *this;
}

inline TRefVec::operator TSliceVec() const
{
    return TSliceVec(elts, 1, data);
}

inline int TRefVec::Elts() const
{
    return elts;
}

inline TElt& TRefVec::operator [] (int i) const
{
    VL_INDEX_MSG(i, elts, "(Vec::[i]) index out of range");

    return data[i];
}

inline TElt* TRefVec::Ref() const
{
    return data;
}

inline bool TRefVec::IsNull() const
{
    return data == 0;
}

#ifdef VL_VEC2_H
inline const TRefVec& TRefVec::operator = (const TVec2& v) const
{
    return *this = TConstRefVec(v);
}

inline const TRefVec& TRefVec::operator = (const TVec3& v) const
{
    return *this = TConstRefVec(v);
}

inline const TRefVec& TRefVec::operator = (const TVec4& v) const
{
    return *this = TConstRefVec(v);
}
#endif

inline const TRefVec& TRefVec::operator = (VLBlock k) const
{
    MakeBlock(TElt(k));
    return *this;
}

inline const TRefVec& TRefVec::operator = (VLAxis a) const
{
    MakeUnit(a);
    return *this;
}

inline const TRefVec& TRefVec::operator = (VLMinusAxis a) const
{
    MakeUnit(a, vl_minus_one);
    return *this;
}

template<class T, class U> inline const TRefVec& TRefVec::operator = (const T& v) const
{
    VL_ASSERT_MSG(v.Elts() == elts || v.Elts() == VL_REPEAT, "(Vec::=) Vector sizes don't match");

    for (int i = 0; i < elts; i++)
        data[i] = TElt(v[i]);

    return *this;
}

inline void TRefVec::ReferTo(TRefVec v)
{
    data = v.data;
    elts = v.elts;
}


// TVec

inline TVec::TVec() : TRefVec(0, 0)
{
}

inline TVec::TVec(int n) : TRefVec(n, VL_NEW TElt[n])
{
    VL_ASSERT_MSG(n > 0,"(Vec) illegal vector size");
}

inline TVec::TVec(int n, VLBlock k) : TRefVec(n, VL_NEW TElt[n])
{
    VL_ASSERT_MSG(n > 0,"(Vec) illegal vector size");
    MakeBlock(TElt(k));
}

inline TVec::TVec(int n, VLAxis a) : TRefVec(n, VL_NEW TElt[n])
{
    VL_ASSERT_MSG(n > 0,"(Vec) illegal vector size");
    MakeUnit(a);
}

inline TVec::TVec(int n, VLMinusAxis a) : TRefVec(n, VL_NEW TElt[n])
{
    VL_ASSERT_MSG(n > 0,"(Vec) illegal vector size");
    MakeUnit(a, vl_minus_one);
}

template<class T, class U> inline TVec::TVec(const T& v) : TRefVec(v.Elts(), VL_NEW TElt[v.Elts()])
{
    VL_ASSERT_MSG(data != 0, "(Vec) Out of memory");

    for (int i = 0; i < v.Elts(); i++)
        (*this)[i] = TElt(v[i]);
}

inline TVec::~TVec()
{
    VL_DELETE[] data;
    data = 0;
}

inline const TElt& TVec::operator [] (int i) const
{
    VL_INDEX_MSG(i, elts, "(Vec::[i]) index out of range");
    return data[i];
}

inline TElt& TVec::operator [] (int i)
{
    VL_INDEX_MSG(i, elts, "(Vec::[i]) index out of range");
    return data[i];
}

inline void TVec::SetSize(TConstRefVec v)
{
    SetSize(v.elts);
}

inline void TVec::MakeNull()
{
    VL_DELETE[] data;
    data = 0;
    elts = 0;
}

inline bool TVec::IsNull() const
{
    return elts == 0;
}

// TConstVec

inline TConstVec::TConstVec(int n, VLBlock k) : TConstRefVec(n, VL_NEW TElt[n])
{
    VL_ASSERT_MSG(n > 0,"(ConstVec) illegal vector size");

    TRefVec& self = (TRefVec&) *this;
    self.MakeBlock(TElt(k));
}

inline TConstVec::TConstVec(int n, VLAxis a) : TConstRefVec(n, VL_NEW TElt[n])
{
    VL_ASSERT_MSG(n > 0,"(ConstVec) illegal vector size");

    TRefVec& self = (TRefVec&) *this;
    self.MakeUnit(a);
}

inline TConstVec::TConstVec(int n, VLMinusAxis a) : TConstRefVec(n, VL_NEW TElt[n])
{
    VL_ASSERT_MSG(n > 0,"(ConstVec) illegal vector size");

    TRefVec& self = (TRefVec&) *this;
    self.MakeUnit(a, vl_minus_one);
}

template<class T, class U> inline TConstVec::TConstVec(const T& v) : TConstRefVec(v.Elts(), VL_NEW TElt[v.Elts()])
{
    VL_ASSERT_MSG(data != 0, "(ConstVec) Out of memory");

    TRefVec& self = (TRefVec&) *this;
    for (int i = 0; i < elts; i++)
        self[i] = TElt(v[i]);
}

inline TConstVec::~TConstVec()
{
    VL_DELETE[] data;
    data = 0;
}


// Operators

inline bool same_size(TConstRefVec a, TConstRefVec b)
{
    return a.elts == b.elts;
}

inline TConstRefVec operator + (TConstRefVec v)
{
    return v;
}

inline TElt sqrlen(TConstRefVec v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL

inline TElt len(TConstRefVec v)
{
    return sqrt(dot(v, v));
}

inline TVec norm(TConstRefVec v)
{
    VL_ASSERT_MSG(TElt(vl_0) < sqrlen(v), "normalising length-zero vector");
    TVec result(v.elts);
    Divide(v, len(v), result);
    return result;
}

inline TVec norm_safe(TConstRefVec v)
{
    TVec result(v.elts);
    Divide(v, len(v) + TElt(1e-8), result);
    return result;
}

#endif

inline TVec transformed(TConstRefVec v, TElt f(TElt))
{
    TVec result(v.elts);
    for (int i = 0; i < v.elts; i++)
        result[i] = f(v.data[i]);
    return result;
}

inline void transform(TRefVec v, TElt f(TElt))
{
    for (int i = 0; i < v.elts; i++)
        v.data[i] = f(v.data[i]);
}

inline TElt reduced(TConstRefVec v, TElt f(TElt, TElt))
{
    TElt result = v.data[0];
    for (int i = 1; i < v.elts; i++)
        result = f(result, v.data[i]);
    return result;
}

inline TElt reduced(TConstRefVec v, TElt f(TElt, TElt), TElt pre(TElt))
{
    TElt result = pre(v.data[0]);
    for (int i = 1; i < v.elts; i++)
        result = f(result, pre(v.data[i]));
    return result;
}

// From VecSlice.h
inline TVec transformed(TConstSliceVec v, TElt f(TElt))
{
    TVec result(v.elts);
    for (int i = 0; i < v.elts; i++)
        result[i] = f(v.data[i * v.span]);
    return result;
}

// Sub-vector

inline TConstRefVec sub(TConstRefVec v, int start, int length)
{
    VL_ASSERT_MSG(start >= 0 && length >= 0 && start + length <= v.elts,
        "(sub(Vec)) illegal subset of vector");

    return TConstRefVec(length, v.data + start);
}

inline TConstRefVec first(TConstRefVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts,
        "(first(Vec)) illegal subset of vector");

    return TConstRefVec(length, v.data);
}

inline TConstRefVec last(TConstRefVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts,
        "(last(Vec)) illegal subset of vector");

    return TConstRefVec(length, v.data + v.elts - length);
}

inline TRefVec sub(TRefVec v, int start, int length)
{
    VL_ASSERT_MSG(start >= 0 && length >= 0 && start + length <= v.elts,
        "(sub(Vec)) illegal subset of vector");

    return TRefVec(length, v.data + start);
}

inline TRefVec first(TRefVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts,
        "(first(Vec)) illegal subset of vector");

    return TRefVec(length, v.data);
}

inline TRefVec last(TRefVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts,
        "(last(Vec)) illegal subset of vector");

    return TRefVec(length, v.data + v.elts - length);
}

// ranged for

inline TElt const* begin(TConstRefVec v) { return v.data; }
inline TElt const* end  (TConstRefVec v) { return v.data + v.elts; }
inline TElt*       begin(TRefVec      v) { return v.data; }
inline TElt*       end  (TRefVec      v) { return v.data + v.elts; }

// Interop

#include "Ops.h"

VL_OPS(TVec, TConstRefVec)
VL_OPS(TVec, TConstSliceVec)

inline TConstSliceVec gen(TConstRefVec v) { return TConstSliceVec(v); }
inline      TSliceVec gen(     TRefVec v) { return      TSliceVec(v); }

VL_OPS_INTEROP1(TSliceVec, TConstRefVec, TSliceVec, TConstSliceVec)
VL_OPS_INTEROP1(TRefVec, TConstSliceVec, TSliceVec, TConstSliceVec)

#define VEC_INTEROP2(R, A, B) \
    inline TElt dot     (A a, B b)     { return dot((A) a, (A) b); } \
    inline TElt dot     (B a, A b)     { return dot((A) a, (A) b); } \

VL_OPS_INTEROP2(TVec, TConstSliceVec, TConstRefVec)
VEC_INTEROP2(TVec, TConstSliceVec, TConstRefVec)

#undef VEC_INTEROP2

#ifdef VL_VEC2_H
    inline TConstRefVec gen(const TVec2& v) { return TConstRefVec(v); }
    inline      TRefVec gen(      TVec2& v) { return      TRefVec(v); }
    inline TConstRefVec gen(const TVec3& v) { return TConstRefVec(v); }
    inline      TRefVec gen(      TVec3& v) { return      TRefVec(v); }
    inline TConstRefVec gen(const TVec4& v) { return TConstRefVec(v); }
    inline      TRefVec gen(      TVec4& v) { return      TRefVec(v); }

    VL_OPS_INTEROP1(TVec2&,  TConstRefVec, TRefVec, TConstRefVec)
    VL_OPS_INTEROP1(TVec3&,  TConstRefVec, TRefVec, TConstRefVec)
    VL_OPS_INTEROP1(TVec4&,  TConstRefVec, TRefVec, TConstRefVec)
    VL_OPS_INTEROP1(TVec2&,  TConstSliceVec, TRefVec, TConstSliceVec)
    VL_OPS_INTEROP1(TVec3&,  TConstSliceVec, TRefVec, TConstSliceVec)
    VL_OPS_INTEROP1(TVec4&,  TConstSliceVec, TRefVec, TConstSliceVec)
#endif

#endif

