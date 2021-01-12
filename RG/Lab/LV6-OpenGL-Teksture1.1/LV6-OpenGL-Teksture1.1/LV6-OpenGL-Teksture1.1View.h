
// LV6-OpenGL-Teksture1.1View.h : interface of the CLV6OpenGLTeksture11View class
//
#include "GLRenderer.h"

#pragma once


class CLV6OpenGLTeksture11View : public CView
{
private:
	CGLRenderer m_glRenderer;
	bool rotateView = false;

protected: // create from serialization only
	CLV6OpenGLTeksture11View() noexcept;
	DECLARE_DYNCREATE(CLV6OpenGLTeksture11View)

// Attributes
public:
	CLV6OpenGLTeksture11Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLV6OpenGLTeksture11View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in LV6-OpenGL-Teksture1.1View.cpp
inline CLV6OpenGLTeksture11Doc* CLV6OpenGLTeksture11View::GetDocument() const
   { return reinterpret_cast<CLV6OpenGLTeksture11Doc*>(m_pDocument); }
#endif

