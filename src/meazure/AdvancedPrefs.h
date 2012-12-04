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
/// @brief Advanced preferences property page header file.

#pragma once


/// Property page for the advanced preferences. This preference page allows
/// a startup profile to be specified and provides the master reset for all
/// application settings.
///
class MeaAdvancedPrefs : public CPropertyPage
{
    DECLARE_DYNCREATE(MeaAdvancedPrefs)

public:
    /// Constructs the advanced preferences property page.
    ///
    MeaAdvancedPrefs();

    /// Destroys the advanced preferences property page.
    ///
    ~MeaAdvancedPrefs();

    //{{AFX_DATA(MeaAdvancedPrefs)
    enum { IDD = IDD_PREF_ADVANCED };
    CString m_startupProfile;
	CString m_screenGrabDirectory;
    //}}AFX_DATA

    /// @var m_startupProfile
    /// Profile file to load on application startup.

    
    CFileDialog *m_startupProfileDlg;       ///< File dialog for selecting the startup profile file.

private:
	BOOL BrowseForScreenGrabDirectory(void);

    //{{AFX_VIRTUAL(MeaAdvancedPrefs)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    //}}AFX_VIRTUAL

    /// @fn DoDataExchange(CDataExchange* pDX)
    /// Performs Dynamic Data Exchange (DDX) for the page.
    ///
    /// @param pDX  [in] DDX object for exchanging data between the page UI
    ///             and the member variables.

protected:
    //{{AFX_MSG(MeaAdvancedPrefs)
    afx_msg void OnProfileBtn();
    afx_msg void OnChangeProfilePathname();
    afx_msg void OnClearProfile();
    afx_msg void OnMasterReset();
	afx_msg void OnSelectScreenGrabOutputDirectoryBtn();
	afx_msg void OnChangeScreenGrabOutputDirectory();
    //}}AFX_MSG

    /// @fn OnProfileBtn()
    /// When the browse button is pressed, this method is called to
    /// display the profile file selection dialog.

    /// @fn OnChangeProfilePathname()
    /// Called when the profile file pathname is changed so that
    /// the modified flag can be set.

    /// @fn OnClearProfile()
    /// Clears the text in the startup profile edit field.

    /// @fn OnMasterReset()
    /// Called when the mast reset button is pressed. A reset confirmation
    /// dialog is displayed and upon an affirmative response, the master
    /// reset is performed.

    /// @fn OnSelectScreenGrabOutputDirectoryBtn()
    /// When the browse for screen grab button is pressed, called to display a browser
	/// for folder dialog

    /// @fn OnChangeScreenGrabOutputDirectory()
    /// Called when the screen grab output pathname is changed so that
    /// the modified flag can be set.

    DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
