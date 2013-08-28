// ImageHandleDoc.h : interface of the CImageHandleDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEHANDLEDOC_H__71BD51D1_EA71_4F0E_B6D6_B75F91E216B8__INCLUDED_)
#define AFX_IMAGEHANDLEDOC_H__71BD51D1_EA71_4F0E_B6D6_B75F91E216B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageHandleDoc : public CDocument
{
protected: // create from serialization only
	CImageHandleDoc();
	DECLARE_DYNCREATE(CImageHandleDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageHandleDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageHandleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageHandleDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEHANDLEDOC_H__71BD51D1_EA71_4F0E_B6D6_B75F91E216B8__INCLUDED_)
