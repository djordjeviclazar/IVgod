
// LV1-GDI-TangramView.h : interface of the CLV1GDITangramView class
//

#pragma once


class CLV1GDITangramView : public CView
{
// Grid
private:
	bool gridOn = false;
	const int unit = 25; // pixels

// Polygon
	POINT* drawPolygon(CDC* pDC, POINT* nodes, int nodeNumber, COLORREF color, COLORREF lineColor, int hached);
	void drawInpolygon(CDC* pDC, POINT* center, int nodeNumber, double radius, double rotation, COLORREF lineColor);
	int distance(POINT& a, POINT& b);

protected: // create from serialization only
	CLV1GDITangramView() noexcept;
	DECLARE_DYNCREATE(CLV1GDITangramView)

// Attributes
public:
	CLV1GDITangramDoc* GetDocument() const;

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
	virtual ~CLV1GDITangramView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in LV1-GDI-TangramView.cpp
inline CLV1GDITangramDoc* CLV1GDITangramView::GetDocument() const
   { return reinterpret_cast<CLV1GDITangramDoc*>(m_pDocument); }
#endif

