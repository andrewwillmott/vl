/*
    File:       Vol.h

    Function:   Defines a generic resizeable volume, defined as a stack of matrices.

    Copyright:  Andrew Willmott
 */

#ifndef VL_VOL_H
#define VL_VOL_H

#include "Mat.h"
#include "VolSlice.h"


// --- RefVol Classes ---------------------------------------------------------

class TConstRefVol : public VLVolType
// Reference to a constant volume -- use this rather than const Vol&
{
public:
    typedef TConstRefMat Mat;

    // Constructors
                                  TConstRefVol();
                                  TConstRefVol(int slices, int rows, int cols, const TElt* data);  // Initialise reference to 'data'
    template<int S, int R, int C> TConstRefVol(const TElt (&array)[S][R][C]); // Convenience C array wrapper

    operator TConstSliceVol() const;

    // Accessor methods
    int           Slices() const;
    int           Rows()   const;
    int           Cols()   const;
    int           Elts()   const;               // Total element count = rows x cols

    TConstRefMat  operator [] (int i) const;                // Indexing by slice
    const TElt&   operator () (int i, int j, int k) const;  // Indexing by element

    const TElt*   Ref() const;                  // Return pointer to data
    bool          IsNull() const;               // True if we've not been initialised
    TConstRefVec  AsVec() const;                // Represent as vector of size 'Elts()'
    TConstRefMat  AsMat() const;                // Represent as matrix of (rows x slices) x cols.

    // Updating
    void          ReferTo(TConstRefVol v);      // Replace current reference with 'v'

    // Data
    const TElt*   data;
    int           cols;
    int           rows;
    int           slices;

    // Prevent assignment
    void operator = (TConstRefVol) = delete;
};


class TRefVol : public VLVolType
// Reference to a writable volume -- use this rather than Vol& or Vol*, unless
// you need to control volume size
{
public:
    typedef TRefMat Mat;

    // Constructors
                                  TRefVol();
                                  TRefVol(int slices, int rows, int cols, TElt* data); // // Initialise reference to 'data'
    template<int S, int R, int C> TRefVol(TElt (&array)[S][R][C]); // Convenience C array wrapper

    operator TConstRefVol() const;
    operator TSliceVol() const;

    // Accessor methods
    int           Slices() const;
    int           Rows()   const;
    int           Cols()   const;
    int           Elts()   const;                 // Total element count = slices x rows x cols

    TRefMat       operator [] (int i) const;                // Indexing by slice
    TElt&         operator () (int i, int j, int k) const;  // Indexing by element

    TElt*         Ref() const;                    // Return pointer to data
    bool          IsNull() const;                 // True if we've not been initialised
    TRefVec       AsVec() const;                  // Represent as vector
    TRefMat       AsMat() const;                  // Represent as matrix of (rows x slices) x cols.

    // Assignment operators
    const TRefVol& operator =  (const TRefVol& v) const; // Necessary to avoid default shallow copy behaviour
    const TRefVol& operator =  (TConstRefVol   v) const; // Assign from dense volume
    const TRefVol& operator =  (TConstSliceVol v) const; // Assign from volume slice

    const TRefVol& operator =  (VLBlock k) const;        // Set to a block volume...

    template<class T, class U = typename T::IsVol> const TRefVol& operator = (const T& v) const;

    // In-Place Operators
    const TRefVol& operator += (TConstRefVol v) const;
    const TRefVol& operator -= (TConstRefVol v) const;
    const TRefVol& operator *= (TConstRefVol v) const;
    const TRefVol& operator /= (TConstRefVol v) const;
    const TRefVol& operator *= (TElt s) const;
    const TRefVol& operator /= (TElt s) const;

    // Volume initialisers
    void           MakeZero() const;
    void           MakeBlock(TElt k = vl_one) const;

    // Updating
    void           ReferTo(TRefVol v);             // Replace current reference with 'v'

    // Data
    TElt*         data;
    int           cols;
    int           rows;
    int           slices;
};


// --- Vol Classes ------------------------------------------------------------


class TVol : public TRefVol
// RefVol with associated storage
{
public:
    typedef TMat Mat;

    // Constructors
    TVol();                          // Null volume: no space allocated
    TVol(const TVol& v);             // Copy constructor
    TVol(TVol&& v);                  // Move constructor

    TVol(int slices, int rows, int cols);             // Uninitialised volume
    TVol(std::initializer_list<TMat>);                // Vol({slice_m0, slice_m1, ...})

    TVol(int slices, int rows, int cols, VLBlock k);  // VLBlock volume (v[i][j][k] = k)

    explicit TVol(TConstRefVol v);
    explicit TVol(TConstSliceVol v);

    template<class T, class U = typename T::IsVol> explicit TVol(const T& m);

    ~TVol();

    // Accessor methods
    TConstRefMat operator [] (int i) const;               // Indexing by slice
    TRefMat      operator [] (int i);                     // Indexing by row
    const TElt&  operator () (int i, int j, int k) const; // Indexing by element
          TElt&  operator () (int i, int j, int k);       // Indexing by element

    // Assignment operators
    TVol&         operator = (const TVol& v);
    TVol&         operator = (TVol&& v);

    using TRefVol::operator =;

    // Sizing
    void    SetSize(int slices, int rows, int cols); // (Re)size the volume, data will be uninitialised
    void    SetSize(TConstRefVol v);                 // Set to same size as 'v'

    void    MakeNull();             // Make this a null (unallocated) volume
    bool    IsNull() const;         // Returns true if this is a null volume
};


class TConstVol : public TConstRefVol
// ConstRefVol with associated storage. Use in place of 'const Vol'.
{
public:
    typedef TConstVec Vec;
    typedef TConstMat Mat;

    TConstVol(const TConstVol& v);       // Copy constructor
    TConstVol(TConstVol&& v);            // Move constructor

    TConstVol(std::initializer_list<TConstMat>);     // Vol({slice_m0, slice_m1, ...})

    TConstVol(int slices, int rows, int cols, VLBlock k);        // block matrix k

    explicit TConstVol(TConstRefVol v);
    explicit TConstVol(TConstSliceVol v);

    template<class T, class U = typename T::IsVol> explicit TConstVol(const T& m);

    ~TConstVol();

    // Accessor methods
    using TConstRefVol::operator [];
    using TConstRefVol::operator ();
};


// --- Vol Comparison Operators -----------------------------------------------

bool    operator == (TConstRefVol a, TConstRefVol b);
bool    operator != (TConstRefVol a, TConstRefVol b);

bool    is_cubic (TConstRefVol v);
bool    same_size(TConstRefVol a, TConstRefVol b);

// --- Vol Arithmetic Operators -----------------------------------------------

TVol    operator + (TConstRefVol a, TConstRefVol b);
TVol    operator - (TConstRefVol a, TConstRefVol b);
TVol    operator * (TConstRefVol a, TConstRefVol b);
TVol    operator / (TConstRefVol a, TConstRefVol b);
TConstRefVol
        operator + (TConstRefVol m);
TVol    operator - (TConstRefVol v);
TVol    operator * (TConstRefVol v, TElt s);
TVol    operator * (TElt s, TConstRefVol v);
TVol    operator / (TConstRefVol v, TElt s);

TElt    sum    (TConstRefVol v);                           // ∑ v_i_j_k
TElt    sumsqr (TConstRefVol v);                           // Sum of elements squared
#ifndef VL_NO_REAL
TElt    frob   (TConstRefVol v);                           // Frobenius norm: sqrt(sumsqr(m))
#endif

TVol    abs    (TConstRefVol v);                           // | v_i_j_k |
TVol    clamped(TConstRefVol v, TElt eps = TElt(1e-7));    // Clamp each entry |e| < eps to 0.
TVol    hprod  (TConstRefVol a, TConstRefVol b);           // Hadamard product: component-wise multiply of a and b
TVol    oprod  (TConstRefVec a, TConstRefVec b, TConstRefVec c);  // Outer product: a x b x c

// Arbitrary per-element function application. E.g., sin(m) = transformed(m, std::sin)
TVol    transformed(TConstRefVol v, TElt op(TElt));        // Returns 'm with 'op' applied to each element
void    transform  (     TRefVol v, TElt op(TElt));        // Applies 'op' to each element of m
TElt    reduced    (TConstRefVol v, TElt op(TElt, TElt));  // Returns op applied cumulatively to each element of m: op(m00, op(m01, op(m02, ...)
TElt    reduced    (TConstRefVol v, TElt op(TElt, TElt), TElt pre(TElt));  // As above, but pre() is applied to each element first.

// --- Vol Functions ----------------------------------------------------------

void Add          (TConstRefVol a, TConstRefVol b, TRefVol result);
void Subtract     (TConstRefVol a, TConstRefVol b, TRefVol result);
void Multiply     (TConstRefVol a, TConstRefVol b, TRefVol result);
void Divide       (TConstRefVol a, TConstRefVol b, TRefVol result);
void Negate       (TConstRefVol v, TRefVol result);
void Multiply     (TConstRefVol v, TElt s, TRefVol result);
void MultiplyAccum(TConstRefVol v, TElt s, TRefVol result);
void Divide       (TConstRefVol v, TElt s, TRefVol result);
void Absolute     (TConstRefVol v, TRefVol result);
void Clamp        (TRefVol v, TElt eps = TElt(1e-7));

TElt InnerProduct   (TConstRefVol  a, TConstRefVol  b);
void OuterProduct   (TConstRefVec a, TConstRefVec b, TConstRefVec c, TRefVol r);
void HadamardProduct(TConstRefVol a, TConstRefVol b, TRefVol result);


// --- Vol Inlines ------------------------------------------------------------

// TConstRefMat

inline TConstRefVol::TConstRefVol() : data(0), cols(0), rows(0), slices(0)
{
}

inline TConstRefVol::TConstRefVol(int s, int r, int c, const TElt* d) :
    data(d), cols(c), rows(r), slices(s)
{
}

template<int SLICES, int ROWS, int COLS> inline TConstRefVol::TConstRefVol(const TElt (&array)[SLICES][ROWS][COLS]) :
    data(array[0]), cols(COLS), rows(ROWS), slices(SLICES)
{
}

inline TConstRefVol::operator TConstSliceVol() const
{
    return TConstSliceVol(slices, rows, cols, rows * cols, cols, 1, data);
}

inline int TConstRefVol::Slices() const
{
    return slices;
}

inline int TConstRefVol::Rows() const
{
    return rows;
}

inline int TConstRefVol::Cols() const
{
    return cols;
}

inline int TConstRefVol::Elts() const
{
    return cols * rows * slices;
}

inline TConstRefMat TConstRefVol::operator [] (int i) const
{
    VL_INDEX_MSG(i, slices, "(Vol::[i]) i index out of range");

    return TConstRefMat(rows, cols, data + i * cols * rows);
}

inline const TElt& TConstRefVol::operator () (int i, int j, int k) const
{
    VL_INDEX_MSG(i, rows,   "(Vol::(i,j,k)) i index out of range");
    VL_INDEX_MSG(j, cols,   "(Vol::(i,j,k)) j index out of range");
    VL_INDEX_MSG(k, slices, "(Vol::(i,j,k)) k index out of range");

    return data[i * cols * rows + j * cols + k];
}

inline const TElt* TConstRefVol::Ref() const
{
    return data;
}

inline bool TConstRefVol::IsNull() const
{
    return data == 0;
}

inline TConstRefMat TConstRefVol::AsMat() const
{
    return TConstRefMat(rows * slices, cols, data);
}

inline TConstRefVec TConstRefVol::AsVec() const
{
    return TConstRefVec(Elts(), data);
}

inline void TConstRefVol::ReferTo(TConstRefVol v)
{
    data   = v.data;
    cols   = v.cols;
    rows   = v.rows;
    slices = v.slices;
}


// TRefVol

inline TRefVol::TRefVol() : data(0), cols(0), rows(0), slices(0)
{
}

inline TRefVol::TRefVol(int s, int r, int c, TElt* d) :
    data(d), cols(c), rows(r), slices(s)
{
}

template<int SLICES, int ROWS, int COLS> inline TRefVol::TRefVol(TElt (&array)[SLICES][ROWS][COLS]) :
    data(array[0]), cols(COLS), rows(ROWS), slices(SLICES)
{
}

inline TRefVol::operator TConstRefVol() const
{
    return (TConstRefVol&) *this;
}

inline TRefVol::operator TSliceVol() const
{
    return TSliceVol(slices, rows, cols, rows * cols, cols, 1, data);
}

inline int TRefVol::Slices() const
{
    return slices;
}

inline int TRefVol::Rows() const
{
    return rows;
}

inline int TRefVol::Cols() const
{
    return cols;
}

inline int TRefVol::Elts() const
{
    return cols * rows * slices;
}

inline TRefMat TRefVol::operator [] (int i) const
{
    VL_INDEX_MSG(i, slices, "(Vol::[i]) i index out of range");

    return TRefMat(rows, cols, data + i * cols * rows);
}

inline TElt& TRefVol::operator () (int i, int j, int k) const
{
    VL_INDEX_MSG(i, slices, "(Vol::(i,j,k)) i index out of range");
    VL_INDEX_MSG(j, rows,   "(Vol::(i,j,k)) j index out of range");
    VL_INDEX_MSG(k, cols,   "(Vol::(i,j,k)) k index out of range");

    return data[i * cols * rows + j * cols + k];
}

inline TElt* TRefVol::Ref() const
{
    return data;
}

inline bool TRefVol::IsNull() const
{
    return data == 0;
}

inline TRefVec TRefVol::AsVec() const
{
    return TRefVec(Elts(), data);
}

inline TRefMat TRefVol::AsMat() const
{
    return TRefMat(rows * slices, cols, data);
}


inline const TRefVol& TRefVol::operator = (VLBlock k) const
{
    MakeBlock(TElt(k));
    return *this;
}

template<class T, class U> inline const TRefVol& TRefVol::operator = (const T& v) const
{
    VL_ASSERT_MSG(v.Slices() == slices || v.Slices() == VL_REPEAT, "(Vol::=) Volume slices don't match");

    for (int i = 0; i < slices; i++)
        (*this)[i] = v[i];

    return *this;
}

inline void TRefVol::ReferTo(TRefVol v)
{
    data   = v.data;
    cols   = v.cols;
    rows   = v.rows;
    slices = v.slices;
}

// TVol

inline TVol::TVol() : TRefVol(0, 0, 0, 0)
{
}

inline TVol::TVol(int s, int r, int c) : TRefVol(s, r, c, VL_NEW TElt[s * r * c])
{
    VL_ASSERT_MSG(slices > 0 && rows > 0 && cols > 0, "(Vol) illegal volume size");
}

inline TVol::TVol(int s, int r, int c, VLBlock k) : TRefVol(s, r, c, VL_NEW TElt[s * r * c])
{
    VL_ASSERT_MSG(slices > 0 && rows > 0 && cols > 0, "(Vol) illegal volume size");
    MakeBlock(TElt(k));
}

template<class T, class U> inline TVol::TVol(const T& v) : TRefVol(v.Slices(), v.Rows(), v.Cols(), VL_NEW TElt[v.Elts()])
{
    VL_ASSERT_MSG(data != 0, "(Vol) Out of memory");

    for (int i = 0; i < v.Slices(); i++)
        (*this)[i] = Mat(v[i]);
}

inline TVol::~TVol()
{
    VL_DELETE[] data;
    data = 0;
}

inline TRefMat TVol::operator [] (int i)
{
    VL_INDEX_MSG(i, slices, "(Vol::[i]) i index out of range");

    return TRefMat(rows, cols, data + i * cols * rows);
}

inline TElt& TVol::operator () (int i, int j, int k)
{
    VL_INDEX_MSG(i, slices, "(Vol::(i,j,k)) i index out of range");
    VL_INDEX_MSG(j, rows,   "(Vol::(i,j,k)) j index out of range");
    VL_INDEX_MSG(k, cols,   "(Vol::(i,j,k)) k index out of range");

    return data[i * cols * rows + j * cols + k];
}

inline TConstRefMat TVol::operator [] (int i) const
{
    VL_INDEX_MSG(i, slices, "(Vol::[i]) i index out of range");

    return TConstRefMat(rows, cols, data + i * cols * rows);
}

inline const TElt& TVol::operator () (int i, int j, int k) const
{
    VL_INDEX_MSG(i, slices, "(Vol::(i,j,k)) i index out of range");
    VL_INDEX_MSG(j, rows,   "(Vol::(i,j,k)) j index out of range");
    VL_INDEX_MSG(k, cols,   "(Vol::(i,j,k)) k index out of range");

    return data[i * cols * rows + j * cols + k];
}

inline void TVol::SetSize(TConstRefVol v)
{
    SetSize(v.slices, v.rows, v.cols);
}

inline void TVol::MakeNull()
{
    VL_DELETE[] data;
    data   = 0;
    cols   = 0;
    rows   = 0;
    slices = 0;
}

inline bool TVol::IsNull() const
{
    return cols == 0;
}

// TConstVol

inline TConstVol::TConstVol(int s, int r, int c, VLBlock k) : TConstRefVol(s, r, c, VL_NEW TElt[s * r * c])
{
    VL_ASSERT_MSG(slices > 0 && rows > 0 && cols > 0, "(ConstVol) illegal volume size");

    TRefVol& self = (TRefVol&) *this;
    self.MakeBlock(TElt(k));
}

template<class T, class U> inline TConstVol::TConstVol(const T& v) : TConstRefVol(v.Slices(), v.Rows(), v.Cols(), VL_NEW TElt[v.Elts()])
{
    VL_ASSERT_MSG(data != 0, "(ConstVol) Out of memory");

    TRefVol& self = (TRefVol&) *this;
    for (int i = 0; i < v.Slices(); i++)
        self[i] = Mat(v[i]);
}

inline TConstVol::~TConstVol()
{
    VL_DELETE[] data;
    data = 0;
}


// Operators

inline bool operator == (TConstRefVol a, TConstRefVol b)
{
    VL_ASSERT_MSG(same_size(a, b), "(Vol::==) Volume dimensions don't match");

    return a.AsVec() == b.AsVec();
}

inline bool operator != (TConstRefVol a, TConstRefVol b)
{
    VL_ASSERT_MSG(same_size(a, b), "(Vol::==) Volume dimensions don't match");

    return !(a.AsVec() == b.AsVec());
}

inline bool is_cubic(TConstRefVol v)
{
    return (v.slices == v.rows) && (v.slices == v.cols);
}

inline bool same_size(TConstRefVol a, TConstRefVol b)
{
    return a.cols == b.cols && a.rows == b.rows && a.slices == b.slices;
}

inline TConstRefVol operator + (TConstRefVol v)
{
    return v;
}

inline TElt sum(TConstRefVol v)
{
    return sum(v.AsVec());
}

inline TElt sumsqr(TConstRefVol v)
{
    return sqrlen(v.AsVec());
}

#ifndef VL_NO_REAL
inline TElt frob(TConstRefVol v)
{
    return len(v.AsVec());
}
#endif

inline TVol transformed(TConstRefVol v, TElt f(TElt))
{
    TVol result(v.slices, v.rows, v.cols);
    for (int i = 0, n = v.slices * v.rows * v.cols; i < n; i++)
        result.data[i] = f(v.data[i]);
    return result;
}

inline void transform(TRefVol v, TElt f(TElt))
{
    for (int i = 0, n = v.slices * v.rows * v.cols; i < n; i++)
        v.data[i] = f(v.data[i]);
}

inline TElt reduced(TConstRefVol v, TElt f(TElt, TElt))
{
    return reduced(v.AsVec(), f);
}

inline TElt reduced(TConstRefVol v, TElt f(TElt, TElt), TElt pre(TElt))
{
    return reduced(v.AsVec(), f, pre);
}

// Interop

#include "Ops.h"

VL_OPS(TVol, TConstRefVol)
VL_OPS(TVol, TConstSliceVol)

inline TConstSliceVol gen(TConstRefVol& v) { return TConstSliceVol(v); }
inline      TSliceVol gen(     TRefVol& v) { return      TSliceVol(v); }

VL_OPS_INTEROP1(TSliceVol, TConstRefVol, TSliceVol, TConstSliceVol)
VL_OPS_INTEROP1(TRefVol, TConstSliceVol, TSliceVol, TConstSliceVol)

#define VOL_INTEROP2(R, A, B) \
    inline R hprod(A a, B b) { return hprod(a, (A) b); } \
    inline R hprod(B a, A b) { return hprod((A) a, b); } \

VL_OPS_INTEROP2(TVol, TConstSliceVol, TConstRefVol)
VOL_INTEROP2(TVol, TConstSliceVol, TConstRefVol)

#undef VOL_INTEROP2

#endif
