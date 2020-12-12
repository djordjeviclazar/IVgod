
// LV03-GDI-BitmapeView.h : interface of the CLV03GDIBitmapeView class
//

#pragma once


class CLV03GDIBitmapeView : public CView
{
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
};

#ifndef _DEBUG  // debug version in LV03-GDI-BitmapeView.cpp
inline CLV03GDIBitmapeDoc* CLV03GDIBitmapeView::GetDocument() const
   { return reinterpret_cast<CLV03GDIBitmapeDoc*>(m_pDocument); }
#endif

