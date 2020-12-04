
// LV02-TransformacijeView.h : interface of the CLV02TransformacijeView class
//

#pragma once

#define PI 3.1415926535

class CLV02TransformacijeView : public CView
{
// Grid and background
private:
	bool gridOn = false;
	const int unit = 25; // pixels

	void drawBackground(CDC* pDC, int height, int width, COLORREF color);
	void drawGrid(CDC* pDC);
	void drawVase(CDC* pDC);
	void signature(CDC* pDC, int x, int y, int rotation, COLORREF color, int textWidth, int textHeight);

// Vertices and edges
	const int radius = 10; // pixels
	const int firstCenterX = 250, firstCenterY = 425; // center of rotation RIGHT/LEFT
	const double rotationAngle = PI / 32.;
	const long edgeHeight = 70, edgeWidth = 60; // pixels
	int rotateRight = 0; // RIGHT++, LEFT--
	int rotateRight2 = 0; // RIGHT2++, LEFT2--

	void drawNode(CDC* pDC, POINT* center);
	void drawCactusPart(CDC* pDC, POINT* center, double factor, bool dark);
	void drawCactus(CDC* pDC);
	void drawLeftPart(CDC* pDC, POINT* center);
	void drawRightPart(CDC* pDC, POINT* center);
	void drawDoubleRotatingPart(CDC* pDC, POINT* center);

	void modifyWorldTransformRotate(CDC* pDC, double angle, DWORD mode);
	void modifyWorldTransformTranslate(CDC* pDC, float eDx, float eDy, DWORD mode);
	void setWorldTransformRotate(CDC* pDC, double angle, DWORD mode);
	void setWorldTransformTranslate(CDC* pDC, float eDx, float eDy, DWORD mode);

protected: // create from serialization only
	CLV02TransformacijeView() noexcept;
	DECLARE_DYNCREATE(CLV02TransformacijeView)

// Attributes
public:
	CLV02TransformacijeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLV02TransformacijeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in LV02-TransformacijeView.cpp
inline CLV02TransformacijeDoc* CLV02TransformacijeView::GetDocument() const
   { return reinterpret_cast<CLV02TransformacijeDoc*>(m_pDocument); }
#endif

