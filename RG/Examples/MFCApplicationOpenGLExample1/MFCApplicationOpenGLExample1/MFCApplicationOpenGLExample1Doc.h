
// MFCApplicationOpenGLExample1Doc.h : interface of the CMFCApplicationOpenGLExample1Doc class
//


#pragma once


class CMFCApplicationOpenGLExample1Doc : public CDocument
{
protected: // create from serialization only
	CMFCApplicationOpenGLExample1Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplicationOpenGLExample1Doc)

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
	virtual ~CMFCApplicationOpenGLExample1Doc();
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
