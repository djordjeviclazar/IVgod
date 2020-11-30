
// LV02-TransformacijeView.cpp : implementation of the CLV02TransformacijeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV02-Transformacije.h"
#endif

#include "LV02-TransformacijeDoc.h"
#include "LV02-TransformacijeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLV02TransformacijeView

IMPLEMENT_DYNCREATE(CLV02TransformacijeView, CView)

BEGIN_MESSAGE_MAP(CLV02TransformacijeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLV02TransformacijeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CLV02TransformacijeView construction/destruction

CLV02TransformacijeView::CLV02TransformacijeView() noexcept
{
	// TODO: add construction code here

}

CLV02TransformacijeView::~CLV02TransformacijeView()
{
}

BOOL CLV02TransformacijeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV02TransformacijeView drawing

void CLV02TransformacijeView::OnDraw(CDC* /*pDC*/)
{
	CLV02TransformacijeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CLV02TransformacijeView printing


void CLV02TransformacijeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLV02TransformacijeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV02TransformacijeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV02TransformacijeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLV02TransformacijeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLV02TransformacijeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CLV02TransformacijeView diagnostics

#ifdef _DEBUG
void CLV02TransformacijeView::AssertValid() const
{
	CView::AssertValid();
}

void CLV02TransformacijeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLV02TransformacijeDoc* CLV02TransformacijeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV02TransformacijeDoc)));
	return (CLV02TransformacijeDoc*)m_pDocument;
}
#endif //_DEBUG


// CLV02TransformacijeView message handlers
