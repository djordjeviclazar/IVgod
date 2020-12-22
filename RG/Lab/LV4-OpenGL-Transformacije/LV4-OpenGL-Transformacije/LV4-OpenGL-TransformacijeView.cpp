
// LV4-OpenGL-TransformacijeView.cpp : implementation of the CLV4OpenGLTransformacijeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV4-OpenGL-Transformacije.h"
#endif

#include "LV4-OpenGL-TransformacijeDoc.h"
#include "LV4-OpenGL-TransformacijeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLV4OpenGLTransformacijeView

IMPLEMENT_DYNCREATE(CLV4OpenGLTransformacijeView, CView)

BEGIN_MESSAGE_MAP(CLV4OpenGLTransformacijeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CLV4OpenGLTransformacijeView construction/destruction

CLV4OpenGLTransformacijeView::CLV4OpenGLTransformacijeView() noexcept
{
	// TODO: add construction code here

}

CLV4OpenGLTransformacijeView::~CLV4OpenGLTransformacijeView()
{
}

BOOL CLV4OpenGLTransformacijeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV4OpenGLTransformacijeView drawing

void CLV4OpenGLTransformacijeView::OnDraw(CDC* pDC)
{
	CLV4OpenGLTransformacijeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	m_glRenderer.DrawScene(pDC);
}

void CLV4OpenGLTransformacijeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


// CLV4OpenGLTransformacijeView printing

BOOL CLV4OpenGLTransformacijeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV4OpenGLTransformacijeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV4OpenGLTransformacijeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLV4OpenGLTransformacijeView diagnostics

#ifdef _DEBUG
void CLV4OpenGLTransformacijeView::AssertValid() const
{
	CView::AssertValid();
}

void CLV4OpenGLTransformacijeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLV4OpenGLTransformacijeDoc* CLV4OpenGLTransformacijeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV4OpenGLTransformacijeDoc)));
	return (CLV4OpenGLTransformacijeDoc*)m_pDocument;
}
#endif //_DEBUG


// CLV4OpenGLTransformacijeView message handlers


int CLV4OpenGLTransformacijeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CLV4OpenGLTransformacijeView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CLV4OpenGLTransformacijeView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL CLV4OpenGLTransformacijeView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;

	//return CView::OnEraseBkgnd(pDC);
}


void CLV4OpenGLTransformacijeView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyUp(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
		case 0x41:
		{
			m_glRenderer.xAxisRotate -= m_glRenderer.angle;
			Invalidate();
		}
		break;
		case 0x44:
		{
			m_glRenderer.xAxisRotate += m_glRenderer.angle;
			Invalidate();
		}
		break;
		case 0x51:
		{
			m_glRenderer.yAxisRotate -= m_glRenderer.angle;
			Invalidate();
		}
		break;
		case 0x45:
		{
			m_glRenderer.yAxisRotate += m_glRenderer.angle;
			Invalidate();
		}
		break;
		case 0x50:
		{
			m_glRenderer.xAxisRotateGlobal -= m_glRenderer.angleGlobal;
			Invalidate();
		}
		break;
		case 0x46:
		{
			m_glRenderer.xAxisRotateGlobal += m_glRenderer.angleGlobal;
			Invalidate();
		}
		break;
		case 0x47:
		{
			m_glRenderer.yAxisRotateGlobal -= m_glRenderer.angleGlobal;
			Invalidate();
		}
		break;
		case 0x48:
		{
			m_glRenderer.yAxisRotateGlobal += m_glRenderer.angleGlobal;
			Invalidate();
		}
		break;

		break;
		default:
			break;
	}
}


void CLV4OpenGLTransformacijeView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnMouseMove(nFlags, point);
}


void CLV4OpenGLTransformacijeView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonUp(nFlags, point);
}


void CLV4OpenGLTransformacijeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnLButtonDown(nFlags, point);
}
