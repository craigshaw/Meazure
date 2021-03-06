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
/// @brief Ruler property page header file.

#pragma once

#include "Ruler.h"


/// Property page for setting ruler preferences. The ruler preferences
/// include the ruler background and border colors and the ruler opacity
/// (Windows 2000 and up). The property page provides a vertical and
/// a horizontal ruler sample to preview the properties before they are
/// applied. 
///
class MeaRulerPrefs : public CPropertyPage
{
    DECLARE_DYNCREATE(MeaRulerPrefs)

public:
    /// Constructs an instance of the ruler property page.
    ///
    MeaRulerPrefs();
    
    /// Destroys an instance of the ruler property page.
    ///
    ~MeaRulerPrefs();

    //{{AFX_DATA(MeaRulerPrefs)
    enum { IDD = IDD_PREF_RULERS };
    int     m_opacity;
    //}}AFX_DATA

    /// @var m_opacity
    /// Opacity of the ruler where 0 is transparent and 255 is opaque.

    
    COLORREF    m_backColor;        ///< Ruler background color.
    COLORREF    m_borderColor;      ///< Color for the ruler border and tick marks.


    /// Called when the property page is created. This method
    /// Creates the sample rulers and initializes the opacity
    /// slider.
    ///
    /// @return TRUE, indicating that the input focus should be
    ///         set to the first control on the page.
    ///
    virtual BOOL OnInitDialog();

    //{{AFX_VIRTUAL(MeaRulerPrefs)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    //}}AFX_VIRTUAL

    /// @fn DoDataExchange(CDataExchange* pDX)
    /// Performs Dynamic Data Exchange (DDX) for the page.
    ///
    /// @param pDX  [in] DDX object for exchanging data between the page UI
    ///             and the member variables.

protected:
    //{{AFX_MSG(MeaRulerPrefs)
    afx_msg void OnChangeBkColor();
    afx_msg void OnChangeBorderColor();
    afx_msg void OnDefBkColor();
    afx_msg void OnDefBorderColor();
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    //}}AFX_MSG

    /// @fn OnChangeBkColor()
    /// Called when the background color button is pressed. This method
    /// displays the color picker dialog and calls the ColorsChanged()
    /// method if a new background color is chosen.

    /// @fn OnChangeBorderColor()
    /// Called when the border color button is pressed. This method
    /// displays the color picker dialog and calls the ColorsChanged()
    /// method if a new border color is chosen.

    /// @fn OnDefBkColor()
    /// Called when the default background color button is pressed. This
    /// method restores the default background color.

    /// @fn OnDefBorderColor()
    /// Called when the default border color button is pressed. This
    /// method restores the default border color.
    
    /// @fn OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
    /// Called when the ruler opacity slider is moved to change the
    /// ruler opacity.

    DECLARE_MESSAGE_MAP()

private:
    /// Sets the background and border color on the sample rulers and
    /// sets the modified flag.
    ///
    void    ColorsChanged();

    MeaRuler        m_vRuler;       ///< Vertical sample ruler.
    MeaRuler        m_hRuler;       ///< Horizontal sample ruler.
};

//{{AFX_INSERT_LOCATION}}
