
// LV5-OpenGL-OsvetljenjeView.h : interface of the CLV5OpenGLOsvetljenjeView class
//
#include "GLRenderer.h"

#pragma once


class CLV5OpenGLOsvetljenjeView : public CView
{
private: 
	CGLRenderer m_glRenderer;
	bool rotateView = false;

protected: // create from serialization only
	CLV5OpenGLOsvetljenjeView() noexcept;
	DECLARE_DYNCREATE(CLV5OpenGLOsvetljenjeView)

// Attributes
public:
	CLV5OpenGLOsvetljenjeDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CLV5OpenGLOsvetljenjeView();
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in LV5-OpenGL-OsvetljenjeView.cpp
inline CLV5OpenGLOsvetljenjeDoc* CLV5OpenGLOsvetljenjeView::GetDocument() const
   { return reinterpret_cast<CLV5OpenGLOsvetljenjeDoc*>(m_pDocument); }
#endif

