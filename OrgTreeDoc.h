// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// OrgTreeDoc.h : interface of the OrgTreeDoc class
//


#pragma once


#include "COrgCtrlData.h"
#include "IOrgTreeDoc.h"


class OrgTreeDoc : public CDocument, public IOrgTreeDoc
{
protected: // create from serialization only
	OrgTreeDoc() noexcept;
	DECLARE_DYNCREATE(OrgTreeDoc)

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
	virtual ~OrgTreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void FillByTestData();
	COrgCtrlData::ptr_t GetData() { return m_data; }

	bool CreateContextNode( const CString & uniqueAggregateNodeId, const CString & productionRuleString, ULONG64 parentCxNodeObjId, ULONG64 cxNodeObjId, DWORD cxNodeThreadId );

	virtual const IOrgTreeDoc::node_handle_t GetRootNode() const;
	virtual const IOrgTreeDoc::node_handle_t GetNextChildNode( const IOrgTreeDoc::node_handle_t hParent, const IOrgTreeDoc::node_handle_t hCurrentChild ) const;
	virtual const CRect GetNodeRect( const IOrgTreeDoc::node_handle_t hNode ) const;

protected:

	COrgCtrlData::ptr_t m_data;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
