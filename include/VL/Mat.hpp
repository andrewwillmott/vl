/*
    File:       Mat.hpp

    Function:   Defines a generic resizeable matrix.

    Copyright:  Andrew Willmott
 */

#ifndef VL_MAT_H
#define VL_MAT_H

#include "Vec.hpp"
#include "MatSlice.hpp"


// --- RefMat Classes ---------------------------------------------------------

class TConstRefMat : public VLMatType
// Reference to a constant matrix -- use this rather than const Mat&
{
public:
    typedef TConstRefVec Vec;

    // Constructors
                           TConstRefMat();
                           TConstRefMat(int rows, int cols, const TElt* data); // Create reference matrix
    template<int R, int C> TConstRefMat(const TElt (&array)[R][C]);            // Convenience C array wrapper

#ifdef VL_MAT2_H
    TConstRefMat(const TMat2& m);  // Mat234 interop
    TConstRefMat(const TMat3& m);
    TConstRefMat(const TMat4& m);
#endif

    operator TConstSliceMat() const;

    // Accessor methods
    int          Rows() const;
    int          Cols() const;
    int          Elts() const;                     // Total element count = rows x cols

    TConstRefVec operator [] (int i) const;        // Indexing by row
    const TElt&  operator () (int i, int j) const; // Indexing by element

    const TElt*  Ref() const;                      // Return pointer to data
    bool         IsNull() const;                   // True if we've not been initialised
    TConstRefVec AsVec() const;                    // Represent as vector

    // Updating
    void         ReferTo(TConstRefMat m);          // Replace current reference with 'm'

    // Data
    const TElt*  data;
    int          cols;
    int          rows;

    // Prevent assignment
    void operator = (TConstRefMat) = delete;
};


class TRefMat : public VLMatType
// Reference to a writable matrix -- use this rather than Mat& or Mat*, unless
// you need to control matrix size
{
public:
    typedef TRefVec Vec;

    // Constructors
                           TRefMat();
                           TRefMat(int rows, int cols, TElt* data); // Initialise reference to 'data'
    template<int R, int C> TRefMat(TElt (&array)[R][C]);            // Convenience C array wrapper

#ifdef VL_MAT2_H
    TRefMat(TMat2& m);  // Mat234 interop
    TRefMat(TMat3& m);
    TRefMat(TMat4& m);
#endif

    operator TConstRefMat() const;
    operator TSliceMat() const;

    // Accessor methods
    int            Rows() const;
    int            Cols() const;
    int            Elts() const;                     // Total element count = rows x cols

    TRefVec        operator [] (int i) const;        // Indexing by row
    TElt&          operator () (int i, int j) const; // Indexing by element

    TElt*          Ref() const;                      // Return pointer to data
    bool           IsNull() const;                   // True if we've not been initialised
    TRefVec        AsVec() const;                    // Represent as a vector

    // Assignment operators
    const TRefMat& operator =  (const TRefMat& m) const; // Necessary to avoid default shallow copy behaviour
    const TRefMat& operator =  (TConstRefMat   m) const; // Assign from dense matrix
    const TRefMat& operator =  (TConstSliceMat m) const; // Assign from matrix slice

#ifdef VL_MAT2_H
    const TRefMat& operator =  (const TMat2& m) const;
    const TRefMat& operator =  (const TMat3& m) const;
    const TRefMat& operator =  (const TMat4& m) const;
#endif

    const TRefMat& operator =  (VLDiag  k) const;        // Set diagonal matrix (usually identity, vl_I)
    const TRefMat& operator =  (VLBlock k) const;        // Set to a block matrix (vl_0, vl_1 ...)

    template<class T, class U = typename T::IsMat> const TRefMat& operator = (const T& v) const;

    // In-Place operators
    const TRefMat& operator += (TConstRefMat m) const;
    const TRefMat& operator -= (TConstRefMat m) const;
    const TRefMat& operator *= (TConstRefMat m) const;
    const TRefMat& operator /= (TConstRefMat m) const;
    const TRefMat& operator *= (TElt s) const;
    const TRefMat& operator /= (TElt s) const;

    // Matrix initialisers
    void           MakeZero() const;
    void           MakeIdentity() const;
    void           MakeDiag (TConstRefVec d) const;
    void           MakeDiag (TElt k = vl_one) const;
    void           MakeBlock(TElt k = vl_one) const;

    // Updating
    void           ReferTo(TRefMat m);  // Replace current reference with 'm'

    // Data
    TElt*          data;
    int            cols;
    int            rows;
};


// --- Mat Classes ------------------------------------------------------------

class TMat : public TRefMat
// RefMat with associated storage
{
public:
    typedef TVec Vec;

    // Constructors
    TMat();                                     // Null matrix: no space allocated
    TMat(const TMat& m);                        // Copy constructor
    TMat(TMat&& m);                             // Move constructor

    TMat(int rows, int cols);                   // Uninitialised rows x cols matrix
    TMat(int rows, int cols, double elt0, ...); // Mat(2, 2, 1.0, 2.0, 3.0, 4.0)
    TMat(std::initializer_list<TVec>);          // Mat({row_v0, row_v1, ...})
    
    TMat(TConstRefVec diagonal);                // diag(M) = diagonal
    TMat(int rows, int cols, VLDiag  k);        // diagonal matrix k
    TMat(int rows, int cols, VLBlock k);        // block matrix k

    explicit TMat(TConstRefMat m);
    explicit TMat(TConstSliceMat m);

    template<class T, class U = typename T::IsMat> explicit TMat(const T& m);

    ~TMat();

    // Accessor methods
    TConstRefVec operator [] (int i) const;        // Indexing by row
    TRefVec      operator [] (int i);              // Indexing by row
    const TElt&  operator () (int i, int j) const; // Indexing by element
          TElt&  operator () (int i, int j);       // Indexing by element

    // Assignment operators
    TMat&         operator = (const TMat& m);
    TMat&         operator = (TMat&& m);

    using TRefMat::operator =;

    // Sizing
    void    SetSize(int rows, int cols);  // (Re)size the matrix, data will be uninitialised
    void    SetSize(TConstRefMat m);      // Set to same size as 'm'

    void    MakeNull();                   // Make this a null (unallocated) matrix
    bool    IsNull() const;               // Returns true if this is a null matrix
};


class TConstMat : public TConstRefMat
// ConstRefMat with associated storage. Use in place of 'const Mat'.
{
public:
    typedef TConstVec Vec;

    TConstMat(const TConstMat& m);       // Copy constructor
    TConstMat(TConstMat&& m);            // Move constructor

    TConstMat(int rows, int cols, double elt0, ...); // Mat(2, 2, 1.0, 2.0, 3.0, 4.0)
    TConstMat(std::initializer_list<TConstVec>);     // Mat({row_v0, row_v1, ...})

    TConstMat(TConstRefVec diagonal);                // diag(M) = diagonal
    TConstMat(int rows, int cols, VLDiag  k);        // diagonal matrix k
    TConstMat(int rows, int cols, VLBlock k);        // block matrix k

    explicit TConstMat(TConstRefMat m);
    explicit TConstMat(TConstSliceMat m);

    template<class T, class U = typename T::IsMat> explicit TConstMat(const T& m);

    ~TConstMat();

    // Accessor methods
    using TConstRefMat::operator [];
    using TConstRefMat::operator ();
};


// --- Mat Comparison Operators -----------------------------------------------

bool    operator == (TConstRefMat a, TConstRefMat b);
bool    operator != (TConstRefMat a, TConstRefMat b);

bool    is_square(TConstRefMat m);
bool    same_size(TConstRefMat a, TConstRefMat b);

// --- Mat Arithmetic Operators -----------------------------------------------

TMat    operator + (TConstRefMat a, TConstRefMat b);
TMat    operator - (TConstRefMat a, TConstRefMat b);
TMat    operator * (TConstRefMat a, TConstRefMat b);
TMat    operator / (TConstRefMat a, TConstRefMat b);
TConstRefMat
        operator + (TConstRefMat m);
TMat    operator - (TConstRefMat m);

TMat    operator * (TConstRefMat m, TElt s);
TMat    operator * (TElt s, TConstRefMat m);
TMat    operator / (TConstRefMat m, TElt s);

TVec    operator * (TConstRefMat m, TConstRefVec v);
TVec    operator * (TConstRefVec v, TConstRefMat m);

TElt    trace  (TConstRefMat m);                           // Trace: sum(diag(M))
TElt    sum    (TConstRefMat m);                           // ∑ m_i_j
TElt    sumsqr (TConstRefMat m);                           // Sum of elements squared

#ifndef VL_NO_REAL
TElt    frob   (TConstRefMat m);                           // Frobenius norm: sqrt(sumsqr(m))
TMat    inv    (TConstRefMat m, TElt* determinant = 0, TElt eps = TElt(1e-20));
#endif

TMat    trans  (TConstRefMat m);                           // Transpose: M_t
TMat    abs    (TConstRefMat m);                           // | m_i_j |
TMat    clamped(TConstRefMat m, TElt eps = TElt(1e-7));    // Clamp each entry |e| < eps to 0.
TMat    hprod  (TConstRefMat a, TConstRefMat b);           // Hadamard product: component-wise multiply of a and b
TMat    oprod  (TConstRefVec a, TConstRefVec b);           // Outer product: a_t b

// Arbitrary per-element function application. E.g., sin(m) = transformed(m, std::sin)
TMat    transformed(TConstRefMat m, TElt op(TElt));        // Returns 'm with 'op' applied to each element
void    transform  (     TRefMat m, TElt op(TElt));        // Applies 'op' to each element of m
TElt    reduced    (TConstRefMat m, TElt op(TElt, TElt));  // Returns op applied cumulatively to each element of m: op(m00, op(m01, op(m02, ...)
TElt    reduced    (TConstRefMat m, TElt op(TElt, TElt), TElt pre(TElt));  // As above, but pre() is applied to each element first.

// --- Mat Functions ----------------------------------------------------------

void    Add          (TConstRefMat a, TConstRefMat b, TRefMat result);
void    Subtract     (TConstRefMat a, TConstRefMat b, TRefMat result);
void    Multiply     (TConstRefMat a, TConstRefMat b, TRefMat result);
void    Divide       (TConstRefMat a, TConstRefMat b, TRefMat result);
void    Negate       (TConstRefMat m, TRefMat result);
void    Multiply     (TConstRefMat m, TElt s, TRefMat result);
void    MultiplyAccum(TConstRefMat m, TElt s, TRefMat result);
void    Divide       (TConstRefMat m, TElt s, TRefMat result);

void    Multiply(TConstRefMat m, TConstRefVec v, TRefVec result);
void    Multiply(TConstRefVec v, TConstRefMat m, TRefVec result);

void    Transpose      (TConstRefMat m, TRefMat result);
void    Absolute       (TConstRefMat m, TRefMat result);
void    Clamp          (TRefMat      m, TElt eps = TElt(1e-7));
TElt    InnerProduct   (TConstRefMat a, TConstRefMat b);
void    OuterProduct   (TConstRefVec a, TConstRefVec b, TRefMat result);
void    HadamardProduct(TConstRefMat a, TConstRefMat b, TRefMat result);

#ifndef VL_NO_REAL
bool    Invert(TConstRefMat m, TRefMat result, TElt* determinant = 0, TElt epsilon = TElt(1e-20));
#endif

// --- Mat Inlines ------------------------------------------------------------

// TConstRefMat

inline TConstRefMat::TConstRefMat() : data(0), cols(0), rows(0)
{
}

inline TConstRefMat::TConstRefMat(int r, int c, const TElt* d) :
    data(d), cols(c), rows(r)
{
}

template<int ROWS, int COLS> inline TConstRefMat::TConstRefMat(const TElt (&array)[ROWS][COLS]) :
    data(array[0]), cols(COLS), rows(ROWS)
{
}

#ifdef VL_MAT2_H
inline TConstRefMat::TConstRefMat(const TMat2& m) : data(m.Ref()), cols(2), rows(2)
{
}

inline TConstRefMat::TConstRefMat(const TMat3& m) : data(m.Ref()), cols(3), rows(3)
{
}

inline TConstRefMat::TConstRefMat(const TMat4& m) : data(m.Ref()), cols(4), rows(4)
{
}
#endif

inline TConstRefMat::operator TConstSliceMat() const
{
   return TConstSliceMat(rows, cols, cols, 1, data);
}

inline int TConstRefMat::Rows() const
{
    return rows;
}

inline int TConstRefMat::Cols() const
{
    return cols;
}

inline int TConstRefMat::Elts() const
{
    return cols * rows;
}

inline TConstRefVec TConstRefMat::operator [] (int i) const
{
    VL_INDEX_MSG(i, rows, "(Mat::[i]) i index out of range");

    return TConstRefVec(cols, data + i * cols);
}

inline const TElt& TConstRefMat::operator () (int i, int j) const
{
    VL_INDEX_MSG(i, rows, "(Mat::(i,j)) i index out of range");
    VL_INDEX_MSG(j, cols, "(Mat::(i,j)) j index out of range");

    return data[i * cols + j];
}

inline const TElt* TConstRefMat::Ref() const
{
    return data;
}

inline bool TConstRefMat::IsNull() const
{
    return data == 0;
}

inline TConstRefVec TConstRefMat::AsVec() const
{
    return TConstRefVec(Elts(), data);
}

inline void TConstRefMat::ReferTo(TConstRefMat m)
{
    data = m.data;
    cols = m.cols;
    rows = m.rows;
}


// TRefMat

inline TRefMat::TRefMat() : data(0), cols(0), rows(0)
{
}

inline TRefMat::TRefMat(int r, int c, TElt* d) :
    data(d), cols(c), rows(r)
{
}

template<int ROWS, int COLS> inline TRefMat::TRefMat(TElt (&array)[ROWS][COLS]) :
    data(array[0]), cols(COLS), rows(ROWS)
{
}

#ifdef VL_MAT2_H
inline TRefMat::TRefMat(TMat2& m) : data(m.Ref()), cols(2), rows(2)
{
}

inline TRefMat::TRefMat(TMat3& m) : data(m.Ref()), cols(3), rows(3)
{
}

inline TRefMat::TRefMat(TMat4& m) : data(m.Ref()), cols(4), rows(4)
{
}
#endif

inline TRefMat::operator TConstRefMat() const
{
    return (TConstRefMat&) *this;
}

inline TRefMat::operator TSliceMat() const
{
   return TSliceMat(rows, cols, cols, 1, data);
}

inline int TRefMat::Rows() const
{
    return rows;
}

inline int TRefMat::Cols() const
{
    return cols;
}

inline int TRefMat::Elts() const
{
    return cols * rows;
}

inline TRefVec TRefMat::operator [] (int i) const
{
    VL_INDEX_MSG(i, rows, "(Mat::[i]) i index out of range");

    return TRefVec(cols, data + i * cols);
}

inline TElt& TRefMat::operator () (int i, int j) const
{
    VL_INDEX_MSG(i, rows, "(Mat::(i,j)) i index out of range");
    VL_INDEX_MSG(j, cols, "(Mat::(i,j)) j index out of range");

    return data[i * cols + j];
}

inline TElt* TRefMat::Ref() const
{
    return data;
}

inline bool TRefMat::IsNull() const
{
    return data == 0;
}

inline TRefVec TRefMat::AsVec() const
{
    return TRefVec(Elts(), data);
}

#ifdef VL_MAT2_H
inline const TRefMat& TRefMat::operator = (const TMat2& m) const
{
    return *this = TConstRefMat(m);
}

inline const TRefMat& TRefMat::operator = (const TMat3& m) const
{
    return *this = TConstRefMat(m);
}

inline const TRefMat& TRefMat::operator = (const TMat4& m) const
{
    return *this = TConstRefMat(m);
}
#endif

inline const TRefMat& TRefMat::operator = (VLDiag k) const
{
    MakeDiag(TElt(k));
    return *this;
}

inline const TRefMat& TRefMat::operator = (VLBlock k) const
{
    MakeBlock(TElt(k));
    return *this;
}

template<class T, class U> inline const TRefMat& TRefMat::operator = (const T& v) const
{
    VL_ASSERT_MSG(v.Rows() == rows || v.Rows() == VL_REPEAT, "(Mat::=) Matrix rows don't match");

    for (int i = 0; i < rows; i++)
        (*this)[i] = v[i];

    return *this;
}

inline void TRefMat::ReferTo(TRefMat m)
{
    data = m.data;
    cols = m.cols;
    rows = m.rows;
}


// TMat

inline TMat::TMat() : TRefMat(0, 0, 0)
{
}

inline TMat::TMat(int r, int c) : TRefMat(r, c, VL_NEW TElt[r * c])
{
    VL_ASSERT_MSG(rows > 0 && cols > 0, "(Mat) illegal matrix size");
}

inline TMat::TMat(TConstRefVec d) : TRefMat(d.elts, d.elts, VL_NEW TElt[d.elts * d.elts])
{
    MakeDiag(d);
}

inline TMat::TMat(int r, int c, VLDiag k) : TRefMat(r, c, VL_NEW TElt[r * c])
{
    VL_ASSERT_MSG(rows > 0 && cols > 0, "(Mat) illegal matrix size");
    MakeDiag(TElt(k));
}

inline TMat::TMat(int r, int c, VLBlock k) : TRefMat(r, c, VL_NEW TElt[r * c])
{
    VL_ASSERT_MSG(rows > 0 && cols > 0, "(Mat) illegal matrix size");
    MakeBlock(TElt(k));
}

template<class T, class U> inline TMat::TMat(const T& m) : TRefMat(m.Rows(), m.Cols(), VL_NEW TElt[m.Elts()])
{
    VL_ASSERT_MSG(data != 0, "(Mat) Out of memory");

    for (int i = 0; i < m.Rows(); i++)
        (*this)[i] = m[i];
}

inline TMat::~TMat()
{
    VL_DELETE[] data;
    data = 0;
}

inline TRefVec TMat::operator [] (int i)
{
    VL_INDEX_MSG(i, rows, "(Mat::[i]) i index out of range");

    return TRefVec(cols, data + i * cols);
}

inline TElt& TMat::operator () (int i, int j)
{
    VL_INDEX_MSG(i, rows, "(Mat::(i,j)) i index out of range");
    VL_INDEX_MSG(j, cols, "(Mat::(i,j)) j index out of range");

    return data[i * cols + j];
}

inline TConstRefVec TMat::operator [] (int i) const
{
    VL_INDEX_MSG(i, rows, "(Mat::[i]) i index out of range");

    return TConstRefVec(cols, data + i * cols);
}

inline const TElt& TMat::operator () (int i, int j) const
{
    VL_INDEX_MSG(i, rows, "(Mat::(i,j)) i index out of range");
    VL_INDEX_MSG(j, cols, "(Mat::(i,j)) j index out of range");

    return data[i * cols + j];
}

inline void TMat::SetSize(TConstRefMat m)
{
    SetSize(m.rows, m.cols);
}

inline void TMat::MakeNull()
{
    VL_DELETE[] data;
    data   = 0;
    cols   = 0;
    rows   = 0;
}

inline bool TMat::IsNull() const
{
    return cols == 0;
}

// TConstMat

inline TConstMat::TConstMat(TConstRefVec d) : TConstRefMat(d.elts, d.elts, VL_NEW TElt[d.elts * d.elts])
{
    TRefMat& self = (TRefMat&) *this;
    self.MakeDiag(d);
}

inline TConstMat::TConstMat(int r, int c, VLDiag k) : TConstRefMat(r, c, VL_NEW TElt[r * c])
{
    VL_ASSERT_MSG(rows > 0 && cols > 0, "(ConstMat) illegal matrix size");

    TRefMat& self = (TRefMat&) *this;
    self.MakeDiag(TElt(k));
}

inline TConstMat::TConstMat(int r, int c, VLBlock k) : TConstRefMat(r, c, VL_NEW TElt[r * c])
{
    VL_ASSERT_MSG(rows > 0 && cols > 0, "(ConstMat) illegal matrix size");

    TRefMat& self = (TRefMat&) *this;
    self.MakeBlock(TElt(k));
}

template<class T, class U> inline TConstMat::TConstMat(const T& m) : TConstRefMat(m.Rows(), m.Cols(), VL_NEW TElt[m.Elts()])
{
    VL_ASSERT_MSG(data != 0, "(ConstMat) Out of memory");

    TRefMat& self = (TRefMat&) *this;
    for (int i = 0; i < m.Rows(); i++)
        self[i] = m[i];
}

inline TConstMat::~TConstMat()
{
    VL_DELETE[] data;
    data = 0;
}


// Operators

inline bool operator == (TConstRefMat a, TConstRefMat b)
{
    VL_ASSERT_MSG(same_size(a, b), "(Mat::==) Matrix dimensions don't match");

    return a.AsVec() == b.AsVec();
}

inline bool operator != (TConstRefMat a, TConstRefMat b)
{
    VL_ASSERT_MSG(same_size(a, b), "(Mat::==) Matrix dimensions don't match");

    return a.AsVec() != b.AsVec();
}

inline bool is_square(TConstRefMat m)
{
    return m.rows == m.cols;
}

inline bool same_size(TConstRefMat a, TConstRefMat b)
{
    return a.cols == b.cols && a.rows == b.rows;
}

inline TConstRefMat operator + (TConstRefMat m)
{
    return m;
}

inline TElt trace(TConstRefMat m)
{
    TElt result = vl_0;

    for (int i = 0; i < m.rows; i++)
        result += m(i, i);

    return result;
}

inline TElt sum(TConstRefMat m)
{
    return sum(m.AsVec());
}

inline TElt sumsqr(TConstRefMat m)
{
    return sqrlen(m.AsVec());
}

#ifndef VL_NO_REAL
inline TElt frob(TConstRefMat m)
{
    return len(m.AsVec());
}
#endif

inline TMat transformed(TConstRefMat m, TElt f(TElt))
{
    TMat result(m.rows, m.cols);
    for (int i = 0, n = m.rows * m.cols; i < n; i++)
        result.data[i] = f(m.data[i]);
    return result;
}

inline void transform(TRefMat m, TElt f(TElt))
{
    for (int i = 0, n = m.rows * m.cols; i < n; i++)
        m.data[i] = f(m.data[i]);
}

inline TElt reduced(TConstRefMat m, TElt f(TElt, TElt))
{
    return reduced(m.AsVec(), f);
}

inline TElt reduced(TConstRefMat m, TElt f(TElt, TElt), TElt pre(TElt))
{
    return reduced(m.AsVec(), f, pre);
}

// Interop

#include "Ops.hpp"

VL_OPS(TMat, TConstRefMat)
VL_OPS(TMat, TConstSliceMat)

inline TConstSliceMat gen(TConstRefMat m) { return TConstSliceMat(m); }
inline      TSliceMat gen(     TRefMat m) { return      TSliceMat(m); }

VL_OPS_INTEROP1(TSliceMat, TConstRefMat, TSliceMat, TConstSliceMat)
VL_OPS_INTEROP1(TRefMat, TConstSliceMat, TSliceMat, TConstSliceMat)

#define MAT_INTEROP2(R, A, B) \
    inline R hprod      (A a, B b) { return hprod(a, (A) b); } \
    inline R hprod      (B b, A a) { return hprod((A) b, a); } \
    inline R oprod      (A::Vec a, B::Vec b) { return oprod(a, (A::Vec) b); } \
    inline R oprod      (B::Vec b, A::Vec a) { return oprod((A::Vec) b, a); } \
    inline R::Vec operator * (A::Vec v, B m) { return operator* (v, (A) m); }      \
    inline R::Vec operator * (B::Vec v, A m) { return operator* ((A::Vec) v, m); } \
    inline R::Vec operator * (B m, A::Vec v) { return operator* ((A) m, v); }      \
    inline R::Vec operator * (A m, B::Vec v) { return operator* (m, (A::Vec) v); } \

VL_OPS_INTEROP2(TMat, TConstSliceMat, TConstRefMat)
MAT_INTEROP2(TMat, TConstSliceMat, TConstRefMat)

#undef MAT_INTEROP2

#ifdef VL_MAT2_H
    inline TConstRefMat gen(const TMat2& m) { return TConstRefMat(m); }
    inline      TRefMat gen(      TMat2& m) { return      TRefMat(m); }
    inline TConstRefMat gen(const TMat3& m) { return TConstRefMat(m); }
    inline      TRefMat gen(      TMat3& m) { return      TRefMat(m); }
    inline TConstRefMat gen(const TMat4& m) { return TConstRefMat(m); }
    inline      TRefMat gen(      TMat4& m) { return      TRefMat(m); }

    VL_OPS_INTEROP1(TMat2&, TConstRefMat,   TRefMat, TConstRefMat)
    VL_OPS_INTEROP1(TMat3&, TConstRefMat,   TRefMat, TConstRefMat)
    VL_OPS_INTEROP1(TMat4&, TConstRefMat,   TRefMat, TConstRefMat)
    VL_OPS_INTEROP1(TMat2&, TConstSliceMat, TRefMat, TConstSliceMat)
    VL_OPS_INTEROP1(TMat3&, TConstSliceMat, TRefMat, TConstSliceMat)
    VL_OPS_INTEROP1(TMat4&, TConstSliceMat, TRefMat, TConstSliceMat)
#endif

#endif
