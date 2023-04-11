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

// OrgTreeDoc.cpp : implementation of the OrgTreeDoc class
//

#include "pch.h"
#include "framework.h"

#include "OrgTreeDoc.h"

#include "OrgTreeView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// OrgTreeDoc

IMPLEMENT_DYNCREATE(OrgTreeDoc, CDocument)

BEGIN_MESSAGE_MAP(OrgTreeDoc, CDocument)
END_MESSAGE_MAP()


// OrgTreeDoc construction/destruction

OrgTreeDoc::OrgTreeDoc() noexcept
	: m_data( std::make_shared< COrgCtrlData >() ) 
{
	// TODO: add one-time construction code here

}

OrgTreeDoc::~OrgTreeDoc()
{
}

void OrgTreeDoc::FillByTestData() {
	COrgCtrlDataItem::ptr_t pRoot = std::make_shared< COrgCtrlDataItem >();
	pRoot->GetRect() = { 50, 50, 70, 60 };
	COrgCtrlDataItem::ptr_t node1 = std::make_shared< COrgCtrlDataItem >();
	node1->GetRect() = { 80, 10, 100, 20 };
	COrgCtrlDataItem::ptr_t node2 = std::make_shared< COrgCtrlDataItem >();
	node2->GetRect() = { 80, 40, 100, 50 };
	COrgCtrlDataItem::ptr_t node3 = std::make_shared< COrgCtrlDataItem >();
	node3->GetRect() = { 80, 70, 100, 80 };
	COrgCtrlDataItem::ptr_t node4 = std::make_shared< COrgCtrlDataItem >();
	node4->GetRect() = { 110, 60, 130, 70 };
	COrgCtrlDataItem::ptr_t node5 = std::make_shared< COrgCtrlDataItem >();
	node5->GetRect() = { 110, 90, 130, 100 };
	pRoot->AddChild( node1 );
	pRoot->AddChild( node2 );
	node2->AddChild( node4 );
	node2->AddChild( node5 );
	pRoot->AddChild( node3 );

	m_data->GetRoot().Clear();
	m_data->GetRoot().AddChild( pRoot );
}

const IOrgTreeDoc::node_handle_t OrgTreeDoc::GetRootNode() const {
	return m_data->GetRoot().GetHandle();
}

const IOrgTreeDoc::node_handle_t OrgTreeDoc::GetNextChildNode( const IOrgTreeDoc::node_handle_t hParent, const IOrgTreeDoc::node_handle_t hCurrentChild ) const {
	auto hResult = IOrgTreeDoc::INVALID_NODE_HANDLE;
	auto parent = COrgCtrlDataItem::FromHandle( hParent );
	if ( parent != NULL ) {
		auto children = parent->GetChildren();
		int iNextChildOrder = COrgCtrlDataItem::INVALID_ORDER_HINT;
		auto currentChild = COrgCtrlDataItem::FromHandle( hCurrentChild );
		if ( currentChild == NULL ) {
			iNextChildOrder = 0;
		} else {
			int iCurrentChildOrder = currentChild->GetOrderHint();
			if ( iCurrentChildOrder == COrgCtrlDataItem::INVALID_ORDER_HINT ) {
				for ( int i = 0; i < children.size(); i++ ) {
					if ( children[ i ].get() == currentChild ) {
						iCurrentChildOrder = i;
						break;
					}
				}
			}
			if ( iCurrentChildOrder != COrgCtrlDataItem::INVALID_ORDER_HINT ) {
				iNextChildOrder = iCurrentChildOrder + 1;
			}
		}
		if ( iNextChildOrder != COrgCtrlDataItem::INVALID_ORDER_HINT && children.size() > iNextChildOrder ) {
			auto child = children[ iNextChildOrder ];
			child->SetOrderHint( iNextChildOrder );
			hResult = child->GetHandle();
		}
	}
	return hResult;
}

const CRect OrgTreeDoc::GetNodeRect( const IOrgTreeDoc::node_handle_t hNode ) const {
	auto node = COrgCtrlDataItem::FromHandle( hNode );
	ASSERT( node != NULL );
	return node == NULL ? CRect() : node->GetRect();
}

BOOL OrgTreeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// OrgTreeDoc serialization

void OrgTreeDoc::Serialize(CArchive& ar)
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
void OrgTreeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void OrgTreeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void OrgTreeDoc::SetSearchContent(const CString& value)
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

// OrgTreeDoc diagnostics

#ifdef _DEBUG
void OrgTreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void OrgTreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

bool OrgTreeDoc::CreateContextNode( const CString & uniqueAggregateNodeId, const CString & productionRuleString, ULONG64 parentCxNodeObjId, ULONG64 cxNodeObjId, DWORD cxNodeThreadId ) {
	m_data->GetRoot().Clear();
	COrgCtrlDataItem::ptr_t pNode = std::make_shared< COrgCtrlDataItem >();
	pNode->GetRect() = { 0, 0, 20, 10 };
	m_data->GetRoot().AddChild( pNode );
	OrgTreeView * pView = NULL;
	POSITION pos = GetFirstViewPosition();
	if ( pos != NULL ) {
		pView = dynamic_cast < OrgTreeView * > ( GetNextView( pos ) );
		if ( pView != NULL ) {
			pView->Invalidate();
		}
	}
	return TRUE;
}

// OrgTreeDoc commands
