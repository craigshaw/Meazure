/*
 * Copyright 2001, 2004, 2011 C Thing Software
 *
 * This file is part of Meazure.
 * 
 * Meazure is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Meazure is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with Meazure.  If not, see <http://www.gnu.org/licenses/>.
 */

/// @file
/// @brief Miscellaneous utility methods.

#pragma once

#include <math.h>
#include <float.h>


/// Tests whether the two specified double precision values
/// are equal. The resolution of the double is used to make
/// the determination of equality.
///
#define MEA_DBL_EQL(x, y)   (fabs((x) - (y)) < DBL_EPSILON)


/// Represents a rectangular size. Unlike the Windows SIZE
/// structure, the dimensions of the FSIZE structure are
/// double precision values.
///
struct FSIZE {
    double  cx;     ///< Length in the x dimension.
    double  cy;     ///< Length in the y dimension.


    /// Adds this and the specified object and returns
    /// a new size object.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     f_x \\
    ///     f_y \\
    ///     \end{array} \right]
    ///     =
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    ///     +
    ///     \left[ \begin{array}{c}
    ///     fsize_x \\
    ///     fsize_y \\
    ///     \end{array} \right]
    /// \f]
    /// @param fsize    [in] Size object to add.
    /// @return New object that is the sum of this and the
    ///         specified object.
    FSIZE operator+(const FSIZE& fsize) const {
        FSIZE f;
        f.cx = cx + fsize.cx;
        f.cy = cy + fsize.cy;
        return f;
    }

    /// Adds this and the specified value and returns
    /// a new size object.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     f_x \\
    ///     f_y \\
    ///     \end{array} \right]
    ///     =
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    ///     +
    ///     \left[ \begin{array}{c}
    ///     val \\
    ///     val \\
    ///     \end{array} \right]
    /// \f]
    /// @param val      [in] Length to add to both dimensions.
    /// @return New object that is the sum of this and the
    ///         specified value.
    FSIZE operator+(double val) const {
        FSIZE f;
        f.cx = cx + val;
        f.cy = cy + val;
        return f;
    }


    /// Multiplies this and the specified object and returns
    /// a new size object.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     f_x \\
    ///     f_y \\
    ///     \end{array} \right]
    ///     =
    ///     \left[ \begin{array}{cc}
    ///     this_x & 0 \\
    ///     0      & this_y \\
    ///     \end{array} \right]
    ///     \left[ \begin{array}{c}
    ///     fsize_x \\
    ///     fsize_y \\
    ///     \end{array} \right]
    /// \f]
    /// @param fsize    [in] Size object to multiply.
    /// @return New object that is the product of this and the
    ///         specified object.
    FSIZE operator*(const FSIZE& fsize) const {
        FSIZE f;
        f.cx = cx * fsize.cx;
        f.cy = cy * fsize.cy;
        return f;
    }

    /// Multiplies this and the specified object and returns
    /// a new size object.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     f_x \\
    ///     f_y \\
    ///     \end{array} \right]
    ///     =
    ///     \left[ \begin{array}{cc}
    ///     this_x & 0 \\
    ///     0      & this_y \\
    ///     \end{array} \right]
    ///     \left[ \begin{array}{c}
    ///     size_x \\
    ///     size_y \\
    ///     \end{array} \right]
    /// \f]
    /// @param size     [in] Size object to multiply.
    /// @return New object that is the product of this and the
    ///         specified object.
    FSIZE operator*(const SIZE& size) const {
        FSIZE f;
        f.cx = cx * size.cx;
        f.cy = cy * size.cy;
        return f;
    }

    /// Multiplies this and the specified value and returns
    /// a new size object.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     f_x \\
    ///     f_y \\
    ///     \end{array} \right]
    ///     = mult
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    /// \f]
    /// @param mult     [in] Value to multiply both dimensions.
    /// @return New object that is the product of this and the
    ///         specified value.
    FSIZE operator*(double mult) const {
        FSIZE f;
        f.cx = cx * mult;
        f.cy = cy * mult;
        return f;
    }


    /// Adds the specified size object to this.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    ///     =
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    ///     +
    ///     \left[ \begin{array}{c}
    ///     fsize_x \\
    ///     fsize_y \\
    ///     \end{array} \right]
    /// \f]
    /// @param fsize        [in] Size object to add to this.
    /// @return this object.
    FSIZE& operator+=(const FSIZE& fsize) {
        cx += fsize.cx;
        cy += fsize.cy;
        return *this;
    }

    /// Subtracts the specified size object from this.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    ///     =
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    ///     -
    ///     \left[ \begin{array}{c}
    ///     fsize_x \\
    ///     fsize_y \\
    ///     \end{array} \right]
    /// \f]
    /// @param fsize        [in] Size object to subtract from this.
    /// @return this object.
    FSIZE& operator-=(const FSIZE& fsize) {
        cx -= fsize.cx;
        cy -= fsize.cy;
        return *this;
    }

    /// Multiplies the specified size object and this.
    /// \f[
    ///     \left[ \begin{array}{c}
    ///     this_x \\
    ///     this_y \\
    ///     \end{array} \right]
    ///     =
    ///     \left[ \begin{array}{cc}
    ///     this_x & 0 \\
    ///     0      & this_y \\
    ///     \end{array} \right]
    ///     \left[ \begin{array}{c}
    ///     fsize_x \\
    ///     fsize_y \\
    ///     \end{array} \right]
    /// \f]
    /// @param fsize        [in] Size object to multiply with this.
    /// @return this object.
    FSIZE& operator*=(const FSIZE& fsize) {
        cx *= fsize.cx;
        cy *= fsize.cy;
        return *this;
    }
};


/// Calculates the log base 10 on each dimension of the specified
/// size object and returns the results in a new size object.
/// \f[
///     \left[ \begin{array}{c}
///     f_x \\
///     f_y \\
///     \end{array} \right]
///     =
///     \left[ \begin{array}{c}
///     \log fsize_x \\
///     \log fsize_y \\
///     \end{array} \right]
/// \f]
/// @param fsize        [in] Size object whose logarithm is to be obtained.
///
/// @return A new size object whose dimensions are the base 10 log of
///         the specified size object's dimensions.
///
inline FSIZE log10(const FSIZE& fsize) {
    FSIZE f;
    f.cx = log10(fsize.cx);
    f.cy = log10(fsize.cy);
    return f;
}


/// Calculates the floor on each dimension of the specified
/// size object and returns the results in a new size object.
/// \f[
///     \left[ \begin{array}{c}
///     f_x \\
///     f_y \\
///     \end{array} \right]
///     =
///     \left[ \begin{array}{c}
///     \lfloor fsize_x \\
///     \lfloor fsize_y \\
///     \end{array} \right]
/// \f]
/// @param fsize        [in] Size object whose floor is to be obtained.
///
/// @return A new size object whose dimensions are the floor of
///         the specified size object's dimensions.
///
inline FSIZE floor(const FSIZE& fsize) {
    FSIZE f;
    f.cx = floor(fsize.cx);
    f.cy = floor(fsize.cy);
    return f;
}

/// Subtracts the specified size object from the specified
/// value and returns a new size object.
/// \f[
///     \left[ \begin{array}{c}
///     f_x \\
///     f_y \\
///     \end{array} \right]
///     =
///     \left[ \begin{array}{c}
///     val \\
///     val \\
///     \end{array} \right]
///     -
///     \left[ \begin{array}{c}
///     fsize_x \\
///     fsize_y \\
///     \end{array} \right]
/// \f]
/// @param val      [in] The specified size object is
///                 subtracted from this value.
/// @param fsize    [in] Size object to subtract from the
///                 specified value.
///
/// @return New size object formed by the specified size
///         object being subtracted from the specified value.
///
inline FSIZE operator-(double val, const FSIZE& fsize) {
    FSIZE f;
    f.cx = val - fsize.cx;
    f.cy = val - fsize.cy;
    return f;
}


/// Represents a rectangular. Unlike the Windows RECT
/// structure, the positions of the FRECT structure are
/// double precision values.
///
struct FRECT {
    double top;         ///< Top of the rectangle.
    double bottom;      ///< Bottom of the rectangle.
    double left;        ///< Left side of the rectangle.
    double right;       ///< Right side of the rectangle.
};



/// Represents a point. Unlike the Windows POINT
/// structure, the positions of the FPOINT structure are
/// double precision values.
///
struct FPOINT {
    double x;       ///< X position.
    double y;       ///< Y position.
};


class MeaUtils
{
public:
    /// Converts the specified double to a string with the
    /// minimum number of decimal places.
    ///
    /// @param value    [in] Numerical value to convert to a string.
    ///
    /// @return String corresponding to the double value.
    ///
    static CString DblToStr(double value);


    /// Tests whether the specified string is a number. For the
    /// purposes of this method, a number is a base 10 double
    /// precision floating point value.
    ///
    /// @param str      [in] String to test
    /// @param valuep   [out] Value parsed from the string. NULL
    ///                 if not interested. If the return value is
    ///                 <b>false</b>, valuep's value is undefined.
    ///
    /// @return <b>true</b> if string represents a number.
    ///
    static bool IsNumber(LPCTSTR str, double *valuep = NULL);

    /// Tests whether the specified string is a boolean value. For
    /// the purpose of this method, the strings "1", "TRUE", "true"
    /// are boolean <b>true</b> values, while "0", "FALSE", "false"
    /// are boolean <b>false</b>.
    ///
    /// @param str      [in] String to test
    /// @param valuep   [out] Value parsed from the string. NULL
    ///                 if not interested. If the return value is
    ///                 <b>false</b>, valuep's value is undefined.
    ///
    /// @return <b>true</b> if string represents a boolean value.
    ///
    static bool IsBoolean(LPCTSTR str, bool *valuep = NULL);


    /// Converts standalone LF characters into a CR+LF pair.
    /// Existing CR+LF pairs in the string are not effected.
    ///
    /// @param str      [in] String to process.
    ///
    /// @return Converted string.
    ///
    static CString LFtoCRLF(CString str);

    /// Converts CR+LF pairs to a single LF character.
    ///
    /// @param str      [in] String to process.
    ///
    /// @return Converted string.
    ///
    static CString CRLFtoLF(CString str);

private:
    /// All members of this class are static. No instances
    /// of this class are ever created.
    ///
    MeaUtils() { }

    /// All members of this class are static. No instances
    /// of this class are ever created.
    ///
    ~MeaUtils() { }
};

