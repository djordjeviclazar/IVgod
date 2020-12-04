
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
	pDC->TextOutW(x + 3, y + 3, CString("16559 Lazar Djordjevic"));
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
	drawCactus(pDC);

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

	/*if (nChar == 0x47 && nRepCnt < 2) // on 'g' key; single click
	{
		gridOn = !gridOn;
		Invalidate();
	}*/
	switch (nChar)
	{
		case 0x41:
		{
			rotateRight--;
			Invalidate();
		}
		break;
		case 0x44:
		{
			rotateRight++;
			Invalidate();
		}
		break;
		case 0x51:
		{
			rotateRight2--;
			Invalidate();
		}
		break;
		case 0x45:
		{
			rotateRight2++;
			Invalidate();
		}
		break;
		case 0x47:
		{
			gridOn = !gridOn;
			Invalidate();
		}
		break;
	default:
		break;
	}

}

void CLV02TransformacijeView::drawNode(CDC* pDC, POINT* center)
{
	CPen* oldPen, * currentPen = new CPen(PS_SOLID, 0, RGB(252, 252, 252));
	CBrush* oldBrush, * currentBrush = new CBrush(RGB(43, 223, 43));

	oldPen = (CPen*)pDC->SelectObject(currentPen);
	oldBrush = (CBrush*)pDC->SelectObject(currentBrush);
	pDC->Ellipse(center->x - radius, center->y - radius, center->x + radius, center->y + radius);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

void CLV02TransformacijeView::drawCactusPart(CDC* pDC, POINT* center, double factor, bool dark)
{
	CString fileName = dark ? CString("res/cactus_part.emf") : CString("res/cactus_part_light.emf");
	HENHMETAFILE cactusPart = GetEnhMetaFile(fileName);

	/*
	* Default: node is under cactus part, spine is 7px
	* Transformation is performed before function call
	*/

	RECT partRect;
	partRect.left = center->x - ((long)(edgeWidth * factor + 0.5) / 2.);
	partRect.right = ((long)(edgeWidth * factor + 0.5) / 2.) + center->x;
	partRect.bottom = center->y - (radius - 7);
	partRect.top = partRect.bottom - edgeHeight;

	pDC->PlayMetaFile(cactusPart, &partRect);

	DeleteEnhMetaFile(cactusPart);
}

void CLV02TransformacijeView::drawCactus(CDC* pDC)
{
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);


	// whole cactus is rotated with LEFT/RIGHT
	// center of rotation is firstCenter
	// this transformation is used while drawing every part except first node
	double angle = rotationAngle * rotateRight;

	setWorldTransformTranslate(pDC, firstCenterX, firstCenterY, MWT_LEFTMULTIPLY);
	modifyWorldTransformRotate(pDC, angle, MWT_LEFTMULTIPLY);
	modifyWorldTransformTranslate(pDC, -firstCenterX, -firstCenterY, MWT_LEFTMULTIPLY);

	// drawing center part:
	POINT p;
	p.x = firstCenterX;
	p.y = firstCenterY;

	drawCactusPart(pDC, &p, 1., false);
	drawNode(pDC, &p); // center of circle is center of rotation
	p.y -= 3 * unit;
	drawCactusPart(pDC, &p, 0.33333, true);
	
	
	// drawing left part:
	drawLeftPart(pDC, &p);
	// drawing right part
	drawRightPart(pDC, &p);
	
	drawNode(pDC, &p);
	
	pDC->SetWorldTransform(&oldMatrix);
	pDC->SetGraphicsMode(oldMode);
}

void CLV02TransformacijeView::drawLeftPart(CDC* pDC, POINT* center)
{
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	// rotate left:
	double angle = -(rotationAngle * 8);
	modifyWorldTransformTranslate(pDC, center->x, center->y, MWT_LEFTMULTIPLY);
	modifyWorldTransformRotate(pDC, angle, MWT_LEFTMULTIPLY);
	modifyWorldTransformTranslate(pDC, -center->x, -center->y, MWT_LEFTMULTIPLY);

	// draw:
	drawCactusPart(pDC, center, 0.33333, true);
	POINT p, p1; p1.x = 100; p.y = 100;
	p.y = center->y - (3 * unit);
	p.x = center->x;
	drawCactusPart(pDC, &p, 1., true);
	drawNode(pDC, &p);
	
	pDC->SetWorldTransform(&oldMatrix);
	pDC->SetGraphicsMode(oldMode);
}

void CLV02TransformacijeView::drawRightPart(CDC* pDC, POINT* center)
{
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	// rotate left:
	double angle = (rotationAngle * 8);
	modifyWorldTransformTranslate(pDC, center->x, center->y, MWT_LEFTMULTIPLY);
	modifyWorldTransformRotate(pDC, angle, MWT_LEFTMULTIPLY);
	modifyWorldTransformTranslate(pDC, -center->x, -center->y, MWT_LEFTMULTIPLY);

	// draw:
	drawCactusPart(pDC, center, 0.33333, true);
	POINT p;
	p.y = center->y - 3 * unit;
	p.x = center->x;
	//drawNode(pDC, &p);
	
	//left part:
	drawLeftPart(pDC, &p);
	// double rotating part:
	drawDoubleRotatingPart(pDC, &p);
	// right part:
	modifyWorldTransformTranslate(pDC, p.x, p.y, MWT_LEFTMULTIPLY);
	modifyWorldTransformRotate(pDC, angle, MWT_LEFTMULTIPLY);
	modifyWorldTransformTranslate(pDC, -p.x, -p.y, MWT_LEFTMULTIPLY);
	drawCactusPart(pDC, &p, 0.33333, true);

	// node:
	drawNode(pDC, &p);
	
	pDC->SetWorldTransform(&oldMatrix);
	pDC->SetGraphicsMode(oldMode);
}

void CLV02TransformacijeView::drawDoubleRotatingPart(CDC* pDC, POINT* center)
{
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	// second rotation:
	double angle = rotationAngle * rotateRight2;

	modifyWorldTransformTranslate(pDC, center->x, center->y, MWT_LEFTMULTIPLY);
	modifyWorldTransformRotate(pDC, angle, MWT_LEFTMULTIPLY);
	modifyWorldTransformTranslate(pDC, -center->x, -center->y, MWT_LEFTMULTIPLY);

	// draw:
	drawCactusPart(pDC, center, 0.33333, false);
	POINT p;
	p.y = center->y - 3 * unit;
	p.x = center->x;

	// rotate left:
	angle = -(rotationAngle * 8) + PI;
	modifyWorldTransformTranslate(pDC, p.x, p.y, MWT_LEFTMULTIPLY);
	modifyWorldTransformRotate(pDC, angle, MWT_LEFTMULTIPLY);
	modifyWorldTransformTranslate(pDC, -p.x, -p.y, MWT_LEFTMULTIPLY);

	drawCactusPart(pDC, center, 0.66667, true); // left part

	// rotate right
	angle = -(angle * 2);
	modifyWorldTransformTranslate(pDC, p.x, p.y, MWT_LEFTMULTIPLY);
	modifyWorldTransformRotate(pDC, angle, MWT_LEFTMULTIPLY);
	modifyWorldTransformTranslate(pDC, -p.x, -p.y, MWT_LEFTMULTIPLY);

	drawCactusPart(pDC, center, 0.66667, true); // right part

	//pDC->SetWorldTransform(&oldMatrix);
	drawNode(pDC, &p);


	pDC->SetGraphicsMode(oldMode);
	pDC->SetWorldTransform(&oldMatrix);
}

void CLV02TransformacijeView::modifyWorldTransformRotate(CDC* pDC, double angle, DWORD mode)
{
	XFORM matrix;
	matrix.eM11 = cos(angle);
	matrix.eM12 = sin(angle);
	matrix.eM21 = -sin(angle);
	matrix.eM22 = cos(angle);
	matrix.eDx = 0;
	matrix.eDy = 0;

	pDC->ModifyWorldTransform(&matrix, mode);
}

void CLV02TransformacijeView::modifyWorldTransformTranslate(CDC* pDC, float eDx, float eDy, DWORD mode)
{
	XFORM matrix;
	matrix.eM11 = (FLOAT)1.;
	matrix.eM12 = (FLOAT)0.;
	matrix.eM21 = (FLOAT)0.;
	matrix.eM22 = (FLOAT)1.;
	matrix.eDx = (FLOAT)eDx;
	matrix.eDy = (FLOAT)eDy;

	pDC->ModifyWorldTransform(&matrix, mode);
}

void CLV02TransformacijeView::setWorldTransformRotate(CDC* pDC, double angle, DWORD mode)
{
	XFORM matrix;
	matrix.eM11 = cos(angle);
	matrix.eM12 = sin(angle);
	matrix.eM21 = -sin(angle);
	matrix.eM22 = cos(angle);
	matrix.eDx = 0;
	matrix.eDy = 0;

	pDC->SetWorldTransform(&matrix);
}

void CLV02TransformacijeView::setWorldTransformTranslate(CDC* pDC, float eDx, float eDy, DWORD mode)
{
	XFORM matrix;
	matrix.eM11 = (FLOAT)1.;
	matrix.eM12 = (FLOAT)0.;
	matrix.eM21 = (FLOAT)0.;
	matrix.eM22 = (FLOAT)1.;
	matrix.eDx = (FLOAT)eDx;
	matrix.eDy = (FLOAT)eDy;

	pDC->SetWorldTransform(&matrix);
}
