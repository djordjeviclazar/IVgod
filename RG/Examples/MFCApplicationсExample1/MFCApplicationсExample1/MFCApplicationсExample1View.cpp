
// MFCApplicationсExample1View.cpp : implementation of the CMFCApplicationсExample1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplicationсExample1.h"
#endif

#include "MFCApplicationсExample1Doc.h"
#include "MFCApplicationсExample1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplicationсExample1View

IMPLEMENT_DYNCREATE(CMFCApplicationсExample1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplicationсExample1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCApplicationсExample1View construction/destruction

CMFCApplicationсExample1View::CMFCApplicationсExample1View() noexcept
{
	// TODO: add construction code here

}

CMFCApplicationсExample1View::~CMFCApplicationсExample1View()
{
}

BOOL CMFCApplicationсExample1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCApplicationсExample1View drawing

void CMFCApplicationсExample1View::OnDraw(CDC* pDC)
{
	CMFCApplicationсExample1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	
	float angle = 3.14159 / 7.;
	XFORM matrix1, matrix2;
	matrix1.eM11 = (FLOAT)cos(angle);
	matrix1.eM12 = (FLOAT)sin(angle);
	matrix1.eM21 = (FLOAT)-sin(angle);
	matrix1.eM22 = (FLOAT)cos(angle);
	matrix1.eDx = (FLOAT)0.;
	matrix1.eDy = (FLOAT)0.;
	pDC->SetWorldTransform(&matrix1);

	matrix2.eM11 = (FLOAT)1.;
	matrix2.eM12 = (FLOAT)0.;
	matrix2.eM21 = (FLOAT)0.;
	matrix2.eM22 = (FLOAT)1.;
	matrix2.eDx = (FLOAT)50.;
	matrix2.eDy = (FLOAT)100.;
	pDC->ModifyWorldTransform(&matrix2, MWT_LEFTMULTIPLY);

	CRect rect = new CRect(200, 100, 300, 200);
	pDC->Rectangle(rect);
}


// CMFCApplicationсExample1View printing

BOOL CMFCApplicationсExample1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCApplicationсExample1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCApplicationсExample1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMFCApplicationсExample1View diagnostics

#ifdef _DEBUG
void CMFCApplicationсExample1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplicationсExample1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplicationсExample1Doc* CMFCApplicationсExample1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplicationсExample1Doc)));
	return (CMFCApplicationсExample1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplicationсExample1View message handlers
