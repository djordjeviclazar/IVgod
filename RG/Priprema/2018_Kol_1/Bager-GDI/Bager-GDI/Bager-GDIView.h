
// Bager-GDIView.h : interface of the CBagerGDIView class
//

#pragma once


class CBagerGDIView : public CView
{
protected: // create from serialization only
	CBagerGDIView() noexcept;
	DECLARE_DYNCREATE(CBagerGDIView)

// Attributes
public:
	CBagerGDIDoc* GetDocument() const;

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
	virtual ~CBagerGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Bager-GDIView.cpp
inline CBagerGDIDoc* CBagerGDIView::GetDocument() const
   { return reinterpret_cast<CBagerGDIDoc*>(m_pDocument); }
#endif

