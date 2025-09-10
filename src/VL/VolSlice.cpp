/*
    File:       VolSlice.cpp

    Function:   Implements VolSlice.hpp

    Copyright:  Andrew Willmott
*/


#include "VL/VolSlice.hpp"

#include "VL/Vol.hpp"


// --- SliceVol Constructors & Destructors ------------------------------------


TConstSliceVol::TConstSliceVol(int s, int r, int c, int ss, int rs, int cs, const TElt data[]) :
    data  (data),
    cols  (c),
    cspan (cs),
    rows  (r),
    rspan (rs),
    slices(s),
    sspan (ss)
{
}

TSliceVol::TSliceVol(int s, int r, int c, int ss, int rs, int cs, TElt data[]) :
    data  (data),
    cols  (c),
    cspan (cs),
    rows  (r),
    rspan (rs),
    slices(s),
    sspan (ss)
{
}


// --- SliceVol Assignment Operators ------------------------------------------


const TSliceVol& TSliceVol::operator = (const TSliceVol& v) const
{
    return operator=((TConstSliceVol) v);
}

const TSliceVol& TSliceVol::operator = (TConstSliceVol v) const
{
    VL_ASSERT_MSG(slices == v.slices || v.slices == VL_REPEAT, "(SliceVol::=) Volume slices don't match");
    for (int i = 0; i < slices; i++)
        (*this)[i] = v[i];

    return *this;
}

const TSliceVol& TSliceVol::operator = (TRefVol v) const
{
    return operator=((TConstRefVol) v);
}

const TSliceVol& TSliceVol::operator = (TConstRefVol v) const
{
    return operator=(TConstSliceVol(v));
}

const TSliceVol& TSliceVol::operator = (VLDiag k) const
{
    MakeDiag(TElt(k));
    return *this;
}

const TSliceVol& TSliceVol::operator = (VLBlock k) const
{
    MakeBlock(TElt(k));
    return *this;
}

// --- SliceVol In-Place operators --------------------------------------------


const TSliceVol& TSliceVol::operator += (TConstSliceVol v) const
{
    VL_ASSERT_MSG(slices == v.slices, "(SliceVol::+=) Volume slices don't match");

    for (int i = 0; i < slices; i++)
        (*this)[i] += v[i];

    return *this;
}

const TSliceVol& TSliceVol::operator -= (TConstSliceVol v) const
{
    VL_ASSERT_MSG(slices == v.slices, "(SliceVol::-=) Volume slices don't match");

    for (int i = 0; i < slices; i++)
        (*this)[i] -= v[i];

    return *this;
}

const TSliceVol& TSliceVol::operator *= (TConstSliceVol v) const
{
    VL_ASSERT_MSG(slices == v.slices, "(SliceVol::*=) Volume slices don't match");
    VL_ASSERT_MSG(rows   == v.rows  , "(SliceVol::*=) Volume rows don't match");

    for (int i = 0; i < slices; i++)
    {
        TSliceMat      mdst = (*this)[i];
        TConstSliceMat msrc = v[i];

        for (int j = 0; j < rows  ; j++)
            mdst[j] *= msrc[j];
    }

    return *this;
}

const TSliceVol& TSliceVol::operator /= (TConstSliceVol v) const
{
    VL_ASSERT_MSG(slices == v.slices, "(SliceVol::*=) Volume slices don't match");

    for (int i = 0; i < slices; i++)
        (*this)[i] /= v[i];

    return *this;
}

const TSliceVol& TSliceVol::operator *= (TElt s) const
{
    for (int i = 0; i < slices; i++)
        (*this)[i] *= s;

    return *this;
}

const TSliceVol& TSliceVol::operator /= (TElt s) const
{
    for (int i = 0; i < slices; i++)
        (*this)[i] /= s;

    return *this;
}

// --- TSliceVol Volume initialisers -------------------------------------------

void TSliceVol::MakeZero() const
{
    for (int i = 0; i < slices; i++)
        (*this)[i].MakeBlock(vl_0);
}

void TSliceVol::MakeIdentity() const
{
    for (int i = 0; i < slices; i++)
        (*this)[i].MakeDiag(vl_1);
}

void TSliceVol::MakeDiag(TElt k) const
{
    for (int i = 0; i < slices; i++)
        (*this)[i].MakeDiag(k);
}

void TSliceVol::MakeBlock(TElt k) const
{
    for (int i = 0; i < slices; i++)
        (*this)[i].MakeBlock(k);
}


// --- SliceVol Comparison Operators ------------------------------------------


bool operator == (TConstSliceVol a, TConstSliceVol b)
{
    VL_ASSERT_MSG(a.slices == b.slices, "(SliceVol::==) Volume slices don't match");

    for (int i = 0; i < a.slices; i++)
        if (a[i] != b[i])
            return false;

    return true;
}


// --- SliceVol Arithmetic Operators ------------------------------------------


TVol operator + (TConstSliceVol a, TConstSliceVol b)
{
    TVol result(a);
    result += b;

    return result;
}

TVol operator - (TConstSliceVol a, TConstSliceVol b)
{
    TVol result(a);
    result -= b;

    return result;
}

TVol operator - (TConstSliceVol v)
{
    TVol result(v);

    for (int i = 0; i < v.slices; i++)
        Negate(result[i], result[i]);

    return result;
}

TVol operator * (TConstSliceVol a, TConstSliceVol b)
{
    TVol result(a);
    result *= b;

    return result;
}

TVol operator * (TConstSliceVol v, TElt s)
{
    TVol result(v);
    result *= s;

    return result;
}

TVol operator / (TConstSliceVol v, TElt s)
{
    TVol result(v);
    result /= s;

    return result;
}

TElt sum(TConstSliceVol v)
{
    TElt result = vl_0;

    for (int i = 0; i < v.slices; i++)
        result += sum(v[i]);

    return result;
}

TVol abs(TConstSliceVol v)
{
    TVol result(v);
    Absolute(result, result);
    return result;
}

TVol clamped(TConstSliceVol v, TElt fuzz)
{
    TVol result(v);
    Clamp(result, fuzz);
    return result;
}

TVol hprod(TConstSliceVol a, TConstSliceVol b)
{
    VL_ASSERT_MSG(a.slices == b.slices, "(hprod(SliceVol)) Volume slices don't match");
    
    TVol result(a);
    for (int i = 0; i < a.slices; i++)
        result[i] *= b[i];
        
    return result;
}

TVol oprod(TConstSliceVec a, TConstSliceVec b, TConstSliceVec c)
{
    TVol result(a.elts, b.elts, c.elts);

    for (int i = 0; i < a.elts; i++)
    for (int j = 0; j < b.elts; j++)
    for (int k = 0; k < c.elts; k++)
        result(i, j, k) = a[i] * b[j] * c[k];

    return result;
}

TVol transformed(TConstSliceVol v, TElt f(TElt))
{
    TVol result(v);

    for (int i = 0; i < v.slices; i++)
        transform(result[i], f);

    return result;
}

void transform(TSliceVol v, TElt f(TElt))
{
    for (int i = 0; i < v.slices; i++)
        transform(v[i], f);
}

TElt reduced(TConstSliceVol v, TElt f(TElt, TElt))
{
    if (v.slices == 0)
        return TElt(vl_0);
    TElt result = reduced(v[0], f);
    for (int i = 1; i < v.slices; i++)
        result = f(result, reduced(v[i], f));
    return result;
}


// --- Sub functions: SliceVol ------------------------------------------------

// TConstSliceVol

TConstSliceVol sub(TConstSliceVol v, int i, int j, int k, int slices, int rows, int cols)
{
    VL_ASSERT_MSG(i >= 0 && slices > 0 && i + slices <= v.slices, "(sub(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(j >= 0 && rows   > 0 && j + rows   <= v.rows  , "(sub(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(k >= 0 && cols   > 0 && k + cols   <= v.cols  , "(sub(SliceVol)) illegal subset of volume");

    return TConstSliceVol(slices, rows, cols, v.sspan, v.rspan, v.cspan, v.data
            + i * v.sspan + j * v.rspan + k * v.cspan);
}

TConstSliceVol first(TConstSliceVol v, int slices, int rows, int cols)
{
    VL_ASSERT_MSG(slices > 0 && slices <= v.slices, "(first(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(rows   > 0 && rows   <= v.rows  , "(first(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(cols   > 0 && cols   <= v.cols  , "(first(SliceVol)) illegal subset of volume");

    return TConstSliceVol(slices, rows, cols, v.sspan, v.rspan, v.cspan, v.data);
}

TConstSliceVol last(TConstSliceVol v, int slices, int rows, int cols)
{
    VL_ASSERT_MSG(slices > 0 && slices <= v.slices, "(last(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(rows   > 0 && rows   <= v.rows  , "(last(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(cols   > 0 && cols   <= v.cols  , "(last(SliceVol)) illegal subset of volume");

    return TConstSliceVol(slices, rows, cols, v.sspan, v.rspan, v.cspan, v.data
            + (v.slices - slices) * v.sspan + (v.rows - rows) * v.rspan + (v.cols - cols) * v.cspan);
}

TConstSliceVec slice(TConstSliceVol v, int j, int k)
{
    VL_RANGE_MSG(j, 0, v.rows, "(slice(SliceVol)) illegal row index");
    VL_RANGE_MSG(k, 0, v.cols, "(slice(SliceVol)) illegal col index");

    return TConstSliceVec(v.slices, v.sspan, v.data + j * v.rspan + k * v.cspan);
}

TConstSliceVec row(TConstSliceVol v, int i, int j)
{
    VL_RANGE_MSG(i, 0, v.slices, "(row(SliceVol)) illegal slice index");
    VL_RANGE_MSG(j, 0, v.rows  , "(row(SliceVol)) illegal row index");

    return TConstSliceVec(v.cols, v.cspan, v.data + i * v.sspan + j * v.rspan);
}

TConstSliceVec col(TConstSliceVol v, int i, int k)
{
    VL_RANGE_MSG(i, 0, v.slices, "(col(SliceVol)) illegal slice index");
    VL_RANGE_MSG(k, 0, v.cols  , "(col(SliceVol)) illegal col index");

    return TConstSliceVec(v.rows, v.rspan, v.data + i * v.sspan + k * v.cspan);
}

TConstSliceMat slice_x(TConstSliceVol v, int k)
{
    VL_RANGE_MSG(k, 0, v.cols, "(slice(SliceVol)) illegal col index");
    return TConstSliceMat(v.rows, v.slices, v.rspan, v.sspan, v.data + k * v.cspan);
}

TConstSliceMat slice_y(TConstSliceVol v, int j)
{
    VL_RANGE_MSG(j, 0, v.rows, "(slice(SliceVol)) illegal row index");
    return TConstSliceMat(v.cols, v.slices, v.cspan, v.sspan, v.data + j * v.rspan);
}

TConstSliceMat slice_z(TConstSliceVol v, int i)
{
    VL_RANGE_MSG(i, 0, v.slices, "(row(SliceVol)) illegal slice index");
    return TConstSliceMat(v.rows, v.cols, v.rspan, v.cspan, v.data + i * v.sspan);
}

TConstSliceVol repeat(const TElt& elt, int slices, int rows, int cols)
{
    return TConstSliceVol(slices, rows, cols, 0, 0, 0, &elt);
}

TConstSliceVol repeat(TConstSliceVec v, int slices, int rows)
{
    return TConstSliceVol(slices, rows, v.elts, 0, 0, v.span, v.data);
}

TConstSliceVol repeat(TConstSliceMat m, int slices)
{
    return TConstSliceVol(slices, m.rows, m.cols, 0, m.rspan, m.cspan, m.data);
}


// TSliceVol

TSliceVol sub(TSliceVol v, int i, int j, int k, int slices, int rows, int cols)
{
    VL_ASSERT_MSG(i >= 0 && slices > 0 && i + slices <= v.slices, "(sub(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(j >= 0 && rows   > 0 && j + rows   <= v.rows  , "(sub(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(k >= 0 && cols   > 0 && k + cols   <= v.cols  , "(sub(SliceVol)) illegal subset of volume");

    return TSliceVol(slices, rows, cols, v.sspan, v.rspan, v.cspan, v.data + i * v.sspan + j * v.rspan + k * v.cspan);
}

TSliceVol first(TSliceVol v, int slices, int rows, int cols)
{
    VL_ASSERT_MSG(slices > 0 && slices <= v.slices, "(first(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(rows   > 0 && rows   <= v.rows  , "(first(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(cols   > 0 && cols   <= v.cols  , "(first(SliceVol)) illegal subset of volume");

    return TSliceVol(slices, rows, cols, v.sspan, v.rspan, v.cspan, v.data);
}

TSliceVol last(TSliceVol v, int slices, int rows, int cols)
{
    VL_ASSERT_MSG(slices > 0 && slices <= v.slices, "(last(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(rows   > 0 && rows   <= v.rows  , "(last(SliceVol)) illegal subset of volume");
    VL_ASSERT_MSG(cols   > 0 && cols   <= v.cols  , "(last(SliceVol)) illegal subset of volume");

    return TSliceVol(slices, rows, cols, v.sspan, v.rspan, v.cspan, v.data
            + (v.slices - slices) * v.sspan + (v.rows - rows) * v.rspan + (v.cols - cols) * v.cspan);
}

TSliceVec slice(TSliceVol v, int j, int k)
{
    VL_RANGE_MSG(j, 0, v.rows, "(slice(SliceVol)) illegal row index");
    VL_RANGE_MSG(k, 0, v.cols, "(slice(SliceVol)) illegal col index");

    return TSliceVec(v.slices, v.sspan, v.data + j * v.rspan + k * v.cspan);
}

TSliceVec col(TSliceVol v, int i, int k)
{
    VL_RANGE_MSG(i, 0, v.slices, "(col(SliceVol)) illegal slice index");
    VL_RANGE_MSG(k, 0, v.cols  , "(col(SliceVol)) illegal col index");

    return TSliceVec(v.rows, v.rspan, v.data + i * v.sspan + k * v.cspan);
}

TSliceVec row(TSliceVol v, int i, int j)
{
    VL_RANGE_MSG(i, 0, v.slices, "(row(SliceVol)) illegal slice index");
    VL_RANGE_MSG(j, 0, v.rows  , "(row(SliceVol)) illegal row index");

    return TSliceVec(v.cols, v.cspan, v.data + i * v.sspan + j * v.rspan);
}

TSliceMat slice_x(TSliceVol v, int k)
{
    VL_RANGE_MSG(k, 0, v.cols, "(slice(SliceVol)) illegal col index");
    return TSliceMat(v.rows, v.slices, v.rspan, v.sspan, v.data + k * v.cspan);
}

TSliceMat slice_y(TSliceVol v, int j)
{
    VL_RANGE_MSG(j, 0, v.rows, "(slice(SliceVol)) illegal row index");
    return TSliceMat(v.cols, v.slices, v.cspan, v.sspan, v.data + j * v.rspan);
}

TSliceMat slice_z(TSliceVol v, int i)
{
    VL_RANGE_MSG(i, 0, v.slices, "(row(SliceVol)) illegal slice index");
    return TSliceMat(v.rows, v.cols, v.rspan, v.cspan, v.data + i * v.sspan);
}

TConstSliceVol repeat(TSliceVec v, int slices, int rows)
{
    return TConstSliceVol(slices, rows, v.elts, 0, 0, v.span, v.data);
}

TConstSliceVol repeat(TSliceMat m, int slices)
{
    return TConstSliceVol(slices, m.rows, m.cols, 0, m.rspan, m.cspan, m.data);
}
