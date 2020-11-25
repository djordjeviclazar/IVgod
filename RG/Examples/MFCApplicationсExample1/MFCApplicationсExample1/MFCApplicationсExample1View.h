
// MFCApplicationсExample1View.h : interface of the CMFCApplicationсExample1View class
//

#pragma once


class CMFCApplicationсExample1View : public CView
{
protected: // create from serialization only
	CMFCApplicationсExample1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplicationсExample1View)

// Attributes
public:
	CMFCApplicationсExample1Doc* GetDocument() const;

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
	virtual ~CMFCApplicationсExample1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCApplicationсExample1View.cpp
inline CMFCApplicationсExample1Doc* CMFCApplicationсExample1View::GetDocument() const
   { return reinterpret_cast<CMFCApplicationсExample1Doc*>(m_pDocument); }
#endif

