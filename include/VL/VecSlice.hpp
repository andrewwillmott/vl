/*
    File:       VecSlice.hpp

    Function:   Defines a vector with a per-element stride, commonly used for
                representing sub-vectors of a dense matrix

    Copyright:  Andrew Willmott
 */

#ifndef VL_VEC_SLICE_H
#define VL_VEC_SLICE_H

class TVec;
class TConstRefVec;
class TRefVec;

// --- SliceVec Classes -------------------------------------------------------

class TConstSliceVec : public VLVecType
{
public:
    // Constructors
    TConstSliceVec(int n, int span, const TElt data[]);

    // Accessor functions
    int         Elts() const;
    TElt        operator [] (int i) const;

    // Data
    const TElt* data;
    int         elts;
    int         span;

    // Prevent assignment
    void operator = (TConstSliceVec v) = delete;
};

class TSliceVec : public VLVecType
{
public:
    // Constructors
    TSliceVec(int n, int span, TElt data[]);

    operator TConstSliceVec() const;

    // Accessor functions
    int               Elts() const;

    TElt&             operator [] (int i) const;

    // Assignment operators
    const TSliceVec&  operator = (const TSliceVec& v) const; // Necessary to avoid default shallow copy behaviour
    const TSliceVec&  operator = (TConstSliceVec v) const;   // Assignment of a vector slice
    const TSliceVec&  operator = (TRefVec v) const;          // Assignment of a vector ref
    const TSliceVec&  operator = (TConstRefVec v) const;     // Assignment of a vector ref

#ifdef VL_VEC2_H
    const TSliceVec&  operator = (const TVec2& v) const;
    const TSliceVec&  operator = (const TVec3& v) const;
    const TSliceVec&  operator = (const TVec4& v) const;
#endif

    const TSliceVec&  operator = (VLBlock     b) const;
    const TSliceVec&  operator = (VLAxis      a) const;
    const TSliceVec&  operator = (VLMinusAxis a) const;

    // In-Place operators
    const TSliceVec&  operator += (TConstSliceVec b) const;
    const TSliceVec&  operator -= (TConstSliceVec b) const;
    const TSliceVec&  operator *= (TConstSliceVec b) const;
    const TSliceVec&  operator /= (TConstSliceVec b) const;
    const TSliceVec&  operator *= (TElt s) const;
    const TSliceVec&  operator /= (TElt s) const;

    // Vector initialisers
    void              MakeZero() const;
    void              MakeUnit(int i, TElt k = vl_one) const;
    void              MakeBlock(TElt k = vl_one) const;

    // Data
    TElt*             data;
    int               elts;
    int               span;
};


// --- SliceVec Comparison Operators ------------------------------------------

bool operator == (TConstSliceVec a, TConstSliceVec b);
bool operator != (TConstSliceVec a, TConstSliceVec b);

bool same_size(TConstSliceVec a, TConstSliceVec b);


// --- SliceVec Arithmetic Operators ------------------------------------------

TVec    operator + (TConstSliceVec a, TConstSliceVec b);
TVec    operator - (TConstSliceVec a, TConstSliceVec b);
TVec    operator * (TConstSliceVec a, TConstSliceVec b);
TVec    operator / (TConstSliceVec a, TConstSliceVec b);

TConstSliceVec
        operator + (TConstSliceVec v);
TVec    operator - (TConstSliceVec v);

TVec    operator * (TConstSliceVec v, TElt s);
TVec    operator * (TElt s, TConstSliceVec v);
TVec    operator / (TConstSliceVec v, TElt s);

TElt    dot(TConstSliceVec a, TConstSliceVec b); // v . a
TElt    sqrlen     (TConstSliceVec v);           // v . v
TElt    sum        (TConstSliceVec v);           // ∑ v_i
#ifndef VL_NO_REAL
TElt    len        (TConstSliceVec v);           // || v ||
TVec    norm       (TConstSliceVec v);           // v / || v ||
TVec    norm_safe  (TConstSliceVec v);           // v / || v ||, handles || v || = 0
#endif
TVec    abs        (TConstSliceVec v);           // | v_i |
TVec    clamped    (TConstSliceVec v, TElt eps = TElt(1e-7));  // Clamp each entry |v_i| < eps to 0.

// Arbitrary per-element function application. E.g., sin(v) = transformed(v, std::sin<float>)
TVec transformed(TConstSliceVec v, TElt op(TElt));        // Returns 'v with 'op' applied to each element
void transform  (TSliceVec      v, TElt op(TElt));        // Applies 'op' to each element of v
TElt reduced    (TConstSliceVec v, TElt op(TElt, TElt));  // Returns op(a, b) applied in turn to each element of v

// --- SliceVec functions -----------------------------------------------------

TConstSliceVec sub    (TConstSliceVec v, int start, int n);  // Return sub vector
TConstSliceVec first  (TConstSliceVec v, int n);             // Return first 'n' elements
TConstSliceVec last   (TConstSliceVec v, int n);             // Return last 'n' elements
TConstSliceVec reverse(TConstSliceVec v);                    // Return reversed vector
TConstSliceVec repeat (const TElt& elt,  int n = VL_REPEAT); // Return 'elt' repeated 'n' times

TSliceVec      sub    (TSliceVec      v, int start, int n);
TSliceVec      first  (TSliceVec      v, int n);
TSliceVec      last   (TSliceVec      v, int n);
TSliceVec      reverse(TSliceVec v);



// --- SliceVec Inlines -------------------------------------------------------

// TConstSliceVec

inline int TConstSliceVec::Elts() const
{
    return elts;
}

inline TElt TConstSliceVec::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, elts, "Vec::[i]");

    return data[i * span];
}

// TSliceVec

inline TSliceVec::operator TConstSliceVec() const
{
    return (TConstSliceVec&) *this;
}

inline int TSliceVec::Elts() const
{
    return elts;
}

inline TElt& TSliceVec::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, elts, "Vec::[i]");

    return data[i * span];
}

// Assignment operators

inline const TSliceVec& TSliceVec::operator = (VLBlock k) const
{
    MakeBlock(TElt(k));
    return *this;
}

inline const TSliceVec& TSliceVec::operator = (VLAxis a) const
{
    MakeUnit(a);
    return *this;
}

inline const TSliceVec& TSliceVec::operator = (VLMinusAxis a) const
{
    MakeUnit(a, vl_minus_one);
    return *this;
}

// Comparison Operators

inline bool operator != (TConstSliceVec a, TConstSliceVec b)
{
    return !(a == b);
}

inline bool same_size(TConstSliceVec a, TConstSliceVec b)
{
    return a.elts == b.elts;
}


// Vec Arithmetic Operators

inline TConstSliceVec operator + (TConstSliceVec v)
{
    return v;
}

inline TElt sqrlen(TConstSliceVec v)
{
    return dot(v, v);
}

#ifndef VL_NO_REAL
inline TElt len(TConstSliceVec v)
{
    return sqrt(TElt(dot(v, v)));
}
#endif

// Because 'transformed' has TVec dep it must go in Vec.hpp

inline void transform(TSliceVec v, TElt f(TElt))
{
    for (int i = 0; i < v.elts; i++)
        v[i] = f(v[i]);
}

inline TElt reduced(TConstSliceVec v, TElt f(TElt, TElt))
{
    TElt result = v[0];
    for (int i = 1; i < v.elts; i++)
        result = f(result, v[i]);
    return result;
}

// Sub-vector functions

inline TConstSliceVec sub(TConstSliceVec v, int start, int length)
{
    VL_ASSERT_MSG(start >= 0 && length >= 0 && start + length <= v.elts, "(sub(Vec)) illegal subset of vector");

    return TConstSliceVec(length, v.span, v.data + start * v.span);
}

inline TConstSliceVec first(TConstSliceVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts, "(first(Vec)) illegal subset of vector");

    return TConstSliceVec(length, v.span, v.data);
}

inline TConstSliceVec last(TConstSliceVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts, "(last(Vec)) illegal subset of vector");

    return TConstSliceVec(length, v.span, v.data + (v.elts - length) * v.span);
}

inline TConstSliceVec reverse(TConstSliceVec v)
{
    return TConstSliceVec(v.elts, -v.span, v.data + (v.elts - 1) * v.span);
}

inline TConstSliceVec repeat(const TElt& elt, int n)
{
    return TConstSliceVec(n, 0, &elt);
}

inline TSliceVec sub(TSliceVec v, int start, int length)
{
    VL_ASSERT_MSG(start >= 0 && length >= 0 && start + length <= v.elts, "(sub(Vec)) illegal subset of vector");

    return TSliceVec(length, v.span, v.data + start * v.span);
}

inline TSliceVec first(TSliceVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts, "(first(Vec)) illegal subset of vector");

    return TSliceVec(length, v.span, v.data);
}

inline TSliceVec last(TSliceVec v, int length)
{
    VL_ASSERT_MSG(length >= 0 && length <= v.elts, "(last(Vec)) illegal subset of vector");

    return TSliceVec(length, v.span, v.data + (v.elts - length) * v.span);
}

inline TSliceVec reverse(TSliceVec v)
{
    return TSliceVec(v.elts, -v.span, v.data + (v.elts - 1) * v.span);
}

// Ranged for

#define TConstSliceIter VL_V_SUFF(ConstSliceIter)
#define TSliceIter VL_V_SUFF(SliceIter)

struct TConstSliceIter
{
    const TElt* data; int span;

    TConstSliceIter(const TElt* dataIn, int spanIn) : data(dataIn), span(spanIn) {}
    void         operator ++ () { data += span; }
    bool         operator != (const TConstSliceIter& other) const { return data != other.data; }
    const TElt&  operator *  () const { return *data; }
};

struct TSliceIter
{
    TElt* data; int span;

    TSliceIter(TElt* dataIn, int spanIn) : data(dataIn), span(spanIn) {}
    TElt&  operator *  () const { return *data; }
    void   operator ++ () { data += span; }
    bool   operator != (const TSliceIter& other) const { return data != other.data; }
};

inline TConstSliceIter begin(TConstSliceVec v) { return TConstSliceIter(v.data, v.span); }
inline TConstSliceIter end  (TConstSliceVec v) { return TConstSliceIter(v.data + v.elts * v.span, 0); }
inline      TSliceIter begin(     TSliceVec v) { return      TSliceIter(v.data, v.span); }
inline      TSliceIter end  (     TSliceVec v) { return      TSliceIter(v.data + v.elts * v.span, 0); }

#endif
