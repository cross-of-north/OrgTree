// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlPainter.h"

COrgCtrlPainter::COrgCtrlPainter( CDC & dc, const CRect & rcClient, const IOrgTreeDoc & data, const COrgCtrlView & view )
    : m_dc( dc )
    , m_rcClient( rcClient )
    , m_data( data )
    , m_view( view )
{
}       

void COrgCtrlPainter::Paint( void ) {
    m_dc.SetDCBrushColor( RGB( 255, 255, 255 ) );
    m_dc.SetDCPenColor( RGB( 255, 255, 255 ) );
    m_dc.FillSolidRect( m_rcClient, RGB( 255, 255, 255 ) );
    m_dc.SetDCPenColor( RGB( 0, 0, 0 ) );

    auto hNode = m_data.GetFirstChildNode( m_data.GetRootNode() );
    if ( m_data.IsValidNode( hNode ) ) {
        MeasureNode( hNode );
        m_view.SetDataRect( m_rcDataBorders );
        int iCount = 0;
        PaintNode( hNode, 0, 0, iCount );
    }
}

void COrgCtrlPainter::PaintNode( const IOrgTreeDoc::node_handle_t hNode, const int iDepth, const int iOrder, int & iCount ) {
    const CRect node_rect = m_view.ToViewRect( m_data.GetNodeRect( hNode ), iDepth, iOrder, iCount );
    iCount++;
    ASSERT( !node_rect.IsRectEmpty() );
    int iChildDepth = iDepth + 1;
    int iChildOrder = 0;
    
    auto hChildNode = m_data.GetFirstChildNode( hNode );
    while ( m_data.IsValidNode( hChildNode ) ) {
        const CRect child_rect = m_view.ToViewRect( m_data.GetNodeRect( hChildNode ), iChildDepth, iChildOrder, iCount );
        m_dc.MoveTo( node_rect.left + node_rect.Width() / 2, node_rect.top + node_rect.Height() / 2 );
        m_dc.LineTo( child_rect.left + child_rect.Width() / 2, child_rect.top + child_rect.Height() / 2 );
        PaintNode( hChildNode, iChildDepth, iChildOrder, iCount );
        iChildOrder++;
        hChildNode = m_data.GetNextChildNode( hNode, hChildNode );
    }

    m_dc.Rectangle( node_rect );
}

void COrgCtrlPainter::MeasureNode( const IOrgTreeDoc::node_handle_t hNode ) {
    m_rcDataBorders.UnionRect( m_rcDataBorders, m_data.GetNodeRect( hNode ) );
    auto hChildNode = m_data.GetFirstChildNode( hNode );
    while ( m_data.IsValidNode( hChildNode ) ) {
        MeasureNode( hChildNode );
        hChildNode = m_data.GetNextChildNode( hNode, hChildNode );
    }
}
