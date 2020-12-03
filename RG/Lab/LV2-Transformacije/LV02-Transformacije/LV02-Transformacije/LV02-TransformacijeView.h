
// LV02-TransformacijeView.h : interface of the CLV02TransformacijeView class
//

#pragma once


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

