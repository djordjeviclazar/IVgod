
// LV03-GDI-BitmapeView.cpp : implementation of the CLV03GDIBitmapeView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV03-GDI-Bitmape.h"
#endif

#include "LV03-GDI-BitmapeDoc.h"
#include "LV03-GDI-BitmapeView.h"

#define PI 3.14159

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLV03GDIBitmapeView

IMPLEMENT_DYNCREATE(CLV03GDIBitmapeView, CView)

BEGIN_MESSAGE_MAP(CLV03GDIBitmapeView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CLV03GDIBitmapeView construction/destruction

void CLV03GDIBitmapeView::drawGrid(CDC* pDC, COLORREF color)
{
	if (gridOn)
	{
		CPen* currentPen = new CPen(PS_SOLID, 0, color);
		CPen* oldPen = (CPen*)pDC->SelectObject(currentPen);
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

void CLV03GDIBitmapeView::translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM matrix;
	matrix.eM11 = (FLOAT)1.;
	matrix.eM12 = (FLOAT)0.;
	matrix.eM21 = (FLOAT)0.;
	matrix.eM22 = (FLOAT)1.;
	matrix.eDx = (FLOAT)dX;
	matrix.eDy = (FLOAT)dY;

	if (rightMultiply) { pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY); }
	else { pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY); }
}

void CLV03GDIBitmapeView::scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM matrix;
	matrix.eM11 = (FLOAT)sX;
	matrix.eM12 = (FLOAT)0.;
	matrix.eM21 = (FLOAT)0.;
	matrix.eM22 = (FLOAT)sY;
	matrix.eDx = (FLOAT)0.;
	matrix.eDy = (FLOAT)0.;

	if (rightMultiply) { pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY); }
	else { pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY); }
}

void CLV03GDIBitmapeView::rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM matrix;
	matrix.eM11 = (FLOAT)cos(angle);
	matrix.eM12 = (FLOAT)sin(angle);
	matrix.eM21 = (FLOAT)-sin(angle);
	matrix.eM22 = (FLOAT)cos(angle);
	matrix.eDx = (FLOAT)0;
	matrix.eDy = (FLOAT)0;

	if (rightMultiply) { pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY); }
	else { pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY); }
}

void CLV03GDIBitmapeView::mirror(CDC* pDC, float mX, float mY, bool rightMultiply)
{
	XFORM matrix;
	matrix.eM11 = (FLOAT)mX;
	matrix.eM12 = (FLOAT)0;
	matrix.eM21 = (FLOAT)0;
	matrix.eM22 = (FLOAT)mY;
	matrix.eDx = (FLOAT)0;
	matrix.eDy = (FLOAT)0;

	if (rightMultiply) { pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY); }
	else { pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY); }
}

CBitmap** CLV03GDIBitmapeView::loadPuzzleResources(CString* files, int filesCount)
{
	CBitmap** result = new CBitmap* [filesCount];
	images = new DImage[filesCount];
	
	for (int i = 0; i < filesCount; i++)
	{
		//DImage dib;

		// load bitmap:
		//dib.Load(files[i]);
		images[i].Load(files[i]);

		// create CBitmap:
		result[i] = new CBitmap();

		//imageHeight = dib.Height();
		//imageWidth = dib.Width();
		imageHeight = images[i].Height();
		imageWidth = images[i].Width();

		int bitmapBytes = images[i].Width() * images[i].Height() * images[i].BPP();
		//unsigned char* dibBits = new unsigned char[bitmapBytes];
		unsigned char* sourceDibBits = images[i].GetDIBBits();
		int g = 1;
		for (int k = 0; k < bitmapBytes; k++)
		{
			if (g == 4)
			{
				int pom = sourceDibBits[k - 1] + sourceDibBits[k - 2] + sourceDibBits[k - 3];
				pom /= 3;
				sourceDibBits[k - 1] = pom;
				sourceDibBits[k - 2] = pom;
				sourceDibBits[k - 3] = pom;
				g = 1;
			}
			else
			{
				g++ ;
			}
		}
		
		images[i].Update();

		//result[i]->CreateBitmap(dib.Width(), dib.Height(), 1, dib.BPP(), dibBits);

		result[i] = images[i].getBitmap();

		// grayscale:
	}

	return result;
}

CBitmap** CLV03GDIBitmapeView::makeTrasnaperent(CDC* pDC, CBitmap** sourceBmp, int bmpCount)
{
	CBitmap** mask = new CBitmap*[bmpCount];
	CDC* tempSrcDC = new CDC(), *tempDestDC = new CDC();
	tempSrcDC->CreateCompatibleDC(pDC);

	DImage test;
	
	for (int i = 0; i < bmpCount; i++)
	{
		CDC* tempSrcDC = new CDC(), * tempDestDC = new CDC();
		tempSrcDC->CreateCompatibleDC(pDC);
		tempDestDC->CreateCompatibleDC(pDC);

		// select bitmaps:
		BITMAP srcBmpEl;
		sourceBmp[i]->GetBitmap(&srcBmpEl);

		mask[i] = new CBitmap();
		mask[i]->CreateBitmap(srcBmpEl.bmWidth, srcBmpEl.bmHeight, 1, 1, 0);

		tempSrcDC->SelectObject(sourceBmp[i]);
		tempDestDC->SelectObject(mask[i]);

		// fill mask:
		COLORREF srcBackground = tempSrcDC->GetPixel(0, 0);
		COLORREF oldSrcBackground = tempSrcDC->SetBkColor(srcBackground);

		tempDestDC->BitBlt(0, 0, srcBmpEl.bmWidth, srcBmpEl.bmHeight, tempSrcDC, 0, 0, SRCCOPY);

		// mark source background
		COLORREF oldSrcForeground = tempSrcDC->SetTextColor(RGB(255, 255, 255));
		tempSrcDC->SetBkColor(RGB(0, 0, 0));

		tempSrcDC->BitBlt(0, 0, imageWidth, imageHeight, tempDestDC, 0, 0, SRCAND);

		tempSrcDC->DeleteDC();
		delete tempSrcDC;
		tempDestDC->DeleteDC();
		delete tempDestDC;
	}

	

	return mask;
}

void CLV03GDIBitmapeView::drawPuzzle(CDC* pDC, CBitmap** bmp, CBitmap** mask, int bmpCount)
{
	CDC* mDC = new CDC(); // memory DC
	mDC->CreateCompatibleDC(pDC);

	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM old;
	pDC->GetWorldTransform(&old);

	// first piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8, -unit * 0.8 - 2, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, 1, -1, false);
		rotate(pDC, 0.54, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[0]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[0]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);

	// second piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8 + 150 - 2, -unit * 0.8 - 15, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, -1, 1, false);
		rotate(pDC, -0.6435, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[1]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[1]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);
	
	// third piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8 + 280 +5, -unit * 0.8 - 3, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, 1, -1, false);
		rotate(pDC, -PI/2. + 0.12, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[2]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[2]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);
	
	// fourth piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8  , -unit * 0.8 - 2 + 6 * unit, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, 1, -1, false);
		rotate(pDC, 0.725, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[3]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[3]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);
	
	// fifth piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8 +  - 2 + 6 * unit - 5, -unit * 0.8 - 15 + 6 * unit + 15, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, 1, -1, false);
		rotate(pDC, -0.7, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[4]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[4]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);
	
	// sixth piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8 + 12 * unit - 10 , -unit * 0.8 - 2 + 6 * unit + 2, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, 1, -1, false);
		rotate(pDC, -0.93, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[5]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[5]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);

	// seventh piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8  , -unit * 0.8 - 2 + 12 * unit, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, 1, 1, false);
		rotate(pDC, -0.92, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[6]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[6]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);

	// eight piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8 - 2 + 6 * unit, -unit * 0.8 - 15 + 12 * unit, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, -1, 1, false);
		rotate(pDC, -0.13, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[7]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[7]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);

	// ninth piece:
	{
		// transormations:

		translate(pDC, -unit * 0.8 + 12 * unit, -unit * 0.8 - 2 + 12 * unit, false);
		translate(pDC, imageWidth / 2., imageHeight / 2., false);
		mirror(pDC, -1, 1, false);
		rotate(pDC, 0.27, false);
		translate(pDC, -imageWidth / 2., -imageHeight / 2., false);
	}
	{
		// draw:
		mDC->SelectObject(mask[8]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCAND);
		mDC->SelectObject(bmp[8]);
		pDC->BitBlt(0, 0, imageWidth, imageHeight, mDC, 0, 0, SRCPAINT);
	}

	pDC->SetWorldTransform(&old);

	pDC->SetWorldTransform(&old);
	pDC->SetGraphicsMode(oldMode);
}

CLV03GDIBitmapeView::CLV03GDIBitmapeView() noexcept
{
	// TODO: add construction code here

}

CLV03GDIBitmapeView::~CLV03GDIBitmapeView()
{
}

BOOL CLV03GDIBitmapeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLV03GDIBitmapeView drawing

void CLV03GDIBitmapeView::OnDraw(CDC* pDC)
{
	CLV03GDIBitmapeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	drawGrid(pDC, RGB(150, 150, 150));

	CString* files = new CString[9];
	files[0] = CString("res/1.bmp");
	files[1] = CString("res/2.bmp");
	files[2] = CString("res/3.bmp");
	files[3] = CString("res/4.bmp");
	files[4] = CString("res/5.bmp");
	files[5] = CString("res/6.bmp");
	files[6] = CString("res/7.bmp");
	files[7] = CString("res/8.bmp");
	files[8] = CString("res/9.bmp");

	// load-transparent-draw:
	CBitmap** resources, ** masks = 0;
	resources = loadPuzzleResources(files, 9);
	masks = makeTrasnaperent(pDC, resources, 9);
	drawPuzzle(pDC, resources, masks, 9);

}


// CLV03GDIBitmapeView printing

BOOL CLV03GDIBitmapeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLV03GDIBitmapeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLV03GDIBitmapeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLV03GDIBitmapeView diagnostics

#ifdef _DEBUG
void CLV03GDIBitmapeView::AssertValid() const
{
	CView::AssertValid();
}

void CLV03GDIBitmapeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLV03GDIBitmapeDoc* CLV03GDIBitmapeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLV03GDIBitmapeDoc)));
	return (CLV03GDIBitmapeDoc*)m_pDocument;
}
#endif //_DEBUG


// CLV03GDIBitmapeView message handlers


void CLV03GDIBitmapeView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyUp(nChar, nRepCnt, nFlags);

	if (nChar == 0x47 && nRepCnt < 2) // on 'g' key; single click
	{
		gridOn = !gridOn;
		Invalidate();
	}
}
