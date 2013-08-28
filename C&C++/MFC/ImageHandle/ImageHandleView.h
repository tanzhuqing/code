// ImageHandleView.h : interface of the CImageHandleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEHANDLEVIEW_H__E7BF0734_1EC2_44CA_9A5B_4398129E180B__INCLUDED_)
#define AFX_IMAGEHANDLEVIEW_H__E7BF0734_1EC2_44CA_9A5B_4398129E180B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageHandleView : public CView
{
protected: // create from serialization only
	CImageHandleView();
	DECLARE_DYNCREATE(CImageHandleView)

// Attributes
public:
	CImageHandleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageHandleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageHandleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageHandleView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageHandleView.cpp
inline CImageHandleDoc* CImageHandleView::GetDocument()
   { return (CImageHandleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEHANDLEVIEW_H__E7BF0734_1EC2_44CA_9A5B_4398129E180B__INCLUDED_)
