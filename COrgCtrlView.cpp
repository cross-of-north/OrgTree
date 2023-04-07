// COrgCtrl.cpp : implementation file
//

#include "pch.h"
#include "COrgCtrlView.h"

CRect COrgCtrlView::ToViewRect( const CRect & rcRect ) const {
    CRect rcViewRect;
    rcViewRect.left = m_rcScreenRect.left + LONG( float( rcRect.left ) * m_fZoomRatio );
    rcViewRect.top = m_rcScreenRect.top + LONG( float( rcRect.top ) * m_fZoomRatio );
    rcViewRect.right = m_rcScreenRect.left + LONG( float( rcRect.right ) * m_fZoomRatio );
    rcViewRect.bottom = m_rcScreenRect.top + LONG( float( rcRect.bottom ) * m_fZoomRatio );
    return rcViewRect;
}


void COrgCtrlView::SetZoomRatio( float fZoomRatio, const CPoint & ptCenter ) {

    // Zooming around the specified point (mouse cursor)
    CPoint ptCornerDistance = ptCenter - m_rcScreenRect.TopLeft();
    CPoint ptNewCornerDistance = ptCornerDistance;
    float fRateChange = fZoomRatio / m_fZoomRatio;
    ptNewCornerDistance.x = LONG( float( ptNewCornerDistance.x ) * fRateChange );
    ptNewCornerDistance.y = LONG( float( ptNewCornerDistance.y ) * fRateChange );
    CPoint ptOffset = ptCornerDistance - ptNewCornerDistance;
    m_rcScreenRect.OffsetRect( ptOffset );

    m_fZoomRatio = fZoomRatio;
}

void COrgCtrlView::Offset( const CPoint & offset ) {
    m_rcScreenRect.OffsetRect( offset );
}

void COrgCtrlView::SetSize( int cx, int cy ) {
    m_rcScreenRect.right = m_rcScreenRect.left + cx;
    m_rcScreenRect.bottom = m_rcScreenRect.top + cy;
}

