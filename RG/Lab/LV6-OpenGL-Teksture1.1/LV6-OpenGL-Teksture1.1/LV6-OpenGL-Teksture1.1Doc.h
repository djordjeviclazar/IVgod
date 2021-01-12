
// LV6-OpenGL-Teksture1.1Doc.h : interface of the CLV6OpenGLTeksture11Doc class
//


#pragma once


class CLV6OpenGLTeksture11Doc : public CDocument
{
protected: // create from serialization only
	CLV6OpenGLTeksture11Doc() noexcept;
	DECLARE_DYNCREATE(CLV6OpenGLTeksture11Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CLV6OpenGLTeksture11Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
