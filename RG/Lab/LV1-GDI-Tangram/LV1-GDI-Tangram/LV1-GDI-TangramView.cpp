
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

#define PI 3.14159


// CLV1GDITangramView

IMPLEMENT_DYNCREATE(CLV1GDITangramView, CView)

BEGIN_MESSAGE_MAP(CLV1GDITangramView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CLV1GDITangramView construction/destruction

POINT* CLV1GDITangramView::drawPolygon(CDC* pDC, POINT* nodes, int nodeNumber, COLORREF color, COLORREF lineColor, int hached)
{
	// drawing:
	CPen* oldPen, * currentPen = new CPen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 5, lineColor);
	CBrush* oldBrush, * currentBrush;
	if (hached < 0) { currentBrush = new CBrush(color); }
	else { currentBrush = new CBrush(hached, color); }

	oldPen = pDC->SelectObject(currentPen);
	oldBrush = pDC->SelectObject(currentBrush);

	pDC->Polygon(nodes, nodeNumber);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	delete currentPen;
	delete currentBrush;

	// return incenter:
	POINT *incenter = 0;
	if (nodeNumber == 3)
	{
		/*
		* coord = (a * A.coord + b * B.coord + c * C.coord) / (a + b + c)
		* !!! must round after division: (int)(x + 0.5 - (x < 0)), coordinates are always positive
		*/
		int a = distance(nodes[1], nodes[2]), b = distance(nodes[0], nodes[2]), c = distance(nodes[0], nodes[1]);

		incenter = new POINT();
		incenter->x = (int)((nodes[0].x * a + nodes[1].x * b + nodes[2].x * c) * 1. / (a + b + c) + 0.5);
		incenter->y = (int)((nodes[0].y * a + nodes[1].y * b + nodes[2].y * c) * 1. / (a + b + c) + 0.5);
	}

	return incenter;
}

void CLV1GDITangramView::drawInpolygon(CDC* pDC, POINT* center, int nodeNumber, int radius, double rotation, COLORREF lineColor)
{
	POINT* nodes = new POINT[nodeNumber];
	double displacementAngle = (1. - 2. / nodeNumber) * PI; // interior polygon angle in radians
	double angle = rotation; // argument in formula

	for (int i = 0; i < nodeNumber; i++)
	{
		// formula
		double x = (center->x + radius * cos(angle) + 0.5);
		nodes[i].x = (int)(x - (x < 0));
		double y = (center->y + radius * sin(angle) + 0.5);
		nodes[i].y = (int)(y - (y < 0));

		angle += displacementAngle;
	}

	// drawing
	CPen* oldPen, * currentPen = new CPen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND, 3, lineColor);
	CBrush* oldBrush;

	oldPen = pDC->SelectObject(currentPen);
	oldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	pDC->Polygon(nodes, nodeNumber);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	delete currentPen;
}

int CLV1GDITangramView::distance(POINT& a, POINT& b)
{
	double aX = a.x, aY = a.y, bX = b.x, bY = b.y;
	double ret = sqrt(pow(aX - bX, 2) + pow(aY - bY, 2));
	return (int)(ret - (ret < 0));
}

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

void CLV1GDITangramView::OnDraw(CDC* pDC)
{
	CLV1GDITangramDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CPen *oldPen;
	CBrush *oldBrush;

	POINT* triangleNodes = new POINT[3], * quadrilateralNodes = new POINT[4];

	// background
	oldPen = (CPen*)pDC->SelectStockObject(NULL_PEN);
	oldBrush = (CBrush*)pDC->SelectStockObject(GRAY_BRUSH);
	pDC->Rectangle(0, 0, 500, 500);

	// polygons:

	int a = unit * 9; // big square edge
	POINT* incenter;
	int radius;
	double rotation;

	// yellow triangle
	triangleNodes[0].x = unit; triangleNodes[0].y = unit;
	triangleNodes[1].x = unit; triangleNodes[1].y = unit + a;
	triangleNodes[2].x = unit + (a >> 1); triangleNodes[2].y = triangleNodes[2].x;

	incenter = drawPolygon(pDC, triangleNodes, 3, RGB(240, 252, 3), RGB(3, 15, 252), -1);
	radius = unit;
	rotation = 0.;
	drawInpolygon(pDC, incenter, 6, radius, rotation, RGB(3, 15, 252));
	delete incenter;

	// red triangle
	triangleNodes[0].x = unit; triangleNodes[0].y = unit;
	triangleNodes[1].x = unit + (a >> 1); triangleNodes[1].y = unit;
	triangleNodes[2].x = unit + (a >> 1); triangleNodes[2].y = triangleNodes[2].x;

	incenter = drawPolygon(pDC, triangleNodes, 3, RGB(252, 3, 3), RGB(3, 15, 252), -1);
	radius = unit >> 1;
	rotation = PI / 2;
	drawInpolygon(pDC, incenter, 4, radius, rotation, RGB(3, 15, 252));
	delete incenter;

	// green triangle
	triangleNodes[0].x = unit + (a >> 1); triangleNodes[0].y = unit + a;
	triangleNodes[1].x = unit + a; triangleNodes[1].y = unit + a;
	triangleNodes[2].x = unit + a; triangleNodes[2].y = unit + (a >> 1);

	incenter = drawPolygon(pDC, triangleNodes, 3, RGB(48, 252, 3), RGB(3, 15, 252), -1);
	radius = unit >> 1;
	rotation = 0.;
	drawInpolygon(pDC, incenter, 8, radius, rotation, RGB(3, 15, 252));
	delete incenter;

	// purple triangle
	triangleNodes[0].x = unit + a; triangleNodes[0].y = unit + a;
	triangleNodes[1].x = unit + (a << 1); triangleNodes[1].y = unit + (a << 1);
	triangleNodes[2].x = unit + a; triangleNodes[2].y = unit + (a << 1);

	incenter = drawPolygon(pDC, triangleNodes, 3, RGB(115, 3, 252), RGB(3, 15, 252), -1);
	radius = unit * 1.4;
	rotation = -0.24;
	drawInpolygon(pDC, incenter, 5, radius, rotation, RGB(3, 15, 252));
	delete incenter;

	// hached triangle
	triangleNodes[0].x = unit + a; triangleNodes[0].y = unit + a;
	triangleNodes[1].x = unit + (a << 1); triangleNodes[1].y = unit + (a << 1);
	triangleNodes[2].x = unit + (a << 1); triangleNodes[2].y = unit + a;

	incenter = drawPolygon(pDC, triangleNodes, 3, RGB(3, 15, 252), RGB(3, 15, 252), HS_FDIAGONAL);
	radius = unit * 1.4;
	rotation = -0.24;
	drawInpolygon(pDC, incenter, 7, radius, rotation, RGB(3, 15, 252));
	delete incenter;

	// orange square
	quadrilateralNodes[0].x = unit + (a >> 1); quadrilateralNodes[0].y = unit;
	quadrilateralNodes[1].x = unit + a; quadrilateralNodes[1].y = unit;
	quadrilateralNodes[2].x = unit + a; quadrilateralNodes[2].y = unit + (a >> 1);
	quadrilateralNodes[3].x = unit + (a >> 1); quadrilateralNodes[3].y = unit + (a >> 1);

	drawPolygon(pDC, quadrilateralNodes, 4, RGB(252, 182, 3), RGB(3, 15, 252), -1);

	// pink romb
	quadrilateralNodes[0].x = unit; quadrilateralNodes[0].y = unit + a;
	quadrilateralNodes[1].x = unit + (a >> 1); quadrilateralNodes[1].y = unit;
	quadrilateralNodes[2].x = unit + a; quadrilateralNodes[2].y = unit + (a >> 1);
	quadrilateralNodes[3].x = unit + (a >> 1); quadrilateralNodes[3].y = unit + (a >> 1);

	drawPolygon(pDC, quadrilateralNodes, 4, RGB(252, 183, 252), RGB(3, 15, 252), -1);

	// grid:
	if (gridOn)
	{
		oldPen = (CPen*)pDC->SelectStockObject(WHITE_PEN);
		for (int i = 25; i < 500; i += unit)
		{
			pDC->MoveTo(0, i);
			pDC->LineTo(500, i);
			pDC->MoveTo(i, 0);
			pDC->LineTo(i, 500);
		}
	}

	pDC->SelectObject(oldPen);
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


void CLV1GDITangramView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CLV1GDITangramView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyUp(nChar, nRepCnt, nFlags);

	if (nChar == 0x47)
	{
		gridOn = !gridOn;
		Invalidate();
	}
}
