
// LV6-OpenGL-Teksture1.1View.cpp : implementation of the CLV6OpenGLTeksture11View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV6-OpenGL-Teksture1.1.h"
#endif

#include "LV6-OpenGL-Teksture1.1Doc.h"
#include "LV6-OpenGL-Teksture1.1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLV6OpenGLTeksture11View

IMPLEMENT_DYNCREATE(CLV6OpenGLTeksture11View, CView)

BEGIN_MESSAGE_MAP(CLV6OpenGLTeksture11View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CLV6OpenGLTeksture11View construction/destruction

CLV6OpenGLTeksture11View::CLV6OpenGLTeksture11View() noexcept
{
	// TODO: add construction code here

}

CLV6OpenGLTeksture11View::~CLV6OpenGLTeksture11View()
{
}

BOOL CLV6OpenGLTeksture11View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV6OpenGLTeksture11View drawing

void CLV6OpenGLTeksture11View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}

void CLV6OpenGLTeksture11View::OnDraw(CDC* pDC)
{
	CLV6OpenGLTeksture11Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	this->m_glRenderer.DrawScene(pDC);
}


// CLV6OpenGLTeksture11View printing

BOOL CLV6OpenGLTeksture11View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV6OpenGLTeksture11View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV6OpenGLTeksture11View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLV6OpenGLTeksture11View diagnostics

#ifdef _DEBUG
void CLV6OpenGLTeksture11View::AssertValid() const
{
	CView::AssertValid();
}

void CLV6OpenGLTeksture11View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLV6OpenGLTeksture11Doc* CLV6OpenGLTeksture11View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV6OpenGLTeksture11Doc)));
	return (CLV6OpenGLTeksture11Doc*)m_pDocument;
}
#endif //_DEBUG


// CLV6OpenGLTeksture11View message handlers


int CLV6OpenGLTeksture11View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CLV6OpenGLTeksture11View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CLV6OpenGLTeksture11View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL CLV6OpenGLTeksture11View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return true;

	//return CView::OnEraseBkgnd(pDC);
}


void CLV6OpenGLTeksture11View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}


void CLV6OpenGLTeksture11View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);

	m_glRenderer.firstRotation = true;
}


void CLV6OpenGLTeksture11View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);

	if (nFlags & MK_LBUTTON)
	{
		m_glRenderer.moveEye(point);
		Invalidate();
	}
}
