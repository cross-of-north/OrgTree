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


class OrgTreeDocNodeHandle : public IOrgTreeDocNodeHandle {

	friend class OrgTreeDoc;

private:

	OrgTreeDocNodeHandle() = delete;
	OrgTreeDocNodeHandle( const OrgTreeDocNodeHandle & ) = delete;
	OrgTreeDocNodeHandle & operator=( const OrgTreeDocNodeHandle & ) = delete;

protected:

	COrgCtrlDataItem * m_node{ nullptr };

public:

	OrgTreeDocNodeHandle( COrgCtrlDataItem * node ) : m_node( node ) {}
	virtual ~OrgTreeDocNodeHandle() = default;

	bool IsValid() const {
		return m_node != NULL;
	}

};


class OrgTreeView;

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

	OrgTreeView * GetView() const;

	bool CreateContextNode( const CString & uniqueAggregateNodeId, const CString & productionRuleString, ULONG64 parentCxNodeObjId, ULONG64 cxNodeObjId, DWORD cxNodeThreadId );
	void CreateDescendantNode( const POrgTreeDocNodeHandle & parent = NULL );
	void CreateSiblingNode( void );
	void DeleteNode();

	void SetNodeRect( COrgCtrlDataItem & node, const CRect & rect );
	void SetNodeProperty( COrgCtrlDataItem & node, const wchar_t * strName, const CString & strValue );

	virtual bool GetRootNode( POrgTreeDocNodeHandle & phNode ) const;
	virtual bool GetNextChildNode( const POrgTreeDocNodeHandle & phParent, POrgTreeDocNodeHandle & phChild ) const;
	virtual const CRect GetNodeRect( const POrgTreeDocNodeHandle & phNode ) const;
	virtual const CRect GetNodeScreenRect( const POrgTreeDocNodeHandle & phNode ) const;
	virtual void SetNodeRect( POrgTreeDocNodeHandle & phNode, const CRect & rect );
	virtual void SetNodeScreenRect( const POrgTreeDocNodeHandle & phNode, const CRect & rect ) const;
	virtual void SetNodeFocus( const POrgTreeDocNodeHandle & phNode, const bool bFocus ) const;
	virtual bool GetNodeFocus( const POrgTreeDocNodeHandle & phNode ) const;
	virtual bool GetLastChildNode( const POrgTreeDocNodeHandle & phParent, POrgTreeDocNodeHandle & phLastChild ) const;
	virtual bool GetParentNode( const POrgTreeDocNodeHandle & phNode, POrgTreeDocNodeHandle & phParent ) const;
	virtual void DeleteNode( POrgTreeDocNodeHandle & phNode );
	virtual void SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const CString & strValue );
	virtual bool GetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, CString & strValue ) const;
	virtual void SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const __int64 iValue );
	virtual bool GetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, __int64 & iValue ) const;

protected:

	static const int INVALID_ORDER_HINT = -1;

	COrgCtrlData::ptr_t m_data;

	void GetNodeHandle( COrgCtrlDataItem * node, POrgTreeDocNodeHandle & phNode ) const;
	static bool FromNodeHandle( const POrgTreeDocNodeHandle & phNode, COrgCtrlDataItem * & node );
	int GetOrderHint( const COrgCtrlDataItem & node ) const;
	void SetOrderHint( COrgCtrlDataItem & node, int orderHint ) const;
	void ResetOrderHints( COrgCtrlDataItem & node );

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
