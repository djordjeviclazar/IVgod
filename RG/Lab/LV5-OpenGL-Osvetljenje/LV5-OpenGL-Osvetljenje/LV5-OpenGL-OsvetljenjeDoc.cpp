
// LV5-OpenGL-OsvetljenjeDoc.cpp : implementation of the CLV5OpenGLOsvetljenjeDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "LV5-OpenGL-Osvetljenje.h"
#endif

#include "LV5-OpenGL-OsvetljenjeDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLV5OpenGLOsvetljenjeDoc

IMPLEMENT_DYNCREATE(CLV5OpenGLOsvetljenjeDoc, CDocument)

BEGIN_MESSAGE_MAP(CLV5OpenGLOsvetljenjeDoc, CDocument)
END_MESSAGE_MAP()


// CLV5OpenGLOsvetljenjeDoc construction/destruction

CLV5OpenGLOsvetljenjeDoc::CLV5OpenGLOsvetljenjeDoc() noexcept
{
	// TODO: add one-time construction code here

}

CLV5OpenGLOsvetljenjeDoc::~CLV5OpenGLOsvetljenjeDoc()
{
}

BOOL CLV5OpenGLOsvetljenjeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CLV5OpenGLOsvetljenjeDoc serialization

void CLV5OpenGLOsvetljenjeDoc::Serialize(CArchive& ar)
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
void CLV5OpenGLOsvetljenjeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CLV5OpenGLOsvetljenjeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CLV5OpenGLOsvetljenjeDoc::SetSearchContent(const CString& value)
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

// CLV5OpenGLOsvetljenjeDoc diagnostics

#ifdef _DEBUG
void CLV5OpenGLOsvetljenjeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLV5OpenGLOsvetljenjeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLV5OpenGLOsvetljenjeDoc commands
