// MFC360Demo.h : main header file for the MFC360DEMO application
//

#if !defined(AFX_MFC360DEMO_H__E20EA6A7_F6CC_45A0_868D_75368B020CFB__INCLUDED_)
#define AFX_MFC360DEMO_H__E20EA6A7_F6CC_45A0_868D_75368B020CFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFC360DemoApp:
// See MFC360Demo.cpp for the implementation of this class
//

class CMFC360DemoApp : public CWinApp
{
public:
	CMFC360DemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFC360DemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFC360DemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC360DEMO_H__E20EA6A7_F6CC_45A0_868D_75368B020CFB__INCLUDED_)
