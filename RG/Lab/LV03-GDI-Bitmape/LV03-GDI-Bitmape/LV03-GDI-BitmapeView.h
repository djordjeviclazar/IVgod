
// LV03-GDI-BitmapeView.h : interface of the CLV03GDIBitmapeView class
//
#include "DImage.h"
#pragma once


class CLV03GDIBitmapeView : public CView
{
private:
	bool gridOn;
	const int unit = 25;
	int imageHeight, imageWidth;

	DImage* images;

	void drawGrid(CDC* pDC, COLORREF color);

	void translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void rotate(CDC* pDC, float angle, bool rightMultiply);
	void mirror(CDC* pDC, float mX, float mY, bool rightMultiply);

	CBitmap** loadPuzzleResources(CString* files, int filesCount); 
	CBitmap** makeTrasnaperent(CDC* pDC, CBitmap** sourceBmp, int bmpCount); // makes source bmps transparent
																			//and returns array with masks 
	void drawPuzzle(CDC* pDC, CBitmap** bmp, CBitmap** mask, int bmpCount);


protected: // create from serialization only
	CLV03GDIBitmapeView() noexcept;
	DECLARE_DYNCREATE(CLV03GDIBitmapeView)

// Attributes
public:
	CLV03GDIBitmapeDoc* GetDocument() const;

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
	virtual ~CLV03GDIBitmapeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in LV03-GDI-BitmapeView.cpp
inline CLV03GDIBitmapeDoc* CLV03GDIBitmapeView::GetDocument() const
   { return reinterpret_cast<CLV03GDIBitmapeDoc*>(m_pDocument); }
#endif

