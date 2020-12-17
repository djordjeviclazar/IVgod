
// MFCApplicationOpenGLExample1View.cpp : implementation of the CMFCApplicationOpenGLExample1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplicationOpenGLExample1.h"
#endif

#include "MFCApplicationOpenGLExample1Doc.h"
#include "MFCApplicationOpenGLExample1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationOpenGLExample1View

IMPLEMENT_DYNCREATE(CMFCApplicationOpenGLExample1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplicationOpenGLExample1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCApplicationOpenGLExample1View construction/destruction

CMFCApplicationOpenGLExample1View::CMFCApplicationOpenGLExample1View() noexcept
{
	// TODO: add construction code here

}

CMFCApplicationOpenGLExample1View::~CMFCApplicationOpenGLExample1View()
{
}

BOOL CMFCApplicationOpenGLExample1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationOpenGLExample1View drawing

void CMFCApplicationOpenGLExample1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplicationOpenGLExample1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCApplicationOpenGLExample1View printing

BOOL CMFCApplicationOpenGLExample1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationOpenGLExample1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplicationOpenGLExample1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCApplicationOpenGLExample1View diagnostics

#ifdef _DEBUG
void CMFCApplicationOpenGLExample1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationOpenGLExample1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationOpenGLExample1Doc* CMFCApplicationOpenGLExample1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationOpenGLExample1Doc)));
	return (CMFCApplicationOpenGLExample1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationOpenGLExample1View message handlers
