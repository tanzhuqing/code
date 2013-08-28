
// waveformView.cpp : CwaveformView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "waveform.h"
#endif

#include "waveformDoc.h"
#include "waveformView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CwaveformView

IMPLEMENT_DYNCREATE(CwaveformView, CView)

BEGIN_MESSAGE_MAP(CwaveformView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CwaveformView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CwaveformView 构造/析构

CwaveformView::CwaveformView()
{
	// TODO: 在此处添加构造代码

}

CwaveformView::~CwaveformView()
{
}

BOOL CwaveformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CwaveformView 绘制

void CwaveformView::OnDraw(CDC* /*pDC*/)
{
	CwaveformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CwaveformView 打印


void CwaveformView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CwaveformView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CwaveformView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CwaveformView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CwaveformView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CwaveformView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CwaveformView 诊断

#ifdef _DEBUG
void CwaveformView::AssertValid() const
{
	CView::AssertValid();
}

void CwaveformView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CwaveformDoc* CwaveformView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CwaveformDoc)));
	return (CwaveformDoc*)m_pDocument;
}
#endif //_DEBUG


// CwaveformView 消息处理程序
