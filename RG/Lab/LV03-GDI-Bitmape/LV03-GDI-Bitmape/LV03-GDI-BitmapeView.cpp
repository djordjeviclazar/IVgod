
// LV03-GDI-BitmapeView.cpp : implementation of the CLV03GDIBitmapeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV03-GDI-Bitmape.h"
#endif

#include "LV03-GDI-BitmapeDoc.h"
#include "LV03-GDI-BitmapeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLV03GDIBitmapeView

IMPLEMENT_DYNCREATE(CLV03GDIBitmapeView, CView)

BEGIN_MESSAGE_MAP(CLV03GDIBitmapeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLV03GDIBitmapeView construction/destruction

CLV03GDIBitmapeView::CLV03GDIBitmapeView() noexcept
{
	// TODO: add construction code here

}

CLV03GDIBitmapeView::~CLV03GDIBitmapeView()
{
}

BOOL CLV03GDIBitmapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV03GDIBitmapeView drawing

void CLV03GDIBitmapeView::OnDraw(CDC* /*pDC*/)
{
	CLV03GDIBitmapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CLV03GDIBitmapeView printing

BOOL CLV03GDIBitmapeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV03GDIBitmapeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV03GDIBitmapeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLV03GDIBitmapeView diagnostics

#ifdef _DEBUG
void CLV03GDIBitmapeView::AssertValid() const
{
	CView::AssertValid();
}

void CLV03GDIBitmapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLV03GDIBitmapeDoc* CLV03GDIBitmapeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV03GDIBitmapeDoc)));
	return (CLV03GDIBitmapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CLV03GDIBitmapeView message handlers
