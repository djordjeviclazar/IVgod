
// LV1-GDI-TangramView.cpp : implementation of the CLV1GDITangramView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV1-GDI-Tangram.h"
#endif

#include "LV1-GDI-TangramDoc.h"
#include "LV1-GDI-TangramView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLV1GDITangramView

IMPLEMENT_DYNCREATE(CLV1GDITangramView, CView)

BEGIN_MESSAGE_MAP(CLV1GDITangramView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLV1GDITangramView construction/destruction

CLV1GDITangramView::CLV1GDITangramView() noexcept
{
	// TODO: add construction code here

}

CLV1GDITangramView::~CLV1GDITangramView()
{
}

BOOL CLV1GDITangramView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV1GDITangramView drawing

void CLV1GDITangramView::OnDraw(CDC* /*pDC*/)
{
	CLV1GDITangramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CLV1GDITangramView printing

BOOL CLV1GDITangramView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV1GDITangramView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV1GDITangramView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLV1GDITangramView diagnostics

#ifdef _DEBUG
void CLV1GDITangramView::AssertValid() const
{
	CView::AssertValid();
}

void CLV1GDITangramView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLV1GDITangramDoc* CLV1GDITangramView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV1GDITangramDoc)));
	return (CLV1GDITangramDoc*)m_pDocument;
}
#endif //_DEBUG


// CLV1GDITangramView message handlers
