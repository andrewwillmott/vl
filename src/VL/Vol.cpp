/*
    File:       Vol.cpp

    Function:   Implements Vol.h

    Copyright:  Andrew Willmott
*/

#include "VL/Vol.h"


// --- RefVol Assignment Operators --------------------------------------------

const TRefVol& TRefVol::operator = (const TRefVol& v) const
{
    VL_ASSERT_MSG(same_size(*this, v), "(Vol::=) Volume dimensions don't match");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = v.data[i];

    return *this;
}

const TRefVol& TRefVol::operator = (TConstRefVol v) const
{
    VL_ASSERT_MSG(same_size(*this, v), "(Vol::=) Volume dimensions don't match");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = v.data[i];

    return *this;
}

const TRefVol& TRefVol::operator = (TConstSliceVol v) const
{
    VL_ASSERT_MSG(slices == v.slices || v.slices == VL_REPEAT, "(Vol::=) Volume slices don't match");

    for (int i = 0; i < slices; i++)
        (*this)[i] = v[i];

    return *this;
}

// --- RefVol In-Place Operators ----------------------------------------------

const TRefVol& TRefVol::operator += (TConstRefVol v) const
{
    VL_ASSERT_MSG(same_size(*this, v), "(Vol::+=) Volume dimensions don't match");
    AsVec() += v.AsVec();
    return *this;
}

const TRefVol& TRefVol::operator -= (TConstRefVol v) const
{
    VL_ASSERT_MSG(same_size(*this, v), "(Vol::-=) Volume dimensions don't match");
    AsVec() -= v.AsVec();
    return *this;
}

const TRefVol& TRefVol::operator *= (TConstRefVol v) const
{
    VL_ASSERT_MSG(same_size(*this, v), "(Vol::*=) Volume dimensions don't match");
    AsVec() *= v.AsVec();
    return *this;
}

const TRefVol& TRefVol::operator /= (TConstRefVol v) const
{
    VL_ASSERT_MSG(same_size(*this, v), "(Vol::/=) Volume dimensions don't match");
    AsVec() /= v.AsVec();
    return *this;
}

const TRefVol& TRefVol::operator *= (TElt s) const
{
    AsVec() *= s;
    return *this;
}

const TRefVol& TRefVol::operator /= (TElt s) const
{
    AsVec() /= s;
    return *this;
}

// --- RefVol Volume initialisers ---------------------------------------------

void TRefVol::MakeZero() const
{
    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = vl_zero;
}

void TRefVol::MakeBlock(TElt k) const
{
    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = k;
}


// --- Vol Constructors & Destructors -----------------------------------------


TVol::TVol(const TVol& v) : TRefVol(v.slices, v.rows, v.cols, VL_NEW TElt[v.slices * v.rows * v.cols])
{
    VL_ASSERT_MSG(v.data != 0, "(Vol) Out of memory");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = v.data[i];
}

TVol::TVol(TVol&& v) : TRefVol(v)
{
    v.data = 0;
}

TVol::TVol(std::initializer_list<TMat> l) : TRefVol(int(l.size()), 0, 0, nullptr)
{
    for (const TMat& m : l)
    {
        if (rows < m.Rows())
            rows = m.Rows();
        if (cols < m.Cols())
            cols = m.Cols();
    }

    data = new TElt[slices * rows * cols];

    std::initializer_list<TMat>::const_iterator it = l.begin();

    for (int i = 0; i < slices; i++, ++it)
    {
        TSliceMat slice = (*this)[i];

        first(slice, it->Rows(), it->Cols()) = *it;

        // Zero out to the right and below if necessary
        sub  (slice, 0, it->Cols(), it->Rows(), cols - it->Cols()) = vl_0;
        last (slice, rows - it->Rows(), cols) = vl_0;
    }
}

TVol::TVol(TConstRefVol v) : TRefVol(v.slices, v.rows, v.cols, VL_NEW TElt[v.slices * v.rows * v.cols])
{
    VL_ASSERT_MSG(v.data != 0, "(Vol) Out of memory");

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = v.data[i];
}

TVol::TVol(TConstSliceVol v) : TRefVol(v.slices, v.rows, v.cols, VL_NEW TElt[v.slices * v.rows * v.cols])
{
    VL_ASSERT_MSG(v.data != 0, "(Vol) Out of memory");

    for (int i = 0; i < slices; i++)
        (*this)[i] = v[i];
}

// --- Vol Assignment Operators -----------------------------------------------


TVol& TVol::operator = (const TVol& v)
{
    SetSize(v);

    for (int i = 0, n = Elts(); i < n; i++)
        data[i] = v.data[i];

    return *this;
}

TVol& TVol::operator = (TVol&& v)
{
    if (this != &v)
    {
        VL_DELETE[] data;
        data   = v.data;
        cols   = v.cols;
        rows   = v.rows;
        slices = v.slices;
        v.data = 0;
    }

    return *this;
}


// --- Vol Sizing -------------------------------------------------------------

void TVol::SetSize(int s, int r, int c)
{
    VL_ASSERT_MSG(s > 0 && r > 0 && c > 0, "(Vol::SetSize) Illegal volume size.");

    int oldElts = Elts();
    int elts = s * r * c;

    cols   = c;
    rows   = r;
    slices = s;

    // Don't reallocate if we already have enough storage
    if (elts <= oldElts)
        return;

    // Otherwise, delete old storage and reallocate
    VL_DELETE[] data;
    data = VL_NEW TElt[elts];
}


// --- ConstVol Constructors & Destructors ------------------------------------

TConstVol::TConstVol(const TConstVol& v) : TConstRefVol(v.slices, v.rows, v.cols, VL_NEW TElt[v.slices * v.rows * v.cols])
{
    VL_ASSERT_MSG(v.data != 0, "(ConstVol) Out of memory");

    TRefVol& self = (TRefVol&) *this;

    for (int i = 0, n = Elts(); i < n; i++)
        self.data[i] = v.data[i];
}

TConstVol::TConstVol(TConstVol&& v) : TConstRefVol(v)
{
    v.data = 0;
}

TConstVol::TConstVol(std::initializer_list<TConstMat> l) : TConstRefVol(int(l.size()), 0, 0, nullptr)
{
    TRefVol& self = (TRefVol&) *this;

    for (const TConstMat& m : l)
    {
        if (rows < m.Rows())
            rows = m.Rows();
        if (cols < m.Cols())
            cols = m.Cols();
    }

    self.data = new TElt[slices * rows * cols];

    std::initializer_list<TConstMat>::const_iterator it = l.begin();

    for (int i = 0; i < slices; i++, ++it)
    {
        first(self[i], it->Rows(), it->Cols()) = *it;

        // Zero out to the right and below if necessary
        sub  (self[i], 0, it->Cols(), it->Rows(), cols - it->Cols()) = vl_0;
        last (self[i], rows - it->Rows(), cols) = vl_0;
    }
}

TConstVol::TConstVol(TConstRefVol v) : TConstRefVol(v.slices, v.rows, v.cols, VL_NEW TElt[v.slices * v.rows * v.cols])
{
    VL_ASSERT_MSG(v.data != 0, "(ConstVol) Out of memory");

    TRefVol& self = (TRefVol&) *this;

    for (int i = 0, n = Elts(); i < n; i++)
        self.data[i] = v.data[i];
}

TConstVol::TConstVol(TConstSliceVol v) : TConstRefVol(v.slices, v.rows, v.cols, VL_NEW TElt[v.slices * v.rows * v.cols])
{
    VL_ASSERT_MSG(v.data != 0, "(Vol) Out of memory");

    TRefVol& self = (TRefVol&) *this;

    for (int i = 0; i < slices; i++)
        self[i] = v[i];
}

// --- Vol Arithmetic Operators -----------------------------------------------

TVol operator + (TConstRefVol a, TConstRefVol b)
{
    TVol r(a.slices, a.rows, a.cols);
    Add(a, b, r);
    return r;
}

TVol operator - (TConstRefVol a, TConstRefVol b)
{
    TVol r(a.slices, a.rows, a.cols);
    Subtract(a, b, r);
    return r;
}

TVol operator * (TConstRefVol a, TConstRefVol b)
{
    TVol r(a.slices, a.rows, a.cols);
    Multiply(a, b, r);
    return r;
}

TVol operator / (TConstRefVol a, TConstRefVol b)
{
    TVol r(a.slices, a.rows, a.cols);
    Divide(a, b, r);
    return r;
}

TVol abs(TConstRefVol v)
{
    TVol result(v.slices, v.rows, v.cols);
    Absolute(v, result);
    return result;
}

TVol clamped(TConstRefVol v, TElt fuzz)
{
    TVol result(v);
    Clamp(result, fuzz);
    return result;
}

TVol hprod(TConstRefVol a, TConstRefVol b)
{
    TVol result(a.slices, a.rows, a.cols);
    HadamardProduct(a, b, result);
    return result;
}

TVol oprod(TConstRefVec a, TConstRefVec b, TConstRefVec c)
{
    TVol result(a.elts, b.elts, c.elts);
    OuterProduct(a, b, c, result);
    return result;
}


// --- Vol Functions ----------------------------------------------------------

void Add(TConstRefVol a, TConstRefVol b, TRefVol r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Vol::+) Volume dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Vol::+) Volume dimensions don't match");
    Add(a.AsVec(), b.AsVec(), r.AsVec());
}

void Subtract(TConstRefVol a, TConstRefVol b, TRefVol r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Vol::-) Volume dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Vol::-) Volume dimensions don't match");
    Subtract(a.AsVec(), b.AsVec(), r.AsVec());
}

void Multiply(TConstRefVol a, TConstRefVol b, TRefVol r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Vol::*) Volume dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Vol::*) Volume dimensions don't match");
    Multiply(a.AsVec(), b.AsVec(), r.AsVec());
}

void Divide(TConstRefVol a, TConstRefVol b, TRefVol r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Vol::/) Volume dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Vol::/) Volume dimensions don't match");
    Divide(a.AsVec(), b.AsVec(), r.AsVec());
}

void Negate(TConstRefVol v, TRefVol r)
{
    VL_ASSERT_MSG(same_size(v, r), "(Vol::-) Volume dimensions don't match");
    Negate(v.AsVec(), r.AsVec());
}

void Multiply(TConstRefVol v, TElt s, TRefVol r)
{
    VL_ASSERT_MSG(same_size(v, r), "(Vol::*s) Volume dimensions don't match");
    Multiply(v.AsVec(), s, r.AsVec());
}

void MultiplyAccum(TConstRefVol v, TElt s, TRefVol r)
{
    VL_ASSERT_MSG(same_size(v, r), "(Vol::*s) Volume dimensions don't match");
    MultiplyAccum(v.AsVec(), s, r.AsVec());
}

void Divide(TConstRefVol v, TElt s, TRefVol r)
{
    VL_ASSERT_MSG(same_size(v, r), "(Vol::/s) Volume dimensions don't match");
    Divide(v.AsVec(), s, r.AsVec());
}

void Absolute(TConstRefVol v, TRefVol r)
{
    VL_ASSERT_MSG(same_size(v, r), "(Vol::abs) Volume dimensions don't match");
    Absolute(v.AsVec(), r.AsVec());
}

void Clamp(TRefVol v, TElt fuzz)
{
    Clamp(v.AsVec(), fuzz);
}

TElt InnerProduct(TConstRefVol a, TConstRefVol b)
{
    VL_ASSERT_MSG(same_size(a, b), "(InnerProduct) Volume dimensions don't match");
    return dot(a.AsVec(), b.AsVec());
}

void OuterProduct(TConstRefVec a, TConstRefVec b, TConstRefVec c, TRefVol r)
{
    VL_ASSERT_MSG(a.elts == r.slices, "(Vol::oprod) Volume dimensions don't match");
    VL_ASSERT_MSG(b.elts == r.rows  , "(Vol::oprod) Volume dimensions don't match");
    VL_ASSERT_MSG(c.elts == r.cols  , "(Vol::oprod) Volume dimensions don't match");

    for (int i = 0; i < a.elts; i++)
    for (int j = 0; j < b.elts; j++)
    for (int k = 0; k < c.elts; k++)
        r(i, j, k) = a.data[i] * b.data[j] * c.data[k];
}

void HadamardProduct(TConstRefVol a, TConstRefVol b, TRefVol r)
{
    VL_ASSERT_MSG(same_size(a, b), "(Vol::-) Volume dimensions don't match");
    VL_ASSERT_MSG(same_size(a, r), "(Vol::-) Volume dimensions don't match");
    Multiply(a.AsVec(), b.AsVec(), r.AsVec());
}

