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

#include "StdAfx.h"
#include "MeaAssert.h"
#include "Resource.h"
#include "Preferences.h"
#include "AdvancedPrefs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(MeaAdvancedPrefs, CPropertyPage)


BEGIN_MESSAGE_MAP(MeaAdvancedPrefs, CPropertyPage)
    //{{AFX_MSG_MAP(MeaAdvancedPrefs)
    ON_BN_CLICKED(IDC_PROFILE_BTN, OnProfileBtn)
    ON_EN_CHANGE(IDC_PROFILE_PATHNAME, OnChangeProfilePathname)
    ON_BN_CLICKED(IDC_CLEAR_PROFILE, OnClearProfile)
    ON_BN_CLICKED(IDC_MASTER_RESET, OnMasterReset)
	ON_BN_CLICKED(IDC_SCREENGRAB_DIR_BTN, OnSelectScreenGrabOutputDirectoryBtn)
	ON_EN_CHANGE(IDC_SCREENGRABS_DIR, OnChangeScreenGrabOutputDirectory)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


MeaAdvancedPrefs::MeaAdvancedPrefs() : CPropertyPage(MeaAdvancedPrefs::IDD),
	m_startupProfileDlg(NULL)
{
    //{{AFX_DATA_INIT(MeaAdvancedPrefs)
    m_startupProfile = _T("");
	m_screenGrabDirectory = _T("");
    //}}AFX_DATA_INIT
}


MeaAdvancedPrefs::~MeaAdvancedPrefs()
{
    m_startupProfileDlg = NULL;
}


void MeaAdvancedPrefs::DoDataExchange(CDataExchange* pDX)
{
    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(MeaAdvancedPrefs)
    DDX_Text(pDX, IDC_PROFILE_PATHNAME, m_startupProfile);
	DDX_Text(pDX, IDC_SCREENGRABS_DIR, m_screenGrabDirectory);
    //}}AFX_DATA_MAP
}


void MeaAdvancedPrefs::OnProfileBtn() 
{
    MeaAssert(m_startupProfileDlg != NULL);
    if (m_startupProfileDlg->DoModal() == IDOK) {
        CEdit *edit = static_cast<CEdit*>(GetDlgItem(IDC_PROFILE_PATHNAME));
        edit->SetWindowText(m_startupProfileDlg->GetPathName());
    }
}

void MeaAdvancedPrefs::OnSelectScreenGrabOutputDirectoryBtn() 
{
    if (BrowseForScreenGrabDirectory() == TRUE) {
		CEdit *edit = static_cast<CEdit*>(GetDlgItem(IDC_SCREENGRABS_DIR));
        edit->SetWindowText(m_screenGrabDirectory);
    }
}

BOOL MeaAdvancedPrefs::BrowseForScreenGrabDirectory(void)
{
	BROWSEINFO bi;
	memset((LPVOID)&bi, 0, sizeof(bi));

	TCHAR szDisplayName[_MAX_PATH];
	szDisplayName[0] = '\0';

	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = _T("Select a folder");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST pIIL = ::SHBrowseForFolder(&bi);
	TCHAR szReturnedDir[_MAX_PATH];

	BOOL bRet = ::SHGetPathFromIDList(pIIL, (TCHAR*)&szReturnedDir);
	
	if (bRet)
	{
		if (szReturnedDir != _T(""))
		{
			m_screenGrabDirectory = szReturnedDir;
		}

		LPMALLOC pMalloc;
		SHGetMalloc(&pMalloc);
		pMalloc->Free(pIIL);
		pMalloc->Release();
	}

	return bRet;
}

void MeaAdvancedPrefs::OnClearProfile()
{
    CEdit *edit = static_cast<CEdit*>(GetDlgItem(IDC_PROFILE_PATHNAME));
    edit->SetWindowText("");
}

void MeaAdvancedPrefs::OnChangeProfilePathname()
{
    SetModified(TRUE);
}

void MeaAdvancedPrefs::OnChangeScreenGrabOutputDirectory()
{
    SetModified(TRUE);
}

void MeaAdvancedPrefs::OnMasterReset()
{
    if (AfxMessageBox(IDS_MEA_MASTER_RESET, MB_YESNO | MB_ICONWARNING) == IDYES) {
        MeaPreferences* sheet = static_cast<MeaPreferences*>(GetParent());
        MeaAssert(sheet != NULL);

        sheet->EndDialog(ID_MEA_MASTER_RESET);
    }
}
