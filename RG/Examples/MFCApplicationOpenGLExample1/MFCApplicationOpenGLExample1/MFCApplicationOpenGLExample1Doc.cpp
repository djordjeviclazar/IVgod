
// MFCApplicationOpenGLExample1Doc.cpp : implementation of the CMFCApplicationOpenGLExample1Doc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApplicationOpenGLExample1.h"
#endif

#include "MFCApplicationOpenGLExample1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplicationOpenGLExample1Doc

IMPLEMENT_DYNCREATE(CMFCApplicationOpenGLExample1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplicationOpenGLExample1Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplicationOpenGLExample1Doc construction/destruction

CMFCApplicationOpenGLExample1Doc::CMFCApplicationOpenGLExample1Doc() noexcept
{
	// TODO: add one-time construction code here

}

CMFCApplicationOpenGLExample1Doc::~CMFCApplicationOpenGLExample1Doc()
{
}

BOOL CMFCApplicationOpenGLExample1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCApplicationOpenGLExample1Doc serialization

void CMFCApplicationOpenGLExample1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCApplicationOpenGLExample1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCApplicationOpenGLExample1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplicationOpenGLExample1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplicationOpenGLExample1Doc diagnostics

#ifdef _DEBUG
void CMFCApplicationOpenGLExample1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplicationOpenGLExample1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplicationOpenGLExample1Doc commands
