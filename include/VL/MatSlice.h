/*
    File:       MatSlice.h

    Function:   Defines a matrix with separate strides for rows and columns,
                commonly used for representing sub-matrices of a dense matrix

    Copyright:  Andrew Willmott
 */

#ifndef VL_MAT_SLICE_H
#define VL_MAT_SLICE_H

#include "VecSlice.h"

class TMat;
class TConstRefMat;
class TRefMat;


// --- SliceMat Classes -------------------------------------------------------

class TConstSliceMat : public VLMatType
{
public:
    typedef TConstSliceVec Vec;

    // Constructors
    TConstSliceMat();
    TConstSliceMat(int r, int c, int rspan, int cspan, const TElt data[]);

    // Accessor functions
    int            Rows() const;
    int            Cols() const;
    int            Elts() const;

    TConstSliceVec operator [] (int i) const;
    const TElt&    operator () (int i, int j) const;

    // Data
    const TElt*    data;
    int            cols;
    int            cspan;
    int            rows;
    int            rspan;

    // Prevent assignment
    void operator = (TConstSliceMat m) = delete;
};

class TSliceMat : public VLMatType
{
public:
    typedef TSliceVec Vec;

    // Constructors
    TSliceMat();
    TSliceMat(int r, int c, int rspan, int cspan, TElt data[]);

    operator TConstSliceMat() const;

    // Accessor functions
    int               Rows() const;
    int               Cols() const;
    int               Elts() const;

    TSliceVec         operator [] (int i) const;
    TElt&             operator () (int i, int j) const;

    // Assignment operators
    const TSliceMat&  operator = (const TSliceMat& m) const; // Necessary to avoid default shallow copy behaviour
    const TSliceMat&  operator = (TConstSliceMat m) const;   // Assignment of a matrix slice
    const TSliceMat&  operator = (TRefMat m) const;          // Assignment of a matrix ref
    const TSliceMat&  operator = (TConstRefMat m) const;     // Assignment of a matrix ref

#ifdef VL_MAT2_H
    const TSliceMat&  operator = (const TMat2& m) const;
    const TSliceMat&  operator = (const TMat3& m) const;
    const TSliceMat&  operator = (const TMat4& m) const;
#endif

    const TSliceMat&  operator = (VLDiag  k) const;          // Set to k * I...
    const TSliceMat&  operator = (VLBlock k) const;          // Set to a block matrix...

    // In-Place Operators
    const TSliceMat&  operator += (TConstSliceMat m) const;
    const TSliceMat&  operator -= (TConstSliceMat m) const;
    const TSliceMat&  operator *= (TConstSliceMat m) const;
    const TSliceMat&  operator /= (TConstSliceMat m) const;
    const TSliceMat&  operator *= (TElt s) const;
    const TSliceMat&  operator /= (TElt s) const;

    // Matrix initialisers
    void              MakeZero() const;
    void              MakeIdentity() const;
    void              MakeDiag (TElt k) const;
    void              MakeBlock(TElt k) const;

    // Data
    TElt*             data;
    int               cols;
    int               cspan;
    int               rows;
    int               rspan;
};


// --- SliceMat Comparison Operators ------------------------------------------

bool    operator == (TConstSliceMat a, TConstSliceMat b);
bool    operator != (TConstSliceMat a, TConstSliceMat b);

bool    same_size(TConstRefMat a, TConstRefMat b);
bool    is_square(TConstRefMat m);


// --- SliceMat Arithmetic Operators ------------------------------------------

TMat    operator + (TConstSliceMat m, TConstSliceMat n);
TMat    operator - (TConstSliceMat m, TConstSliceMat n);
TMat    operator * (TConstSliceMat m, TConstSliceMat n);
TMat    operator / (TConstSliceMat m, TConstSliceMat n);

TConstSliceMat
        operator + (TConstSliceMat m);
TMat    operator - (TConstSliceMat m);

TMat    operator * (TConstSliceMat m, TElt s);
TMat    operator * (TElt s, TConstSliceMat m);
TMat    operator / (TConstSliceMat m, TElt s);

TVec    operator * (TConstSliceMat m, TConstSliceVec v);
TVec    operator * (TConstSliceVec v, TConstSliceMat m);

TElt    trace  (TConstSliceMat m);                        // Trace: sum(diag(M))
TElt    sum    (TConstSliceMat m);                        // ∑ m_i_j
TElt    sumsqr (TConstSliceMat m);                        // Sum of elements squared

#ifndef VL_NO_REAL
TElt    frob   (TConstSliceMat m);                        // Frobenius norm: sqrt(sumsqr(m))
TMat    inv    (TConstSliceMat m, TElt* determinant = 0, TElt eps = TElt(1e-20));
#endif

TMat    trans  (TConstSliceMat m);                        // Transpose: M_t
TMat    abs    (TConstSliceMat m);                        // | m_i_j |
TMat    clamped(TConstSliceMat m, TElt eps = TElt(1e-7)); // Clamp each entry |e| < eps to 0.
TMat    hprod  (TConstSliceMat m, TConstSliceMat n);      // Hadamard product: component-wise multiply of m and n
TMat    oprod  (TConstSliceVec a, TConstSliceVec b);      // Outer product: a_t b

// Arbitrary per-element function application. E.g., sin(m) = transformed(m, std::sin)
TMat    transformed(TConstSliceMat m, TElt op(TElt));        // Returns 'm with 'op' applied to each element
void    transform  (     TSliceMat m, TElt op(TElt));        // Applies 'op' to each element of m
TElt    reduced    (TConstSliceMat m, TElt op(TElt, TElt));  // Returns op(a, b) applied in turn to each element of m

// --- SliceMat functions -----------------------------------------------------

TConstSliceMat  sub      (TConstSliceMat m, int i, int j, int rows, int cols);  // returns sub matrix
TConstSliceMat  first    (TConstSliceMat m, int rows, int cols);    // returns first (upper-left) rows/cols of matrix
TConstSliceMat  last     (TConstSliceMat m, int rows, int cols);    // returns last (lower-right) rows/cols of matrix

TConstSliceVec  row      (TConstSliceMat m, int i);                 // row 'i'
TConstSliceVec  col      (TConstSliceMat m, int i);                 // col 'j'
TConstSliceVec  diag     (TConstSliceMat m, int i = 0);             //  -i = diag. starting on row i, +i = diag. starting on col i
TConstSliceMat  transpose(TConstSliceMat m);                        // transpose of 'm'

TConstSliceMat  repeat   (const TElt& elt,  int rows, int cols);    // return elt repeated for the given rows/cols count
TConstSliceMat  repeat   (TConstSliceVec v, int rows = VL_REPEAT);  // returns given vector repeated 'rows' times

TSliceMat       sub      (TSliceMat      m, int i, int j, int rows, int cols);  // returns sub matrix
TSliceMat       first    (TSliceMat      m, int rows, int cols);    // returns first (upper-left) rows/cols of matrix
TSliceMat       last     (TSliceMat      m, int rows, int cols);    // returns last (lower-right) rows/cols of matrix

TSliceVec       row      (TSliceMat      m, int i);                 // row 'i'
TSliceVec       col      (TSliceMat      m, int i);                 // col 'j'
TSliceVec       diag     (TSliceMat      m, int i = 0);             //  -i = diag. starting on row i, +i = diag. starting on col i
TSliceMat       transpose(TSliceMat      m);                        // transpose of 'm'

TConstSliceMat  repeat   (TSliceVec      v, int rows = VL_REPEAT);  // returns given vector repeated 'rows' times


// --- SliceMat Inlines -------------------------------------------------------


// TConstSliceMat

inline TConstSliceMat::TConstSliceMat() : data(0), cols(0), cspan(0), rows(0), rspan(0)
{
}

inline TConstSliceMat::TConstSliceMat(int r, int c, int rs, int cs, const TElt data[]) :
    data (data),
    cols (c),
    cspan(cs),
    rows (r),
    rspan(rs)
{
}

inline int TConstSliceMat::Rows() const
{
    return rows;
}

inline int TConstSliceMat::Cols() const
{
    return cols;
}

inline int TConstSliceMat::Elts() const
{
    return cols * rows;
}

inline TConstSliceVec TConstSliceMat::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, rows, "(SliceMat::(i)) index out of range");
    return TConstSliceVec(cols, cspan, data + i * rspan);
}

inline const TElt& TConstSliceMat::operator() (int i, int j) const
{
    VL_RANGE_MSG(i, 0, rows, "(SliceMat::(i,j)) i index out of range");
    VL_RANGE_MSG(j, 0, cols, "(SliceMat::(i,j)) j index out of range");
    return data[i * rspan + j * cspan];
}

// TSliceMat

inline TSliceMat::TSliceMat() : data(0), cols(0), cspan(0), rows(0), rspan(0)
{
}

inline TSliceMat::TSliceMat(int r, int c, int rs, int cs, TElt data[]) :
    data (data),
    cols (c),
    cspan(cs),
    rows (r),
    rspan(rs)
{
}

inline TSliceMat::operator TConstSliceMat() const
{
    return (TConstSliceMat&) *this;
}

inline int TSliceMat::Rows() const
{
    return rows;
}

inline int TSliceMat::Cols() const
{
    return cols;
}

inline int TSliceMat::Elts() const
{
    return cols * rows;
}

inline TSliceVec TSliceMat::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, rows, "(SliceMat::(i)) index out of range");
    return TSliceVec(cols, cspan, data + i * rspan);
}

inline TElt& TSliceMat::operator() (int i, int j) const
{
    VL_RANGE_MSG(i, 0, rows, "(SliceMat::(i,j)) i index out of range");
    VL_RANGE_MSG(j, 0, cols, "(SliceMat::(i,j)) j index out of range");
    return data[i * rspan + j * cspan];
}

// Comparison Operators

inline bool operator != (TConstSliceMat a, TConstSliceMat b)
{
    return !(a == b);
}

inline bool same_size(TConstSliceMat a, TConstSliceMat b)
{
    return a.cols == b.cols && a.rows == b.rows;
}

inline bool is_square(TConstSliceMat m)
{
    return m.rows == m.cols;
}

// Mat Arithmetic Operators

inline TConstSliceMat operator + (TConstSliceMat m)
{
    return m;
}

inline TElt trace(TConstSliceMat m)
{
    TElt  result = vl_0;

    for (int i = 0; i < m.rows; i++)
        result += m(i, i);

    return result;
}

#endif
