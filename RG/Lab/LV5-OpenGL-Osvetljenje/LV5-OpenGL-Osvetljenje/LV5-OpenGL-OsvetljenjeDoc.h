
// LV5-OpenGL-OsvetljenjeDoc.h : interface of the CLV5OpenGLOsvetljenjeDoc class
//


#pragma once


class CLV5OpenGLOsvetljenjeDoc : public CDocument
{
protected: // create from serialization only
	CLV5OpenGLOsvetljenjeDoc() noexcept;
	DECLARE_DYNCREATE(CLV5OpenGLOsvetljenjeDoc)

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
	virtual ~CLV5OpenGLOsvetljenjeDoc();
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
