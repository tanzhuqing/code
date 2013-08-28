// ImageHandleView.cpp : implementation of the CImageHandleView class
//

#include "stdafx.h"
#include "ImageHandle.h"

#include "ImageHandleDoc.h"
#include "ImageHandleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageHandleView

IMPLEMENT_DYNCREATE(CImageHandleView, CView)

BEGIN_MESSAGE_MAP(CImageHandleView, CView)
	//{{AFX_MSG_MAP(CImageHandleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageHandleView construction/destruction

CImageHandleView::CImageHandleView()
{
	// TODO: add construction code here

}

CImageHandleView::~CImageHandleView()
{
}

BOOL CImageHandleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageHandleView drawing

void CImageHandleView::OnDraw(CDC* pDC)
{
	CImageHandleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CImageHandleView printing

BOOL CImageHandleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageHandleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageHandleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImageHandleView diagnostics

#ifdef _DEBUG
void CImageHandleView::AssertValid() const
{
	CView::AssertValid();
}

void CImageHandleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageHandleDoc* CImageHandleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageHandleDoc)));
	return (CImageHandleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageHandleView message handlers
