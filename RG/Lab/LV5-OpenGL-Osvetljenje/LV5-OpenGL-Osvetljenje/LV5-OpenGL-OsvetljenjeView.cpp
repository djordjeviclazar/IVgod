
// LV5-OpenGL-OsvetljenjeView.cpp : implementation of the CLV5OpenGLOsvetljenjeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV5-OpenGL-Osvetljenje.h"
#endif

#include "LV5-OpenGL-OsvetljenjeDoc.h"
#include "LV5-OpenGL-OsvetljenjeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLV5OpenGLOsvetljenjeView

IMPLEMENT_DYNCREATE(CLV5OpenGLOsvetljenjeView, CView)

BEGIN_MESSAGE_MAP(CLV5OpenGLOsvetljenjeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CLV5OpenGLOsvetljenjeView construction/destruction

CLV5OpenGLOsvetljenjeView::CLV5OpenGLOsvetljenjeView() noexcept
{
	// TODO: add construction code here

}

CLV5OpenGLOsvetljenjeView::~CLV5OpenGLOsvetljenjeView()
{
}

BOOL CLV5OpenGLOsvetljenjeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV5OpenGLOsvetljenjeView drawing

void CLV5OpenGLOsvetljenjeView::OnDraw(CDC* pDC)
{
	CLV5OpenGLOsvetljenjeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	this->m_glRenderer.DrawScene(pDC);
}

void CLV5OpenGLOsvetljenjeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


// CLV5OpenGLOsvetljenjeView printing

BOOL CLV5OpenGLOsvetljenjeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV5OpenGLOsvetljenjeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV5OpenGLOsvetljenjeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLV5OpenGLOsvetljenjeView diagnostics

#ifdef _DEBUG
void CLV5OpenGLOsvetljenjeView::AssertValid() const
{
	CView::AssertValid();
}

void CLV5OpenGLOsvetljenjeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLV5OpenGLOsvetljenjeDoc* CLV5OpenGLOsvetljenjeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV5OpenGLOsvetljenjeDoc)));
	return (CLV5OpenGLOsvetljenjeDoc*)m_pDocument;
}
#endif //_DEBUG


// CLV5OpenGLOsvetljenjeView message handlers


int CLV5OpenGLOsvetljenjeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CLV5OpenGLOsvetljenjeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CLV5OpenGLOsvetljenjeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


void CLV5OpenGLOsvetljenjeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);

	//m_glRenderer.startPoint.x = point.x;
	//m_glRenderer.startPoint.y = point.y;
	//rotateView = true;
}


void CLV5OpenGLOsvetljenjeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);

	//rotateView = false;
	m_glRenderer.firstRotation = true;
}


void CLV5OpenGLOsvetljenjeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//if (rotateView )
	if (nFlags & MK_LBUTTON)
	{
		m_glRenderer.moveEye(point);
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);

	
	
}
