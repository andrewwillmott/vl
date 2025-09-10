/*
    File:       VolSlice.hpp

    Function:   Defines a volume with separate strides for slices/rows/columns,
                commonly used for representing sub-volumes of a dense volumes

    Copyright:  Andrew Willmott
 */

#ifndef VL_VOL_SLICE_H
#define VL_VOL_SLICE_H

#include "MatSlice.hpp"

class TVol;
class TConstRefVol;
class TRefVol;


// --- SliceVol Classes -------------------------------------------------------

class TConstSliceVol : public VLVolType
{
public:
    typedef TConstSliceVec Vec;
    typedef TConstSliceMat Mat;

    // Constructors
    TConstSliceVol(int s, int r, int c, int sspan, int rspan, int cspan, const TElt data[]);

    // Accessor functions
    int            Slices() const;
    int            Rows() const;
    int            Cols() const;
    int            Elts() const;

    TConstSliceMat operator [] (int i) const;
    const TElt&    operator () (int i, int j, int k) const;

    // Data
    const TElt*    data;
    int            cols;
    int            cspan;
    int            rows;
    int            rspan;
    int            slices;
    int            sspan;

    // Prevent assignment
    void operator = (TConstSliceVol v) = delete;
};

class TSliceVol : public VLVolType
{
public:
    typedef TSliceVec Vec;
    typedef TSliceMat Mat;

    // Constructors
    TSliceVol(int s, int r, int c, int sspan, int rspan, int cspan, TElt data[]);

    operator TConstSliceVol() const;

    // Accessor functions
    int               Slices() const;
    int               Rows() const;
    int               Cols() const;
    int               Elts() const;

    TSliceMat         operator [] (int i) const;
    TElt&             operator () (int i, int j, int k) const;

    // Assignment operators
    const TSliceVol&  operator = (const TSliceVol& v) const; // Necessary to avoid default shallow copy behaviour
    const TSliceVol&  operator = (TConstSliceVol v) const;   // Assignment of a volume slice
    const TSliceVol&  operator = (TRefVol v) const;          // Assignment of a volume ref
    const TSliceVol&  operator = (TConstRefVol v) const;     // Assignment of a volume ref

    const TSliceVol&  operator = (VLDiag  k) const;          // Set to k * I...
    const TSliceVol&  operator = (VLBlock k) const;          // Set to a block matrix...

    // In-Place Operators
    const TSliceVol&  operator += (TConstSliceVol v) const;
    const TSliceVol&  operator -= (TConstSliceVol v) const;
    const TSliceVol&  operator *= (TConstSliceVol v) const;
    const TSliceVol&  operator /= (TConstSliceVol v) const;
    const TSliceVol&  operator *= (TElt s) const;
    const TSliceVol&  operator /= (TElt s) const;

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
    int               slices;
    int               sspan;
};


// --- SliceVol Comparison Operators ------------------------------------------

bool    operator == (TConstSliceVol a, TConstSliceVol b);
bool    operator != (TConstSliceVol a, TConstSliceVol b);

bool    same_size(TConstRefVol a, TConstRefVol b);
bool    is_cubic (TConstRefVol v);


// --- SliceVol Arithmetic Operators ------------------------------------------

TVol    operator + (TConstSliceVol a, TConstSliceVol b);
TVol    operator - (TConstSliceVol a, TConstSliceVol b);
TVol    operator * (TConstSliceVol a, TConstSliceVol b);
TVol    operator / (TConstSliceVol a, TConstSliceVol b);

TConstSliceVol
        operator + (TConstSliceVol v);
TVol    operator - (TConstSliceVol v);

TVol    operator * (TConstSliceVol v, TElt s);
TVol    operator * (TElt s, TConstSliceVol v);
TVol    operator / (TConstSliceVol v, TElt s);

TElt    sum    (TConstSliceVol v);                           // ∑ v_i_j_k
TElt    sumsqr (TConstSliceVol v);                           // Sum of elements squared
TElt    frob   (TConstSliceVol v);                           // Frobenius norm: sqrt(sumsqr(m))

TVol    abs    (TConstSliceVol v);                           // | v_i_j_k |
TVol    clamped(TConstSliceVol v, TElt eps = TElt(1e-7));    // Clamp each entry |e| < eps to 0.
TVol    hprod  (TConstSliceVol a, TConstSliceVol b);         // Hadamard product: component-wise multiply of a and b
TVol    oprod  (TConstSliceVec a, TConstSliceVec b, TConstSliceVec c); // Outer product: a x b x c

// Arbitrary per-element function application. E.g., sin(v) = transformed(v, std::sin)
TVol    transformed(TConstSliceVol v, TElt op(TElt));        // Returns 'v with 'op' applied to each element
void    transform  (     TSliceVol v, TElt op(TElt));        // Applies 'op' to each element of v
TElt    reduced    (TConstSliceVol v, TElt op(TElt, TElt));  // Returns op(a, b) applied in turn to each element of v

// --- SliceVol functions -----------------------------------------------------

TConstSliceVol  sub      (TConstSliceVol v, int i, int j, int k, int slices, int rows, int cols);  // slices x rows x cols block at (i, j, k)
TConstSliceVol  first    (TConstSliceVol v, int slices, int rows, int cols);  // top-upper-left slices x rows x cols block
TConstSliceVol  last     (TConstSliceVol v, int slices, int rows, int cols);  // bottom-lower-right slices x rows x cols block

TConstSliceVec  slice    (TConstSliceVol v, int j, int k);  // vector at row j, col k
TConstSliceVec  row      (TConstSliceVol v, int i, int j);  // vector at slice i, row j
TConstSliceVec  col      (TConstSliceVol v, int i, int k);  // vector at slice i, col k

TConstSliceMat  slice_x  (TConstSliceVol v, int k);         // slice (2d image/matrix) in x direction, at col k
TConstSliceMat  slice_y  (TConstSliceVol v, int j);         // slice (2d image/matrix) in y direction, at row j
TConstSliceMat  slice_z  (TConstSliceVol v, int i);         // slice (2d image/matrix) in z direction, at slice i

TConstSliceVol  repeat   (const TElt&    e, int slices, int rows, int cols);  // repeat 'elt' over the given block
TConstSliceVol  repeat   (TConstSliceVec v, int slices, int rows);            // repeat 'v' for 'rows' rows and 'slices' slices
TConstSliceVol  repeat   (TConstSliceMat m, int slices = VL_REPEAT);          // repeat 'm' over 'slices' slices

TSliceVol       sub      (TSliceVol      v, int i, int j, int k, int slices, int rows, int cols);  // slices x rows x cols block at (i, j, k)
TSliceVol       first    (TSliceVol      v, int slices, int rows, int cols);  // top-upper-left slices x rows x cols block
TSliceVol       last     (TSliceVol      v, int slices, int rows, int cols);  // bottom-lower-right slices x rows x cols block

TSliceVec       slice    (TSliceVol      v, int j, int k);  // vector at row j, col k
TSliceVec       row      (TSliceVol      v, int i, int j);  // vector at slice i, row j
TSliceVec       col      (TSliceVol      v, int i, int k);  // vector at slice i, col k

TSliceMat       slice_x  (TSliceVol      v, int k);         // slice (2d image/matrix) in x direction, at col k
TSliceMat       slice_y  (TSliceVol      v, int j);         // slice (2d image/matrix) in y direction, at row j
TSliceMat       slice_z  (TSliceVol      v, int i);         // slice (2d image/matrix) in z direction, at slice i

TConstSliceVol  repeat   (TSliceVec      v, int slices, int rows);    // repeat 'v' for 'rows' rows and 'slices' slices
TConstSliceVol  repeat   (TSliceMat      m, int slices = VL_REPEAT);  // repeat 'm' over 'slices' slices


// --- SliceVol Inlines -------------------------------------------------------

// ConstSliceVol

inline int TConstSliceVol::Slices() const
{
    return slices;
}

inline int TConstSliceVol::Rows() const
{
    return rows;
}

inline int TConstSliceVol::Cols() const
{
    return cols;
}

inline int TConstSliceVol::Elts() const
{
    return cols * rows;
}

inline TConstSliceMat TConstSliceVol::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, rows, "(SliceVol::(i)) index out of range");
    return TConstSliceMat(rows, cols, rspan, cspan, data + i * sspan);
}

inline const TElt& TConstSliceVol::operator() (int i, int j, int k) const
{
    VL_RANGE_MSG(i, 0, slices, "(SliceVol::(i,j,k)) i index out of range");
    VL_RANGE_MSG(j, 0, rows,   "(SliceVol::(i,j,k)) j index out of range");
    VL_RANGE_MSG(k, 0, cols,   "(SliceVol::(i,j,k)) k index out of range");
    return data[i * sspan + j * rspan + k * cspan];
}

// SliceVol

inline TSliceVol::operator TConstSliceVol() const
{
    return (TConstSliceVol&) *this;
}

inline int TSliceVol::Slices() const
{
    return slices;
}

inline int TSliceVol::Rows() const
{
    return rows;
}

inline int TSliceVol::Cols() const
{
    return cols;
}

inline int TSliceVol::Elts() const
{
    return cols * rows;
}

inline TSliceMat TSliceVol::operator [] (int i) const
{
    VL_RANGE_MSG(i, 0, rows, "(SliceVol::(i)) index out of range");
    return TSliceMat(rows, cols, rspan, cspan, data + i * sspan);
}

inline TElt& TSliceVol::operator() (int i, int j, int k) const
{
    VL_RANGE_MSG(i, 0, slices, "(SliceVol::(i,j,k)) i index out of range");
    VL_RANGE_MSG(j, 0, rows,   "(SliceVol::(i,j,k)) j index out of range");
    VL_RANGE_MSG(k, 0, cols,   "(SliceVol::(i,j,k)) k index out of range");
    return data[i * sspan + j * rspan + k * cspan];
}

// Comparison Operators

inline bool operator != (TConstSliceVol a, TConstSliceVol b)
{
    return !(a == b);
}

inline bool same_size(TConstSliceVol a, TConstSliceVol b)
{
    return a.cols == b.cols && a.rows == b.rows;
}

inline bool is_cubic(TConstSliceVol v)
{
    return (v.slices == v.rows) && (v.slices == v.cols);
}

// Vol Arithmetic Operators

inline TConstSliceVol operator + (TConstSliceVol v)
{
    return v;
}

#endif
