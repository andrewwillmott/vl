/*
    File:       Stream.cpp

    Function:   iostream support

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_IOSTREAM

#include "VL/Stream.hpp"

VL_NS_END
#include <vector>
#include <iomanip>
#include <ctype.h>
VL_NS_BEGIN

using namespace std;

template<class T> ostream& operator << (ostream& s, vector<T>& array)
{
	s << '[';

	char sepChar;

	if (array.NumItems() >= 16)
		sepChar = '\n';
	else
		sepChar = ' ';

	if (array.NumItems() > 0)
	{
		s << array[0];

		for (int i = 1; i < array.NumItems(); i++)
			s << sepChar << array[i];
	}

	s << ']';

	return s;
}

template<class T> istream& operator >> (istream& s, vector<T>& array)
{
    T tmp;
    char c;

	//	Expected format: [a b c d ...]

    while (isspace(s.peek()))			// 	chomp white space
		s.get(c);

    if (s.peek() == '[')
    {
    	s.get(c);
    	array.clear();

	    while (isspace(s.peek()))		// 	chomp white space
			s.get(c);

		while (s.peek() != ']')
		{
            s >> tmp;

			if (!s)
			{
				VL_WARNING("Couldn't read array component");
				return s;
			}

			array.push_back(tmp);

		    while (isspace(s.peek()))	// 	chomp white space
				s.get(c);
		}
		s.get(c);
	}
    else
	{
	    s.clear(ios::failbit);
	    VL_WARNING("Error: Expected '[' while reading array");
	    return s;
	}

    return s;
}

ostream& operator << (ostream& s, TConstRefVec v)
{
    int w = (int) s.width();
    s << setw(0) << '[';

    if (v.Elts() > 0)
    {
        s << setw(w) << v[0];

        for (int i = 1; i < v.Elts(); i++)
            s << ' ' << setw(w) << v[i];
    }

    s << ']';

    return s;
}

istream& operator >> (istream& s, TVec& v)
{
    vector<TElt> array;

    // Expected format: [1 2 3 4 ...]

    s >> array;                              // Read input into variable-sized array

    v = TRefVec((int) array.size(), array.data());  // Copy input into vector

    return s;
}


ostream& operator << (ostream& s, TConstSliceVec v)
{
    int w = (int) s.width();
    s << setw(0) << '[';

    if (v.Elts() > 0)
    {
        s << setw(w) << v[0];

        for (int i = 1; i < v.Elts(); i++)
            s << ' ' << setw(w) << v[i];
    }

    s << ']';

    return s;
}

istream& operator >> (istream& s, TSliceVec v)
{
    vector<TElt> array;

    // Expected format: [1 2 3 4 ...]

    s >> array;                              // Read input into variable-sized array

    v = TRefVec((int) array.size(), array.data());  // Copy input into vector

    return s;
}

// MatN

ostream& operator << (ostream& s, TConstRefMat m)
{
    int w = (int) s.width();

    s << setw(0) << '[';

    if (m.Rows() > 0)
    {
        s << setw(w) << m[0];

        for (int i = 1; i < m.Rows(); i++)
            s << endl << ' ' << setw(w) << m[i];
    }

    s << ']' << endl;

    return s;
}

istream& operator >> (istream& s, TMat& m)
{
    vector<vector<TElt> > array;

    s >> array;                     // Read input into array of arrays

    m.SetSize((int) array.size(), (int) array[0].size());

    for (int i = 0; i < m.Rows(); i++)  // copy the result into m
    {
        VL_ASSERT_MSG(m.Cols() == (int) array[i].size(), "(Mat/>>) different sized matrix rows");
        m[i] = TRefVec(m.Cols(), &array[i].front());
    }

    return s;
}

ostream& operator << (ostream& s, TConstSliceMat m)
{
    int w = (int) s.width();

    s << setw(0) << '[';

    if (m.Rows() > 0)
    {
        s << setw(w) << m[0];

        for (int i = 1; i < m.Rows(); i++)
            s << endl << ' ' << setw(w) << m[i];
    }

    s << ']' << endl;

    return s;
}

istream& operator >> (istream& s, TSliceMat m)
{
    vector<vector<TElt> > array;

    s >> array;                     // Read input into array of arrays

    VL_ASSERT_MSG(m.Rows() == (int) array.size(), "(SliceMat:>>) different sized matrix");

    for (int i = 0; i < m.rows; i++)  // copy the result into m
    {
        VL_ASSERT_MSG(m.cols == (int) array[i].size(), "(SliceMat:>>) different sized matrix rows");
        m[i] = TRefVec(m.cols, &array[i].front());
    }

    return s;
}

// VolN

ostream& operator << (ostream& s, TConstRefVol v)
{
    int w = (int) s.width();

    s << setw(0) << "[";

    if (v.Slices() > 0)
    {
        s << endl;
        for (int i = 0; i < v.Slices(); i++)
            s << setw(w) << v[i];
    }

    s << "]" << endl;
    return s;
}

istream& operator >> (istream& s, TVol& v)
{
    vector<vector<vector<TElt> > > array;

    s >> array;

    v.SetSize((int) array.size(), (int) array[0].size(), (int) array[0][0].size());

    VL_ASSERT_MSG(v.Slices() == (int) array.size(), "(SliceVol:>>) different sized volume");

    for (int i = 0; i < v.Slices(); i++)
    {
        VL_ASSERT_MSG(v.rows == (int) array[i].size(), "(SliceVol:>>) different sized volume rows");

        for (int j = 0; j < v.rows; j++)
        {
            VL_ASSERT_MSG(v.cols == (int) array[i][j].size(), "(SliceVol:>>) different sized volume cols");
            v[i][j] = TRefVec(v.cols, &array[i][j].front());
        }
    }

    return s;
}

ostream& operator << (ostream& s, TConstSliceVol v)
{
    int w = (int) s.width();

    s << setw(0) << "[" << endl;

    if (v.Slices() > 0)
    {
        s << endl;
        for (int i = 0; i < v.Slices(); i++)
            s << setw(w) << v[i];
    }
    
    s << "]" << endl;
    return s;
}

istream& operator >> (istream& s, TSliceVol v)
{
    vector<vector<vector<TElt> > > array;

    s >> array;

    VL_ASSERT_MSG(v.Slices() == (int) array.size(), "(SliceVol:>>) different sized volume");

    for (int i = 0; i < v.slices; i++)
    {
        VL_ASSERT_MSG(v.rows == (int) array[i].size(), "(SliceVol:>>) different sized volume rows");

        for (int j = 0; j < v.rows; j++)
        {
            VL_ASSERT_MSG(v.cols == (int) array[i][j].size(), "(SliceVol:>>) different sized volume cols");
            v[i][j] = TRefVec(v.cols, &array[i][j].front());
        }
    }

    return s;
}

#endif
