
// LV02-TransformacijeView.h : interface of the CLV02TransformacijeView class
//

#pragma once


class CLV02TransformacijeView : public CView
{
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
};

#ifndef _DEBUG  // debug version in LV02-TransformacijeView.cpp
inline CLV02TransformacijeDoc* CLV02TransformacijeView::GetDocument() const
   { return reinterpret_cast<CLV02TransformacijeDoc*>(m_pDocument); }
#endif

