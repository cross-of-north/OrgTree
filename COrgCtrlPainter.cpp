// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlPainter.h"

COrgCtrlPainter::COrgCtrlPainter( CDC & dc, const CRect & rcClient, const COrgCtrlData & data, const COrgCtrlView & view )
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

    auto it = m_data.GetRoot().GetChildren().begin();
    if ( it != m_data.GetRoot().GetChildren().end() ) {
        MeasureNode( *it );
        m_view.SetDataRect( m_rcDataBorders );
        int iCount = 0;
        PaintNode( *it, 0, 0, iCount );
    }
}

void COrgCtrlPainter::PaintNode( const COrgCtrlDataItem::ptr_t & node, const int iDepth, const int iOrder, int & iCount ) {
    const CRect node_rect = m_view.ToViewRect( node->GetRect(), iDepth, iOrder, iCount );
    iCount++;
    ASSERT( !node_rect.IsRectEmpty() );
    int iChildDepth = iDepth + 1;
    int iChildOrder = 0;
    for ( const auto & child : node->GetChildren() ) {
        const CRect child_rect = m_view.ToViewRect( child->GetRect(), iChildDepth, iChildOrder, iCount );
        m_dc.MoveTo( node_rect.left + node_rect.Width() / 2, node_rect.top + node_rect.Height() / 2 );
        m_dc.LineTo( child_rect.left + child_rect.Width() / 2, child_rect.top + child_rect.Height() / 2 );
        PaintNode( child, iChildDepth, iChildOrder, iCount );
        iChildOrder++;
    }
    m_dc.Rectangle( node_rect );
}

void COrgCtrlPainter::MeasureNode( const COrgCtrlDataItem::ptr_t & node ) {
    m_rcDataBorders.UnionRect( m_rcDataBorders, node->GetRect() );
    for ( const auto & child : node->GetChildren() ) {
        MeasureNode( child );
    }
}
