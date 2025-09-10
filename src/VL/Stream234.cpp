/*
    File:       Stream234.cpp

    Function:   iostream support

    Copyright:  Andrew Willmott
*/

#ifndef VL_NO_IOSTREAM

#include "VL/Stream234.hpp"

VL_NS_END
#include <vector>
#include <iomanip>
#include <ctype.h>
VL_NS_BEGIN

using namespace std;

ostream& operator << (ostream& s, const TVec2& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ']';
}

istream& operator >> (istream& s, TVec2& v)
{
    TVec2   result;
    char    c;

    // Expected format: [1 2]

    while (s >> c && isspace(c))
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1];

        if (!s)
        {
            cerr << "Error: Expected number while reading vector\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Error: Expected ']' while reading vector\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Error: Expected '[' while reading vector\n";
        return s;
    }

    v = result;
    return s;
}


ostream& operator << (ostream& s, const TVec3& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ' ' << setw(w) << v[2] << ']';
}

istream& operator >> (istream& s, TVec3& v)
{
    TVec3   result;
    char    c;

    // Expected format: [1 2 3]

    while (s >> c && isspace(c))
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2];

        if (!s)
        {
            cerr << "Error: Expected number while reading vector\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Error: Expected ']' while reading vector\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Error: Expected '[' while reading vector\n";
        return s;
    }

    v = result;
    return s;
}


ostream& operator << (ostream& s, const TVec4& v)
{
    int w = (int) s.width();

    return s << '[' << v[0] << ' ' << setw(w) << v[1] << ' '
        << setw(w) << v[2] << ' ' << setw(w) << v[3] << ']';
}

istream& operator >> (istream& s, TVec4& v)
{
    TVec4   result;
    char    c;

    // Expected format: [1 2 3 4]

    while (s >> c && isspace(c))
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2] >> result[3];

        if (!s)
        {
            cerr << "Error: Expected number while reading vector\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Error: Expected ']' while reading vector\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Error: Expected '[' while reading vector\n";
        return s;
    }

    v = result;
    return s;
}


// Mat234

ostream& operator << (ostream& s, const TMat2& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << ']' << endl;
}

istream& operator >> (istream& s, TMat2& m)
{
    TMat2   result;
    char    c;

    // Expected format: [[1 2] [3 4]]
    // Each vector is a row of the row matrix.

    while (s >> c && isspace(c))        // ignore leading white space
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1];

        if (!s)
        {
            cerr << "Expected number while reading matrix\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Expected ']' while reading matrix\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Expected '[' while reading matrix\n";
        return s;
    }

    m = result;
    return s;
}


ostream& operator << (ostream& s, const TMat3& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << endl
             << ' ' << setw(w) << m[2] << ']' << endl;
}

istream& operator >> (istream& s, TMat3& m)
{
    TMat3   result;
    char    c;

    // Expected format: [[1 2 3] [4 5 6] [7 8 9]]
    // Each vector is a column of the matrix.

    while (s >> c && isspace(c))        // ignore leading white space
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2];

        if (!s)
        {
            cerr << "Expected number while reading matrix\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Expected ']' while reading matrix\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Expected '[' while reading matrix\n";
        return s;
    }

    m = result;
    return s;
}


ostream& operator << (ostream& s, const TMat4& m)
{
    int w = (int) s.width();

    return s << '[' <<            m[0] << endl
             << ' ' << setw(w) << m[1] << endl
             << ' ' << setw(w) << m[2] << endl
             << ' ' << setw(w) << m[3] << ']' << endl;
}

istream& operator >> (istream& s, TMat4& m)
{
    TMat4   result;
    char    c;

    // Expected format: [[1 2 3] [4 5 6] [7 8 9]]
    // Each vector is a column of the matrix.

    while (s >> c && isspace(c))        // ignore leading white space
        ;

    if (c == '[')
    {
        s >> result[0] >> result[1] >> result[2] >> result[3];

        if (!s)
        {
            cerr << "Expected number while reading matrix\n";
            return s;
        }

        while (s >> c && isspace(c))
            ;

        if (c != ']')
        {
            s.clear(ios::failbit);
            cerr << "Expected ']' while reading matrix\n";
            return s;
        }
    }
    else
    {
        s.clear(ios::failbit);
        cerr << "Expected '[' while reading matrix\n";
        return s;
    }

    m = result;
    return s;
}

#endif
