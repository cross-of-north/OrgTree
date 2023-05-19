// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlPainter.h"

#include "PropertyNames.h"

COrgCtrlPainter::COrgCtrlPainter( CDC & dc, const CRect & rcClient, const IOrgTreeDoc & document, const COrgCtrlView & view )
    : m_dc( dc )
    , m_rcClient( rcClient )
    , m_document( document )
    , m_view( view )
{
}       

void COrgCtrlPainter::SetupNodePainting( const bool bFocused ) {
    if ( bFocused ) {
        m_dc.SetDCPenColor( RGB( 0xC0, 0xC0, 0xC0 ) );
    } else {
        m_dc.SetDCPenColor( RGB( 0, 0, 0 ) );
    }
}

void COrgCtrlPainter::Paint( void ) {

    m_dc.SetDCBrushColor( RGB( 255, 255, 255 ) );
    m_dc.SetDCPenColor( RGB( 255, 255, 255 ) );
    m_dc.FillSolidRect( m_rcClient, RGB( 255, 255, 255 ) );

    SetupNodePainting( false );

    POrgTreeDocNodeHandle phRootNode;
    POrgTreeDocNodeHandle phFirstNode;
    if ( 
        m_document.GetRootNode( phRootNode ) &&
        m_document.GetNextChildNode( phRootNode, phFirstNode )
    ) {
        MeasureNode( phFirstNode );
        m_view.SetDataRect( m_rcDataBorders );
        int iCount = 0;
        PaintNode( phFirstNode, 0, 0, iCount );
    }
}

void COrgCtrlPainter::PaintNode( const POrgTreeDocNodeHandle & phNode, const int iDepth, const int iOrder, int & iCount ) {
    const CRect node_rect = m_view.ToViewRect( m_document.GetNodeRect( phNode ), iDepth, iOrder, iCount );
    iCount++;
    ASSERT( !node_rect.IsRectEmpty() );
    int iChildDepth = iDepth + 1;
    int iChildOrder = 0;

    POrgTreeDocNodeHandle phChildNode;
    while ( m_document.GetNextChildNode( phNode, phChildNode ) ) {
        const CRect child_rect = m_view.ToViewRect( m_document.GetNodeRect( phChildNode ), iChildDepth, iChildOrder, iCount );
        m_dc.MoveTo( node_rect.left + node_rect.Width() / 2, node_rect.top + node_rect.Height() / 2 );
        m_dc.LineTo( child_rect.left + child_rect.Width() / 2, child_rect.top + child_rect.Height() / 2 );
        PaintNode( phChildNode, iChildDepth, iChildOrder, iCount );
        iChildOrder++;
    }

    m_document.SetNodeScreenRect( phNode, node_rect );
    if ( m_document.GetNodeFocus( phNode ) ) {
        SetupNodePainting( true );
        for ( int i = 4; i > 0; i-- ) {
            CRect rect = node_rect;
            rect.TopLeft().x -= i;
            rect.TopLeft().y -= i;
            rect.BottomRight().x += i;
            rect.BottomRight().y += i;
            m_dc.Rectangle( rect );
        }
        SetupNodePainting( false );
        m_dc.Rectangle( node_rect );
    } else {
        m_dc.Rectangle( node_rect );
    }
    CString s;
    if ( m_document.GetNodeProperty( phNode, S_NAME, s ) ) {
        m_dc.TextOutW( node_rect.left + 1, node_rect.top + 1, s );
    }
}

void COrgCtrlPainter::MeasureNode( const POrgTreeDocNodeHandle & phNode ) {
    m_rcDataBorders.UnionRect( m_rcDataBorders, m_document.GetNodeRect( phNode ) );
    POrgTreeDocNodeHandle phChildNode;
    while ( m_document.GetNextChildNode( phNode, phChildNode ) ) {
        MeasureNode( phChildNode );
    }
}
