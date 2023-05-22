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
#include "PropertyNames.h"

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
#define NODE_WIDTH 60
#define SUBNODE_WIDTH 20
#define NODE_HEIGHT 30
#define SUBNODE_HEIGHT 10
#define NODE_HSPACE 40
#define NODE_VSPACE 5
#define SUBNODE_HSPACE 5
#define SUBNODE_VSPACE 5
#define NODE_HSPAN ( NODE_WIDTH + NODE_HSPACE )
#define NODE_VSPAN ( NODE_HEIGHT + NODE_VSPACE )

#define STARTX 50
#define STARTY 50
#define NODE_RECT { left, top, left + NODE_WIDTH, top + NODE_HEIGHT }
#define SUBNODE_RECT { left + subnode_left, top + subnode_top + NODE_HEIGHT + SUBNODE_VSPACE, left + subnode_left + SUBNODE_WIDTH, top + subnode_top + NODE_HEIGHT + SUBNODE_VSPACE + SUBNODE_HEIGHT }
class CTreeExampleBuilder {
public:
	int left{ STARTX };
	int top{ STARTY + 7 * NODE_VSPAN };
	int subnode_left{ 0 };
	int subnode_top{ 0 };
	OrgTreeDoc & doc;
	
	CTreeExampleBuilder( OrgTreeDoc & doc_ ) : doc( doc_ ) {}
	
	COrgCtrlDataItem::ptr_t CreateNode(
		const wchar_t * name,
		const wchar_t * type,
		const COrgCtrlDataItem::ptr_t & parent = NULL
	) {
		ASSERT( type == S_HUSBAND || type == S_WIFE || type == S_MYFAMILY );

		COrgCtrlDataItem * pParentsNode = NULL;

		if ( parent ) {
			POrgTreeDocNodeHandle phParent;
			doc.GetNodeHandle( parent.get(), phParent );
			COrgTreeDocNodeHandleList children;
			doc.GetChildrenByProperty( phParent, S_TYPE, S_PARENTS, children );
			ASSERT( children.size() == 1 );
			if ( children.size() > 0 ) {
				doc.FromNodeHandle( children[ 0 ], pParentsNode );
			}
		}

		const wchar_t * parent_type( type == S_MYFAMILY ? S_MYFAMILY : (
			type == S_HUSBAND ? S_PATERNAL : S_MATERNAL
		) );
		subnode_left = 0;
		COrgCtrlDataItem::ptr_t pPaternalMaternalNode = CreateSubNode( parent_type, pParentsNode );
		subnode_top += SUBNODE_VSPACE + SUBNODE_HEIGHT;
		//subnode_left += SUBNODE_HSPACE + SUBNODE_WIDTH;
		COrgCtrlDataItem::ptr_t pHusbandNode = CreateSubNode( S_HUSBAND, pPaternalMaternalNode.get() );
		subnode_left += SUBNODE_HSPACE + SUBNODE_WIDTH;
		COrgCtrlDataItem::ptr_t pWifeNode = CreateSubNode( S_WIFE, pPaternalMaternalNode.get() );
		subnode_left += SUBNODE_HSPACE + SUBNODE_WIDTH;
		CreateSubNode( S_CHILDREN, pPaternalMaternalNode.get() );
		subnode_left += SUBNODE_HSPACE + SUBNODE_WIDTH;
		CreateSubNode( S_PARENTS, pPaternalMaternalNode.get() );

		COrgCtrlDataItem::ptr_t pNamedNode = 
			( type == S_MYFAMILY ) ? 
			pPaternalMaternalNode : 
			( type == S_HUSBAND ? pHusbandNode : pWifeNode );

		doc.SetNodeRect( *pNamedNode, NODE_RECT );
		doc.SetNodeProperty( *pNamedNode, S_NAME, name );
		POrgTreeDocNodeHandle phNamedNode;
		doc.GetNodeHandle( pNamedNode.get(), phNamedNode );
		doc.SetNodeVisible( phNamedNode, true );

		return pPaternalMaternalNode;
	}

	COrgCtrlDataItem::ptr_t CreateSubNode(
		const wchar_t * type,
		COrgCtrlDataItem * parent
	) {
		COrgCtrlDataItem::ptr_t pNode = std::make_shared< COrgCtrlDataItem >();
		doc.SetNodeRect( *pNode, SUBNODE_RECT );
		doc.SetNodeProperty( *pNode, S_TYPE, type );
		if ( parent ) {
			parent->AddChild( pNode );
		}
		return pNode;
	}

	COrgCtrlDataItem::ptr_t Build() {

		COrgCtrlDataItem::ptr_t pRoot = CreateNode( L"Robert George", S_MYFAMILY );

		left += NODE_HSPAN;
		top -= NODE_VSPAN * 4;

		COrgCtrlDataItem::ptr_t node1 = CreateNode( L"Fred", S_HUSBAND, pRoot );

		top += NODE_VSPAN * 8;

		COrgCtrlDataItem::ptr_t node2 = CreateNode( L"Johanna", S_WIFE, pRoot );

		left += NODE_HSPAN;
		top -= NODE_VSPAN * 10;

		COrgCtrlDataItem::ptr_t node11 = CreateNode( L"Urs", S_HUSBAND, node1 );

		top += NODE_VSPAN * 4;

		COrgCtrlDataItem::ptr_t node12 = CreateNode( L"Elizabeth", S_WIFE, node1 );

		top += NODE_VSPAN * 4;

		COrgCtrlDataItem::ptr_t node21 = CreateNode( L"Charles", S_HUSBAND, node2 );

		top += NODE_VSPAN * 4;

		COrgCtrlDataItem::ptr_t node22 = CreateNode( L"Wilhemena", S_WIFE, node2 );

		left += NODE_HSPAN;
		top -= NODE_VSPAN * 13;

		COrgCtrlDataItem::ptr_t node111 = CreateNode( L"E", S_HUSBAND, node11 );

		top += NODE_VSPAN * 2;

		COrgCtrlDataItem::ptr_t node112 = CreateNode( L"M", S_WIFE, node11 );

		top += NODE_VSPAN * 2;

		COrgCtrlDataItem::ptr_t node121 = CreateNode( L"H", S_HUSBAND, node12 );

		top += NODE_VSPAN * 2;

		COrgCtrlDataItem::ptr_t node122 = CreateNode( L"M", S_WIFE, node12 );

		top += NODE_VSPAN * 2;

		COrgCtrlDataItem::ptr_t node211 = CreateNode( L"?", S_HUSBAND, node21 );

		return pRoot;
	}
};

void OrgTreeDoc::FillByTestData() {
	m_data->GetRoot().Clear();
	m_data->GetRoot().AddChild( CTreeExampleBuilder( *this ).Build() );
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
		int iNextChildOrder = INVALID_ORDER_HINT;
		COrgCtrlDataItem * currentChild = NULL;
		if ( FromNodeHandle( phChild, currentChild ) ) {
			int iCurrentChildOrder = GetOrderHint( *currentChild );
			if ( iCurrentChildOrder == INVALID_ORDER_HINT ) {
				for ( int i = 0; i < children.size(); i++ ) {
					if ( children[ i ].get() == currentChild ) {
						iCurrentChildOrder = i;
						break;
					}
				}
			}
			if ( iCurrentChildOrder != INVALID_ORDER_HINT ) {
				iNextChildOrder = iCurrentChildOrder + 1;
			}
		} else {
			iNextChildOrder = 0;
		}
		if ( iNextChildOrder != INVALID_ORDER_HINT && children.size() > iNextChildOrder ) {
			auto child = children[ iNextChildOrder ];
			SetOrderHint( *child, iNextChildOrder );
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
			SetOrderHint( *child, int( children.size() - 1 ) );
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
	SetNodeRect( *pNode, NODE_RECT );
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
		POrgTreeDocNodeHandle overlapped;
		bool bScreenCoords = false;
		while ( HitTest( rect, overlapped, bScreenCoords ) ) {
			rect.OffsetRect( NODE_WIDTH + NODE_HSPACE, 0 );
		}
		SetNodeRect( *pNode, rect );
		COrgCtrlDataItem * pParentImpl = NULL;
		if ( FromNodeHandle( parent, pParentImpl ) ) {
			pParentImpl->AddChild( pNode );
			ResetOrderHints( *pParentImpl );
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

#define SCREEN_RECT_TOP L"__screen_rect.top"
#define SCREEN_RECT_LEFT L"__screen_rect.left"
#define SCREEN_RECT_BOTTOM L"__screen_rect.bottom"
#define SCREEN_RECT_RIGHT L"__screen_rect.right"
#define RECT_TOP L"__rect.top"
#define RECT_LEFT L"__rect.left"
#define RECT_BOTTOM L"__rect.bottom"
#define RECT_RIGHT L"__rect.right"
#define FOCUS L"__focus"
#define VISIBLE L"__visible"
#define ORDER_HINT L"__order_hint"

const CRect OrgTreeDoc::GetNodeScreenRect( const POrgTreeDocNodeHandle & phNode ) const {
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	CRect rect;
	if ( node != NULL ) {
		__int64 top{ 0 };
		node->GetInt( SCREEN_RECT_TOP, top );
		rect.top = LODWORD( top );
		__int64 left{ 0 };
		node->GetInt( SCREEN_RECT_LEFT, left );
		rect.left = LODWORD( left );
		__int64 bottom{ 0 };
		node->GetInt( SCREEN_RECT_BOTTOM, bottom );
		rect.bottom = LODWORD( bottom );
		__int64 right{ 0 };
		node->GetInt( SCREEN_RECT_RIGHT, right );
		rect.right = LODWORD( right );
    }
	return rect;
}

void OrgTreeDoc::SetNodeScreenRect( const POrgTreeDocNodeHandle & phNode, const CRect & rect ) const {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		node->SetInt( SCREEN_RECT_TOP, rect.top );
		node->SetInt( SCREEN_RECT_LEFT, rect.left );
		node->SetInt( SCREEN_RECT_BOTTOM, rect.bottom );
		node->SetInt( SCREEN_RECT_RIGHT, rect.right );
    }
	ASSERT( node != NULL );
}

const CRect OrgTreeDoc::GetNodeRect( const POrgTreeDocNodeHandle & phNode ) const {
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	CRect rect;
	if ( node != NULL ) {
		__int64 top{ 0 };
		node->GetInt( RECT_TOP, top );
		rect.top = LODWORD( top );
		__int64 left{ 0 };
		node->GetInt( RECT_LEFT, left );
		rect.left = LODWORD( left );
		__int64 bottom{ 0 };
		node->GetInt( RECT_BOTTOM, bottom );
		rect.bottom = LODWORD( bottom );
		__int64 right{ 0 };
		node->GetInt( RECT_RIGHT, right );
		rect.right = LODWORD( right );
	}
	return rect;
}

void OrgTreeDoc::SetNodeRect( COrgCtrlDataItem & node, const CRect & rect ) {
	node.SetInt( RECT_TOP, rect.top );
	node.SetInt( RECT_LEFT, rect.left );
	node.SetInt( RECT_BOTTOM, rect.bottom );
	node.SetInt( RECT_RIGHT, rect.right );
}

void OrgTreeDoc::SetNodeRect( POrgTreeDocNodeHandle & phNode, const CRect & rect ) {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		SetNodeRect( *node, rect );
	}
	ASSERT( node != NULL );
}

void OrgTreeDoc::SetNodeFlag( const POrgTreeDocNodeHandle & phNode, const bool bValue, const wchar_t * name ) const {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		node->SetInt( name, bValue ? 1 : 0 );
	}
	ASSERT( node != NULL );
}

bool OrgTreeDoc::GetNodeFlag( const POrgTreeDocNodeHandle & phNode, const wchar_t * name ) const {
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	bool bResult = false;
	if ( node != NULL ) {
		__int64 result{ 0 };
		node->GetInt( name, result );
		bResult = ( result != 0 );
	}
	return bResult;
}

void OrgTreeDoc::SetNodeFocus( const POrgTreeDocNodeHandle & phNode, const bool bFocus ) const {
	SetNodeFlag( phNode, bFocus, FOCUS );
}

bool OrgTreeDoc::GetNodeFocus( const POrgTreeDocNodeHandle & phNode ) const {
	return GetNodeFlag( phNode, FOCUS );
}

bool OrgTreeDoc::IsNodeVisible( const POrgTreeDocNodeHandle & phNode ) const {
	return GetNodeFlag( phNode, VISIBLE );
}

void OrgTreeDoc::SetNodeVisible( const POrgTreeDocNodeHandle & phNode, const bool bVisible ) const {
	SetNodeFlag( phNode, bVisible, VISIBLE );
}

void OrgTreeDoc::SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const CString & strValue ) {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		std::wstring s( strValue );
		node->SetString( strName, s );
	}
	ASSERT( node != NULL );
}

bool OrgTreeDoc::GetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, CString & strValue ) const {
	strValue.Empty();
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	bool bResult = false;
	if ( node != NULL ) {
		std::wstring s;
		bResult = node->GetString( strName, s );
		if ( bResult ) {
			strValue = s.c_str();
		}
	}
	return bResult;
}

void OrgTreeDoc::SetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, const __int64 iValue ) {
	COrgCtrlDataItem * node = NULL;
	if ( FromNodeHandle( phNode, node ) ) {
		node->SetInt( strName, iValue );
	}
	ASSERT( node != NULL );
}

bool OrgTreeDoc::GetNodeProperty( const POrgTreeDocNodeHandle & phNode, const wchar_t * strName, __int64 & iValue ) const {
	iValue = 0;
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	bool bResult = false;
	if ( node != NULL ) {
		bResult = node->GetInt( strName, iValue );
	}
	return bResult;
}

void OrgTreeDoc::GetNodeProperties( const POrgTreeDocNodeHandle & phNode, CMapStringToString & properties ) const {
	properties.RemoveAll();
	COrgCtrlDataItem * node = NULL;
	FromNodeHandle( phNode, node );
	ASSERT( node != NULL );
	auto nodeProperties = node->GetProperties();
	for ( auto it = nodeProperties.begin(); it != nodeProperties.end(); it++ ) {
        properties.SetAt( it->first.c_str(), it->second.c_str() );
    }
}

int OrgTreeDoc::GetOrderHint( const COrgCtrlDataItem & node ) const {
	__int64 result{ 0 };
	if ( !node.GetInt( ORDER_HINT, result ) ) {
		result = INVALID_ORDER_HINT;
	}		
	return LODWORD( result );
}

void OrgTreeDoc::SetOrderHint( COrgCtrlDataItem & node, int orderHint ) const {
	node.SetInt( ORDER_HINT, orderHint );
}

void OrgTreeDoc::ResetOrderHints( COrgCtrlDataItem & node ) {
	auto children = node.GetChildren();
	for ( int i = 0; i < children.size(); i++ ) {
		SetOrderHint( *children[ i ], INVALID_ORDER_HINT );
	}
}

void OrgTreeDoc::SetNodeProperty( COrgCtrlDataItem & node, const wchar_t * strName, const CString & strValue ) {
	node.SetString( strName, strValue.GetString() );
}

// OrgTreeDoc commands
