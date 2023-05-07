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

// until layout is implemented, we use fixed parameters
#define NODE_WIDTH 40
#define NODE_HEIGHT 20
#define NODE_HSPACE 40
#define NODE_VSPACE 40

void OrgTreeDoc::FillByTestData() {
	#define STARTX 50
	#define STARTY 50
	int left = STARTX;
	int top = STARTY;
	#define NODE_RECT { left, top, left + NODE_WIDTH, top + NODE_HEIGHT }
	
	COrgCtrlDataItem::ptr_t pRoot = std::make_shared< COrgCtrlDataItem >();
	pRoot->GetRect() = NODE_RECT;

	left += NODE_WIDTH + NODE_HSPACE;
	top = 10;

	COrgCtrlDataItem::ptr_t node1 = std::make_shared< COrgCtrlDataItem >();
	node1->GetRect() = NODE_RECT;
	top += NODE_HEIGHT + NODE_VSPACE;

	COrgCtrlDataItem::ptr_t node2 = std::make_shared< COrgCtrlDataItem >();
	node2->GetRect() = NODE_RECT;
	top += NODE_HEIGHT + NODE_VSPACE;

	COrgCtrlDataItem::ptr_t node3 = std::make_shared< COrgCtrlDataItem >();
	node3->GetRect() = NODE_RECT;
	top += NODE_HEIGHT + NODE_VSPACE;

	left += NODE_WIDTH + NODE_HSPACE;
	top = top/2;

	COrgCtrlDataItem::ptr_t node4 = std::make_shared< COrgCtrlDataItem >();
	node4->GetRect() = NODE_RECT;
	top += NODE_HEIGHT + NODE_VSPACE;

	COrgCtrlDataItem::ptr_t node5 = std::make_shared< COrgCtrlDataItem >();
	node5->GetRect() = NODE_RECT;
	top += NODE_HEIGHT + NODE_VSPACE;

	pRoot->AddChild( node1 );
	pRoot->AddChild( node2 );
	node2->AddChild( node4 );
	node2->AddChild( node5 );
	pRoot->AddChild( node3 );

	m_data->GetRoot().Clear();
	m_data->GetRoot().AddChild( pRoot );
}


void OrgTreeDoc::GetNodeHandle( COrgCtrlDataItem * node, POrgTreeDocNodeHandle & phNode ) const {
	phNode = std::make_shared< OrgTreeDocNodeHandle >( node );
}

bool OrgTreeDoc::FromNodeHandle( const POrgTreeDocNodeHandle & phNode, COrgCtrlDataItem * & node ) {
	node = NULL;
	if ( phNode ) {
		const OrgTreeDocNodeHandle & hNode = static_cast < const OrgTreeDocNodeHandle & > ( *phNode );
		if ( hNode.IsValid() ) {
			node = hNode.m_node;
		}
	}
	return node != NULL;
}

bool OrgTreeDoc::GetRootNode( POrgTreeDocNodeHandle & phNode ) const {
	GetNodeHandle( &m_data->GetRoot(), phNode );
	return true;
}

bool OrgTreeDoc::GetNextChildNode( const POrgTreeDocNodeHandle & phParent, POrgTreeDocNodeHandle & phChild ) const {

	POrgTreeDocNodeHandle phNextChild;

	COrgCtrlDataItem * parent = NULL;
	if ( FromNodeHandle( phParent, parent ) ) {
		auto children = parent->GetChildren();
		int iNextChildOrder = COrgCtrlDataItem::INVALID_ORDER_HINT;
		COrgCtrlDataItem * currentChild = NULL;
		if ( FromNodeHandle( phChild, currentChild ) ) {
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
		} else {
			iNextChildOrder = 0;
		}
		if ( iNextChildOrder != COrgCtrlDataItem::INVALID_ORDER_HINT && children.size() > iNextChildOrder ) {
			auto child = children[ iNextChildOrder ];
			child->SetOrderHint( iNextChildOrder );
			GetNodeHandle( child.get(), phNextChild );
		}
	}
	
	phChild = phNextChild;

	return phChild && ( static_cast < OrgTreeDocNodeHandle & > ( *phChild ) ).IsValid();
}

bool OrgTreeDoc::GetLastChildNode( const POrgTreeDocNodeHandle & phParent, POrgTreeDocNodeHandle & phLastChild ) const {

	phLastChild = NULL;

	COrgCtrlDataItem * parent = NULL;
	if ( FromNodeHandle( phParent, parent ) ) {
		auto children = parent->GetChildren();
		if ( children.size() > 0 ) {
			auto child = children[ children.size() - 1 ];
			child->SetOrderHint( int( children.size() - 1 ) );
			GetNodeHandle( child.get(), phLastChild );
		}
	}

	return phLastChild && ( static_cast < OrgTreeDocNodeHandle & > ( *phLastChild ) ).IsValid();
}

bool OrgTreeDoc::GetParentNode( const POrgTreeDocNodeHandle & phNode, POrgTreeDocNodeHandle & phParent ) const {
	phParent = NULL;
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		COrgCtrlDataItem * parent = node->GetParent();
		if ( parent != NULL ) {
			GetNodeHandle( parent, phParent );
		}
	}
	return phParent && ( static_cast < OrgTreeDocNodeHandle & > ( *phParent ) ).IsValid();
}

const CRect OrgTreeDoc::GetNodeRect( const POrgTreeDocNodeHandle & phNode ) const {
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	return node == NULL ? CRect() : node->GetRect();
}

void OrgTreeDoc::DeleteNode( POrgTreeDocNodeHandle & phNode ) {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		phNode.reset();
		node->Delete();
	}
	ASSERT( node != NULL );
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

OrgTreeView * OrgTreeDoc::GetView() const {
	OrgTreeView * pView = NULL;
	POSITION pos = GetFirstViewPosition();
	if ( pos != NULL ) {
		pView = dynamic_cast < OrgTreeView * > ( GetNextView( pos ) );
	}
	return pView;
}

bool OrgTreeDoc::CreateContextNode( const CString & uniqueAggregateNodeId, const CString & productionRuleString, ULONG64 parentCxNodeObjId, ULONG64 cxNodeObjId, DWORD cxNodeThreadId ) {
	m_data->GetRoot().Clear();
	COrgCtrlDataItem::ptr_t pNode = std::make_shared< COrgCtrlDataItem >();
	int left = STARTX;
	int top = STARTY;
	pNode->GetRect() = NODE_RECT;
	m_data->GetRoot().AddChild( pNode );
	if ( OrgTreeView * pView = GetView() ) {
		pView->Invalidate();
	}
	return TRUE;
}

void OrgTreeDoc::CreateDescendantNode( const POrgTreeDocNodeHandle & parent_ ) {
	POrgTreeDocNodeHandle parent = parent_;
	if ( !parent ) {
		GetFocusedNode( parent );
	}
	if ( parent ) {
		const CRect & parentRect = GetNodeRect( parent );
		int left = parentRect.right + NODE_HSPACE;
		int top = parentRect.top;
		POrgTreeDocNodeHandle prev_sibling;
		if ( GetLastChildNode( parent, prev_sibling ) ) {
			const CRect & prevSiblingRect = GetNodeRect( prev_sibling );
			top = prevSiblingRect.bottom + NODE_VSPACE;
		}
        COrgCtrlDataItem::ptr_t pNode = std::make_shared< COrgCtrlDataItem >();
		CRect rect = {
			left,
			top,
			left + NODE_WIDTH,
			top + NODE_HEIGHT
		};
        pNode->GetRect() = rect;
		COrgCtrlDataItem * pParentImpl = NULL;
		if ( FromNodeHandle( parent, pParentImpl ) ) {
			pParentImpl->AddChild( pNode );
		}
		if ( OrgTreeView * pView = GetView() ) {
			pView->Invalidate();
		}
	}
}

void OrgTreeDoc::CreateSiblingNode( void ) {
	POrgTreeDocNodeHandle sibling;
	if ( GetFocusedNode( sibling ) ) {
		POrgTreeDocNodeHandle parent;
		POrgTreeDocNodeHandle parent_of_parent;
		if (
			GetParentNode( sibling, parent ) &&
			GetParentNode( parent, parent_of_parent ) // shouldn't create second root node
		) {
            CreateDescendantNode( parent );
        }
	}
}

void OrgTreeDoc::DeleteNode() {
	POrgTreeDocNodeHandle node;
	if ( GetFocusedNode( node ) ) {
		DeleteNode( node );
		if ( OrgTreeView * pView = GetView() ) {
			pView->Invalidate();
		}
	}
}

const CRect OrgTreeDoc::GetNodeScreenRect( const POrgTreeDocNodeHandle & phNode ) const {
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	return node == NULL ? CRect() : node->GetScreenRect();
}

void OrgTreeDoc::SetNodeScreenRect( const POrgTreeDocNodeHandle & phNode, const CRect & rect ) const {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
        node->GetScreenRect() = rect;
    }
	ASSERT( node != NULL );
}

void OrgTreeDoc::SetNodeFocus( const POrgTreeDocNodeHandle & phNode, const bool bFocus ) const {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		node->SetFocus( bFocus );
	}
	ASSERT( node != NULL );
}

bool OrgTreeDoc::GetNodeFocus( const POrgTreeDocNodeHandle & phNode ) const {
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	return node == NULL ? CRect() : node->GetFocus();
}

// OrgTreeDoc commands
