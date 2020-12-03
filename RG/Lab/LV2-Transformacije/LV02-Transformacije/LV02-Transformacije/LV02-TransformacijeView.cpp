
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
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CLV02TransformacijeView construction/destruction

void CLV02TransformacijeView::drawBackground(CDC* pDC, int height, int width, COLORREF color)
{
	CPen* oldPen = (CPen*)pDC->SelectStockObject(NULL_PEN);
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(new CBrush(color));
	pDC->Rectangle(0, 0, width, height);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

void CLV02TransformacijeView::drawGrid(CDC* pDC)
{
	if (gridOn)
	{
		CPen* oldPen = (CPen*)pDC->SelectStockObject(WHITE_PEN);
		for (int i = 25; i < 500; i += unit)
		{
			pDC->MoveTo(0, i);
			pDC->LineTo(500, i);
			pDC->MoveTo(i, 0);
			pDC->LineTo(i, 500);
		}

		pDC->SelectObject(oldPen);
	}
}

void CLV02TransformacijeView::drawVase(CDC* pDC)
{
	CPen* oldPen = (CPen*)pDC->SelectStockObject(BLACK_PEN);
	CBrush* currentBrush = new CBrush(RGB(223, 147, 3));
	CBrush* oldBrush = (CBrush*)pDC->SelectObject(currentBrush);

	POINT points[8];
	points[0].x = 210; points[0].y = 500;
	points[1].x = 200; points[1].y = 450;
	points[2].x = 190; points[2].y = 450;
	points[3].x = 190; points[3].y = 430;
	points[4].x = 310; points[4].y = 430;
	points[5].x = 310; points[5].y = 450;
	points[6].x = 300; points[6].y = 450;
	points[7].x = 290; points[7].y = 500;

	pDC->Polygon(points, 8);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	delete currentBrush;
}

void CLV02TransformacijeView::signature(CDC* pDC, int x, int y, int rotation, COLORREF color, int textWidth, int textHeight)
{
	CFont currentFont;
	currentFont.CreateFontW(textHeight, textWidth, rotation, rotation, FW_DEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
							OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, 0);
	CFont* oldFont = pDC->SelectObject(&currentFont);
	
	/*LOGFONT p;
	oldFont->GetLogFont(&p);
	pDC->SelectObject(oldFont);

	p.lfHeight = textHeight * 10;
	p.lfWidth = textWidth;
	p.lfEscapement = 900;
	currentFont.CreatePointFontIndirect(&p, pDC);*/

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldTextColor = pDC->SetTextColor(color);
	pDC->TextOutW(x, y, CString("16559 Lazar Djordjevic"));

	pDC->SelectObject(oldFont);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextColor(oldTextColor);
}

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

void CLV02TransformacijeView::OnDraw(CDC* pDC)
{
	CLV02TransformacijeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	drawBackground(pDC, 500, 500, RGB(3, 225, 250));

	/* TODO: Draw cactus */

	drawVase(pDC);
	drawGrid(pDC);
	signature(pDC, 475, 25, 2700, RGB(255, 255, 3), 15, 30);
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


void CLV02TransformacijeView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyUp(nChar, nRepCnt, nFlags);

	if (nChar == 0x47 && nRepCnt < 2) // on 'g' key; single click
	{
		gridOn = !gridOn;
		Invalidate();
	}
}
