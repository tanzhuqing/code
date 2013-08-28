// ImageHandleDoc.cpp : implementation of the CImageHandleDoc class
//

#include "stdafx.h"
#include "ImageHandle.h"

#include "ImageHandleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageHandleDoc

IMPLEMENT_DYNCREATE(CImageHandleDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageHandleDoc, CDocument)
	//{{AFX_MSG_MAP(CImageHandleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageHandleDoc construction/destruction

CImageHandleDoc::CImageHandleDoc()
{
	// TODO: add one-time construction code here

}

CImageHandleDoc::~CImageHandleDoc()
{
}

BOOL CImageHandleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImageHandleDoc serialization

void CImageHandleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImageHandleDoc diagnostics

#ifdef _DEBUG
void CImageHandleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageHandleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageHandleDoc commands
