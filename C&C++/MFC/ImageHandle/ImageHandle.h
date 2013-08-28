// ImageHandle.h : main header file for the IMAGEHANDLE application
//

#if !defined(AFX_IMAGEHANDLE_H__7975BF95_0ACC_4D8B_B62E_0E02C3C2578E__INCLUDED_)
#define AFX_IMAGEHANDLE_H__7975BF95_0ACC_4D8B_B62E_0E02C3C2578E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageHandleApp:
// See ImageHandle.cpp for the implementation of this class
//

class CImageHandleApp : public CWinApp
{
public:
	CImageHandleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageHandleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImageHandleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEHANDLE_H__7975BF95_0ACC_4D8B_B62E_0E02C3C2578E__INCLUDED_)
