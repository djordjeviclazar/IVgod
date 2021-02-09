
// Bager-GDIView.cpp : implementation of the CBagerGDIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Bager-GDI.h"
#endif

#include "Bager-GDIDoc.h"
#include "Bager-GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBagerGDIView

IMPLEMENT_DYNCREATE(CBagerGDIView, CView)

BEGIN_MESSAGE_MAP(CBagerGDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CBagerGDIView construction/destruction

CBagerGDIView::CBagerGDIView() noexcept
{
	// TODO: add construction code here

}

CBagerGDIView::~CBagerGDIView()
{
}

BOOL CBagerGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBagerGDIView drawing

void CBagerGDIView::OnDraw(CDC* /*pDC*/)
{
	CBagerGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CBagerGDIView printing

BOOL CBagerGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBagerGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBagerGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBagerGDIView diagnostics

#ifdef _DEBUG
void CBagerGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CBagerGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBagerGDIDoc* CBagerGDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBagerGDIDoc)));
	return (CBagerGDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CBagerGDIView message handlers
