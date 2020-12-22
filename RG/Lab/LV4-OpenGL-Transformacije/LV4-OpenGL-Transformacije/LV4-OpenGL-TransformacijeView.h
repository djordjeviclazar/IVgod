
// LV4-OpenGL-TransformacijeView.h : interface of the CLV4OpenGLTransformacijeView class
//

#pragma once
#include "GLRenderer.h"


class CLV4OpenGLTransformacijeView : public CView
{
private:
	CGLRenderer m_glRenderer;

protected: // create from serialization only
	CLV4OpenGLTransformacijeView() noexcept;
	DECLARE_DYNCREATE(CLV4OpenGLTransformacijeView)

// Attributes
public:
	CLV4OpenGLTransformacijeDoc* GetDocument() const;

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
	virtual ~CLV4OpenGLTransformacijeView();
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
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in LV4-OpenGL-TransformacijeView.cpp
inline CLV4OpenGLTransformacijeDoc* CLV4OpenGLTransformacijeView::GetDocument() const
   { return reinterpret_cast<CLV4OpenGLTransformacijeDoc*>(m_pDocument); }
#endif

