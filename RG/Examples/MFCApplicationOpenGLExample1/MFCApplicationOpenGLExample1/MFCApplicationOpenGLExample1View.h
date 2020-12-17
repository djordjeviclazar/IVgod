
// MFCApplicationOpenGLExample1View.h : interface of the CMFCApplicationOpenGLExample1View class
//

#pragma once


class CMFCApplicationOpenGLExample1View : public CView
{
protected: // create from serialization only
	CMFCApplicationOpenGLExample1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplicationOpenGLExample1View)

// Attributes
public:
	CMFCApplicationOpenGLExample1Doc* GetDocument() const;

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
	virtual ~CMFCApplicationOpenGLExample1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCApplicationOpenGLExample1View.cpp
inline CMFCApplicationOpenGLExample1Doc* CMFCApplicationOpenGLExample1View::GetDocument() const
   { return reinterpret_cast<CMFCApplicationOpenGLExample1Doc*>(m_pDocument); }
#endif

