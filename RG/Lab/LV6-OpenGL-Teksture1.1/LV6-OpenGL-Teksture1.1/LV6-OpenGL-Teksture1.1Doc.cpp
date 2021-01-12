
// LV6-OpenGL-Teksture1.1Doc.cpp : implementation of the CLV6OpenGLTeksture11Doc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV6-OpenGL-Teksture1.1.h"
#endif

#include "LV6-OpenGL-Teksture1.1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLV6OpenGLTeksture11Doc

IMPLEMENT_DYNCREATE(CLV6OpenGLTeksture11Doc, CDocument)

BEGIN_MESSAGE_MAP(CLV6OpenGLTeksture11Doc, CDocument)
END_MESSAGE_MAP()


// CLV6OpenGLTeksture11Doc construction/destruction

CLV6OpenGLTeksture11Doc::CLV6OpenGLTeksture11Doc() noexcept
{
	// TODO: add one-time construction code here

}

CLV6OpenGLTeksture11Doc::~CLV6OpenGLTeksture11Doc()
{
}

BOOL CLV6OpenGLTeksture11Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CLV6OpenGLTeksture11Doc serialization

void CLV6OpenGLTeksture11Doc::Serialize(CArchive& ar)
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
void CLV6OpenGLTeksture11Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CLV6OpenGLTeksture11Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CLV6OpenGLTeksture11Doc::SetSearchContent(const CString& value)
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

// CLV6OpenGLTeksture11Doc diagnostics

#ifdef _DEBUG
void CLV6OpenGLTeksture11Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLV6OpenGLTeksture11Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLV6OpenGLTeksture11Doc commands
